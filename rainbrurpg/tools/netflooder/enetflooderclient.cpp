/*
 *  Copyright 2006-2007 Jerome PASQUIER
 * 
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "enetflooderclient.h"

#include <logger.h>
#include <npconnectionresponse.h>

/** The default constructor
  *
  */
RainbruRPG::Network::EnetFlooderClient::EnetFlooderClient(){

}

/** The destructor
  *
  */
RainbruRPG::Network::EnetFlooderClient::~EnetFlooderClient(){

}

/** Waiting for network event for 1000 miliseconds
  *
  */
void RainbruRPG::Network::EnetFlooderClient::eventLoop(){
  NetPacketBase npb;

  while (enet_host_service (client, & event, 700) > 0){

    switch (event.type){
    case ENET_EVENT_TYPE_CONNECT:
      break;
      
    case ENET_EVENT_TYPE_RECEIVE:
      cout << "A packet of length " <<event.packet -> dataLength
	   <<" containing " <<event.packet -> data
	   <<" was received from "<<event.peer -> data
	   <<" on channel "<<event.channelID<< endl;

      npb.setData(event.packet -> data, event.packet -> dataLength);
      npb.netDeserialize();
      treatPacket(&npb, &event);

      /* Clean up the packet now that we're done using it. */
      enet_packet_destroy (event.packet);
      
      break;
      
    case ENET_EVENT_TYPE_DISCONNECT:
      cout << event.peer -> data << " disconected" << endl;
      
      /* Reset the peer's client information. */
      event.peer -> data = NULL;

    case ENET_EVENT_TYPE_NONE:
      break;
    }
  }

}

/** Treat a single received network packet
  *
  * The NetPacketBase may be netDeserialized before a call to this function
  *
  * The ENetEvent pointer shound not be NULL cause it is used to 
  * netDeserialize the correct packet subclass when its type is known.
  *
  * \param p The packet in its base form
  * \param e The ENetEvent coming from eventLoop()
  *
  */
void RainbruRPG::Network::EnetFlooderClient::
treatPacket(NetPacketBase* p, ENetEvent* e ){

  tNetPacketIdentifier i=p->getIdentifier();

  if (i==NPI_SVR_CONRESP){
    LOGI("A connection response was received");
    npConnectionResponse ncr;
    ncr.setData(e->packet -> data, e->packet -> dataLength);
    ncr.netDeserialize();
    tServerConnectionResponse res=ncr.getResponse();

    switch(res){
    case NCR_UNDEFINED:
      LOGW("The server response is undefined");
      sigConnectionUndefined.emit();
      break;
    case NCR_ACCEPTED:
      LOGI("The selected server accepts flooder connection");
      sigConnectionAccepted.emit();
      break;
    case NCR_REFUSED:
      LOGI("The selected server refuses flooder connection");
      sigConnectionRefused.emit();
      break;

    }
  }

}

/** Send a packet and wait the response
  *
  * This function send the given packet over the network and wait for
  * the response. When the response is given, we return the time elapsed
  * in miliseconds.
  *
  * \param p The packet to send
  * \param reliable Is this packet sent in reliable mode ?
  *
  * \return The time elapsed between the packet was sent and the response
  *         was received in miliseconds
  *
  */
int RainbruRPG::Network::EnetFlooderClient::
sendPacketAndWaitResponse(NetPacketFlooderBase* p, bool reliable){
  // To be sure the packet is (or not) reliable
  p->setReliable(reliable);
}

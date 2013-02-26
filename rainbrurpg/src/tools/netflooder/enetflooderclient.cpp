/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file tools/netflooder/enetflooderclient.cpp
  * Implements the enet client used by NetFlooder
  *
  */

#include "enetflooderclient.h"

#include <Logger.hpp>
#include <NpConnectionResponse.hpp>
#include <NpFlooder0004.hpp>

/** The default constructor
  *
  */
RainbruRPG::Network::EnetFlooderClient::EnetFlooderClient()
  :EnetClient()

{

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

/** Wait a packet of a type with a given response
  *
  * \param packetId The packet identifier we are waiting
  * \param responseId The response we are waiting
  *
  * \return true if received
  *
  */
bool RainbruRPG::Network::EnetFlooderClient::
waitPacket(tNetPacketIdentifier packetId, unsigned short responseId){

  NetPacketBase npb;
  npFlooder0004 npf4(0);
  tNetPacketIdentifier i1;

  while (enet_host_service (client, & event, 3000) > 0){

    switch (event.type){
    case ENET_EVENT_TYPE_CONNECT:
      break;
      
    case ENET_EVENT_TYPE_RECEIVE:
      npb.setData(event.packet -> data, event.packet -> dataLength);
      npb.netDeserialize();

      i1=npb.getIdentifier();
      // The packet type is good
      if (i1==packetId){

	if (i1==NPI_FLOOD_0004){

	  npf4.setData(event.packet -> data, event.packet -> dataLength);
	  npf4.netDeserialize();
	  if (responseId==npf4.getResponseId()){
	    return true;
	  }
	  else{
	    return false;
	  }

	}
	else{
	  return false;
	}

      }
      else{
	return false;
      }

      /* Clean up the packet now that we're done using it. */
      enet_packet_destroy (event.packet);
      break;
      
    case ENET_EVENT_TYPE_DISCONNECT:

      LOGW("Client disconnected");
      break;

    case ENET_EVENT_TYPE_NONE:
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
  LOGI("sendPacketAndWaitResponse called");

  // To be sure the packet is (or not) reliable
  p->setReliable(reliable);
  p->netSerialize();

  ENetPacket * packet;

  if (p->isReliable()){
    packet= enet_packet_create 
      (p->getData(), p->getDataLength(), ENET_PACKET_FLAG_RELIABLE);
  }
  else{
    packet = enet_packet_create 
      (p->getData(), p->getDataLength(), 0);

  }

  if (peer==NULL){
    LOGE("Enet peer not initialized, the program will probably crash");
  }

  if (packet==NULL){
    LOGE("Enet packet not initialized, the program will probably crash");
  }

  enet_peer_send (peer, 0, packet);
  enet_host_flush (client);
  //  bool ret=waitPacket(p->getIdentifier(), p->getResponseId());
  bool ret=waitPacket(p->getIdentifier(), p->getResponseId());

  if (ret){
    LOGI("The packet is comming back");
  }


}


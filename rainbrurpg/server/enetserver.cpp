/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

#include "enetserver.h"

#include <logger.h>

/** The default constructor
  *
  */
RainbruRPG::Network::EnetServer::EnetServer()
  :EnetBase(){

  address=new ENetAddress();
  address->host = ENET_HOST_ANY;
  address->port = 50000;

  maxClient=32;
  timeout=500;
}

/** The destructor
  *
  */
RainbruRPG::Network::EnetServer::~EnetServer(){
  delete address;

  address=NULL;
}

/** Set the host port
  *
  * \param i The new UDP port used
  *
  */
void RainbruRPG::Network::EnetServer::setPort(int i){
  address->port = i;
}


/** Set the maximum number of allowed clients
  *
  * \param i The new maxClient value
  *
  */
void RainbruRPG::Network::EnetServer::setMaxClient(int i){
  maxClient=i;
}


/** Creates and initialize the Enet host
  *
  */
void RainbruRPG::Network::EnetServer::createServer(){
  server = enet_host_create (address , maxClient, 0 ,0 );
  if (server == NULL)    {
    LOGE("Cannot create the Enet host");
  }
  else{
    LOGI("Server creation successfull");
  }
}

/** Deletes the Enet host
  *
  */
void RainbruRPG::Network::EnetServer::cleanupServer(){
  enet_host_destroy(server);

}

/** Waits enet event 
  *
  */
void RainbruRPG::Network::EnetServer::eventLoop(){
  while (enet_host_service (server, & event, timeout) > 0){

    switch (event.type){
    case ENET_EVENT_TYPE_CONNECT:
      cout << "A new client connected from "
	   << event.peer->address.host << ":"
	   << event.peer->address.port <<endl;
      
      /* Store any relevant client information here. */
      //      event.peer -> data = "Client information";

      emit(clientConnected(event.peer->address));
      
      break;
      
    case ENET_EVENT_TYPE_RECEIVE:
      cout << "A packet of length " <<event.packet -> dataLength
	   <<" containing " <<event.packet -> data
	   <<" was received from "<<event.peer -> data
	   <<" on channel "<<event.channelID<< endl;


      tReceivedPacket temp;
      temp.dataLength=event.packet->dataLength;

      temp.data=(enet_uint8*)calloc(1, temp.dataLength);
      memcpy ( temp.data, event.packet->data, temp.dataLength);
      
      temp.host=event.peer->address.host;
      temp.port=event.peer->address.port;
      temp.peer=event.peer;

      emit(packetReceived(temp));
      
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

/** Send the given network packet to a single peer
  *
  * \param peer The peer to send the packet to
  * \param p The packet to send
  *
  */
void RainbruRPG::Network::EnetServer::
sendPacket(ENetPeer* peer, NetPacketBase* p){

  LOGI("Sending a packet");

  p->netSerialize();
  ENetPacket * packet;

#ifndef ALWAYS_USE_RELIABLE
  if (p->isReliable()){
    packet = enet_packet_create 
      (p->getData(), p->getDataLength(), ENET_PACKET_FLAG_RELIABLE);
  }
  else{
    packet = enet_packet_create 
      (p->getData(), p->getDataLength(), 0);

  }
#else
    packet = enet_packet_create 
      (p->getData(), p->getDataLength(), ENET_PACKET_FLAG_RELIABLE);
#endif

  enet_peer_send (peer, 0, packet);
  enet_host_flush (server);
}

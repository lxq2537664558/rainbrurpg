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

/** \file enetclient.cpp
  * Implements the Enet client
  *
  */

#include "enetclient.h"

#include "logger.h"

/** The default constructor
 *
 */
RainbruRPG::Network::EnetClient::EnetClient(){
  init();
  peer=NULL;

  connected=false;

  /* create a client host */
  /* only allow 1 outgoing connection */
  /* 56K modem with 56 Kbps downstream bandwidth */
  /* 56K modem with 14 Kbps upstream bandwidth */
  client = enet_host_create (NULL , 1 , 57600 / 8 , 14400 / 8 );
  address=new ENetAddress();

}

/** The destructor
  *
  */
RainbruRPG::Network::EnetClient::~EnetClient(){
  /* Modified for cross-compilation
   *
   * The statement enet_peer_disconnect(peer, 0) failed with the following
   * error :enet.h:408: error: too many arguments to function 
   * `void enet_peer_disconnect(ENetPeer*)'.
   *
   * Removing the 0 seems to fix this.
   *
   */
  enet_peer_disconnect(peer, 0);
  enet_host_destroy(client);

  delete address;

  client=NULL;
  address=NULL;
  peer=NULL;

  deinit();
}

/** Try to connect this client to the given server
  *
  * \param hostName The host naùme or the ip adress to resolve
  * \param port The port of the server to contact
  * \param waitingTime The waitingTime in miliseconds
  *
  */
void RainbruRPG::Network::EnetClient::
connect(const char* hostName, enet_uint16 port, int waitingTime){

  if (!connected){
    // Sets the server adress
    enet_address_set_host (address, hostName);
    address->port = port;
    
    /* Initiate the connection, allocating the two channels 0 and 1. */
    peer = enet_host_connect (client, address, 2);    
    
    if (peer == NULL){
      LOGE("No available peers for initiating an ENet connection.");
    }
    
    /* Wait up to 5 seconds for the connection attempt to succeed.*/
    if (enet_host_service (client, & event, waitingTime) > 0 &&
	event.type == ENET_EVENT_TYPE_CONNECT){
      LOGI("Connection to server succeeded.");
      connected=true;
      
    }
    else{   
      /* Either the 5 seconds are up or a disconnect event was */
      /* received. Reset the peer in the event the 5 seconds   */
      /* had run out without any significant event.            */
      enet_peer_reset(peer);
      LOGE ("Connection to server failed.");
    }
  }
  else{
    LOGW("Trying to connect an already connected client");
  }
}

/** Is this client connected ?
  *
  * \return \c true or \c false
  *
  * \sa connected
  *
  */
bool RainbruRPG::Network::EnetClient::isConnected(){
  return connected;
}

/** Send the given packet over the netwotk
  *
  * \param p The packet to send
  *
  */
void RainbruRPG::Network::EnetClient::sendPacket(NetPacketBase* p){
  p->netSerialize();

  ENetPacket * packet;

#ifndef ALWAYS_USE_RELIABLE
  if (p->isReliable()){
    packet= enet_packet_create 
      (p->getData(), p->getDataLength(), ENET_PACKET_FLAG_RELIABLE);
  }
  else{
    packet = enet_packet_create 
      (p->getData(), p->getDataLength(), 0);

  }

#else
    packet= enet_packet_create 
      (p->getData(), p->getDataLength(), ENET_PACKET_FLAG_RELIABLE);
#endif

  enet_peer_send (peer, 0, packet);
  enet_host_flush (client);

}

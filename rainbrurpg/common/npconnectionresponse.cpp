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

/** \file npconnectionresponse.cpp
  * Implements the packet used by server to answer to a client's connection
  *
  */
#include "npconnectionresponse.h"

#include <logger.h>

/** The default constructor
  *
  */
RainbruRPG::Network::npConnectionResponse::npConnectionResponse()
  :NetPacketBase(NPI_SVR_CONRESP){

  data=new npConnectionResponseData();
  response=NCR_UNDEFINED;
}

/** A typed constructor
  *
  * \param t the new client type
  *
  */
RainbruRPG::Network::npConnectionResponse::npConnectionResponse(tServerConnectionResponse t)
  :NetPacketBase(NPI_SVR_CONRESP){

  data=new npConnectionResponseData();
  response=t;
}


/** The destructor
  *
  */
RainbruRPG::Network::npConnectionResponse::~npConnectionResponse(){
  delete data;
}

/** Prepare the packet to be sent over the network
  *
  * It initialize the data values with the local private fields.
  *
  */
void RainbruRPG::Network::npConnectionResponse::netSerialize(){
  if (response==NCR_UNDEFINED){
    LOGW("The server's response is not set");
  }
  data->packetIdentifier=GUINT16_TO_LE(this->id);

  data->response=GUINT16_TO_LE(this->response);
}

/** Get the values from a packet comming from the network
  *
  * It initialize the local private fields with the
  * data.
  *
  */
void RainbruRPG::Network::npConnectionResponse::netDeserialize(){
  // Note the explicit cast from integer to enum type ^^
  this->id=static_cast<RainbruRPG::Network::tNetPacketIdentifier>
    GUINT16_FROM_LE(data->packetIdentifier);

  this->response=static_cast<RainbruRPG::Network::tServerConnectionResponse>
    GUINT16_FROM_LE(data->response);
}

/** Get the data in the ENet form
  *
  * \return The data as needed by the ENet library
  *
  */
enet_uint8* RainbruRPG::Network::npConnectionResponse::getData(){
  return data->data;
}

/** Get the length of data
  *
  * \return The length of the data field in bytes
  *
  */
size_t RainbruRPG::Network::npConnectionResponse::getDataLength(){
  return sizeof(data->data);
}

/** Set the data from the ENetPacket
  *
  * \param d The ENet data of the packet
  * \param len The packet length in byte
  *
  */
void RainbruRPG::Network::npConnectionResponse::
setData(enet_uint8* d, size_t len){
  memcpy(data->data, d, len);
}

/** Change the response to send
  *
  * \param r The new response value
  *
  */
void RainbruRPG::Network::npConnectionResponse::
setResponse(tServerConnectionResponse r){
  this->response=r;
}

/** Get the response to send
  *
  * \return The new response value
  *
  */
RainbruRPG::Network::tServerConnectionResponse 
RainbruRPG::Network::npConnectionResponse::
getResponse(){

  return this->response;
}

/** Tell if the connection is accepted
  *
  * \param t The server connection response to treat
  *
  * \return \c true if the connection is accepted, \c false if it is
  *         refused
  *
  */
bool RainbruRPG::Network::npConnectionResponse::
responseToBool(tServerConnectionResponse t){
  bool ret=false;

  switch(t){
  case NCR_UNDEFINED:
    ret=false;
    break;

  case NCR_REFUSED:
    ret=false;
    break;

  case NCR_ACCEPTED:
    ret=true;
    break;
  }

  return ret;
}

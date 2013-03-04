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

/** \file npidentification.cpp
  * Implements the client identification packet
  *
  */

#include "NpIdentification.hpp"

#include "Logger.hpp"

/** The default constructor
  *
  */
RainbruRPG::Network::npIdentification::npIdentification()
  :NetPacketBase(NPI_GEN_IDENT){

  data=new npIdentificationData();
  clientType=NCT_UNKNOWN;
}

/** A typed constructor
  *
  * \param t the new client type
  *
  */
RainbruRPG::Network::npIdentification::npIdentification(tNetworkClientType t)
  :NetPacketBase(NPI_GEN_IDENT){

  data=new npIdentificationData();
  setClientType(t);
}


/** The destructor
  *
  */
RainbruRPG::Network::npIdentification::~npIdentification(){
  delete data;
}

/** Change the client's type
  *
  * \param t the new client type
  *
  */
void RainbruRPG::Network::npIdentification::
setClientType(tNetworkClientType t){
  clientType=t;
}

/** Prepare the packet to be sent over the network
  *
  * It initialize the data values with the local private fields.
  *
  */
void RainbruRPG::Network::npIdentification::netSerialize(){
  if (clientType==NCT_UNKNOWN){
    LOGW(_("The client type is not set"));
  }
  data->packetIdentifier=GUINT16_TO_LE(this->id);

  data->clientType=GUINT16_TO_LE(this->clientType);
}

/** Get the values from a packet comming from the network
  *
  * It initialize the local private fields with the
  * data.
  *
  */
void RainbruRPG::Network::npIdentification::netDeserialize(){
  // Note the explicit cast from integer to enum type ^^
  this->id=static_cast<RainbruRPG::Network::tNetPacketIdentifier>
    GUINT16_FROM_LE(data->packetIdentifier);

  this->clientType=static_cast<RainbruRPG::Network::tNetworkClientType>
    GUINT16_FROM_LE(data->clientType);
}

/** Get the data in the ENet form
  *
  * \return The data as needed by the ENet library
  *
  */
enet_uint8* RainbruRPG::Network::npIdentification::getData(){
  return data->data;
}

/** Get the length of data
  *
  * \return The length of the data field in bytes
  *
  */
size_t RainbruRPG::Network::npIdentification::getDataLength(){
  return sizeof(data->data);
}

/** Set the data from the ENetPacket
  *
  * \param d The ENet data of the packet
  * \param len The packet length in byte
  *
  */
void RainbruRPG::Network::npIdentification::
setData(enet_uint8* d, size_t len){
  memcpy(data->data, d, len);
}

/** Get the client type
  *
  * \return The type of client
  *
  */
RainbruRPG::Network::tNetworkClientType 
RainbruRPG::Network::npIdentification::
getClientType(){

  return this->clientType;
}

/** Get a string describing the client type
  *
  * \param t The type you want the description
  *
  * \return A string corresponding to the given client type
  *
  */
const char* RainbruRPG::Network::npIdentification::
clientTypeToString(RainbruRPG::Network::tNetworkClientType t){

  const char* ret;

  switch (t){
  case NCT_FLOODER:
    // TRANSLATORS: This is the name of a client type.
    ret=_("NetFlooder");
    break;

  case NCT_EDITOR:
    // TRANSLATORS: This is the name of a client type.
    ret=_("Editor");
    break;

  case NCT_GAME:  
    // TRANSLATORS: This is the name of a client type.
    ret=_("Game");
    break;

  case NCT_UNKNOWN:
    // TRANSLATORS: This is the unknown client type.
    ret=_("Unknown");
    break;

  default:
    // TRANSLATORS: This is the unknown client type.
    ret=_("Default");
    break;

  }

  return ret;

}

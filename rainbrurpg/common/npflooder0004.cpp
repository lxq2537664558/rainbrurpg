/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file npflooder0004.cpp
  * Implements a packet of 4 bytes used by the flooder
  *
  */

#include "npflooder0004.h"

/** The identified constructor
  *
  * It initialize the data pointer with the \c new operator.
  *
  * \param r The response identifier
  *
  */
RainbruRPG::Network::npFlooder0004::npFlooder0004(guint16 r)
  :NetPacketFlooderBase(NPI_FLOOD_0004, r)
{

  data=new npFlooder0004Data();

}

/** The destructor     
  *
  * It deallocates the data pointer with the delete operator.
  *
  */
RainbruRPG::Network::npFlooder0004::~npFlooder0004(){
  delete data;
}

/** Prepare the packet to be sent over the network
  *
  * It initialize the data values with the local private fields and
  * set up data to be sent over network.
  *
  */
void RainbruRPG::Network::npFlooder0004::netSerialize(){
  data->packetIdentifier=GUINT16_TO_LE(this->id);
  data->responseId=GUINT16_TO_LE(this->responseId);
}

/** Get the values from a packet comming from the network
  *
  * It initialize the local private fields with the
  * data to translate from network data to local structure.
  *
  */
void RainbruRPG::Network::npFlooder0004::netDeserialize(){
  // Note the explicit cast from integer to enum type ^^
  this->id=static_cast<RainbruRPG::Network::tNetPacketIdentifier>
    GUINT16_FROM_LE(data->packetIdentifier);

  this->responseId=GUINT16_FROM_LE(data->responseId);

}

/** Get the data in the ENet form
  *
  * \return The data as needed by the ENet library
  *
  */
enet_uint8* RainbruRPG::Network::npFlooder0004::getData(){
  return data->data;

}

/** Get the length of data
  *
  * \return The length of the data field in bytes
  *
  */
size_t RainbruRPG::Network::npFlooder0004::getDataLength(){
  return sizeof(data->data);

}

/** Set the data from the ENetPacket
  *
  * Using \c memcpy, this set the \c d content in the local data member.
  *
  * \param d The ENet data of the packet
  * \param len The packet length in byte
  *
  */
void RainbruRPG::Network::npFlooder0004::setData(enet_uint8* d, size_t len){
  memcpy(data->data, d, len);

}

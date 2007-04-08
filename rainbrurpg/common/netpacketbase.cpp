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

#include "netpacketbase.h"

#include "logger.h"

/** Default constructor
  *
  * It sets the current id to NPI_INVALID and the packet is by default
  * reliable.
  *
  */
RainbruRPG::Network::NetPacketBase::NetPacketBase(){
  this->id=NPI_INVALID;
  reliable=true;
  data=new npPacketBaseData();
}

/** The identified constructor
  *
  * The packet is by default reliable.
  *
  * \param i The identifier of the packet
  *
  */
RainbruRPG::Network::NetPacketBase::NetPacketBase(tNetPacketIdentifier i){
  this->id=i;
  reliable=true;
  data=new npPacketBaseData();
}


/** Destructor
  *
  */
RainbruRPG::Network::NetPacketBase::~NetPacketBase(){

  delete data;
  data=NULL;

}

/** Convert an int to the little-endian Byte Order
  *
  * If your CPU work in little-endian, it does nothing but if it is
  * big-endian, a conversion is needed.
  *
  */
int RainbruRPG::Network::NetPacketBase::convert(int i){
#if __BYTE_ORDER == __LITTLE_ENDIAN
  return i;
#elif __BYTE_ORDER == __BIG_ENDIAN
  return GINT_TO_LE(i);
#else
# error	"Please fix <bits/endian.h>"
#endif
}

/** Send the packet over the network
  *
  * 
  *
  */
void RainbruRPG::Network::NetPacketBase::send(){


}

/** Get the packet type
  *
  */
RainbruRPG::Network::tNetPacketIdentifier 
RainbruRPG::Network::NetPacketBase::getIdentifier(){
  return id;
}

/** Set the data from a ENetPacket data structure
  *
  * \param d The data pointer
  * \param len The length in bytes
  */
void RainbruRPG::Network::NetPacketBase::
setData(enet_uint8* d, size_t len){
  // Copy 2 bytes to get the packet identifier
  memcpy(&data->data, d, 2);
  id=static_cast<RainbruRPG::Network::tNetPacketIdentifier>
    GUINT16_FROM_LE(data->packetIdentifier);
}

/** Get a string from a packet identifier
  *
  * \param t The identifier you want a string from
  *
  * \return A string corresponding to the given packet identifier
  *
  */
const char* RainbruRPG::Network::NetPacketBase::
typeToString(tNetPacketIdentifier t){

  const char* ret;

  switch(t){
  case NPI_GEN_IDENT :
    ret="Identification";
    break;

  case NPI_SVR_CONRESP:
    ret="Server connection response";
    break;

  case NPI_INVALID:
    ret="Unset";
    break;

  default:
    ret="Error";
    break;
  }

  return ret;
}

/** Set the reliable attribute of the packet
  *
  * \param r The new reliable status
  *
  */
void RainbruRPG::Network::NetPacketBase::setReliable(bool r){
  this->reliable=r;
}

/** Is this packet sent in reliable mode ?
  *
  * \return The reliable status
  *
  */
bool RainbruRPG::Network::NetPacketBase::isReliable(){
  return this->reliable;
}

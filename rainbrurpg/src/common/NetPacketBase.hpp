/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file netpacketbase.h
  * Defines the base packet sent over Enet network 
  *
  * Modifications :
  * - 19 mar 2007 : 
  *   - Documentation update
  *   - Adding \ref RainbruRPG::Network::NetPacketBase::getData() "getData()" 
  *     and \ref RainbruRPG::Network::NetPacketBase::getDataLength() 
  *     "getDataLength"
  * - 04 mar 2007 : starting implementation
  *
  * \todo 
  * - Some function are implemented inline and empty. These can't be pure 
  *   virtual ? (example \ref RainbruRPG::Network::NetPacketBase::netSerialize
  *   "netSerialize()").
  */


#ifndef NET_PACKET_BASE_H
#define NET_PACKET_BASE_H

#include <enet/enet.h>
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <glib.h>

#include <cstring> // For memcpy()

using namespace std;

/** \def ALWAYS_USE_RELIABLE
  * The packets are all reliable if defined 
  *
  */
#define ALWAYS_USE_RELIABLE

namespace RainbruRPG{
  namespace Network{

    /** The packet identification integer
      *
      * To identify each packet and to know how to deserialize it, it must
      * be identify by the receiver. This is the goal oh this enumeration.
      *
      * To make easier future expansion, the identifiers are grouped by 
      * sender type :
      * - General : 0x0000 -> 0x0FFF
      * - Flooder : 0x1000 -> 0x1FFF
      * - Editor  : 0x2000 -> 0x3FFF
      * - Server  : 0x4000 -> 0x5FFF
      * - Client  : 0x6000 -> 0x7FFF
      *
      * This identifier is 4 bytes lenght.
      *
      * This identifier should be the first field of all packet.
      *
      * \sa NetPacketBase
      */
    typedef enum{
      /** <b>The identification packet identifier</b>
        *
	* This type of packet is sent to a server to tell what type of
	* client is asking the connection. This identifier only tells
	* that the packet is an identification packet, it does not
	* give the type of client but the packet's data does. See the
	* identification packet documentation for more information.
	*
	*/
      NPI_GEN_IDENT     = 0x0000,

      /** A packet of 4 bytes for the netflooder
        *
	* \sa npFlooder0004
	*
	*/
      NPI_FLOOD_0004    = 0x1000,

      /** <b>The server connection response</b>
        *
	* If a server receive a new connection request, the connection
	* is accepted or rejected according to the server's options and
	* the client type (determined by NPI_GEN_IDENT). A packet of this
	* type is sent by the server to tell if the connection is accepted
	* or refused.
	*
	*/
      NPI_SVR_CONRESP   = 0x4000,

      /** <b>An invalid identifier used to check if the id was set</b>
        *
	* This value is set in the NetPacketBase constructor. If you
	* do not set your own identifier, a warning message can be logged.
	*
	*/
      NPI_INVALID       =0xFFFF
    }tNetPacketIdentifier;

    /** Only used to get the packet identifier
      *
      */
    typedef union{
      /** The data abstraction structure */
      struct {
	/** The paket identifier
	  *
	  * A guint16 id 2 bytes length.
	  *
	  * \sa tNetPacketIdentifier
	  *
	  */
	guint16 packetIdentifier;
      };
      /** The data to be sent  over the network */
      enet_uint8 data[2];
    }npPacketBaseData;

    /** The base Enet network packet
      *
      * All the packets send to/received from a server should subclass this
      * class. It is based on the libenet (http://enet.cubik.org/index.html)
      * library.
      *
      * \section sec_NetPacketBase_general General purpose
      *
      * The goal of this class is to provide a common way to create the data
      * section of the packet which is of type enet_uint8*. enet_uint8 is a 
      * typedef to unsigned char. The packet's data is made in the 
      * netSerialize() function and read in the netDeserialize() one.
      *
      * \section sec_NetPacketBase_byteOrder Byte order
      *
      * The little-endian byte order is used to send the packet instead of the 
      * netword byte order and the conversion functions are provided by glibc.
      *
      * I choose the little-endian byte order to do not charge x86 CPU's
      * with conversions time. The big-endian based processors will have
      * a performance issue caused by the little andian/big endian conversion.
      *
      * The conversion is made in the netSerialize() and netDeserialize() 
      * function. Typically, netSerialize will use GINT_TO_LE for an 
      * integer. netDeserailize should use GINT_FROM_LE. Please see
      * http://developer.gnome.org/doc/API/glib/glib-byte-order-macros.html
      * for the available conversion macros.
      *
      * \section sec_Reliable Reliable or not reliable ?
      *
      * A preprocessor macro called \ref ALWAYS_USE_RELIABLE is defined in
      * the header common/netpacketbase.h to tells always use reliable
      * network packets.
      * 
      * \sa tNetPacketIdentifier
      */
    class NetPacketBase{
    public:
      NetPacketBase();
      NetPacketBase(tNetPacketIdentifier);
      ~NetPacketBase();

      /** Serialize the packet to go over the network
        *
	* It creates the packet's data according to this class instance
	* values.
	*
	*/
      virtual void netSerialize(){};

      /** Deserialize a packet coming from the network
        *
	* It initalize this class instance's values with
	* a packet coming from the network.
	*
	*/
      virtual void netDeserialize(){};

      /** Get the resulting data of the netSerialization
        *
	* \return The packet data
	*
	*/
      virtual enet_uint8* getData(){};

      virtual void setData(enet_uint8*, size_t);
      /** The data length
        *
	* \return the data length as given from sizeof()
	*
	*/
      virtual size_t getDataLength(){};

      void send();
      tNetPacketIdentifier getIdentifier();

      const char* typeToString(tNetPacketIdentifier);

      void setReliable(bool);
      bool isReliable();

    protected:

      int convert(int);

      /** The packet identifier
        *
	* You must set this in the sub-class constructor. 
	*
	*/
      tNetPacketIdentifier id;

    private:

      /** Defines if the packet is reliable
        *
	* This value is overriden with the \ref ALWAYS_USE_RELIABLE macro 
	* if defined.
	*
	*/
      bool reliable;

      /** The data sent by this packet */
      npPacketBaseData* data;
    };

  }
}


#endif // NET_PACKET_BASE_H

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

/** \file npflooder0004.h
  * Defines a packet of 4 bytes used by the flooder
  *
  * Modifications :
  * - 17 jun 2007 : Documentation improvement
  * - 06 apr 2007 : Implementation
  */
#ifndef NETWORK_PACKET_FLOODER_0004_H
#define NETWORK_PACKET_FLOODER_0004_H

#include "netpacketflooderbase.h"

namespace RainbruRPG{
  namespace Network{

    /** Defines the data of a npFlooder0004 packet
      *
      * This basic data structure has a lenght of 4 bytes. It is used as
      * data for npFlooder0004. The \c netflooder uses this packet for test 
      * purpose.
      *
      * The union can be used to set values (by the abstraction structure)
      * and to get the packet to be sent (by the enet_uint8 array).
      *
      * \sa npFlooder0004
      *
      */
    typedef union{
      /** The data abstraction structure
        *
	* This is the only way to modify the data content.
	*
	*/
      struct {
	/** The paket identifier
	  *
	  * A guint16 is 2 bytes length.
	  *
	  * \sa tNetPacketIdentifier
	  *
	  */
	guint16 packetIdentifier;
	/** The response identifier
	  * 
	  * \sa NetPacketFlooderBase
	  *
	  */
	guint16 responseId; 
      };
      /** The data to be sent over the network */
      enet_uint8 data[4];
    }npFlooder0004Data;

    /** A basic netflooder packet with a lenght of 4 bytes
      *
      * The identifier of this packet is \c NPI_FLOOD_0004 (see 
      * tNetPacketIdentifier for more informations). This packet is used 
      * by the \c netflooder tool for test purpose only. The \c netflooder
      * send several packets of this type and wait for response from the 
      * server. We can compute the response time and make test.
      *
      * \sa tNetPacketIdentifier, Gui::NetFlooderWindow, npFlooder0004Data
      *
      */
    class npFlooder0004 : public NetPacketFlooderBase {
    public:
      npFlooder0004(guint16);
      ~npFlooder0004();

      virtual void netSerialize();
      virtual void netDeserialize();
      virtual enet_uint8* getData();
      virtual size_t getDataLength();
      virtual void setData(enet_uint8*, size_t);

    private:
      /** The npFlooder0004 packet data */
      npFlooder0004Data* data;
    };
  }
}

#endif //NETWORK_PACKET_FLOODER_0004_H

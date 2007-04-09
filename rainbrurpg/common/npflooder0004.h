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

/* Modifications :
 * - 06 apr 2007 : Implementation
 */

#ifndef NETWORK_PACKET_FLOODER_0004_H
#define NETWORK_PACKET_FLOODER_0004_H

#include "netpacketflooderbase.h"

namespace RainbruRPG{
  namespace Network{

    /** defines the data of a npFlooder0004 packet
      *
      * The client type is defines in the NetworkClientType enumeration.
      *
      * \sa npFlooder0004
      *
      */
    typedef union npFlooder0004Data{
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
	/** The response identifier
	  * 
	  * \sa NetPacketFlooderBase
	  *
	  */
	guint16 responseId; 
      };
      /** The data to be sent  over the network */
      enet_uint8 data[4];
    };

    /** A basic netflooder packet with a lenght of 4 bytes
      *
      * Its packet identifier is NPI_FLOOD_0004.
      *
      * \sa tNetPacketIdentifier
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

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
 * - 19 mar 2007 : Starting implementation of serialize deserialize and 
 *      other pure virtual function from NetPacketBase
 * - 05 mar 2007 : starting implementation
 */

#ifndef NETWORK_PACKET_IDENTIFICATION_H
#define NETWORK_PACKET_IDENTIFICATION_H

#include "netpacketbase.h"

namespace RainbruRPG{
  namespace Network{

    /** The client type identifier
      *
      * It is stored in a guint8 type so it needs 1 byte.
      *
      * \sa npIdentification, npIdentificationData
      */
    typedef enum tNetworkClientType{
      NCT_FLOODER    =0x01, //<! The client is a flooder
      NCT_EDITOR     =0x02, //<! The client is an editor
      NCT_GAME       =0x03, //<! The client is a flooder
      NCT_UNKNOWN    =0x99  //<! Not yet set
    };

    /** defines the data of a npIdentification packet
      *
      * The client type is defines in the NetworkClientType enumeration.
      *
      * \sa npIdentification, NetworkClientType
      *
      */
    typedef union npIdentificationData{
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
	/** The client type. 
	  * 
	  * \sa NetworkClientType
	  *
	  */
	guint16 clientType; 
      };
      /** The data to be sent  over the network */
      enet_uint8 data[4];
    };

    /** The identification packet
      *
      *
      * \sa npIdentificationData, NetworkClientType
      *
      */
    class npIdentification : public NetPacketBase{
    public:
      npIdentification();
      npIdentification(tNetworkClientType);

      ~npIdentification();

      void setClientType(tNetworkClientType);
      tNetworkClientType getClientType();

      virtual void netSerialize();
      virtual void netDeserialize();
      virtual enet_uint8* getData();
      virtual size_t getDataLength();
      virtual void setData(enet_uint8*, size_t);

      const char* clientTypeToString(tNetworkClientType);

    private:
      /** The network packet data */
      npIdentificationData* data;
      /** The client type */
      tNetworkClientType clientType;
    };

  }
}

#endif // NETWORK_PACKET_IDENTIFICATION_H
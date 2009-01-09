/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file npidentification.h
  * Defines the client identification packet
  *
  * Modifications :
  * - 19 mar 2007 : Starting implementation of 
  *      \ref RainbruRPG::Network::NetPacketBase::netSerialize "netSerialize()",
  *      \ref RainbruRPG::Network::NetPacketBase::netDeserialize 
  *      "netDeserialize" and  other pure virtual functions from 
  *      \ref RainbruRPG::Network::NetPacketBase "NetPacketBase".
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
    typedef enum{
      NCT_FLOODER    =0x01, //<! The client is a flooder
      NCT_EDITOR     =0x02, //<! The client is an editor
      NCT_GAME       =0x03, //<! The client is a flooder
      NCT_UNKNOWN    =0x99  //<! Not yet set
    }tNetworkClientType;

    /** defines the data of a npIdentification packet
      *
      * The client type is defines in the \ref tNetworkClientType enumeration.
      * This union is used for 
      *
      * - individual access in the anonymouse structure defining the 
      *   \ref npIdentificationData::packetIdentifier "packetIdentifier" and 
      *   the \ref npIdentificationData::clientType "clientType" members
      *
      * - direct access on the \c data memory to be sent over the network.
      *
      * \sa \ref npIdentification, \ref tNetworkClientType
      *
      */
    typedef union{
      /** The data abstraction structure */
      struct {
	/** The paket identifier
	  *
	  * A guint16 is 2 bytes length.
	  *
	  * \sa \ref tNetPacketIdentifier
	  *
	  */
	guint16 packetIdentifier;
	/** The client type. 
	  * 
	  * \sa \ref tNetworkClientType
	  *
	  */
	guint16 clientType; 
      };
      /** The data to be sent  over the network */
      enet_uint8 data[4];
    }npIdentificationData;

    /** The identification packet
      *
      * This packet is used by a network client to tell the server its type.
      * There are several types, a game client, an editor or a flooder 
      * (a tool). These differents client types are defined in the 
      * \ref tNetworkClientType enumeration.
      *
      * \sa \ref npIdentificationData, \ref tNetworkClientType
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
      /** The network packet data 
        *
	* It is the data, sent when connecting to a server.
	*
	*/
      npIdentificationData* data;
      /** The client type 
        *
	* The client type set to the npIdentification object. Its value
	* is set to \ref data in the \ref netSerialize() function and it takes
	* its value from \ref data by a call to \ref netDeserialize().
	*
	*/
      tNetworkClientType clientType;

    };

  }
}

#endif // NETWORK_PACKET_IDENTIFICATION_H

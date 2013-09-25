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
 * - 20 mar 2007 : starting implementation
 */

#ifndef NETWORK_PACKET_CONNECTION_RESPONSE_H
#define NETWORK_PACKET_CONNECTION_RESPONSE_H

#include "netpacketbase.h"

namespace RainbruRPG{
  namespace Network{

    /** The server answer to a client connection
      *
      *
      *
      */
    typedef enum tServerConnectionResponse{
      NCR_UNDEFINED    =0x01, //<! The response is undefined
      NCR_ACCEPTED     =0x02, //<! The connection is accepted
      NCR_REFUSED      =0x03, //<! The connection is refused

    };

    /** The data of the npConnectionResponse network packet
      *
      */
    typedef union npConnectionResponseData{
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
	guint16 response; 
      };
      /** The data to be sent  over the network */
      enet_uint8 data[4];
    };

    /** The connection response packet
      *
      *
      * \sa npConnectionResponseData, tServerConnectionResponse
      *
      */
    class npConnectionResponse : public NetPacketBase{
    public:
      npConnectionResponse();
      npConnectionResponse(tServerConnectionResponse);

      ~npConnectionResponse();

      void setResponse(tServerConnectionResponse);
      tServerConnectionResponse getResponse();

      virtual void netSerialize();
      virtual void netDeserialize();
      virtual enet_uint8* getData();
      virtual size_t getDataLength();
      virtual void setData(enet_uint8*, size_t);

      bool responseToBool(tServerConnectionResponse);

    private:
      /** The network packet data */
      npConnectionResponseData* data;
      /** The server response */
      tServerConnectionResponse response;
    };
  }
}
#endif // NETWORK_PACKET_CONNECTION_RESPONSE_H


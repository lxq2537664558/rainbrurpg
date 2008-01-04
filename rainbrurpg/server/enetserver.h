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

/* Modifications :
 * - 22 mar 2007 : sendPacket() function implementation
 * - 16 mar 2007 : starting implementation
 */


#ifndef ENET_SERVER_H
#define ENET_SERVER_H

#include <enet/enet.h>
#include <string>
#include <glib.h>
#include <QObject>
#include <cstring>

#include "enetbase.h"
#include "netpacketbase.h"

using namespace std;
using namespace RainbruRPG::Network;

namespace RainbruRPG{
  namespace Network{

    /** A structure defining what is send to the application when
      * a packet is received.
      *
      * This structure is used in some Qt signals/slots. The peer pointer
      * can be used to send a response to the client.
      *
      */
    typedef struct tReceivedPacket{

      enet_uint8* data; //!< The data received
      size_t dataLength;//!< The length of data received
      enet_uint32 host; //!< The host address
      enet_uint16 port; //!< The host port
      ENetPeer*   peer; //!< The peer used to send this packet
    };

    /** The enet server class
      *
      * This class is only used by the game server. The EnetAddress.host 
      * value is always set to ENET_HOST_ANY. The
      * EnetAddress.port value must be set by a call to setPort().
      * Then, you call eventLoop to wait connections.
      *
      * The default port number is 50000. maxClient is by default set to 32.
      *
      */
    class EnetServer : public QObject, public EnetBase{
      Q_OBJECT
    public:
      EnetServer();
      virtual ~EnetServer();

      virtual void eventLoop();
      void setPort(int);
      void setMaxClient(int);

      void createServer();
      void cleanupServer();

      virtual void sendPacket(ENetPeer*, NetPacketBase*);

    signals:
      /** A signal emitted when a client request a connection
        *
	* This signal is emitted when a ENet host request a connection.
	* We don't know the client type and we can't tell if the connection 
	* is accepted or refused.
	*
	* \param e The address of the server that request the connection
	*
	*/
      void clientConnected(const ENetAddress &e);
      /** A packet was received
        *
	*/
      void packetReceived(const tReceivedPacket&);

    private:

      /** The enet adress structure
        *
	*/
      ENetAddress* address;
      /** The enet host used to be the server
        *
	*/
      ENetHost * server;
      /** The enet event structure
        *
	*/
      ENetEvent event;
      /** The maximum number of connection allowed */
      int maxClient;
      /** The event loop timeout */
      int timeout;
    };


  }
}

#endif // ENET_SERVER_H

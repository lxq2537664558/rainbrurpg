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
 * - 19 mar 2007 : cleanupServer() function added
 * - 16 mar 2007 : Starting implementation
 *
 */

#ifndef SERVER_THREAD_H
#define SERVER_THREAD_H

#include <QThread>
#include <enet/enet.h>

#include "enetserver.h"

using namespace RainbruRPG::Network;

namespace RainbruRPG{
  namespace Server{

    /** Encapsulates a EnetServer in a Qt thread
      *
      *
      *
      */
    class ServerThread : public QThread{
      Q_OBJECT
    public:
      ServerThread();
      ~ServerThread();


      void setPort(int);
      void setMaxClient(int);
      void createServer();
      void cleanupServer();
      void run();

      EnetServer* getServer();

    signals:
      /** A signal emitted when a client request a connection
        *
	* This signal is only a relay of the 
	* RainbruRPG::Network::EnetServer::clientConnected()
	* signal.
	*
	* \param e The address of the server that request the connection
	*
	*/
      void clientConnected(const ENetAddress &e);
      /** A signal emitted when a network packet is received
        *
	* This signal is only a relay of the 
	* RainbruRPG::Network::EnetServer::packetReceived()
	* signal.
	*
	* \param p The received packet
	*
	*/
      void packetReceived(const tReceivedPacket& p);

    private:
      /** The ENet server used for connnection */
      EnetServer* server;
      
    };

  }
}

#endif // SERVER_THREAD_H

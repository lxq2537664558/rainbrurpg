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

/** \file enetclient.h
  * Declares the Enet client
  *
  * Modifications :
  * - 19 mar 2007 : Adds the \ref RainbruRPG::Network::EnetClient::connect()
  *                 "connect()"  and 
  *                 \ref RainbruRPG::Network::EnetClient::isConnected() 
  *                 "isConnected()" functions
  * - 13 mar 2007 : starting implementation
  */


#ifndef ENET_CLIENT_H
#define ENET_CLIENT_H

#include <string>
#include <enet/enet.h>
#include <glib.h>

#include "enetbase.h"
#include "netpacketbase.h"

using namespace std;
using namespace RainbruRPG::Network;

namespace RainbruRPG{
  namespace Network{

    /** The enet client base class
      *
      * To send packets only when the client is connected, try something 
      * like :
      * <pre>
      * EnetClient ec;
      * while(!ec.isConnected()){
      *   ec.connect(...);
      * }
      * </pre>
      *
      * Be careful because the while statement may be endless.
      */
    class EnetClient : public EnetBase{
    public:
      EnetClient();
      virtual ~EnetClient();

      /** The event loop that should be overriden in subclasses
        * 
	* By a call to this function, you're entering in the event loop
	*
	*/
      virtual void eventLoop()=0;

      void connect(const char*, enet_uint16, int waitingTime=3000);
      virtual void sendPacket(NetPacketBase*);

      bool isConnected();

    protected:
      /** The enet adress structure
        *
	*/
      ENetAddress* address;
      /** The enet host used to be the client
        *
	*/
      ENetHost * client;
      /** The global enet peer
        *
	*/
      ENetPeer * peer;
      /** The enet event structure
        *
	*/
      ENetEvent event;
      /** Is this peer successfully connected
        *
	* Set by default to false, this value is set to \c true
	* if the peer is succeffully created.
	*
	* \sa isConnected()
	*
	*/
      bool connected;
    };


  }
}

#endif // ENET_CLIENT_H

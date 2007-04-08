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
 * - 23 mar 2007 : Using sigc++ signals
 * - 22 mar 2007 : eventLoop() and treatPacket() implementation
 * - 13 mar 2007 : starting implementation
 */

#ifndef ENET_FLOODER_CLIENT_H
#define ENET_FLOODER_CLIENT_H

#include <enetclient.h>
#include <netpacketbase.h>
#include <sigc++/sigc++.h>

#include "netpacketflooderbase.h"

namespace RainbruRPG{
  namespace Network{

    /** The enet client used with the netflooder
      *
      * It uses the sigc++ library for signal/slot mechanism.
      *
      */
    class EnetFlooderClient : public EnetClient, public sigc::trackable {
    public:
      /** Defines a signal returning void with none parameters */
      typedef sigc::signal<void> tVoidSignal;

      EnetFlooderClient();
      ~EnetFlooderClient();

      virtual void eventLoop();
      int sendPacketAndWaitResponse(NetPacketFlooderBase*, bool);

      /** A signal sent if the connection is accepted by the selected server*/
      tVoidSignal sigConnectionAccepted;
      /** A signal sent if the connection is refused by the selected server*/
      tVoidSignal sigConnectionRefused;
      /** A signal sent if the npConnectionResponse received is undefined*/
      tVoidSignal sigConnectionUndefined;

    private:
      void treatPacket(NetPacketBase*, ENetEvent* );

    };

  }
}

#endif // ENET_FLOODER_CLIENT_H

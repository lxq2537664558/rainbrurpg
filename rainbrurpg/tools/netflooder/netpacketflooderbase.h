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
 *
 */

#ifndef NET_PACKET_FLOODER_BASE_H
#define NET_PACKET_FLOODER_BASE_H

#include <netpacketbase.h>

namespace RainbruRPG {
  namespace Network{

    /** A class implementaing a response identifier used by NetFlooder
      *
      * This class only add a field to the NetPacketBase one.
      * The responseId is used to get the ersponse of a given packet.
      *
      */
    class NetPacketFlooderBase : public NetPacketBase{
    public:
      NetPacketFlooderBase(tNetPacketIdentifier, guint16);

      void setResponseId(guint16);
      guint16 getResponseId();

    protected:
      /** The response controlled in the response packet */
      guint16 responseId;
    };

  }
}

#endif //NET_PACKET_FLOODER_BASE_H

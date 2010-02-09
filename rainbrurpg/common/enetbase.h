/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file enetbase.h
  * Defines a base-class for all enet based classes
  *
  * Modifications :
  * - 06 aug 2008 : Single file documentation
  * - 13 mar 2007 : starting implementation
  *
  */


#ifndef ENET_BASE_H
#define ENET_BASE_H

#include <enet/enet.h>
#include <string>
#include <glib.h>

#include "netpacketbase.h"
#include "rainbrudef.h" // For the gettext stuff

using namespace std;
using namespace RainbruRPG::Network;

namespace RainbruRPG{
  namespace Network{

    /** The enet host abstraction super-class
      *
      * The init() and deinit() should be called once. Then, you can call
      * eventLoop().
      *
      * You should not subclass this. There is EnetClient and EnetServer 
      * that can be easier to subclass.
      *
      */
    class EnetBase{
    public:
      EnetBase();
      virtual ~EnetBase();

      /** The event that should be overriden in subclasses
        * 
	* By a call to this function, you're entering in the event loop
	*
	*/
      virtual void eventLoop()=0;
      virtual void sendPacket(NetPacketBase*);

    protected:
      void init();
      void deinit();


    private:
      /** Is the enet library initialized
        *
	* \sa init(), deinit()
	*
	*/
      bool isInitialized;
    };


  }
}

#endif // ENET_BASE_H

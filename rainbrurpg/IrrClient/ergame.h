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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#ifndef ER_GAME_H
#define ER_GAME_H

#include <irrlicht.h>
#include <IEventReceiver.h>
#include <logger.h>

#include "gameengine.h"
#include "screenshotmanager.h"

using namespace irr;

namespace RainbruRPG{
  namespace Events{

    /** The Irrlicht Event Recever for gsGame
      *
      * This class is instancied and set up to the IrrlichtDevice in
      * the gsGame::run(). If we set up this in gsGame::init(), the
      * IrrlichtDevice isn't yet initialized and it may cause a SegFault.
      */
    class erGame : public IEventReceiver{
    public:
      virtual bool OnEvent(SEvent event);

    };
  }
}

#endif //ER_GAME_H

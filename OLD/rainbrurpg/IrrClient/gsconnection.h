/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

#ifndef GS_CONNECTION_H
#define GS_CONNECTION_H

#include <irrlicht.h>
//#include <IGUIEditBox.h>

#include "gamestate.h"
#include "irrfontmanager.h"

using namespace irr;
using namespace gui;
using namespace core;
//using namespace RainbruRPG::Events;

namespace RainbruRPG {
  namespace Core {

    /** The connection GameState
      *
      * Here the user can enter its usernameand password.
      */
    class gsConnection : public GameState {
    public:
      virtual void init();
      virtual void cleanup();
      
      virtual void pause();
      virtual void resume();
      
      virtual void run();

      void createGui();

    private:

      /** The Irrlicht device */
      irr::IrrlichtDevice*       irrDevice;
      /** The Irrlicht driver type */
      irr::video::E_DRIVER_TYPE  driverType;
      /** The Irrlicht video driver */
      irr::video::IVideoDriver*  irrDriver;
      /** The Irrlicht scene manager */
      irr::scene::ISceneManager* irrSmgr;
      /** The Irrlicht gui environmant */
      irr::gui::IGUIEnvironment* irrGui;

     /** The Irrlicht GUI tab in wich the menu is drawn
        *
	*/
      IGUITab * irrTab;

    };
  }
}

#endif // GS_CONNECTION_H

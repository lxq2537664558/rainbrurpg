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

#ifndef GS_GAME_ESC_H
#define GS_GAME_ESC_H

#include <irrlicht.h>
#include <IGUITabControl.h>

#include "gamestate.h"
#include "ergameesc.h"

using namespace irr;
using namespace gui;
using namespace core;
using namespace RainbruRPG::Events;

namespace RainbruRPG {
  namespace Core {

    /** The gameEsc menu GameState
      *
      * This class provides the ingame menu GameState. It is called
      * when you hit the Esc key when you're in game.
      *
      * It uses a Irrlicht GUI tab widget to provide the show and hide
      * functions. 
      * 
      */
    class gsGameEsc : public GameState {
    public:
      virtual void init();
      virtual void cleanup();
      
      virtual void pause();
      virtual void resume();
      
      virtual void run();

      void createGui();

    private:
      /** Set if we debug the selector
        *
	* If true, this will highligth the triangle in front of
	* player in red
	*/
      bool triangleSelector;

      /** The Irrlicht device
        *
	*/
      irr::IrrlichtDevice*       irrDevice;

      /** The IrrlichtDriver type
        *
	*/
      irr::video::E_DRIVER_TYPE  driverType;

      /** The Irrlicht video driver
        *
	*/
      irr::video::IVideoDriver*  irrDriver;

      /** The Irrlicht scene manager
        *
	*/
      irr::scene::ISceneManager* irrSmgr;

      /** The mesh representing the Quake 3 level
        *
	*/
      irr::scene::IAnimatedMesh* q3levelmesh;

      /** The node representing the Quake 3 level
        *
	*/
      irr::scene::ISceneNode* q3node;

      /** The irrlicht triangle selector
        *
	*/
      irr::scene::ITriangleSelector* irrSelector;

      /** The player's camera
        *
	*/
      irr::scene::ICameraSceneNode* irrCamera;

      /** The material used to highlight the faeries
        *
	*/
      irr::video::SMaterial faerieMaterial;

      /** The Irrlicht GUI environment
        *
	*/
      irr::gui::IGUIEnvironment* irrGui;

     /** The Irrlicht GUI tab in wich the menu is drawn
        *
	*/
      IGUITab * irrTab;

    };
  }
}

#endif // GS_GAME_ESC_H

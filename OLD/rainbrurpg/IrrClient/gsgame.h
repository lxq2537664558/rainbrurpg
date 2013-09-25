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

#ifndef GS_GAME_H
#define GS_GAME_H

#include <irrlicht.h>

#include "gamestate.h"
#include "ergame.h"

using namespace irr;
using namespace gui;
using namespace core;
using namespace RainbruRPG::Events;

namespace RainbruRPG {
  namespace Core {

    /** The game GameState
      *
      * This class provides the ingame GameState.
      *
      * It can load a example Quake3 map, debug the colision detection
      * (triangle selector and model highligthing).
      *
      * \warning The Event Receiver must be set up in the
      * IrrlichtDevice in the run() method. If we do it in the init()
      * method, the IrrlichtDevice isn't yet initialized and it cause
      * a SegFault.
      */
    class gsGame : public GameState {
    public:
      virtual void init();
      virtual void cleanup();
      
      virtual void pause();
      virtual void resume();
      
      virtual void run();

      void loadExampleMap();

      void initTriangleSelector();
      void initCamera();
      void initExampleFaeries();
      void initBillboard();

      void createGui();
      void drawDebug();
    private:
      /** Set if we debug the selector
        *
	* If true, this will highligth the triangle in front of
	* player in red
	*/
      bool triangleSelector;

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

      /** A mesh tha represents a Quake3 level */
      irr::scene::IAnimatedMesh* q3levelmesh;
      /** A node tha represents a Quake3 level */
      irr::scene::ISceneNode* q3node;
      /** The irrlicht triangle selector */
      irr::scene::ITriangleSelector* irrSelector;
      /** The player's camera */
      irr::scene::ICameraSceneNode* irrCamera;
      /** The material used to highlight the faeries */
      irr::video::SMaterial faerieMaterial;

      /** The scene node used to draw a billboard */
      scene::IBillboardSceneNode * bill;
      /** The current node (triangle) pointed by the player */
      scene::ISceneNode* selectedSceneNode;
      /** The last node (triangle) pointed by the player */
      scene::ISceneNode* lastSelectedSceneNode;


      /** Enable or disable all the debug tools
        *
	* The debug tools are the billboard, the triangle selector and
	* the model detector. If debug is set to false, none of the
	* debug tools will be enabled, even if there are one. If you
	* set debug to true, you must also set to true the debug tools
	* you want to enabled.
	*
	*/
      bool debug;
      /** Enable or disable all the triangle selection debugging tool
        *
	* Highlights the triangle pointed by the player in red.
	*
	* This debug tool is used only if \c debug is set to \c
	* true. If \c debug is set to \c false, this boolean will not
	* be considered
	*
	*/
      bool debugTriangleSelection;
      /** Enable or disable all the model selection debugging tool
        *
	* Highlights the pointed model.
	*
	* This debug tool is used only if \c debug is set to \c
	* true. If \c debug is set to \c false, this boolean will not
	* be considered
	*
	*/
      bool debugModelSelection;
      /** Enable or disable all the triangle selection debugging tool
        *
	* Draws a billboard (a round particle) in front of the player.
	*
	* This debug tool is used only if \c debug is set to \c
	* true. If \c debug is set to \c false, this boolean will not
	* be considered
	*
	*/
      bool debugBillboard;
    };
  }
}

#endif // GS_GAME_H

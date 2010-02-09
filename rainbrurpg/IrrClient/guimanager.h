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

#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <irrlicht.h>
#include <singleton.h>

#include "gameengine.h"

using namespace std;
using namespace irr;
using namespace irr::core;
using namespace video;
using namespace gui;
using namespace RainbruRPG::Core;

namespace RainbruRPG {
  namespace Gui{

    /** The Gui Manager used by the client
      *
      * This singleton class is used to create Irrlicht build-in GUI
      * creating. The objects created can be :
      * - centered windows;
      * - create commons windows (Numeric Debug, Console...)
      */
    class GuiManager : public Singleton<GuiManager>{
    public:
      GuiManager(){};
      void init();
      void cleanup();

      void createNumDebugWindow();
      void showFPS();

    private:
      /** Unimplemented copy constructors 
        *
	* In a singleton the use of this method must be forbidden.
	* 
	* \param obj A GuiManager
	*/
      GuiManager(const GuiManager& obj);

      /** Unimplemented assignment
        *
	* In a singleton the use of this method must be forbidden.
	* \param obj A GuiManager
	*/
      GuiManager& operator=(const GuiManager& obj);

      /// The Irrlicht Device
      irr::IrrlichtDevice *irrDevice;

      /// The Irrlicht driver type
      irr::video::E_DRIVER_TYPE driverType;

      /// The Irrlicht video driver
      irr::video::IVideoDriver* irrDriver;

      /// The Irrlicht scene manager
      irr::scene::ISceneManager* irrSmgr;

      /// The Irrlicht build-in Gui environment
      irr::gui::IGUIEnvironment* irrGui;

      /// The GUI element showing the minimum fps value
      IGUIStaticText* minFps;
      /// The GUI element showing the current fps value
      IGUIStaticText* curFps;
      /// The GUI element showing the maximum fps value
      IGUIStaticText* maxFps;

      /// The GUI element showing the minimum count of primitives
      IGUIStaticText* minPri;
      /// The GUI element showing the current count of primitives
      IGUIStaticText* curPri;
      /// The GUI element showing the maximum count of primitives
      IGUIStaticText* maxPri;

      /** The last drawn fps value
        *
	* This integer is used to know if the FPS value has
	* changed. so we can change the curFps text property only if
	* the value has changed.
	*
	*/
      int lastFPS;
      /// The integer used to store the minimum FPS value
      int i_minFPS;
      /// The integer used to store the maximum FPS value
      int i_maxFPS;

      /** The last drawn primitives count value
        *
	* This integer is used to know if the primitives value has
	* changed. so we can change the curPri text property only if
	* the value has changed.
	*
	*/
      int lastPri;
      /// The integer used to store the minimum primitives count value
      int i_minPri;
      /// The integer used to store the maximum primitives count value
      int i_maxPri;
    };
  }
}
#endif // GUI_MANAGER_H

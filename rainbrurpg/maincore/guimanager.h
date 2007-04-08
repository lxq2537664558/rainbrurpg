/*
 *  Copyright 2006 Jerome PASQUIER
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

#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <singleton.h>
#include <OGRE/Ogre.h>
#include <OGRE/OgreKeyEvent.h>
#include <OGRE/OgreEventListeners.h>
#include <OGRE/OgreStringConverter.h>
#include <OGRE/OgreException.h>

#include "gameengine.h"
#include "velocitycalculator.h"
#include "vcconstant.h"

using namespace std;
using namespace RainbruRPG::Core;

namespace RainbruRPG {
  namespace Gui{

    /** The Gui Manager used by the client
      *
      * This singleton class is used to create GUI forms.
      *
      */
    class GuiManager : public RainbruRPG::Core::Singleton<GuiManager>{
    public:
      /** An empty default constructor */
      GuiManager(){};
      void init();
      void cleanup();

      void createNumDebugWindow(Ogre::RenderWindow*);
      void createTitleOverlay(Ogre::RenderWindow*);
      void detroyTitleOverlay();

      void showFPS();
      void loadCEGUILayout(const char*);
      void removeCurrentCEGUILayout();

      void setTransitionTime(unsigned int);
      unsigned int getTransitionTime();

      void setGuiTransparency(float);
      void beginGuiFadeIn();
      void beginGuiFadeOut();

      bool isInGuiFadeOut();

      void guiFade();

      Ogre::RenderWindow* getRenderWindow();
      void debugChild(const char*);

    private:
      void debugWindow(CEGUI::Window*);

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

      void increaseGuiTransparency(float);

      /** The current Ogre render window */
      Ogre::RenderWindow* win;

      /** The menu transition time in milliseconds*/
      unsigned int transitionTime;
      /** The GUI fade in time in milliseconds*/
      unsigned int guiFadeInTime;

      /** The standard velocity calculator used for menu transition */
      VelocityCalculator* velocity;
      /** Are we in GUI fade in transition */
      bool inGuiFadeIn;
      /** Are we in GUI fade out transition */
      bool inGuiFadeOut;

      /** The opacity of the GUI */
      float guiOpacity;

      /** The title overlay */
      Ogre::Overlay* mTitleOverlay;
    };
  }
}
#endif // GUI_MANAGER_H

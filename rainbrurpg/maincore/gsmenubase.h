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

#ifndef GS_MAIN_MENU_BASE_H
#define GS_MAIN_MENU_BASE_H

#include "OGRE/Ogre.h"

#include <OIS/OISPrereqs.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include "gamestate.h"

using namespace Ogre;

// Forward declarations
namespace RainbruRPG {
  namespace Core{
    class InputManager;
    class InputWrapper;
    class VelocityCalculator;
  }
  namespace Gui{
    class GuiManager;
    class KeyboardNavigation;
  }
}
// End of forward declarations

using namespace RainbruRPG::Gui;

namespace RainbruRPG {
  namespace Core{

    /** A super-class for menus drawing shareable capabilities
      *
      * A menu contains a moveable border with two panels. Typically,
      * the right panel contains CEGUI elements.
      *
      */
    class gsMenuBase : public GameState{
    public:
      gsMenuBase(bool createMenu);
      /** An empty default destructor needed to avoid compilation warnings */
      virtual ~gsMenuBase(){};

      virtual void init();
      virtual void cleanup();
      virtual void pause();
      virtual void resume();
      virtual void run();
      virtual void transition();

      virtual void frameStarted(const FrameEvent&);
      virtual void frameEnded(const FrameEvent&);

      void translateTo(float);

      bool isInTransition();

      virtual bool keyPressed(const OIS::KeyEvent&);
      virtual bool keyReleased(const OIS::KeyEvent&);
      virtual bool mouseMoved(const OIS::MouseEvent&);
      virtual bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
      virtual bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);
 
      /** \brief Implements the focus tab order
        *
	* You \b must override this to setup the tabOrder.
	*
	* This function should be called in the init() function \b after 
	* the CEGUI layout was loaded and in the resume() function.
	*
	* \sa \ref RainbruRPG::Core::gsMenuBase::tabNav "tabNav",
	*     KeyboardNavigation.
	*
	*/
      virtual void setupTabOrder()=0;

    protected:
      /** An empty default constructor 
        *
	* It is protected to borbid its use.
	*
	*/
      gsMenuBase(){};

      void drawBorder();
      void drawMenuBackground();
      void drawDynamicBackground();

      void setCorners();
      float getTranslationLenght(float, float);

      /** A shortcut to the Ogre::Root object */
      Root *mRoot;
       /** A shortcut to the Ogre::SceneManager object */
      SceneManager* mSceneMgr;
      /** The menu scene node */
      SceneNode* menuNode;
      /** The object used to rendering the menu border */
      Rectangle2D* bordRect;
      /** The object used to rendering the right menu */
      Rectangle2D* menuRect;
      /** The object used to rendering the left menu */
      Rectangle2D* dynaRect;

      /** The position of the border */
      double yBorder;
      /** The transition start point */
      float yBorderFrom;
      /** The transition end point */
      float yBorderTo;
      /** The transition time in miliseconds */
      int transitionTime;
      /** The number of repeated textures */
      float uMappingScreenSize;
      /** The number of repeated textures */
      float vMappingScreenSize;

      /** Are we in transition */
      bool inTransition;
      /** The velocity calculator instance */
      VelocityCalculator* velocity;

      /** The number of initialization frame
        *
        * The number of frame during wich the transition is not made
	* to prevent transition during graphic engine initialization
	*
	*/
      unsigned int initFrameNumber;
      /** Counts the initialization frame passed
        *
	*/
      unsigned int initFrameCount;

      /** The inputwrapper */
      InputWrapper* inputWrapper;
      /** Should we create the dynamic menu */
      bool createMenu;

      /** Provides the Tab/Shift+Tab widget navigation 
        *
	* This is used for implementation of the tab order (see 
	* setupTabOrder()).
	*
        */
      KeyboardNavigation* tabNav;
    };
  }
}

#endif // GS_MAIN_MENU_BASE_H


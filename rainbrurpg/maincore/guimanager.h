/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

/** \file guimanager.h
  * Declares a singleton used to manage GUI
  *
  * Modifications :
  * - 05 sep 2008 : Setting a logger output in showMessageBox()
  * - 02 sep 2008 : Added ErrorMsg overlay
  * - 18 aug 2008 : Single file documentation
  * - 17 nov 2007 : GuiManager::showMessageBox doesn't need a parent anymore
  * - 08 nov 2007 : isInGuiFadeIn() added
  * - 31 jul 2007 : Ogre3D log partially deactivate
  * - 24 jul 2007 : showMessageBox implementaion
  *
  * \todo Remove CEGUI layout section when OgreGui will completely replace
  *       CEGUI (see \ref cegui_layout_sec).
  *
  */

#ifndef GUI_MANAGER_H
#define GUI_MANAGER_H

#include <singleton.h>
#include <ogreimport.h>

#include "gameengine.h"
#include "velocitycalculator.h"
#include "vcconstant.h"
#include "messagebox.h"

//#define MGM_SHOW_MESSAGE_BOX_WARNING

// Conditionnal documentation to avoid a doxygen warning if 
// MGM_SHOW_MESSAGE_BOX_WARNING is undefined
#ifdef MGM_SHOW_MESSAGE_BOX_WARNING
/** \def MGM_SHOW_MESSAGE_BOX_WARNING
  * Should we show a warning if using the showMessageBox() function 
  *
  * Please comment this macro to deactivate this warning
  *
  * \note This is used as test, to know where are the calls to showMessageBox()
  *       function
  *
  */
#endif // !MGM_SHOW_MESSAGE_BOX_WARNING


using namespace std;
using namespace RainbruRPG::Core;

// Forward declarations
namespace BetaGUI{
  class Window;
}
namespace RainbruRPG {
  namespace OgreGui{
    class StatusLabel;
  }
}
// End of forward declarations

namespace RainbruRPG {
  namespace Gui{

    /** The graphical user interface manager used by the client
      *
      * This singleton class is used to create GUI forms, manage CEGUI
      * layouts and Ogre overlays. It is also responsible of the GUI
      * fading effect you can see in client's menus.
      *
      * \section ogre_overlays_sec Ogre overlays 
      *
      * Ogre3D provides the overlay management facility. Overlays are
      * simple GUI element that not provide user interaction. This class 
      * manages two overlays :
      * - mTitleOverlay : the overlay showing the title and game version.
      *   It is shown with createTitleOverlay() and destroyed with 
      *   detroyTitleOverlay().
      * - The numeric debug window : this one has not a private class member.
      *   it is create by createNumDebugWindow() and can not be destroy
      *   individually.
      *
      * \section cegui_layout_sec CEGUI layouts
      *
      * CEGUI is the library I use for advanced GUI (providing keyboard
      * and mouse interaction). Every GUI definition is stored in layout
      * files. You can find these layout in the \c data/gui/layout 
      * directory. The gsMenuBase subclasses use CEGUI layout.
      *
      * There is two member functions that hold CEGUI layout : 
      * loadCEGUILayout() that load and draw the named layout and 
      * removeCurrentCEGUILayout() that removed from the screen and the memory
      * the actual guiSheet (root window).
      *
      * \section gui_fading_sec Gui fading
      *
      * Between two menu, a transition effect is based on GUI fading (aka
      * alpha channel). The \ref setGuiTransparency(float), 
      * \ref beginGuiFadeIn() and \ref beginGuiFadeOut() are interresting. 
      * To use this effect you should use the following code :
      * \code
      *   GuiManager::getSingleton().beginGuiFadeOut();
      *
      *   // We must wait for the CEGUI fade end to prevent
      *   // SEGFAULT in access to CEGUI windows (getAlpha())
      *   while (GuiManager::getSingleton().isInGuiFadeOut()){
      *     Ogre::Root::getSingleton().renderOneFrame();
      *   }
      *
      *   GuiManager::getSingleton().detroyTitleOverlay();
      *   GuiManager::getSingleton().removeCurrentCEGUILayout();
      *   GameEngine::getSingleton().changeState(ST_MENU_CONNECT);
      *
      *   GuiManager::getSingleton().beginGuiFadeIn();      
      * \endcode
      *
      * \section mess_box_sec Message boxes
      *
      * The \ref showMessageBox() provides a simple CEGUI message box with 
      * a single OK button . For the \ref hideMessageBox(), please see its own 
      * documentation.
      *
      * \section error_message_sec Error message
      *
      * The game menus uses, since build 185, a new concept. In the
      * bottom edge of the screen, there is a \ref OgreGui::StatusLabel, 
      * that can print temporaly error messages. The messages can be set with
      * the \ref setErrorMessage() function.
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
      void destroyTitleOverlay();

      void showFPS();

      void setTransitionTime(unsigned int);
      unsigned int getTransitionTime();

      void setGuiTransparency(float);
      void beginGuiFadeIn();
      void beginGuiFadeOut();

      bool isInGuiFadeOut();
      bool isInGuiFadeIn();

      void guiFade();

      Ogre::RenderWindow* getRenderWindow();

      void showMessageBox(const String&, const String&); 
      void hideMessageBox(bool);

      void createErrorLabel(void);
      void setErrorMessage(const String&);

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

      /** The title overlay 
        *
	* This Ogre overlay, shown in the first menu of the game client,
	* shows the game name and version number. It is shown only the first
	* time the gsMainMenu is drawn.
	*
	* This value is used to know if the overlay exist. detroyTitleOverlay()
	* set it to \c NULL when it is destroyed. The other times 
	* detroyTitleOverlay() is called, if \c mTitleOverlay==NULL, we
	* donot try to destroy it.
	*
	* \sa createTitleOverlay(), detroyTitleOverlay().
	*
	*/
      Ogre::Overlay* mTitleOverlay;

      /** The label used to print errors */
      StatusLabel* mErrorLabel;

      /** The window that contains mErrorLabel */
      BetaGUI::Window* errorLabelWindow;
    };
  }
}
#endif // GUI_MANAGER_H

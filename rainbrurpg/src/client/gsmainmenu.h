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

/** \file gsmainmenu.h
  * Declares the main menu game state
  *
  * Modifications :
  * - 01 oct 2008 : Documentation improved
  * - 16 aug 2008 : Single file documentation
  * - 24 mar 2008 : MultiColumnList test window implementation
  * - 20 sep 2007 : Uses BetaGUI
  * - 22 jul 2007 : Moving the connection menu to gsConnection
  *
  */

#ifndef GS_MAIN_MENU_H
#define GS_MAIN_MENU_H

#include <hashpassword.h>

#include "gsmenubase.h"
//#include "bgbutton.h"
//#include "bgwindow.h"
#include "bglistener.h"

#include "../config.h"

// Forward declarations
namespace BetaGUI{
  class Button;
}
namespace RainbruRPG{
  namespace OgreGui{
    class PushButton;
    class Window;
  }
}
// End of forward declarations

using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Core{

    /** The main menu gamestate
      *
      * The main menu is the first screen to appears when the game is 
      * launched. It provides 3 buttons : 
      * - Network game : you can play in a worldwide server
      *     Switch to the \ref gsConnection game state)
      * - Local test : You play alone to test the rendering engine.
      *     Switch to the \ref gsLocalTest game state.
      * - Quit : exit the game without any advice or prompt.
      *
      * \section gsMainMenu_configure_sec Configure script options
      *
      * \note A ScrollPane test window is created if the \c configure script
      *       is called with the \c --enable-scrollp-test option.
      *
      * \note A MultiColumnList test window is created if the \c configure 
      *       script is called with the \c --enable-mcl-test option.
      *
      */
    class gsMainMenu : public gsMenuBase, public BetaGUI::BetaGUIListener{
    public:
      gsMainMenu();
      virtual ~gsMainMenu();

      virtual void init();
      virtual void resume();
      virtual void pause();

      virtual void setupTabOrder();
      virtual void onButtonPress(BetaGUI::Button*);

    protected:
#ifdef RB_SCROLLPANE_TEST
      void createScrollPaneTestWindow(void);
      void onAddLabel(void);

      /** The add label button, used in ScrollPane test window */
      PushButton* btnAddLabel;
      /** The widget containing the X position of the new label */
      TextInput* tiXPos;
      /** The widget containing the Y position of the new label */
      TextInput* tiYPos;
      /** The window to test ScrollPane */
      Window* ScrollPaneTestWin;
      /** The control window to test ScrollPane */
      Window* ctrlWin;
#endif // RB_SCROLLPANE_TEST

#ifdef RB_MULTICOLUMNLIST_TEST
      void createMultiColumnListTestWindow(void);
      void onAddItem(void);
      void addItem(const string&, const string&, const string&);

      /** The MultiColumnList widget */
      MultiColumnList* mcl;
      /** The window used to test MultiColumnList widget */
      Window* MultiColumnListWin;
      /** The control window used to test MultiColumnList widget */
      Window* MultiColumnListCtrlWin;
      /** The button that adds a label in the MultiColumnList <idget */
      PushButton* btnAddMclItem;
      /** The test to add in MultiColumnList first column */
      TextInput* tiMclCol1;
      /** The test to add in MultiColumnList second column */
      TextInput* tiMclCol2;
      /** The test to add in MultiColumnList third column */
      TextInput* tiMclCol3;
#endif // RB_MULTICOLUMNLIST_TEST

    private:
      bool onNetworkGameClicked(void);
      void setupMainMenu(void);

      /** The network game button, kept for testing it */
      BetaGUI::Button* btnNetworkGame;
      /** The local test button, kept for testing it */
      BetaGUI::Button* btnLocalTest;
      /** The Exit button, kept for testing it */
      BetaGUI::Button* btnExit;
      /** The window where the buttons are added */
      BetaGUI::Window* window;
    };
  }
}

#endif // GS_MAIN_MENU_H

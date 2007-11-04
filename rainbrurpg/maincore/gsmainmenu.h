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

/* Modifications :
 * - 20 set 2007 : Uses BetaGUI
 * - 22 jul 2007 : Moving the connection menu to gsConnection
 *
 */

#ifndef GS_MAIN_MENU_H
#define GS_MAIN_MENU_H

#include <hashpassword.h>

#include "gsmenubase.h"
#include "bgbutton.h"
#include "bgwindow.h"
#include "bglistener.h"

using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Core{

    /** The main menu gamestate
      *
      * The main menu is the first screen to appears when the game is 
      * launched. It provides 3 buttons : 
      * - Network game : you can play in a worldwide server
      * - Local test : You play alone to test the rendering engine
      * - Quit
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

    private:
      bool onNetworkGameClicked();
      void setupMainMenu();

      /** The network game button, kept for testing it */
      BetaGUI::Button* btnNetworkGame;
      /** The local test button, kept for testing it */
      BetaGUI::Button* btnLocalTest;
      /** The Exit button, kept for testing it */
      BetaGUI::Button* btnExit;
      /** The Button where the buttons are aded */
      BetaGUI::Window* window;
    };
  }
}

#endif // GS_MAIN_MENU_H

/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file gsconnection.h
  * Declares a gamestate that lets the user enter its username and password
  *
  * Modifications :
  * - 31 oct 2008 : Added a showMessageBox() call when connection fails
  * - 16 aug 2008 : Single file documentation
  * - 22 jul 2007 : Starting implementation
  *
  */

#ifndef GS_CONNECTION_H
#define GS_CONNECTION_H

#include <HashPassword.hpp>
//#include <Window.hpp>

#include "gsmenubase.h"
#include "vcconstant.h"
#include "guimanager.h"
#include "bglistener.h"

// Forward declarations
namespace BetaGUI {
  //  class TextInput;
}
namespace RainbruRPG{
  namespace OgreGui{
    class PushButton;
    class Window;
  }
}
// End of forward declarations

// A hack to make the object built
namespace BetaGUI{
  typedef void Button;
  typedef void TextInput;
}

using namespace RainbruRPG::OgreGui;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Core{

    /** The connection menu
      *
      * This is the first screen shown when the user choose the network
      * game. It provides a typical user name/password identification.
      *
      * \todo Must get rid of all these member pointers
      *
      */
    class gsConnection : public gsMenuBase, public BetaGUI::BetaGUIListener{
    public:
      gsConnection();
      virtual ~gsConnection();

      virtual void init();
      virtual void resume();
      virtual void pause();

      virtual void setupTabOrder();
      virtual void onButtonPress(BetaGUI::Button*);

    private:
      void onBackClicked(void);
      bool onQuitClicked();
      bool onConnectClicked();

      bool onCreateAccountClicked();
      bool onLostPasswordClicked();

      void setupConnectionMenu();

    };
  }
}

#endif // GS_CONNECTION_H

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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/* Modifications :
 * - 22 jul 2007 : Starting implementation
 *
 */

#ifndef GS_CONNECTION_H
#define GS_CONNECTION_H

#include <hashpassword.h>

#include "gsmenubase.h"
#include "vcconstant.h"
#include "guimanager.h"
#include "bglistener.h"

// Forward declarations
namespace BetaGUI {
  class TextInput;
}
namespace RainbruRPG{
  namespace OgreGui{
    class PushButton;
  }
}
// End of forward declarations

using namespace RainbruRPG::OgreGui;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Core{

    /** The connection menu
      *
      * This is the first screen shown when the user choose the network
      * game. It provides a typical user name/password identification.
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

      /** The connect button */
      PushButton* btnConnect;
      /** The create acount button */
      PushButton* btnCreateAccount;
      /** The lost password button */
      PushButton* btnLostPwd;
      /** The Back navigation button */
      PushButton* btnBack; 

      /** The main OgreGUI window */
      Window* window;
      /** The OgreGUI window containing the Back button */
      Window* winBack;
      /** The widget where the user name is entered */
      TextInput* tiUserName;
      /** The widget where the password is entered */
      TextInput* tiPassword;
    };
  }
}

#endif // GS_CONNECTION_H

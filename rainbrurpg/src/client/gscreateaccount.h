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

/** \file gscreateaccount.h
  * Declares a gamestate that lets the user create an account
  *
  * Modifications :
  * - 16 aug 2008 : Single file documentation
  * - 18 nov 2007 : Using OgreGUI
  * - 25 jul 2007 : Starting implementation
  *
  */

#ifndef GS_CREATE_ACCOUNT_H
#define GS_CREATE_ACCOUNT_H

#include <hashpassword.h>
#include <curlaccountadd.h>

#include "gsmenubase.h"
#include "vcconstant.h"
#include "guimanager.h"
#include "bglistener.h"

// Forward declarations
/*namespace BetaGUI{
  class Window;
  class Button;
  class TextInput;
}
*/
namespace RainbruRPG{
  namespace OgreGui{
    class Label;
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

using namespace BetaGUI;
using namespace RainbruRPG::OgreGui;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Core{

    /** The game state provided to submit an account creation
      *
      * This class show a creen (CEGUI layout) used to submit
      * an account creation to the administration site.
      *
      * \todo Must get rid of all these member pointers
      *
      */
    class gsCreateAccount : public gsMenuBase, public BetaGUI::BetaGUIListener{
    public:
      gsCreateAccount(void);
      virtual ~gsCreateAccount(void);

      virtual void init(void);
      virtual void resume(void);
      virtual void pause(void);

      virtual void setupTabOrder(void);
      virtual void onButtonPress(BetaGUI::Button*);

   private:
      void onBackClicked(void);
      void onSubmitClicked(void);

      void setupCreateAccountMenu(void);

      /** The create account window */
      RainbruRPG::OgreGui::Window* window;
      /** The back button window */
      RainbruRPG::OgreGui::Window* winBack;
      /** The back button */
      PushButton* btnBack;
      /** The submit button */
      PushButton* btnSubmit;

      /** The help label */
      Label* labHelp;
      /** The name label */
      Label* labName;
      /** The password first entry label */
      Label* labPwd1;
      /** The password second entry label */
      Label* labPwd2;
      /** The email address label */
      Label* labMail;

      /** The name text input */
      TextInput* tiName;
      /** The password first entry text input */
      TextInput* tiPwd1;
      /** The password second entry text input */
      TextInput* tiPwd2;
      /** The email address text input */
      TextInput* tiMail;

    };
  }
}

#endif // GS_CREATE_ACCOUNT_H

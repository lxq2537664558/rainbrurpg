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
 * - 22 jul 2007 : Starting implementation
 *
 */

#ifndef GS_CONNECTION_H
#define GS_CONNECTION_H

#include <CEGUI/CEGUISystem.h>
#include <CEGUI/CEGUIRenderer.h>
#include <CEGUI/CEGUIEventArgs.h>
#include <CEGUI/CEGUIEvent.h>
#include <CEGUI/elements/CEGUIEditbox.h>

#include <hashpassword.h>

#include "gsmenubase.h"
#include "vcconstant.h"
#include "guimanager.h"

using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Core{

    /** The connection menu
      *
      * This is the first screen shown when the user choose the network
      * game. It provides a typical user name/password identification.
      * The CEGUI loaded is connection.layout (in data/gui/layout/ directory).
      *
      */
    class gsConnection : public gsMenuBase{
    public:
      virtual ~gsConnection();
      gsConnection();

      virtual void init();
      virtual void resume();

      virtual void setupTabOrder();


    private:
      bool onQuitClicked(const CEGUI::EventArgs&);
      bool onBackToMainClicked(const CEGUI::EventArgs&);
      bool onConnectClicked(const CEGUI::EventArgs&);

      bool onCreateAccountClicked(const CEGUI::EventArgs&);
      bool onLostPasswordClicked(const CEGUI::EventArgs&);

      void setupConnectionMenu();

      /** The TextEdit where we enter the account name */
      CEGUI::Window* nameWidget;
      /** The TextEdit where we enter the account password */
      CEGUI::Window* pwdWidget;



    };
  }
}

#endif // GS_CONNECTION_H

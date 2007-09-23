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
 * - 25 jul 2007 : Starting implementation
 *
 */

#ifndef GS_CREATE_ACCOUNT_H
#define GS_CREATE_ACCOUNT_H

#include <CEGUI/CEGUI.h>

#include <hashpassword.h>
#include <curlaccountadd.h>

#include "gsmenubase.h"
#include "vcconstant.h"
#include "guimanager.h"

using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Core{

    /** The game state provided to submit an account creation
      *
      * This class show a creen (CEGUI layout) used to submit
      * an account creation to the administration site.
      *
      */
    class gsCreateAccount : public gsMenuBase{
    public:
      gsCreateAccount();
      virtual ~gsCreateAccount();

      virtual void init();
      virtual void resume();

       virtual void setupTabOrder();

   private:
      bool onBackClicked(const CEGUI::EventArgs&);
      bool onSubmitClicked(const CEGUI::EventArgs&);

      void setupCreateAccountMenu();

    };
  }
}

#endif // GS_CREATE_ACCOUNT_H
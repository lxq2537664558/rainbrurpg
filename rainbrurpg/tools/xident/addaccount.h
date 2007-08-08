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
 * - 08 aug 2007 : Starting implementation
 *
 */

#ifndef XIDENT_ADD_ACCOUNT_H
#define XIDENT_ADD_ACCOUNT_H

#include <fox-1.6/fx.h>
#include <curlserveradd.h>
#include <httpresponse.h>

using namespace FX;
using namespace RainbruRPG::Network;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Gui{

    /** The xident add account dialog
      *
      * It is used by the xIdent tool to add an account using
      * curlAccountAdd.
      *
      */
    class AddAccount : public FXDialogBox{
      FXDECLARE(AddAccount)
    public:
      AddAccount(FXApp *);
      ~AddAccount();

      virtual void create();

      long onNotYetImplemented(FXObject *,FXSelector,void*);

      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXDialogBox::ID_LAST,
	/** Setting the new value to  FXDialogBox::ID_LAST */
	ID_LAST
      };

    };
  }
}

#endif // XIDENT_ADD_ACCOUNT_H

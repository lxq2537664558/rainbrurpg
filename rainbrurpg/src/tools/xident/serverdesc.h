/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file tools/xident/serverdesc.h
  * Declares a dialog used to show the server description
  *
  * Modifications :
  * - 22 sep 2008 : Single file documentation
  *
  */

#ifndef XIDENT_SERVER_DESC_DIALOG_H
#define XIDENT_SERVER_DESC_DIALOG_H

#include <fox-1.6/fx.h>

#include <serverlistitem.h>
#include <stringconv.h>

#include "xmlserverlist.h"

using namespace FX;
using namespace RainbruRPG::Core;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Gui{

    /** The xident description server dialog
      *
      * It is used by the xIdent tool to show the description of a server.
      * The description is read-only. The design of this dialog is very 
      * similar to the ServerTechNote one.
      *
      * \sa ServerTechNote
      *
      */
    class ServerDesc : public FXDialogBox{
      FXDECLARE(ServerDesc)
    public:
      ServerDesc(FXApp *, FXString);
      ~ServerDesc();

      virtual void create();

      long onNotYetImplemented(FXObject *,FXSelector,void*);
      long onOkClicked(FXObject *,FXSelector,void*);

      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXDialogBox::ID_LAST,
	/** The OK button identifier */
	ID_BTN_OK,
	/** Setting the new value to  FXDialogBox::ID_LAST */
	ID_LAST
      };


    private:
      /** Required or Undefined references */
      ServerDesc(){};
      /** Required or Undefined references */
      ServerDesc(const ServerDesc&);
      /** Required or Undefined references */
      ServerDesc &operator=(const ServerDesc&);

      FXString getServerDesc(FXString);

    };

  }
}


#endif // XIDENT_SERVER_DESC_DIALOG_H

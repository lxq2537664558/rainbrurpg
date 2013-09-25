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

#ifndef XIDENT_MODIFY_SERVER_H
#define XIDENT_MODIFY_SERVER_H

#include <fox-1.6/fx.h>
#include <httpresponse.h>
#include <xmlserverlist.h>
#include <curlservermodifclients.h>

using namespace FX;
using namespace RainbruRPG::Network;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Gui{

    /** The xident modify server dialog
      *
      * It is used by the xIdent tool to modify a server using
      * curlServerModify.
      *
      */
    class ModifyServer : public FXDialogBox{
      FXDECLARE(ModifyServer)
    public:
      ModifyServer(FXApp *, FXString);
      ~ModifyServer();

      virtual void create();

      long onNotYetImplemented(FXObject *,FXSelector,void*);
      long onOkClicked(FXObject *,FXSelector,void*);
      long onCancelClicked(FXObject *,FXSelector,void*);
      long onSpinnerClicked(FXObject *,FXSelector,void*);

      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXDialogBox::ID_LAST,
	/** The OK button identifier */
	ID_BTN_OK,
	/** The cencel button identifier */
	ID_BTN_CANCEL,
	/** Setting the new value to  FXDialogBox::ID_LAST */
	ID_SPI_CLI,
	/** Setting the new value to  FXDialogBox::ID_LAST */
	ID_LAST
      };


    private:
      /** Required or Undefined references */
      ModifyServer(){};
      /** Required or Undefined references */
      ModifyServer(const ModifyServer&);
      /** Required or Undefined references */
      ModifyServer &operator=(const ModifyServer&);

      /** The server we're about to modify */
      FXString serverName;

      /** The actual number of client
        *
	* This value is submitted with the CurlServerModifClients
	* when we click OK
	*
	*/
      int actClients;
    };

  }
}

#endif // XIDENT_MODIFY_SERVER_H

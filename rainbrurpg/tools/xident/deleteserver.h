/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file tools/xident/deleteserver.h
  * Declares a dialog used to delete a server
  *
  * Modifications :
  * - 22 sep 2008 : Single file documentation
  *
  */

#ifndef XIDENT_DELETE_SERVER_H
#define XIDENT_DELETE_SERVER_H

#include <fox-1.6/fx.h>
#include <string>
#include <curlserverdelete.h>
#include <httpresponse.h>

using namespace std;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Gui{

    /** The xident delete server dialog
      *
      * It is used by the xIdent tool to delete a server using
      * curlServerDelete. The constructor must be called with a
      * server name as second parameter.
      *
      */
    class DeleteServer : public FXDialogBox{
      FXDECLARE(DeleteServer)
    public:
      DeleteServer(FXApp *, FXString);
      ~DeleteServer();

      virtual void create();

      long onNotYetImplemented(FXObject *,FXSelector,void*);
      long onOkClicked(FXObject *,FXSelector,void*);
      long onCancelClicked(FXObject *,FXSelector,void*);

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
	ID_LAST
      };

    private:
      /** Required or Undefined references */
      DeleteServer(){};
      /** Required or Undefined references */
      DeleteServer(const DeleteServer&);
      /** Required or Undefined references */
      DeleteServer &operator=(const DeleteServer&);
      /** The name of the server that will be deleted
        *
	* This variable is initialized by the constructor, with the 
	* second parameter value.
	*
	*/
      FXString serverName;

    };
  }
}

#endif // XIDENT_DELETE_SERVER_H


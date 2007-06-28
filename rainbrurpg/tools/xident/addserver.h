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
 * - 28 jun 2007 : Adding the 'uniquename' and 'type' column
 * - 29 may 2007 : Adding the 'ftp' column
 *
 */

#ifndef XIDENT_ADD_SERVER_H
#define XIDENT_ADD_SERVER_H

#include <fox-1.6/fx.h>
#include <curlserveradd.h>
#include <httpresponse.h>

using namespace FX;
using namespace RainbruRPG::Network;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Gui{

    /** The xident add server dialog
      *
      * It is used by the xIdent tool to add a server using
      * curlServerAdd.
      *
      */
    class AddServer : public FXDialogBox{
      FXDECLARE(AddServer)
    public:
      AddServer(FXApp *);
      ~AddServer();

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
      AddServer(){};
      /** Required or Undefined references */
      AddServer(const AddServer&);
      /** Required or Undefined references */
      AddServer &operator=(const AddServer&);

      bool controls();
      void addServer();

      /** The widget containing the server name */
      FXTextField* tfServerName;
      /** The widget containing the server's unique name */
      FXTextField* tfServerUniqueName;
      /** The widget containing the server IP adress */
      FXTextField* tfServerIp;
      /** The widget containing the server UDP port */
      FXTextField* tfServerPort;
      /** The widget containing the server FTP port */
      FXTextField* tfServerFtp;
      /** The widget containing the server maximum allowed client */
      FXTextField* tfServerCli;
      /** The widget containing the server description */
      FXText* txtDesc;
      /** The widget containing the server technical note */
      FXText* txtTech;
      /** The combo box containint the possible server's types */
      FXComboBox* cbServerType;
      /** An error string used for validation error
        *
	* This string is fed up by the controls() function to send
	* an error message if the controls failed. The onOkClicked()
	* function shows it in a fox message box if the validation failed.
	*
	*/
      const char* errorMsg;
    };

  }
}

#endif // XIDENT_ADD_SERVER_H

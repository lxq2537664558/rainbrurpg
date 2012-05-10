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

/** \file tools/netflooder/connectionpanel.h
  * Declares the netFlooder connection panel
  *
  * Modifications :
  * - 20 sep 2008 : Single file documentation
  * - 21 mar 2007 : Fix a bug in getSelectedServerName()
  *
  */

#ifndef CONNECTION_PANEL_H
#define CONNECTION_PANEL_H

#include <fox-1.6/fx.h>

#include <ServerListItem.hpp>
#include <XmlServerList.hpp>
#include <StringConv.hpp>

#include <string>

using namespace std;
using namespace RainbruRPG::Core;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Gui{
    /** The netFlooder connection panel
      *
      * It shows a table containing the server list. The user can select
      * a server to flood.
      *
      * This panel send message telling to the sender to switch to the
      * WaitingPanel and launching connection. The sender and ID are set in 
      * the constructor.
      *
      */
    class ConnectionPanel : public FX::FXPacker {
      FXDECLARE(ConnectionPanel)
	
    public:
      ConnectionPanel(FXComposite* parent=0, FXuint opts=0, 
		      FXObject* sender=NULL, FXuint id=0); 
      virtual ~ConnectionPanel(); 

      virtual void create();
      
      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXPacker::ID_LAST,
	/** The refresh button identifier */
	ID_BTN_REFRESH,
	/** The connect button identifier */
	ID_BTN_CONNECT,
        /** The server table identifier */
	ID_TABLE,
	/** Setting the new value to  FXMainWindow::ID_LAST*/
	ID_LAST
      };
 
      long onNotYetImplemented(FXObject *,FXSelector,void*);
      long onRefreshClicked(FXObject *,FXSelector,void*);
      long onConnectClicked(FXObject *,FXSelector,void*);
      long onTableSelectionChange(FXObject *,FXSelector,void*);

    private:
      void changeToWaitingPanel(ServerListItem*);
      void createTableHeader();
      void addServer(RainbruRPG::Network::Ident::ServerListItem*);
      void feedTable();
      FXString getSelectedServerName();

      /** The account list */
      xmlServerList* serverList;
      /** The server's table */
      FXTable* table;
      /** Contains the selected server's name */
      FXString selServer;
      /** The connect button
        *
	* It is kept to be able to enable/disable it
	*
	*/
      FXButton* btnConnect;
      /** The sender used to send FOX messages
        *
	* This is set by the constructor parameter and cannot be NULL.
	*
	*/
      FXObject* sender;
      /** The message identifier used to send FOX messages
        *
	* This is set by the constructor parameter and cannot be NULL.
	*
	*/
      FXuint messageId;
    }; 
  }
}

#endif // CONNECTION_PANEL_H

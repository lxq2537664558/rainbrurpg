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
 * - 04 aug 2007 : Now using ServerListItem
 * - 28 jun 2007 : Adding the 'uniquename' and 'type' column
 * - 29 may 2007 : Adding the 'ftp' column
 *
 */

#ifndef FOX_SERVER_LIST_H
#define FOX_SERVER_LIST_H

#include <fox-1.6/fx.h>

#include <string>

#include <serverlistitem.h>
#include <xmlserverlist.h>
#include <stringconv.h>

using namespace std;
using namespace RainbruRPG::Core;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Gui{
    /** The xIdent server list
      *
      * It shows a table containing the server list. Some buttons are
      * available to add, edit or delete a given server.
      *
      */
    class FoxServerList : public FX::FXPacker {
      FXDECLARE(FoxServerList)
	
    public:
      FoxServerList(FXComposite* parent=0, FXuint opts=0); 
      virtual ~FoxServerList(); 

      virtual void create();
      
      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXPacker::ID_LAST,
	/** The Add server button identifier */
	ID_ADD,
	/** The Delete server button identifier */
	ID_DEL,
	/** The edit server button identifier */
	ID_EDIT,
	/** The server table identifier */
	ID_TABLE,
	/** The description button identifier */
	ID_DESC,
	/** The description button identifier */
	ID_TECH,
	/** Setting the new value to  FXMainWindow::ID_LAST*/
	ID_LAST
      };
 
      long onNotYetImplemented(FXObject *,FXSelector,void*);
      long onShowAddServerDialog(FXObject *,FXSelector,void*);
      long onShowDeleteServerDialog(FXObject *,FXSelector,void*);
      long onShowEditServerDialog(FXObject *,FXSelector,void*);
      long onShowDescriptionDialog(FXObject *,FXSelector,void*);
      long onShowTechNoteDialog(FXObject *,FXSelector,void*);
      long onTableSelectionChange(FXObject *,FXSelector,void*);

    private:
      void feedTable();
      void setServerNumber(unsigned int);
      void addServer(RainbruRPG::Network::Ident::ServerListItem*);
      void createTableHeader();
      FXString getSelectedServerName();
      void refresh();



      /** The account list */
      xmlServerList* serverList;
      /** The account's table */
      FXTable* table;
      /** The label where we print the total number of server */
      FXLabel* labPlCount;
      /** Contains the currently selected server's name
        *
	* If a server is selected, it contains its name. If no server
	* is selected, it is an empty string. The value is changed in 
	* onTableSelectionChange(), using getSelectedServerName() to
	* retrieve the current server's name.
	*
	*/
      FXString selServer;
      /** The 'delete' button
        *
	* I keep it to be able enable/disable it in the onTableSelectionChange
	* callback.
	*
	*/
      FXButton* btnDelete;
      /** The 'Edit' button
        *
	* I keep it to be able enable/disable it in the onTableSelectionChange
	* callback.
	*
	*/
      FXButton* btnEdit;
      /** The 'Description' button
        *
	* I keep it to be able enable/disable it in the onTableSelectionChange
	* callback.
	*
	*/
      FXButton* btnDesc;
      /** The 'TechNote' button
        *
	* I keep it to be able enable/disable it in the onTableSelectionChange
	* callback.
	*
	*/
      FXButton* btnTech;
    }; 

  }
}

#endif // FOX_ACCOUNT_LIST_H

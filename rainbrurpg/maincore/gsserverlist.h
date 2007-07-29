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
 * - 27 jul 2007 : Starting implementation
 *
 */

#ifndef GS_SERVER_LIST_H
#define GS_SERVER_LIST_H

#include <CEGUI/CEGUI.h>

#include <xmlserverlist.h>

#include "gsmenubase.h"
#include "vcconstant.h"
#include "guimanager.h"

using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Core{

    /** Defines the direction of a row selection change
      *
      */
    typedef enum{
      RSD_UP,
      RSD_DOWN
    }tRowSelectionDirection;

    /** The server list menu
      *
      * If the account connection is accepted, this list appears. Here you
      * can select a server and connect your client to it.
      *
      */
    class gsServerList : public gsMenuBase{
    public:
      gsServerList();
      virtual ~gsServerList();

      virtual void init();
      virtual void resume();

      virtual void setupTabOrder();

      bool onBackClicked(const CEGUI::EventArgs&);
      bool onRefreshClicked(const CEGUI::EventArgs&);
      bool onConnectClicked(const CEGUI::EventArgs&);

      bool onListSelectionChange(const CEGUI::EventArgs&);
      bool onListDoubleClick(const CEGUI::EventArgs&);
      bool onListKeyDown(const CEGUI::EventArgs&);

    private:
      void setupServerList();
      void feedList();

      void selectNext();
      void selectPrevious();
      int getSelectedRow();
      void setRowSelectState(int, bool, tRowSelectionDirection);

      /** The server list widget
        *
	* It is initialized in the setupServerList() function.
        *
	* \sa setupServerList().
	*
        */
      CEGUI::MultiColumnList* serverList;
      /** Load and manage the server list 
        *
	* It is used to feed the serverList widget in the feedList()
	* function. It is initialized 
	* in gsServerList() and destroyed in ~gsServerList()
	*
	* \sa serverList, feedList(), gsServerList(), ~gsServerList().
	*
        */
      xmlServerList* xml;

      /** The connect button
        *
	* It is kept as a class member to be hide and show acording to
	* the serverlist selection.
	*
	*/
      CEGUI::Window* btnConnect;
    };
  }
}


#endif // GS_SERVER_LIST_H

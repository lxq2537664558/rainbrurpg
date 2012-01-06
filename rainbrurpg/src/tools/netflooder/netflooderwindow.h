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

/** \file tools/netflooder/netflooderwindow.h
  * Declares the NetFlooder's main window
  *
  * Modifications :
  * - 22 sep 2008 : Single file documentation
  * - 27 mar 2007 : Add the FloodManel
  *
  */
 
#ifndef NET_FLOODER_WINDOW_H
#define NET_FLOODER_WINDOW_H

#include <fox-1.6/fx.h>
#include <sigc++/sigc++.h>

#include "enetflooderclient.h"
#include "waitingpanel.h"
#include "floodpanel.h"

namespace RainbruRPG{
  namespace Gui{

    /** The netflooder main window
      *
      * The netflooder is a tool used to flood a selected server. For
      * security reason, the selected server must accept flooder 
      * connections.
      *
      */
    class NetFlooderWindow : public FX::FXMainWindow {
      FXDECLARE(NetFlooderWindow)
	
    public:
      NetFlooderWindow(FXApp *); 
      virtual ~NetFlooderWindow(); 

      virtual void create();
      
      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXMainWindow::ID_LAST,
	/** The Identifier of the Help/About menu item */
	ID_HELP_ABOUT,
	/** The Identifier of the Tool/Server menu item */
	ID_TOOL_SERVER,
	/** The Identifier of the Tool/Waiting menu item */
	ID_TOOL_WAITING,
	/** The Identifier of the Tool/Flooding menu item */
	ID_TOOL_FLOOD,
	/** The show waiting panel identifier */
	ID_SHOW_WAITING_PANEL,
	/** Setting the new value to  FXMainWindow::ID_LAST*/
	ID_LAST
      };
 
      long onNotYetImplemented(FXObject *,FXSelector,void*);

      long onHelpAbout(FXObject *,FXSelector,void*);
      long onManageServer(FXObject *,FXSelector,void*);
      long onManageWaiting(FXObject *,FXSelector,void*);
      long onManageFlood(FXObject *,FXSelector,void*);
      long onShowWaitingPanel(FXObject *,FXSelector,void*);

      void slotConnectionRefused();
      void slotConnectionAccepted();
 
    private:
      /** Required or Undefined references */
      NetFlooderWindow(){};
      /** Required or Undefined references */
      NetFlooderWindow(const NetFlooderWindow&);
      /** Required or Undefined references */
      NetFlooderWindow &operator=(const NetFlooderWindow&);

      /** The child switcher's Id 
        *
	* This ID is incremented for each switcher child we create. So we have
	* the id of the newly created switcher panel
	*
	* \sa panelHelpId, panelAccountId, panelServerId.
	*
	*/
      FXint switcherChildId;

      /** The Id if the Connection switcher's panel
        *
	* Contains the unique identifier of this panel. Its value is taken from
	* switcherChildId during creation of the panel.
	*
	* \sa switcherChildId.
	*
	*/
      FXint panelConnectionId;

      /** The Id if the Waiting witcher's panel
        *
	* Contains the unique identifier of this panel. Its value is taken from
	* switcherChildId during creation of the panel.
	*
	* \sa switcherChildId.
	*
	*/
      FXint panelWaitingId;

      /** The Id if the Flood witcher's panel
        *
	* Contains the unique identifier of this panel. Its value is taken from
	* switcherChildId during creation of the panel.
	*
	* \sa switcherChildId.
	*
	*/
      FXint panelFloodId;

      /** The enet client
        *
	*/
      EnetFlooderClient * client;

      /** The panel for waiting connection
        * 
	*/
      WaitingPanel* wp;

      /** The panel for flooding a selected server
        * 
	*/
      FloodPanel* fp;


    protected:
      /** The file menu panel
        *
	* It is defines protected to prevent SEGFAULTS
	*
	*/
      FXMenuPane* filemenu;
      /** The help menu panel
        *
	* It is defines protected to prevent SEGFAULTS
	*
	*/
      FXMenuPane* helpmenu;
      /** The manage menu panel
        *
	* It is defines protected to prevent SEGFAULTS
	*
	*/
      FXMenuPane* toolmenu;


      /** The switcher 
        *
	* This FOX widget is a layout used to add several widgets and showing
	* only one. 
	*/
      FXSwitcher* switcher;
    }; 
  }
}

#endif// NET_FLOODER_WINDOW_H




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
 * - 19 jul 2007 : Adds a 'persolist' menu item
 *
 */

#include <fox-1.6/fx.h>

#include "foxaccountlist.h"
#include "foxserverlist.h"
#include "foxpersolist.h"

namespace RainbruRPG{
  namespace Gui{

    /** The xIdent main window
      *
      *
      */
    class XIdentWindow : public FX::FXMainWindow {
      FXDECLARE(XIdentWindow)
	
    public:
      XIdentWindow(FXApp *); 
      virtual ~XIdentWindow(); 

      virtual void create();
      
      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI,
	/** The Identifier of the Help/About menu item */
	ID_HELP_ABOUT,
	/** The Identifier of the Tool/Account menu item */
	ID_TOOL_ACCOUNT,
	/** The Identifier of the Tool/Account menu item */
	ID_TOOL_SERVER,
	/** The Identifier of the Tool/Persos menu item */
	ID_TOOL_PERSOS,
	/** Setting the new value to  FXMainWindow::ID_LAST*/
	ID_LAST
      };
 
      long onNotYetImplemented(FXObject *,FXSelector,void*);

      long onHelpAbout(FXObject *,FXSelector,void*);
      long onManageAccount(FXObject *,FXSelector,void*);
      long onManageServer(FXObject *,FXSelector,void*);
      long onManagePersos(FXObject *,FXSelector,void*);
   
    private:
      /** Required or Undefined references */
      XIdentWindow(){};
      /** Required or Undefined references */
      XIdentWindow(const XIdentWindow&);
      /** Required or Undefined references */
      XIdentWindow &operator=(const XIdentWindow&);

      /** The child switcher's Id 
        *
	* This ID is incremented for each switcher child we create. So we have
	* the id of the newly created switcher panel
	*
	* \sa panelHelpId, panelAccountId, panelServerId.
	*
	*/
      FXint switcherChildId;
      /** The Id if the Help switcher's panel
        *
	* Contains the unique identifier of this panel. Its value is taken from
	* switcherChildId during creation of the panel.
	*
	* \sa switcherChildId.
	*
	*/
      FXint panelHelpId;
      /** The Id if the Account manager switcher's panel
        *
	* Contains the unique identifier of this panel. Its value is taken from
	* switcherChildId during creation of the panel.
	*
	* \sa switcherChildId.
	*
	*/
      FXint panelAccountId;
      /** The Id if the Server manager switcher's panel
        *
	* Contains the unique identifier of this panel. Its value is taken from
	* switcherChildId during creation of the panel.
	*
	* \sa switcherChildId.
	*
	*/
      FXint panelServerId;
      /** The Id if the Perso manager switcher's panel
        *
	* Contains the unique identifier of this panel. Its value is taken from
	* switcherChildId during creation of the panel.
	*
	* \sa switcherChildId.
	*
	*/
      FXint panelPersosId;

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

      /** The FoxAccountList pointer we keep */
      FoxAccountList* fal;

      /** The switcher 
        *
	* This FOX widget is a layout used to add several widgets and showing
	* only one. 
	*/
      FXSwitcher* switcher;
    }; 
  }
}





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

/* This code was found in the official CEGUI wiki :
 * http://www.cegui.org.uk/wiki/index.php/DialogSystem
 */

/* Modifications :
 * - 23 jul 2007 : Initial import fro CEGUI wiki
 *
 */

#ifndef _DialogSystem_h_
#define _DialogSystem_h_

#include <CEGUI/CEGUI.h>
#include <vector>

#include <logger.h>

namespace RainbruRPG{
  namespace Gui{

    /** An enumeration defining the DialogSystem events
      *
      * These events can be bind with the DialogSystem::bindEvent() function.
      *
      */
    typedef enum{ 
      DSE_OPEN,      //!< The dialog is open
      DSE_OK,        //!< The OK button was pressed
      DSE_CANCEL,    //!< The cancel button was pressed
      DSE_ESCAPE,    //!< The escape key was pressed
      DSE_APPLY,     //!< The apply button was pressed
      DSE_MODIFIED,  //!< A widget within the dialog was modified
    }tDialogSystemEvents;
    
    
    /** A class defining the bases of all CEGUI based dialogs
      *
      * You should not use this class directly, please use the 
      * GuiManager::showMessageBox function instead.
      *
      * \note This code was found in the official CEGUI wiki :
      * http://www.cegui.org.uk/wiki/index.php/DialogSystem
      *
      */
    class DialogSystem{
    public:
      
      DialogSystem();
      bool isModified();
      
      // Actions
      virtual bool doOpen();
      virtual bool doLoad();
      virtual bool doSave();
      virtual bool doClose();
      
      void initialise(const CEGUI::String&, bool, 
		      const CEGUI::String& parent="");

      void bindEvent(const CEGUI::String&, const CEGUI::String&, 
		     tDialogSystemEvents); 
      
    private:
      // Events
      bool onOpen(const CEGUI::EventArgs& e);
      bool onOk(const CEGUI::EventArgs& e);
      bool onCancel(const CEGUI::EventArgs& e);
      bool onEscape(const CEGUI::EventArgs& e);
      bool onApply(const CEGUI::EventArgs& e);
      bool onModified(const CEGUI::EventArgs& e);
      
      /// Handle to the parent
      CEGUI::String m_parent; 
      /// Handle to the window
      CEGUI::String m_window;
      /// Handle of the apply button
      CEGUI::String m_apply;  
      /// Whether the window is modal
      bool m_modal; 
    };
  }
}

#endif // _DialogSystem_h_


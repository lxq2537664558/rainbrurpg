/*
 *  Copyright 2006 Jerome PASQUIER
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

#ifndef _DIALOG_SYSTEM_H_
#define _DIALOG_SYSTEM_H_

#include "dialogsystem.h"

namespace RainbruRPG{
  namespace Gui{

    /** A dialog based on DialogSystem
      *
      * You should not use this class directly, please use the 
      * GuiManager::showMessageBox function instead.
      *
      * \note Do not create an instance of this class in the header 
      *       file. Create it when you need one. This block other 
      *       window's focus.
      *
      */
    class MessageBox : public DialogSystem{
    public:
      MessageBox();
      void initWindow(const CEGUI::String& parent="");
      
      void setMessage(const CEGUI::String&);
      void setTitle(const CEGUI::String&);

      const CEGUI::String& getMessage(void);
      const CEGUI::String& getTitle(void);
      
    protected:
      bool doLoad();
      bool doSave();
      
    private:
      /** The messagebox message */
      CEGUI::String message;
      /** The messagebox title content */
      CEGUI::String title;
           
      /** The data content */
      CEGUI::String dataString;
    };
  }
}

#endif // _DIALOG_SYSTEM_H_

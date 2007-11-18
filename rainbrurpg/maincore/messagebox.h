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
 * - 16 nov 2007 : No more based on DialogSystem (removed)
 * - 12 sep 2007 : Renamed from MessageBox to RbMessageBox
 * - 23 jul 2007 : Initial import fro CEGUI wiki
 *
 */

#ifndef _DIALOG_SYSTEM_H_
#define _DIALOG_SYSTEM_H_

#include <OgrePrerequisites.h> // For Ogre::String

#include <ogreGui/bglistener.h>

// Forward declarations
namespace BetaGUI {
  class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class Label;
    class PushButton;
  }
}
// End of forward declarations

using namespace Ogre;
using namespace BetaGUI;
using namespace RainbruRPG::OgreGui;

namespace RainbruRPG{
  namespace Gui{

    /** A dialog based on OgreGUI
      *
      * You should not use this class directly, please use the 
      * GuiManager::showMessageBox function instead.
      *
      * \note Renamed RbMessageBox because of cross-compilation name
      *       conflict
      *
      * \note Do not create an instance of this class in the header 
      *       file. Create it when you need one. This block other 
      *       window's focus.
      *
      */
    class RbMessageBox : public BetaGUIListener{
    public:
      RbMessageBox();
      void initWindow();
      
      void setMessage(const String&);
      void setTitle(const String&);

      const String& getMessage(void);
      const String& getTitle(void);
      
      void show(void);
      void hide(void);

      virtual void onButtonPress(Button *ref);

    private:
      /** The messagebox message */
      String message;
      /** The messagebox title content */
      String title;
           
      /** The data content */
      String dataString;

      /** The OgreGUI window shown by this dialog */
      Window* mWin;
      /** The label of this dialog */
      Label* caption;

      /** The width of this dialog in pixels */
      unsigned int width;
      /** The height of this dialog in pixels */
      unsigned int height;
    };
  }
}

#endif // _DIALOG_SYSTEM_H_

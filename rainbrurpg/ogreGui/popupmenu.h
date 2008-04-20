/*
 *  Copyright 2006-2008 Jerome PASQUIER
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
 * - 15 apr 2008 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_POPUP_MENU_H_
#define _OGRE_GUI_POPUP_MENU_H_

#include <OgreVector4.h>
#include <OgreOverlayContainer.h>
#include <list>

#include "widget.h" 
#include "skinmanager.h" // For OgreGuiSkinID
#include "mouseevent.h"

// Forward declaration
namespace BetaGUI {
  class Window;
}
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class Skin;
    class PopupMenuItem;
    class pmiTitle;
    class pmiSeparator;
  }
}
// End of Forward declaration

using namespace std;
using namespace BetaGUI;
using namespace RainbruRPG::OgreGui;

namespace RainbruRPG{
  namespace OgreGui{

    /** A list of items for the PopupMenu class */
    typedef list<PopupMenuItem*> tPopupMenuItemList;

    /** A popup menu
      *
      * A widget used to show contextual menus, with a title item only
      * if you provide a non-null string to the constructor.
      *
      */
    class PopupMenu : public Widget{
    public:
      PopupMenu(Vector4, String, Widget*,
	   RainbruRPG::OgreGui::OgreGuiSkinID sid=OSI_PARENT);
      ~PopupMenu();

      void setCaption( const Ogre::String&);
      void setWidth(unsigned int);

      const Ogre::String& getCaption(void)const;
      unsigned int getWidth(void)const;

      virtual void draw(QuadRenderer*);

      const Ogre::Rectangle& getAbsCorners(void)const;

      void addItem(PopupMenuItem*);

      bool injectMouse(unsigned int, unsigned int, const MouseEvent&);

    protected:
      void makeCorners(void);

    private:
      /** The current skin */
      Skin* mSkin;
      /** The menu caption */
      String mCaption;
      /** The width of the menu in pixels */
      unsigned int mWidth;

      /** The list of items */
      tPopupMenuItemList mItemList;

      /** The absolute corners (from the screen start) */
      Ogre::Rectangle mAbsCorners;
      /** The title of this popup menu */
      pmiTitle* mTitle;
      /** The separator under the title */
      pmiSeparator* mSeparator;
    };
  }
}

#endif // _OGRE_GUI_POPUP_MENU_H_

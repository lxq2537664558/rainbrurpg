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
 * - 16 apr 2008 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_POPUP_MENU_ITEM_TITLE_H_
#define _OGRE_GUI_POPUP_MENU_ITEM_TITLE_H_

#include "popupmenuitem.h"

#include <OgreString.h>


// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
  }
}
// End of forward declarations

namespace RainbruRPG{
  namespace OgreGui{

    /** A title item for PopupMenu widget
      *
      */
    class pmiTitle : public PopupMenuItem{
    public:
      pmiTitle(const Ogre::String&);
      virtual ~pmiTitle();

      virtual void draw( QuadRenderer* qr);

    private:
      Ogre::String mCaption;
    };

  }
}




#endif // _OGRE_GUI_POPUP_MENU_ITEM_TITLE_H_

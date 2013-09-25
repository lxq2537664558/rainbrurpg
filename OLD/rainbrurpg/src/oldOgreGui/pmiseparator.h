/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file pmiseparator.h
  * Declares a separator for popup menu 
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 19 apr 2008 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_POPUP_MENU_ITEM_SEPARATOR_H_
#define _OGRE_GUI_POPUP_MENU_ITEM_SEPARATOR_H_


#include "popupmenuitem.h"
#include "mouseevent.h"

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
  }
}
// End of forward declarations

namespace RainbruRPG{
  namespace OgreGui{

    /** A separator for PopupMenu widget
      *
      */
    class pmiSeparator : public PopupMenuItem{
    public:
      pmiSeparator();
      virtual ~pmiSeparator();

      virtual void draw( QuadRenderer* );
      virtual bool injectMouse(unsigned int, unsigned int, const MouseEvent&);

    };
  }
}
#endif // _OGRE_GUI_POPUP_MENU_ITEM_SEPARATOR_H_

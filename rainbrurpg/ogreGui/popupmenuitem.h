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

#ifndef _OGRE_GUI_POPUP_MENU_ITEM_H_
#define _OGRE_GUI_POPUP_MENU_ITEM_H_

namespace RainbruRPG{
  namespace OgreGui{

    /** Base class for all menu items
      *
      */
    class PopupMenuItem{
    public:
      PopupMenuItem();
      virtual ~PopupMenuItem();

      void setHeight(unsigned int);
      unsigned int getHeight(void)const;

      /** Draw this item
        *
	* \note The drawingdev feature of the given QuadRenderer should
	*       be set to the top left corner of this menu
	*
	*/
      void draw( QuadRenderer* qr)=0;

    private:
      /** The height of the item in pixels */
      unsigned int mHeight;
    };

  }
}

#endif // _OGRE_GUI_POPUP_MENU_ITEM_H_

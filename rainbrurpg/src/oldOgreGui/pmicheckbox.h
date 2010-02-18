/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file pmicheckbox.h
  * Declares a popum menu item containing a check box
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 18 apr 2008 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_POPUP_MENU_ITEM_CHECKBOX_H_
#define _OGRE_GUI_POPUP_MENU_ITEM_CHECKBOX_H_

#include "popupmenuitem.h"
#include "mouseevent.h"

#include <OgreTexture.h>
#include <sigc++/sigc++.h>

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
  }
}
// End of forward declarations

using namespace Ogre;

namespace RainbruRPG{
  namespace OgreGui{

    /** A popup menu item that contains a CheckBox
      *
      */
    class pmiCheckBox : public PopupMenuItem{
    public:
      /** Defines a signal returning void with an integer parameter */
      typedef sigc::signal<void, int> tVoidIntSignal;

      pmiCheckBox(const Ogre::String&);
      virtual ~pmiCheckBox();

      virtual void draw( QuadRenderer* qr);

      void setCaption(const Ogre::String&);
      const Ogre::String& getCaption(void)const;
      virtual bool injectMouse(unsigned int, unsigned int,const MouseEvent& );

      void toggleCheck(void);
      /** A signal emitted when the check value changed
        *
	* The \c int parameter is the new value of mCheck;
	*
	*/
      tVoidIntSignal sigValueChanged;

    private:
      /** This item's caption */
      Ogre::String mCaption;
      /** Is this item checked */
      bool mCheck;
      /** The texture used to draw checked item */
      static TexturePtr mTxtOn;
      /** The texture used to draw unchecked item */
      static TexturePtr mTxtOff;

    };

  }
}


#endif // _OGRE_GUI_POPUP_MENU_ITEM_CHECKBOX_H_
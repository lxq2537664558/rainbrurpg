/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file sonavigation.h
  * Declares a skin that draw navigation buttons
  *
  * \note We must scope the Rectangle class with its namespace in this 
  *       file to avoid complications when cross-compiling to Win32
  *       platform.
  *
  * Modifications :
  * - 23 sep 2008 : \ref 
  *                 RainbruRPG::OgreGui::soNavigation::getVScrollBarMinHeight
  *                 "getVScrollBarMinHeight()" and 
  *                 \ref 
  *                 RainbruRPG::OgreGui::soNavigation::getHScrollBarMinWidth 
  *                 "getHScrollBarMinWidth()" added.
  * - 30 aug 2008 : Single file documentation
  * - 02 nov 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_SKIN_NAVIGATION_H_
#define _OGRE_GUI_SKIN_NAVIGATION_H_

#include "skin.h"

#include <OgreVector4.h>
#include <OgreTexture.h>

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class Font;
    class QuadRenderer;
    class TextSettings;
    class VScrollBar;
    class HScrollBar;
    class MultiColumnList;
    class PopupMenu;
    class ToolTip;
  }
}
// End of forward declarations

using namespace Ogre;
using namespace RainbruRPG::OgreGui;

namespace RainbruRPG{
  namespace OgreGui{

    /** A skin based on SkinOverlay, drawing navigation buttons
      *
      * This skin can only create PushButton. The other widgets 
      * aren't not supported. Only the window widget can be usefull
      * as it is a container for PushButton.
      *
      */
    class soNavigation : public Skin{

    public:
      soNavigation();
      virtual ~soNavigation();

      virtual void drawWindow(QuadRenderer*, Ogre::Rectangle, String);
      virtual void drawPushButton(QuadRenderer*,Vector4, String, Window*, 
				  bool, bool);
      virtual void drawLabel(QuadRenderer* qr, Ogre::Rectangle dim, 
			     String caption, Window* parent);

      virtual int getVScrollBarMinHeight(void);
      virtual int getHScrollBarMinWidth(void);

    private:
      /** The font used in PushButtons */
      TextSettings* tsPushButton;

      /** The texture of the push button background */
      TexturePtr mPushButtonTexture;
      /** The texture of the active push button background */
      TexturePtr mPushButtonActiveTexture;

      /** The text setting for drawing label caption */
      TextSettings* tsLabel;
    };
  }
}
#endif // _OGRE_GUI_SKIN_NAVIGATION_H_

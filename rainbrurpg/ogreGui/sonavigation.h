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
 * - 02 nov 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_SKIN_OVERLAY_NAVIGATION_H_
#define _OGRE_GUI_SKIN_OVERLAY_NAVIGATION_H_

#include "skinoverlay.h"

#include <OgreVector4.h>
#include <OgreTexture.h>

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class Font;
    class QuadRenderer;
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
    class soNavigation : public SkinOverlay{

    public:
      soNavigation();

      virtual void drawWindow(QuadRenderer*,Rectangle, String);
      virtual void drawPushButton(QuadRenderer*,Vector4, String, Window*, bool);
      virtual void drawResizeGrip(QuadRenderer*, Vector4, bool);
      virtual void drawTitleBar(QuadRenderer*, Vector4, String, bool);

      virtual void createDialog(String, Vector4, String ,BetaGUI::GUI*);
      virtual void createTextInput(String, Vector4, String, Window*);
      virtual void createLabel(String, Vector4, String, Window*);
      virtual void createVerticalScrollbar(const String&, Vector4, Window*);

    private:
      /** The font used in PushButtons */
      OgreGui::Font* buttonFont;

      /** The texture of the push button background */
      TexturePtr mPushButtonTexture;
      /** The texture of the active push button background */
      TexturePtr mPushButtonActiveTexture;
    };
  }
}
#endif // _OGRE_GUI_SKIN_OVERLAY_NAVIGATION_H_

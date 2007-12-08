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
 * - 27 sep 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_SKIN_OVERLAY_BETA_GUI_H_
#define _OGRE_GUI_SKIN_OVERLAY_BETA_GUI_H_

#include "skinoverlay.h"

#include <OGRE/OgreVector4.h>


// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class QuadRenderer;
    class Font;
  }
}
// End of forward declarations


using namespace Ogre;

namespace RainbruRPG{
  namespace OgreGui{

    /** A skin based on SkinOverlay, drawing like BetaGUI does
      *
      */
    class soBetaGui : public SkinOverlay{
    public:
      soBetaGui();

      virtual void drawWindow(QuadRenderer*, Vector4, String);
      virtual void drawPushButton(QuadRenderer*,Vector4, String, Window*);
      virtual void drawResizeGrip(QuadRenderer*, Vector4, bool);
      virtual void drawTitleBar(QuadRenderer*, Vector4, String, bool);

      virtual void createDialog(String, Vector4, String ,BetaGUI::GUI*);
      virtual void createTextInput(String, Vector4, String, Window*);
      virtual void createLabel(String, Vector4, String, Window*);
      virtual void createVerticalScrollbar( const String&, Vector4, Window* );

    private:
      // ============= MATERIALS VALUES =================
      /** The window's material name */
      Ogre::String mnWindow;
      /** The text input's material name */
      Ogre::String mnTextInput;
      /** The dialog border material name */
      Ogre::String mnDialogBorder;


      // ============= FONTS VALUES =================
      /** The font name used to draw the PushButton */
      Ogre::String fnPushButton;
      /** The font size used to draw the PushButton */
      unsigned int fsPushButton;

      /** The font name used to draw captions */
      Ogre::String fnCaption;
      /** The font size used to draw captions */
      unsigned int fsCaption;

      /** The font used in window's titlebar */
      Font* titleFont;
    };

  }
}
#endif //_OGRE_GUI_SKIN_OVERLAY_BETA_GUI_H_

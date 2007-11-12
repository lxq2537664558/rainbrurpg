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
 * - 02 nov 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_SKIN_OVERLAY_NAVIGATION_H_
#define _OGRE_GUI_SKIN_OVERLAY_NAVIGATION_H_

#include "skinoverlay.h"

#include <OGRE/OgreVector4.h>

using namespace Ogre;

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

      virtual void createWindow(String, Vector4, String ,BetaGUI::GUI*);
      virtual void createResizeGrip(String, Vector4, Window*);
      virtual void createTitleBar(String, Vector4, String, Window*);
      virtual void createPushButton(String, Vector4, String, Window*);
      virtual void createTextInput(String, Vector4, String, Window*);
      virtual void createLabel(String, Vector4, String, Window*);

    private:
      /** The material name used to draw windows */
      Ogre::String mnWindow;
      /** The font name used to draw the PushButton */
      Ogre::String fnPushButton;
      /** The font size used to draw the PushButton */
      unsigned int fsPushButton;
  };
  }
}
#endif // _OGRE_GUI_SKIN_OVERLAY_NAVIGATION_H_

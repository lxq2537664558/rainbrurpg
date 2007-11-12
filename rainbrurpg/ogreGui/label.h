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
 * - 09 nov 2007 : Handling OgreSkinID in constructor
 * - 17 oct 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_LABEL_H_
#define _OGRE_GUI_LABEL_H_

#include <OGRE/OgreVector4.h>
#include <OGRE/OgreOverlayContainer.h>

#include "widget.h" 
#include "skinmanager.h" // For OgreGuiSkinID

using namespace RainbruRPG::OgreGui;

namespace RainbruRPG{
  namespace OgreGui{
    /** A simple widget drawing caption 
      *
      * This does not provide a frame or background.
      *
      */
    class Label : public Widget{
    public:
      Label(Vector4, String, BetaGUI::Window*,
	   RainbruRPG::OgreGui::OgreGuiSkinID sid=OSI_PARENT);
      ~Label();

      virtual void setTransparency(float);

    private:
    
      /** The overlay used to draw the text
        *
	*
	*/
      OverlayContainer* contentOverlay;
    };
  }
}

#endif // _OGRE_GUI_LABEL_H_

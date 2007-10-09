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

#ifndef _OGRE_GUI_SKIN_OVERLAY_H_
#define _OGRE_GUI_SKIN_OVERLAY_H_

#include "skin.h"

#include <string>
#include <OGRE/OgreOverlayContainer.h>

using namespace Ogre;

namespace RainbruRPG{
  namespace OgreGui{

    /** A skin base-class on Ogre::Overlay
      *
      * There is two createOverlay() functions depending wich is the
      * parent's type bacause Ogre::Overlay and Ogre::OverlayContainer 
      * cannot be casted. Internally, both use createOverlayImpl to 
      * graphically create the Overlay.
      *
      * For the buttons to get a mouse over effect, the materials names
      * must be \e basename and <em>basename.active</em>. The 
      * <em>.active</em> is mandatory and must be the last characters of
      * the material name.
      *
      */
    class SkinOverlay: public Skin{
    public:
      SkinOverlay(std::string n="unamedSkinOverlay");

      Ogre::OverlayContainer* getOverlayByName(Ogre::String);

      void createOverlay(String, Vector4,String, Overlay*);
      void createOverlay(String, Vector4, String, OverlayContainer*);

      void createCaption(String, Vector4, String, String, 
			 unsigned int, OverlayContainer*);

      virtual void activateButton(Button*, bool);

    protected:
      /** The resizeGrip material name*/
      Ogre::String mnResizeGrip;
      /** The TitleBar material name*/
      Ogre::String mnTitleBar;
      /** The PushButton material name*/
      Ogre::String mnPushButton;

    private:
      OverlayContainer* createOverlayImpl(String, Vector4, String);

    };

  }
}

#endif // _OGRE_GUI_SKIN_OVERLAY_H_

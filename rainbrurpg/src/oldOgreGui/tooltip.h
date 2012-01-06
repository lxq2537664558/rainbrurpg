/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file tooltip.h
  * Declares a tooltip widget for OgreGui
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 02 apr 2008 : Starting implementation
  *         
  */

#ifndef _OGRE_GUI_TOOL_TIP_H_
#define _OGRE_GUI_TOOL_TIP_H_

#include <ogreimport.h>

#include "widget.h" 
#include "skinmanager.h" // For OgreGuiSkinID

/** The transition time of the tooltip effect */
#define TOOLTIP_EFFECT_TIME 400

/** The transition lenght of the tooltip effect */
#define TOOLTIP_EFFECT_ALPHA 0.7f

// Forward declaration
namespace BetaGUI {
  class Window;
}
namespace RainbruRPG{
  namespace Core{
    class VelocityCalculator;
  }
  namespace OgreGui{
    class QuadRenderer;
    class Skin;
  }
}
// End of Forward declaration

namespace RainbruRPG{
  namespace OgreGui{

    /** A ToolTip widget with fade in/ fade out effect
      *
      * The fade in/out effect is automatically based on the show()
      * and hide() call.
      *
      */
    class ToolTip : public Widget{
    public:
      ToolTip(Vector4, String, BetaGUI::Window*,
	   RainbruRPG::OgreGui::OgreGuiSkinID sid=OSI_PARENT);
      ~ToolTip();

      virtual void draw(QuadRenderer*);

      const Ogre::String& getText(void)const;

      virtual void show(void);
      virtual void hide(void);

      float getAlpha(void)const;
      bool inTransition(void)const;

    private:
      /** The skin used to draw */
      Skin* mSkin;
      /** The text of this ToolTip */
      Ogre::String mText;

      /** The velocity calculator used to make a mouse over fade out effect */
      VelocityCalculator* mVelocityCalculator;
      /** Is a transition started ? */
      bool mTransition;
    };
  }
}

#endif // _OGRE_GUI_TOOL_TIP_H_

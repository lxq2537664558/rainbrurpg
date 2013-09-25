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

/** \file statuslabel.h
  * Declares a label showing status message
  *
  * Modifications :
  * - 03 sep 2008 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_STATUS_LABEL_H_
#define _OGRE_GUI_STATUS_LABEL_H_

#include <ogreimport.h>

#include "label.h"

/** How many milliseconds the text will be drawn before fading out */
#define STO_WAITING_FADE_TIME 3000

/** The time for complete fade out */
#define STO_FADE_TIME 500


// Forward declarations
namespace RainbruRPG{
  namespace Core{
    class VelocityCalculator;
  }
  namespace OgreGui{
    class TextSettings;
  }
}
// End of forward declarations

namespace RainbruRPG{
  namespace OgreGui{

    /** A label used to draw error messages in menu states
      *
      * This label is not affected by the global alpha value and provides
      * a temporary message, that fade out after \ref STO_WAITING_FADE_TIME
      * milliseconds waited. The fade out time is defined by 
      * \ref STO_FADE_TIME.
      *
      */
    class StatusLabel : public Label{
    public:
      StatusLabel(Vector4, String, BetaGUI::Window*,
	   RainbruRPG::OgreGui::OgreGuiSkinID sid=OSI_PARENT);
      ~StatusLabel();

      virtual void draw(QuadRenderer* qr);
      virtual void setCaption(const String&);

    private:

      /** The text setting for drawing label caption */
      TextSettings* tsLabel;

      /** The current alpha value */
      float mStatusAlpha;

      /** the velocity calculator need for transition */
      VelocityCalculator* vcStatus;
      /**  Is this label in fade out */
      bool isInFadeOut;
      /** Is this label in transition (in fade out or waiting for it) */
      bool isInTransition;
    };
  }
};

#endif // _OGRE_GUI_STATUS_LABEL_H_

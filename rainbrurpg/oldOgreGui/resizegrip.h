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

/** \file resizegrip.h
  * Declares a resize grip for windows
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 09 nov 2007 : Handling OgreSkinID in constructor
  * - 04 oct 2007 : Now using skin for graphical creation
  * - 03 oct 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_RESIZE_GRIP_H_
#define _OGRE_GUI_RESIZE_GRIP_H_

#include "bgbutton.h"
#include "bgcallback.h"
#include "skinmanager.h" // For OgreGuiSkinID

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class Skin;
  }
}
// End of forward declarations


using namespace BetaGUI;
using namespace RainbruRPG::OgreGui;

namespace RainbruRPG{
  namespace OgreGui{

    /** A ResizeGrip for window
      *
      * This widget is used to resize windows. 
      *
      */
    class ResizeGrip : public BetaGUI::Button{
    public:
      ResizeGrip(Vector4, Callback,GUI *,Widget*,OgreGuiSkinID sid=OSI_PARENT);
      virtual ~ResizeGrip();

      virtual void draw(QuadRenderer*);

    private:
      /** The current Skin, used to speed-up drawing */
      Skin* mSkin;
    };

  }
}

#endif // _OGRE_GUI_RESIZE_GRIP_H_


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

/** \file ogreGui/pushbutton.h
  * Declares a push button widget
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 04 nov 2007 : Can apply a OgreGuiSkinID in constructor
  * - 17 oct 2007 : No more need a BetaGUI::GUI in constructor parameters
  * - 05 oct 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_PUSH_BUTTON_H_
#define _OGRE_GUI_PUSH_BUTTON_H_

#include "bgbutton.h"
#include "bgcallback.h"
#include "mouseevent.h"

using namespace BetaGUI;

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class Skin;
  }
}
namespace BetaGUI{
  class Window;
}
// End of forward declarations

using namespace BetaGUI;

namespace RainbruRPG{
  namespace OgreGui{

    /** A widget drawing a push button
      *
      * It is based on Button to be able to use a callback.
      *
      */
    class PushButton : public BetaGUI::Button{
    public:
      PushButton(Vector4, String, Callback, Window*, 
		 OgreGuiSkinID sid=OSI_PARENT);
      ~PushButton();

      virtual void draw(QuadRenderer*);


    private:
      /** A reference to the current skin used to speed up drawing */
      Skin* mSkin;
      /** The parent window */
      Window* winParent;

   };
  }
}

#endif // _OGRE_GUI_PUSH_BUTTON_H_

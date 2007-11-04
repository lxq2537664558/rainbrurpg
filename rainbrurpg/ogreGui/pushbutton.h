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
 * - 17 oct 2007 : No more need a BetaGUI::GUI in constructor parameters
 * - 05 oct 2007 : starting implementation
 *         
 */

#ifndef _OGRE_GUI_PUSH_BUTTON_H_
#define _OGRE_GUI_PUSH_BUTTON_H_

#include "bgbutton.h"
#include "bgcallback.h"

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
		 OgreGuiSkinID sid=OSI_DEFAULT);
      ~PushButton();

      virtual void setTransparency(float);
    };

  }
}

#endif // _OGRE_GUI_PUSH_BUTTON_H_

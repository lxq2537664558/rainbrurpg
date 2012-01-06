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

/** \file titlebar.h
  * Declares a Window's title bar
  *
  * Modifications :
  * - 30 aug 2008 : Single file documentation
  * - 09 nov 2007 : Handling OgreSkinID in constructor
  * - 05 oct 2007 : Now using skin for graphiwal creation
  * - 03 oct 2007 : starting implementation
  *         
  */

#ifndef _OGRE_GUI_TITLE_BAR_H_
#define _OGRE_GUI_TITLE_BAR_H_

#include "bgbutton.h"
#include "bgcallback.h"
#include "skinmanager.h" // For OgreGuiSkinID

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class Skin;
    class Widget;
  }
}
// End of forward declarations


using namespace BetaGUI;
using namespace RainbruRPG::OgreGui;

namespace RainbruRPG{
  namespace OgreGui{

    /** A widget drawing a Window's title bar
      *
      * It is based on Button to be able to use its callback
      * for moving the window.
      *
      */
    class TitleBar : public BetaGUI::Button{
    public:
      TitleBar(Vector4, String, Callback, GUI*, Widget*, 
	       OgreGuiSkinID sid=OSI_PARENT);

      ~TitleBar();

      virtual void draw(QuadRenderer*);

    private:
      /** The current used Skin
        *
	* We keep a pointer to the current Skin to speed up drawing, as
	* we do not have to get it for every frame.
	*
	*/
      Skin* mSkin;

    };
  }
}

#endif // _OGRE_GUI_TITLE_BAR_H_


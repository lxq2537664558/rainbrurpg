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

#ifndef _OGRE_GUI_SKIN_H_
#define _OGRE_GUI_SKIN_H_

#include <string>
#include <OGRE/OgrePrerequisites.h> // For Ogre::String

#include "bggui.h"


// Forward declarations

namespace BetaGUI{
  class Window;
}
// End of forward declarations

using namespace std;
using namespace Ogre;
using namespace BetaGUI;

namespace RainbruRPG{
  namespace OgreGui{

    /** The base class of all skins
      *
      * It defines some pure virtual functions that must be reimplemented.
      * These function should \b create the graphical representation
      * of a widget, not draw it. There is not an update per frame. 
      *
      */
    class Skin{
    public:
      Skin(std::string n="defaultSkinName");

      std::string getName(void);
      void setName(std::string);

      /** Create a window
        *
	* Please see the sub-class documentation for implementation
	* details.
	*
	* \param name    The internal name of the window
	* \param dim     The window's dimension in pixels in a 
	*                Ogre::Vector4 object
	* \param caption The title bar caption
	* \param bg      The BetaGUI::GUI object 
	*
	*/
      virtual void createWindow(String name, Vector4 dim, String caption, 
				GUI* bg)=0;
      /** Graphically create a ResizeGrip widget
        *
	* \param name    The internal name of the ResizeGrip (must be unique)
	* \param dim     The widget's dimension in pixels in a 
	*                Ogre::Vector4 object
	* \param parent  The parent window
	*
	*/
     virtual void createResizeGrip(String name, Vector4 dim, Window* parent)=0;

      /** Graphically create a TitleBar widget
        *
	* \param name    The internal name of the ResizeGrip (must be unique)
	* \param dim     The widget's dimension in pixels in a 
	*                Ogre::Vector4 object
	* \param parent  The parent window
	*
	*/
     virtual void createTitleBar(String name, Vector4 dim, Window* parent)=0;

    private:
      /** The name of the skin */
      std::string name;
    };

  }
}

#endif // _OGRE_GUI_SKIN_H_

/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file Container.hpp
  *
  * Declares an ogreGui container
  *
  * Modifications :
  * - 08 jul 2010 : Starting implementation
  *
  */

#ifndef _CONTAINER_HPP_
#define _CONTAINER_HPP_

#include "Widget.hpp"
#include "WidgetList.hpp"

#include <string>
#include <OIS.h>

using namespace std;

// Forward declarations
namespace RainbruRPG{
  namespace OgreGui{
    class Focusable;
  }
}
// End of forward declarations

namespace RainbruRPG{
  namespace OgreGui{

    /** An ogregui container
      *
      * A container is a \ref WidgetList that can be drawn, by inheriting
      * the \ref Widget interface.
      *
      */
    class Container : public Widget, public WidgetList
    {
    public:
      Container(Widget*, const string&, int, int, int, int);
      virtual ~Container();

      virtual bool keyPressed(const OIS::KeyEvent&);
      virtual bool keyReleased(const OIS::KeyEvent&);

      virtual bool mouseMoved(const OIS::MouseEvent&);
      virtual bool mousePressed(const OIS::MouseEvent&, 
				const OIS::MouseButtonID&);
      virtual bool mouseReleased(const OIS::MouseEvent&, 
				 const OIS::MouseButtonID&);

      virtual void draw(Brush*);
      virtual void compute(int, int, const Ogre::Rectangle&);
    private:
      /** The currently focused widget
        *
	* This pointer can be \c NULL.
	*
	*/
      Focusable* mFocused;
    };

  }
}

#endif // _CONTAINER_HPP_

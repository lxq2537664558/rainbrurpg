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

/** \file Widget.hpp
  *
  * Declare an ogreGui widget
  *
  * Modifications :
  * - 16 nov 2009 : Starting implementation
  *
  */

#ifndef _WIDGET_HPP_
#define _WIDGET_HPP_

#include "Drawable.hpp"
#include "Focusable.hpp"
#include "Serializable.hpp"

#include <string>

using namespace std;

namespace RainbruRPG{
  namespace OgreGui{
    /** The base class of all widgets
      *
      * - a Widget is serializable.
      *
      */
    class Widget : public Drawable, public Focusable, public Serializable{

    public:
      Widget(Widget*, const string&, int, int, int, int);
      virtual ~Widget();
    };
  }
}
#endif // !_WIDGET_HPP_


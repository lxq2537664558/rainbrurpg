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

/** \file Window.hpp
  *
  * Declare an ogreGui window
  *
  * Modifications :
  * - 21 aug 2010 : Starting implementation
  *
  */

#ifndef _WINDOW_HPP_
#define _WINDOW_HPP_

#include "Container.hpp"

// Forward declaratinos
// End of forward declarations

namespace RainbruRPG{
  namespace OgreGui{

    class Window : public Container
    {
      Window(Container*, const string&, int, int, int, int);
      virtual ~Window();
    };
  }
}

#endif // !_WINDOW_HPP_

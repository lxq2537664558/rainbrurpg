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

/** \file WindowHandle.hpp
  * Declares an centralized way to get an Ogre3D window's handle
  *
  * Modifications :
  * - 08 jan 2011 : First implementation
  *
  */

#ifndef _WINDOW_HANDLE_HPP_
#define _WINDOW_HANDLE_HPP_

#include <cstring> // for size_t

// Forward declaration
namespace Ogre
{
  class RenderWindow;
}
//end of forward declaration

namespace RainbruRPG
{
  namespace Core
  {
    /** A class used to centralize the way to get a window handle
      *
      */
    class WindowHandle
    {
    public:
      static size_t get(Ogre::RenderWindow*);
    };
  }
}

#endif // !_WINDOW_HANDLE_HPP_



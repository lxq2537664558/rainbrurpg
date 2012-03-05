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

/** \file WindowHandle.cpp
  * Implements an centralized way to get an Ogre3D window's handle
  *
  */

#include "WindowHandle.hpp"

#include "ogreimport.h"
#include "NullWindowHandleException.hpp"
#include <Logger.hpp>

#ifdef WIN32
#  include <OgreD3D9RenderWindow.h>
#endif

using namespace RainbruRPG::Exception;

/** Get a window handle for the given render window
  *
  * \param vRenderWindow An Ogre3D render window
  *
  * \return The window handle
  *
  */
size_t RainbruRPG::Core::WindowHandle::get(Ogre::RenderWindow* vRenderWindow)
{
  if (!vRenderWindow)
    throw NullWindowHandleException(vRenderWindow);


  size_t windowHnd = 0;

    //#if defined OIS_WIN32_PLATFORM
#ifdef WIN32
    vRenderWindow->getCustomAttribute( "HWND", &windowHnd );

    if (!windowHnd){
      windowHnd = (size_t)((Ogre::D3D9RenderWindow*)vRenderWindow)
	->getWindowHandle();
    }

    //#elif defined OIS_LINUX_PLATFORM
#else // WIN32
    /* v0.0.5-164
     *
     * Mouse reappears when replace GLXWINDOW by WINDOW as 
     * custom attribute string identifier. To provide error
     * detection, an assertion was added on windowHnd.
     *
     */
    vRenderWindow->getCustomAttribute( "WINDOW", &windowHnd );

#endif // WIN32

  if (!windowHnd)
    throw NullWindowHandleException(vRenderWindow);

  return windowHnd;
}

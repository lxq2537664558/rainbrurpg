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

/** \file NullWindowHandleException.cpp
  * Implements an exception thrown if window handle cannot be found
  *
  */

#include "NullWindowHandleException.hpp"

#include <sstream>
#include <OgreImport.hpp>

/** The exception constructor
  *
  * \param vRenderWindow The Ogre3D render window
  *
  */
RainbruRPG::Exception::NullWindowHandleException::
NullWindowHandleException(Ogre::RenderWindow* vRenderWindow) throw()
{
  string rendererName=Ogre::Root::getSingleton().getRenderSystem()->getName();

  ostringstream oss;
  if (vRenderWindow){
    oss << "Cannot get window handle for RenderWindow '"
	<< vRenderWindow->getName() << "' ";
  }
  else{
    oss << "Cannot get window handle for NULL RenderWindow ";
  }

  oss << "with Ogre3D renderer '" << rendererName << "' ";
  oss << "on platform '" << getPlatform() << "' ";

  mMessage=oss.str();
}

/// An empty destructor
RainbruRPG::Exception::NullWindowHandleException::
~NullWindowHandleException() throw()
{

}

/** Return the exception's message
  *
  * \return The message created in the constructor
  *
  */
const char* RainbruRPG::Exception::NullWindowHandleException::
what() const throw()
{
  return mMessage.c_str();
}

/** Get the current platform as string
  *
  * \return A string conteining the platform name
  *
  */
string RainbruRPG::Exception::NullWindowHandleException::
getPlatform() const
{
#ifdef WIN32
  return "Win32";
#else  // WIN32
  return "GNU/Linux";
#endif // WIN32
}


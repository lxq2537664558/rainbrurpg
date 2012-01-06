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

#include "SkinNotFoundException.hpp"


/** The exception's constructor
  *
  * \param vSkinName    The skin name
  * \param vTextureName The name of the texture
  *
  */
RainbruRPG::Exception::SkinNotFoundException::
SkinNotFoundException(const string& vSkinName, const string& vTextureName) throw()
{
  mMessage = "Skin '" + vSkinName + "' not found for texture '" + vTextureName + "'.";
}

/// The destructor
RainbruRPG::Exception::SkinNotFoundException::
~SkinNotFoundException() throw()
{

}

/** Returns the message as a C string
  *
  * \return The exception's message
  *
  */
const char* RainbruRPG::Exception::SkinNotFoundException::
what() const throw()
{
  return mMessage.c_str();
}

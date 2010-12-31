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

#include "NullHeightGlyphException.hpp"

#include <sstream>

/** The exception's constructor
  *
  * \param vCharCode the character code of the glyph
  *
  */
RainbruRPG::Exception::NullHeightGlyphException::
NullHeightGlyphException(long int vCharCode) throw()
{
  ostringstream oss;
  oss << "The glyph with char code '";
  oss << vCharCode;
  oss << "' has null height";
  mMessage = oss.str();
}

/// The destructor
RainbruRPG::Exception::NullHeightGlyphException::
~NullHeightGlyphException() throw()
{

}

/** Returns the message as a C string
  *
  * \return The exception's message
  *
  */
const char* RainbruRPG::Exception::NullHeightGlyphException::
what() const throw()
{
  return mMessage.c_str();
}

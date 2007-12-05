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

#include "glyph.h"

/** The constructor
  *
  * \param vRect    The geometry of the glyph
  * \param vOffsetX The X offset
  * \param vOffsetY The Y offset
  * \param vSpace   The spacing
  *
  */
RainbruRPG::OgreGui::Glyph::
Glyph(Ogre::Rectangle vRect, float vOffsetX, float vOffsetY, float vSpace):
  mRect(vRect),
  mOffsetX(vOffsetX),
  mOffsetY(vOffsetY),
  mSpace(vSpace)
{

}

/** The default constructor
  *
  */
RainbruRPG::OgreGui::Glyph::Glyph(){

}

/** The destructor 
  *
  */
RainbruRPG::OgreGui::Glyph::~Glyph(){

}

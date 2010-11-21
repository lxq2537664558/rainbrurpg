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

/** \file glyph.cpp
  * Implements the class that stores informations about a single glyph 
  *
  */

#include "Glyph.hpp"
#include "logger.h"

#include <dumpogreobject.h>

#include "NullHeightGlyphException.hpp"

using namespace RainbruRPG::Exception;

/** The constructor
  *
  * \param vRect    The geometry of the glyph
  * \param vOffsetX The X offset
  * \param vOffsetY The Y offset
  * \param vSpace   The spacing
  * \param cc       The charcode assigned to this glyph
  *
  */
RainbruRPG::OgreGui::Glyph::
Glyph(const Ogre::Rectangle& vRect,float vOffsetX,float vOffsetY, 
      float vSpace, long int cc):
  mOffsetX(vOffsetX),
  mOffsetY(vOffsetY),
  mSpace(vSpace),
  charcode(cc)
{
  mRect.top=vRect.top;
  mRect.left=vRect.left;
  mRect.right=vRect.right;
  mRect.bottom=vRect.bottom;

  if (vRect.bottom-vRect.top==0){
    throw NullHeightGlyphException(cc);
  }
}

/** The default constructor
  *
  */
RainbruRPG::OgreGui::Glyph::Glyph():
  mOffsetX(0),
  mOffsetY(0),
  mSpace(0),
  charcode(0)
{
  mRect.top=0.0f;
  mRect.left=0.0f;
  mRect.right=0.0f;
  mRect.bottom=0.0f;
}

/** The destructor 
  *
  */
RainbruRPG::OgreGui::Glyph::~Glyph(){

}

/** Get the space of this glyph
  *
  * \return The space
  *
  */
float RainbruRPG::OgreGui::Glyph::getSpace(void)const{
  return mSpace;
}

/** Get the geometry rectangle
  *
  * \return The rectangle containing this glyph
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::Glyph::getGeometry()const{
  return mRect;
}

/** Get the height of this glyph
  *
  * \return The height of this glyph
  *
  */
float RainbruRPG::OgreGui::Glyph::getHeight(void)const{
  float height=mRect.bottom-mRect.top;
  return height;
}

/** Get the width of this glyph
  *
  * \return The width of this glyph
  *
  */
float RainbruRPG::OgreGui::Glyph::getWidth(void)const{
  float width=mRect.right-mRect.left;
  return width;
}

/** Get the X offset of this glyph
  *
  * \return The X offset of this glyph
  *
  */
float RainbruRPG::OgreGui::Glyph::getOffsetX()const{
  return mOffsetX;
}

/** Get the Y offset of this glyph
  *
  * \return The Y offset of this glyph
  *
  */
float RainbruRPG::OgreGui::Glyph::getOffsetY()const{
 return mOffsetY;
}

/** Get the top value
  *
  * \return The top geometry of this glyph.
  *
  */
float RainbruRPG::OgreGui::Glyph::getTop(void)const{
  return mRect.top;
}

/** Get the left value
  *
  * \return The left geometry of this glyph.
  *
  */
float RainbruRPG::OgreGui::Glyph::getLeft(void)const{
  return mRect.left;
}

/** Get the right value
  *
  * \return The right geometry of this glyph.
  *
  */
float RainbruRPG::OgreGui::Glyph::getRight(void)const{
  return mRect.right;
}

/** Get the bottom value
  *
  * \return The bottom geometry of this glyph.
  *
  */
float RainbruRPG::OgreGui::Glyph::getBottom(void)const{
  return mRect.bottom;
}

/** The copy constructor
  *
  * \param g The Glyph to copy. 
  *
  */
RainbruRPG::OgreGui::Glyph::Glyph(const Glyph& g){
  mRect.top=g.getTop();
  mRect.bottom=g.getBottom();
  mRect.left=g.getLeft();
  mRect.right=g.getRight();

  mOffsetX =g.getOffsetX();
  mOffsetY =g.getOffsetY();
  mSpace   =g.getSpace();

  charcode=g.getCharCode();
}

/** The assignment operator
  *
  * \param g The Glyph to assign
  *
  * \return This glyph
  *
  */
RainbruRPG::OgreGui::Glyph& 
RainbruRPG::OgreGui::Glyph::operator=(const RainbruRPG::OgreGui::Glyph& g){
  mRect.top=g.getTop();
  mRect.bottom=g.getBottom();
  mRect.left=g.getLeft();
  mRect.right=g.getRight();

  mOffsetX =g.getOffsetX();
  mOffsetY =g.getOffsetY();
  mSpace   =g.getSpace();
  
  charcode=g.getCharCode();

  return *this;
}

/** Set this glyph's charcode
  *
  * \param cc The charcode
  *
  */
void RainbruRPG::OgreGui::Glyph::setCharCode(long int cc){
  charcode=cc;
}

/** Get this glyph's charcode
  *
  * \return The charcode
  *
  */
long int RainbruRPG::OgreGui::Glyph::getCharCode(void)const{
  return charcode;
}

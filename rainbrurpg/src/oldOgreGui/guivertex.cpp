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

/** \file guivertex.cpp
  * Implements a vertex when sent to hardware bufer by QuadRenderer
  *
  */

#include "guivertex.h"

#include <logger.h>

/** Default constructor
  *
  */
RainbruRPG::OgreGui::GuiVertex::GuiVertex():
  pos(),
  color(),
  uv()
{

}

/** Get the position of this vertex
  *
  * \return The position as a Vector3
  *
  */
const OgreGui::Vector3& RainbruRPG::OgreGui::GuiVertex::
getPosition(void) const{
  return pos;
}

/** Get the color
  *
  * \return The color
  *
  */
const ColourValue& RainbruRPG::OgreGui::GuiVertex::getColor(void) const{
  return color;
}

/** Get the Uv mapping
  *
  * \return The uv mapping
  *
  */
const Vector2& RainbruRPG::OgreGui::GuiVertex::getUvMapping(void) const{
  return uv;
}

/** Change the poition of this gui vertex
  *
  * \param vPos The new podition as a Vector3 object
  *
  */
void RainbruRPG::OgreGui::GuiVertex::setPosition(const OgreGui::Vector3& vPos){
  /* Testing the vVect integrity
   *
   * See the complete trace of this SEGFAULT in v0.0.5-168's changelog.
   *
   */
  LOGA(&vPos, _("GuiVertex::setPosition parameter is NULL."));
  pos=vPos;
}

/** Change the color of this vertex
  * 
  * \param vColor The new color
  *
  */
void RainbruRPG::OgreGui::GuiVertex::setColor(const ColourValue& vColor){
  color=vColor;
}

/** Change the uvMpping
  *
  * \param vUv The new UV mapping
  *
  */
void RainbruRPG::OgreGui::GuiVertex::setUvMapping(const Vector2& vUv){
  uv=vUv;
}


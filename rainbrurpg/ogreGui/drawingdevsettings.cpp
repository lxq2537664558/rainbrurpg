/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

/** \file drawingdevsettings.cpp
  * Implements a QuadRenderer deviation setting
  *
  */

#include "drawingdevsettings.h"

/** The constructor
  *
  * \param vOwner The owner name
  * \param vDevX  The X dev value
  * \param vDevY  The Y dev value
  *
  */
RainbruRPG::OgreGui::DrawingDevSettings::
DrawingDevSettings(string vOwner, int vDevX, int vDevY):
  mOwner(vOwner),
  mDevX(vDevX),
  mDevY(vDevY)
{
  
}

/** Change both X and Y value at the same time
  *
  * \param vDevX The X dev value
  * \param vDevY The Y dev value
  *
  */
void RainbruRPG::OgreGui::DrawingDevSettings::move(int vDevX, int vDevY){
  mDevX = vDevX;
  mDevY = vDevY;
}

/** Changes the X value
  *
  * \param vDevX The X dev value
  *
  */
void RainbruRPG::OgreGui::DrawingDevSettings::setDevX(int vDevX){
  mDevX = vDevX;
}

/** Changes the Y value
  *
  * \param vDevY The Y dev value
  *
  */
void RainbruRPG::OgreGui::DrawingDevSettings::setDevY(int vDevY){
  mDevY = vDevY;
}

/** Get the owner name
  *
  * \return The owner name as a STL string
  *
  */
const std::string& RainbruRPG::OgreGui::DrawingDevSettings::
getOwner(void)const{
  return mOwner;
}

/** Get the X value
  *
  * \return The X value
  *
  */
int RainbruRPG::OgreGui::DrawingDevSettings::getDevX(void)const{
  return mDevX;
}

/** Get the Y value
  *
  * \return The Y value
  *
  */
int RainbruRPG::OgreGui::DrawingDevSettings::getDevY(void)const{
  return mDevY;
}

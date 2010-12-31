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

/** \file vector3.cpp
  * Implements a 3-dimensional vector
  *
  */

#include "vector3.h"

#include <logger.h>

/** A default constructor
  *
  * All members values are set to 0.0f.
  *
  */
RainbruRPG::OgreGui::Vector3::Vector3():
  x(0.0f),
  y(0.0f),
  z(0.0f)
{

}

/** A constructor
  *
  */
RainbruRPG::OgreGui::Vector3::Vector3(float rX, float rY, float rZ):
  x(rX),
  y(rY),
  z(rZ)
{

}

/** The assignment operator
  *
  * \param vVect The vector to assign
  *
  */
RainbruRPG::OgreGui::Vector3& 
RainbruRPG::OgreGui::Vector3::
operator= ( const RainbruRPG::OgreGui::Vector3& vVect){
  /* Testing the vVect integrity
   *
   * See the complete trace of this SEGFAULT in v0.0.5-168's changelog.
   *
   */
  LOGA(&vVect, "Vector3::operator= parameter is NULL. Program should crash.");
  x=vVect.getX();
  y=vVect.getY();
  z=vVect.getZ();

  return *this;
}


/** Change the X coordonate value
  *
  * \param rX The new X value
  *
  * \sa \link RainbruRPG::OgreGui::Vector3::x x(member) \endlink
  *
  */
void RainbruRPG::OgreGui::Vector3::setX(float rX){
  x=rX;
}

/** Change the Y coordonate value
  *
  * \param rY The new Y value
  *
  * \sa \link RainbruRPG::OgreGui::Vector3::y y(member) \endlink
  *
  */
void RainbruRPG::OgreGui::Vector3::setY(float rY){
  y=rY;
}

/** Change the Z coordonate value
  *
  * \param rZ The new Z value
  *
  * \sa \link RainbruRPG::OgreGui::Vector3::z z(member) \endlink
  *
  */
void RainbruRPG::OgreGui::Vector3::setZ(float rZ){
  z=rZ;
}

/** Get the X coordonate value
  *
  * \return The X value
  *
  * \sa \link RainbruRPG::OgreGui::Vector3::x x(member) \endlink
  *
  */
float RainbruRPG::OgreGui::Vector3::getX(void) const{
  return x;
}

/** Get the Y coordonate value
  *
  * \return The Y value
  *
  * \sa \link RainbruRPG::OgreGui::Vector3::y y(member) \endlink
  *
  */
float RainbruRPG::OgreGui::Vector3::getY(void) const{
  return y;
}

/** Get the Z coordonate value
  *
  * \return The Z value
  *
  * \sa \link RainbruRPG::OgreGui::Vector3::z z(member) \endlink
  *
  */
float RainbruRPG::OgreGui::Vector3::getZ(void) const{
  return z;
}


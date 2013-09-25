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

/** \file tools/netflooder/floodertestbase.cpp
  * Implements the base class of all netflooder's tests
  *
  */

#include "floodertestbase.h"

/** The default constructor
  *
  */
RainbruRPG::Network::FlooderTestBase::FlooderTestBase(){
  imageFilename="";
  imageWidth=0;
  imageHeiht=0;
}

/** The destructor
  *
  */
RainbruRPG::Network::FlooderTestBase::~FlooderTestBase(){

}

/** Get the name of the test
  *
  * \return The name
  *
  */
const char* RainbruRPG::Network::FlooderTestBase::getName(){
  return this->name;
}

/** Get the description of the test
  *
  * \return The description
  *
  */
const char* RainbruRPG::Network::FlooderTestBase::getDescription(){
  return this->description;
}

/** Get the result image filename
  *
  * \return The filename where the image will be saved
  *
  */
const char* RainbruRPG::Network::FlooderTestBase::getImageFilename(){
  return imageFilename;
}

/** Get the image width in pixels
  *
  * \return The image width
  *
  */
int RainbruRPG::Network::FlooderTestBase::getImageWidth(){
  return imageWidth;
}

/** Get the image height in pixels
  *
  * \return The image height
  *
  */
int RainbruRPG::Network::FlooderTestBase::getImageHeight(){
  return imageHeiht;
}


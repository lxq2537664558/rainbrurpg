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

#include "floodertestbase.h"

/** The default constructor
  *
  */
RainbruRPG::Network::FlooderTestBase::FlooderTestBase(){

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

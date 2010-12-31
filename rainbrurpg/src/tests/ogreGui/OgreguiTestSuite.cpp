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

/** \file OgreguiTestSuite.cpp
  * Implements the test suite designed to test the OgreGui library
  *
  */

#include "OgreguiTestSuite.hpp"

// TestFixtures implementations
#include "DeserializationErrorTest.hpp"
#include "DrawableTest.hpp"
#include "SerializableTest.hpp"

// Classes to be tested
#include <DeserializationErrorList.hpp>
#include <Drawable.hpp>
#include <Serializable.hpp>

using namespace RainbruRPG::OgreGui;

/** Test suite constructor
  *
  */
OgreguiTestSuite::OgreguiTestSuite()
  :TestSuite("OgreGui")
{
  addTest( DeserializationErrorTest<DeserializationErrorList>::suite() );
  addTest( SerializableTest<Serializable>::suite() );
  addTest( DrawableTest<Drawable>::suite() );
}

/** Destructor
  *
  */
OgreguiTestSuite::~OgreguiTestSuite(){

}

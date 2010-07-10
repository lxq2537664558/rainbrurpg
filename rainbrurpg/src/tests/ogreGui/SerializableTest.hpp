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

/** \file labeltest.h
  * Implements the unit tests of the Label class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef SERIALIZABLE_TEST_H
#define SERIALIZABLE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>
#include <sstream>
#include <iostream>

#include <logger.h>
#include <Serializable.hpp>

using namespace std;
using namespace RainbruRPG::OgreGui;

/** A test class for TerminalAPI's  Label widget
  *
  */
class SerializableTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the Label test 
  CPPUNIT_TEST_SUITE( SerializableTest );

  CPPUNIT_TEST( testUniqueName ); //!< Test the unique name
  CPPUNIT_TEST( testEqual );      //!< Test the equality operator
  CPPUNIT_TEST( testNotEqual );   //!< Test the non-eaqual operator
  CPPUNIT_TEST( testSeekg );      //!< Test the seekg function
  CPPUNIT_TEST( testEqualPtr );   //!< Test equal pointers

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the caption widget
    *
    */
  Serializable	*m_instance;
  
public:
  void setUp();
  void tearDown();
  
  void testUniqueName();
  void testEqual();
  void testNotEqual();
  void testSeekg();
  void testEqualPtr();

};


#endif // SERIALIZABLE_TEST_H

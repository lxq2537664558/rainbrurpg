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

#ifndef CONTAINER_TEST_H
#define CONTAINER_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <Container.hpp>

using namespace RainbruRPG::OgreGui;

/** A test case for ogreGui's Drawable
  *
  */
class ContainerTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the ContainerTest
  CPPUNIT_TEST_SUITE( ContainerTest );

  CPPUNIT_TEST( testEmpty );         //!< Test an empty container
  CPPUNIT_TEST( testTrueFocusable ); //!< Test an container with a focusable

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the tested class
    *
    */
  Container* m_instance;
  
public:
  void setUp();
  void tearDown();

  void testEmpty();
  void testTrueFocusable();
};

#endif // CONTAINER_TEST_H

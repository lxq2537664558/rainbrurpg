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

#ifndef FOCUSABLE_TEST_H
#define FOCUSABLE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <Focusable.hpp>

using namespace std;
using namespace RainbruRPG::OgreGui;

/** A test case for ogreGui's Focusable
  *
  */
class FocusableTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the FocusableTest
  CPPUNIT_TEST_SUITE( FocusableTest );

  CPPUNIT_TEST( testConstructor );       //!< Test the constructor
  CPPUNIT_TEST( testCanTakeFocus );      //!< Test canTakeFocus
  CPPUNIT_TEST( testConsumedEvents );    //!< Test if events are consumed
  CPPUNIT_TEST( testFocus );             //!< Test the focus ability
  CPPUNIT_TEST( testNonFocusableFocus ); //!< Test with non-focusable

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the caption widget
    *
    */
  Focusable* m_instance;
  
public:
  void setUp();
  void tearDown();

  void testConstructor();
  void testCanTakeFocus();
  void testConsumedEvents();
  void testFocus();
  void testNonFocusableFocus();
};


#endif // FOCUSABLE_TEST_H

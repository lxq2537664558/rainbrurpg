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

#ifndef WIDGET_LIST_TEST_H
#define WIDGET_LIST_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>
#include <sstream>
#include <iostream>

#include <WidgetList.hpp>

using namespace std;
using namespace RainbruRPG::OgreGui;

/** A test case for ogreGui's Drawable
  *
  */
class WidgetListTest : public CPPUNIT_NS::TestFixture 
{
  /// Start this test fixture
  CPPUNIT_TEST_SUITE( WidgetListTest );

  CPPUNIT_TEST( testNew );           //!< Test the constructor
  CPPUNIT_TEST( testEmpty );         //!< Test for an empty list
  CPPUNIT_TEST( testPushBack );      //!< Test the push_back function
  CPPUNIT_TEST( testUniqueName );    //!< Test the uniqueName
  CPPUNIT_TEST( testFocusNext );     //!< Test for focusNext
  CPPUNIT_TEST( testFocusPrevious ); //!< Test for focusPrevious
  CPPUNIT_TEST( testFocusMixed );    //!< Test for next/previous mixed

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the caption widget
    *
    */
  WidgetList* m_instance;
  
public:
  void setUp();
  void tearDown();

  void testNew();
  void testEmpty();
  void testPushBack();
  void testUniqueName();
  void testFocusNext();
  void testFocusPrevious();
  void testFocusMixed();
};

#endif // WIDGET_LIST_TEST_H

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

#ifndef BRUSH_TEST_H
#define BRUSH_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <Brush.hpp>

using namespace RainbruRPG::OgreGui;

/** A test case for ogreGui's Brush
  *
  */
class BrushTest : public CPPUNIT_NS::TestFixture 
{
  /// The beginning of the test fixture
  CPPUNIT_TEST_SUITE( BrushTest );

  //  CPPUNIT_TEST( testParent );           //!< The parent's test

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the caption widget
    *
    */
  Brush* m_instance;
  
public:
  void setUp();
  void tearDown();
};


#endif // BRUSH_TEST_H

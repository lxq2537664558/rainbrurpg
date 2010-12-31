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

#ifndef DRAWABLE_TEST_H
#define DRAWABLE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>
#include <sstream>
#include <iostream>

#include <Drawable.hpp>
#include <TextureNotFoundException.hpp>
#include <SkinNotFoundException.hpp>

#include <ogreimport.h>
#include <OgreRectangle.h>

using namespace std;
using namespace Ogre;
using namespace RainbruRPG::OgreGui;

#define RECT Rectangle()

/** A test case for ogreGui's Drawable 
  *
  * \note These tests are only for Drawable without Ogre. For Drawable tests
  *       needing Ogre, please see DrawableTestWithOgre.
  *
  */
class DrawableTest : public CPPUNIT_NS::TestFixture
{
  /// The beginning of the test fixture
  CPPUNIT_TEST_SUITE( DrawableTest );

  CPPUNIT_TEST( testParent );           //!< The parent's test
  CPPUNIT_TEST( testDirty );            //!< The dirty flag test
  CPPUNIT_TEST( testDirtyPropagation ); //!< Test the dirty flag propagation
  CPPUNIT_TEST( testComputeAbsolute );  //!< Test the absolute position
  CPPUNIT_TEST( testAdjustScissor1 );   //!< First test of the scissor
  CPPUNIT_TEST( testAdjustScissor2 );   //!< Second test of the scissor

  CPPUNIT_TEST( testSkinName1 );         //!< Test the skin name propagation
  CPPUNIT_TEST( testSkinName2 );         //!< Test the skin name propagation (2)
  
  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the tested class
    *
    */
  Drawable* m_instance;
  
public:
  void setUp();
  void tearDown();

  void testParent();
  void testDirty();
  void testDirtyPropagation();
  void testComputeAbsolute();
  void testAdjustScissor1();
  void testAdjustScissor2();
  void testSkinName1();
  void testSkinName2();

protected:
  void setRectangle(Rectangle* r, int x1, int y1, int x2, int y2);
};

#endif // DRAWABLE_TEST_H

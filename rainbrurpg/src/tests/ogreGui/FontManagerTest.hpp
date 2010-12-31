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

#ifndef _FONT_MANAGER_TEST_HPP_
#define _FONT_MANAGER_TEST_HPP_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>


#include <FontManager.hpp>
#include <OgreMinimalSetup.hpp>

// Must use OgreGui::FontManager to avoid ambigous declaration 
// with Ogre::FontManager
using namespace RainbruRPG;

using namespace RainbruRPG::OgreGui;

/** A test case for the OgreGui's FontManager
  *
  */
class FontManagerTest : 
  public CPPUNIT_NS::TestFixture
#ifndef NO_OGRE
  ,public OgreMinimalSetup
#endif
{

  /// The beginning of the test fixture
  CPPUNIT_TEST_SUITE( FontManagerTest );

  CPPUNIT_TEST( testLoadFont );           //!< The loadfont() function test

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();


public:
  FontManagerTest(){};
  virtual ~FontManagerTest(){};

  void setUp();
  void tearDown();

  void testLoadFont();
};


#endif // !_FONT_MANAGER_TEST_HPP_

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

#ifndef _DRAWABLE_TEST_WITH_OGRE_HPP_
#define _DRAWABLE_TEST_WITH_OGRE_HPP_

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

#include <OgreMinimalSetup.hpp>

using namespace RainbruRPG::OgreGui;

class DrawableTestWithOgre : 
  public CPPUNIT_NS::TestFixture, 
  public OgreMinimalSetup
{
  /// The beginning of the test fixture
  CPPUNIT_TEST_SUITE( DrawableTestWithOgre );

  CPPUNIT_TEST( testLoadTexture );      //!< Test the loading of a texture
  CPPUNIT_TEST_EXCEPTION(testLoadTextureThrow, TextureNotFoundException);
  CPPUNIT_TEST( testLoadSkinnable );    //!< Test the loading of a skinnable texture
  CPPUNIT_TEST_EXCEPTION(testLoadSkinnableSkinNotFound, SkinNotFoundException);
  CPPUNIT_TEST_EXCEPTION(testLoadSkinnableTextureNotFound, TextureNotFoundException);
  
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

  void testLoadTexture();
  void testLoadTextureThrow();
  void testLoadSkinnable();
  void testLoadSkinnableSkinNotFound();
  void testLoadSkinnableTextureNotFound();
};


#endif // ! _DRAWABLE_TEST_WITH_OGRE_HPP_

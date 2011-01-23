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

/** \file DrawableTestWithOgre.cpp
  * A test case for ogreGui's Drawable (using OgreMinimalSetup)
  *
  * \note These tests are only for Drawable with Ogre. For Drawable tests
  *       without Ogre, please see DrawableTest.
  *
  */

#include "Drawable.hpp"

#include "TextureNotFoundException.hpp" // uses in throw() cannot be forwarded
#include "SkinNotFoundException.hpp"

#include <OgreMinimalSetup.hpp>

#include <boost/test/unit_test.hpp>

#include <string>
#include <sstream>
#include <iostream>

#include <TextureNotFoundException.hpp>
#include <SkinNotFoundException.hpp>

#include <ogreimport.h>
#include <OgreRectangle.h>

// Do not use namespace Ogre for Rectangle and win32 name conflicts
using namespace RainbruRPG::OgreGui;

#define RECT Ogre::Rectangle()
OgreMinimalSetup* oms_DrawableWithOgre;

Drawable* setup_DrawableWithOgre()
{
  oms_DrawableWithOgre = new OgreMinimalSetup();
  oms_DrawableWithOgre->setupOgre();
  return new Drawable(NULL, RECT);
}

void teardown_DrawableWithOgre(Drawable* d)
{
  delete d;
  oms_DrawableWithOgre->teardownOgre();
  delete oms_DrawableWithOgre;
}

/// Test if Drawable::loadTexture does not return a NULL texture
BOOST_AUTO_TEST_CASE( test_drawableWithOgre_LoadTexture )
{
  Drawable* instance= setup_DrawableWithOgre();
  instance->loadTexture("main.bmp");
  BOOST_ASSERT(!instance->getTexturePtr().isNull());
  teardown_DrawableWithOgre( instance );
}

/// Test if trying to load an non-existing texture throw an exception
BOOST_AUTO_TEST_CASE( test_drawableWithOgre_LoadTextureThrow )
{
  Drawable* instance= setup_DrawableWithOgre();
  string tn = "UnbelievableTextureNameThatShouldNotBeFound.png";
  BOOST_CHECK_THROW( instance->loadTexture( tn ),
		     TextureNotFoundException);
  teardown_DrawableWithOgre( instance );
}

/// Test if Drawable::loadSkinnable works with an existing texture
BOOST_AUTO_TEST_CASE( test_drawableWithOgre_LoadSkinnable )
{
  Drawable* instance= setup_DrawableWithOgre();
  Ogre::Root::getSingleton()
    .addResourceLocation("../../data/gui/ogreGui", "FileSystem");

  instance->loadSkinnableTexture("bgui", "pointer.png");
  BOOST_ASSERT(!instance->getTexturePtr().isNull());
  teardown_DrawableWithOgre( instance );
}

/// Test if throw an exception if skin not found
BOOST_AUTO_TEST_CASE( test_drawableWithOgre_LoadSkinnableSkinNotFound )
{
  Drawable* instance= setup_DrawableWithOgre();
  Ogre::Root::getSingleton()
    .addResourceLocation("../../data/gui/ogreGui", "FileSystem");

  BOOST_CHECK_THROW( instance->loadSkinnableTexture("UnexpectedSkinName", 
						    "pointer.png"),
		     SkinNotFoundException);
  teardown_DrawableWithOgre( instance );
}

/// Test if throw an exception with a non-existing texture in existing skin
BOOST_AUTO_TEST_CASE( test_drawableWithOgre_LoadSkinnableTextureNotFound )
{
  Drawable* instance= setup_DrawableWithOgre();
  Ogre::Root::getSingleton()
    .addResourceLocation("../../data/gui/ogreGui", "FileSystem");
  
  BOOST_CHECK_THROW( instance->loadSkinnableTexture("bgui", "EvenWithDefaultSkin.png");,
		     TextureNotFoundException);
  teardown_DrawableWithOgre( instance );
}

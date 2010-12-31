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

#include "DrawableTestWithOgre.hpp"

#include <OgreRectangle.h>

// Registers the fixture to the registry
CPPUNIT_TEST_SUITE_REGISTRATION( DrawableTestWithOgre );
  
/** Creates a new instance to test
  *
  */
void DrawableTestWithOgre::setUp()
{
  this->m_instance = new Drawable(NULL, Ogre::Rectangle()); 
  setupOgre();

}
  
/** Delete the current tested instance
 *
 */
void DrawableTestWithOgre::tearDown(){ 
  // Must be deleted before Ogre shutdown: 
  // This is a hack to prevent a segfault from Ogre::TextureManager when
  // it tries to delete Drawbles's TexturePtr member
  delete m_instance;
  m_instance=NULL;

  teardownOgre();
}

void DrawableTestWithOgre::testLoadTexture()
{
  m_instance->loadTexture("main.bmp");
  CPPUNIT_ASSERT(!m_instance->getTexturePtr().isNull());
}

void DrawableTestWithOgre::testLoadTextureThrow()
{
  m_instance->loadTexture("UnbelievableTextureNameThatShouldNotBeFound.bmp");
}

void DrawableTestWithOgre::testLoadSkinnable()
{
  Ogre::Root::getSingleton().addResourceLocation("../../../data/gui/ogreGui", "FileSystem");

  m_instance->loadSkinnableTexture("bgui", "pointer.png");
  CPPUNIT_ASSERT(!m_instance->getTexturePtr().isNull());
}

void DrawableTestWithOgre::testLoadSkinnableSkinNotFound()
{
  Ogre::Root::getSingleton().addResourceLocation("../../../data/gui/ogreGui", "FileSystem");

  m_instance->loadSkinnableTexture("UnexpectedSkinName", "pointer.png");
  CPPUNIT_ASSERT(!m_instance->getTexturePtr().isNull());
}

void DrawableTestWithOgre::testLoadSkinnableTextureNotFound()
{
  Ogre::Root::getSingleton().addResourceLocation("../../../data/gui/ogreGui", "FileSystem");

  m_instance->loadSkinnableTexture("UnexpectedSkinName", "EvenWithDefaultSkin.png");
  CPPUNIT_ASSERT(!m_instance->getTexturePtr().isNull());
}

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

#include "DrawableTest.hpp"

// Registers the fixture to the registry
CPPUNIT_TEST_SUITE_REGISTRATION( DrawableTest );
  
/** Creates a new instance to test
  *
  */
void DrawableTest::setUp()
{
  mRoot = NULL;
  this->m_instance = new Drawable(NULL, RECT); 
  }
  
/** Delete the current tested instance
 *
 */
void DrawableTest::tearDown(){ 
  delete this->m_instance; 
}

/// Test if the parent is correctly set by the constructor
void DrawableTest::testParent(){ 
  Drawable d1(NULL, RECT);
  CPPUNIT_ASSERT( d1.getParent() == NULL);
  Drawable d2(&d1, RECT);
  CPPUNIT_ASSERT( d2.getParent() != NULL);
  CPPUNIT_ASSERT( d2.getParent() == &d1);
}

/// Test the dirty flag
void DrawableTest::testDirty(){ 
  // At startup, dirty should be true
  CPPUNIT_ASSERT( m_instance->isDirty());
}

/// Test the dirty propagation property
void DrawableTest::testDirtyPropagation(){ 
  // No segfault if parent is NULL ?
  Drawable* d1=new Drawable(NULL, RECT);
  d1->setDirty(true);
  
  // Propagation test
  d1->setDirty(false);
  CPPUNIT_ASSERT( d1->isDirty() == false);
  Drawable d2(d1, RECT);      // Creating a child
  d2.setDirty(true);     // Parent should be dirty now
  CPPUNIT_ASSERT( d1->isDirty() == true);
  d2.setDirty(false);     // Parent should also be dirty
  CPPUNIT_ASSERT( d1->isDirty() == true);
  delete d1;
}

/// Test the correct computation of absolute position
void DrawableTest::testComputeAbsolute(){ 
  Rectangle r1;
  setRectangle(&r1, 50, 50 ,100 ,100);
  Drawable d(NULL, r1);
  d.compute(20, 30, r1); // to call computeAbsolute
  Rectangle r2 = d.getAbsolute();
  CPPUNIT_ASSERT( r2.left == r1.left + 20);
  CPPUNIT_ASSERT( r2.right == r1.right + 20);
  CPPUNIT_ASSERT( r2.top == r1.top + 30);
  CPPUNIT_ASSERT( r2.bottom == r1.bottom + 30);
}

/// First test of scissor adjustement
void DrawableTest::testAdjustScissor1(){ 
  Rectangle r1;
  setRectangle(&r1, 50, 50 ,100 ,100);
  Drawable d(NULL, r1);
  
  // First test : chop all
  Rectangle s1;
  setRectangle(&s1, 70, 75 ,80 ,85);
  d.compute(0, 0, s1); // to call computeAbsolute
  Rectangle r2 = d.getScissor();
  CPPUNIT_ASSERT( r2.left   == 70);
  CPPUNIT_ASSERT( r2.right  == 80);
  CPPUNIT_ASSERT( r2.top    == 75);
  CPPUNIT_ASSERT( r2.bottom == 85);
}

/// Second test of scissor adjustement
void DrawableTest::testAdjustScissor2(){ 
  Rectangle r1;
  setRectangle(&r1, 50, 50 ,100 ,100);
  Drawable d(NULL, r1);

  // First test : chop none
  Rectangle s1;
  setRectangle(&s1, 30, 35 ,110 ,115);
  d.compute(0, 0, s1); // to call computeAbsolute
  Rectangle r2 = d.getScissor();
  CPPUNIT_ASSERT( r2.left   == 50);
  CPPUNIT_ASSERT( r2.right  == 100);
  CPPUNIT_ASSERT( r2.top    == 50);
  CPPUNIT_ASSERT( r2.bottom == 100);
}

/** Set the values of a rectangle
  *
  * \param r  The rectangle to change values to
  * \param x1 The left value
  * \param y1 The top value
  * \param x2 The right value
  * \param y2 The bottom value
  *
  */
void DrawableTest::setRectangle(Rectangle* r, int x1, int y1, int x2, int y2){
  r->left   = x1;
  r->top    = y1;
  r->right  = x2;
  r->bottom = y2;
}

/** Test the loading of a texture by its name
  *
  *
  *
  */

void DrawableTest::listRenderers(void){
  Ogre::RenderSystemList::iterator listIt;
  Ogre::RenderSystemList* list=Ogre::Root::getSingleton().getAvailableRenderers();

  // Adds the render name to the hold browser
  cout << "Listing available Ogre renderers :" << endl;
  for( listIt= list->begin(); listIt!= list->end(); listIt++){
    cout << (*listIt)->getName().c_str() << endl;
  }
}

void DrawableTest::testLoadTexture()
{
  TexturePtr t;
  try{
    string dir="../../../config/";
    new Ogre::Root(dir + "plugins.cfg", dir + "ogre.cfg", dir + "ogre-unittests.log");
    listRenderers();

    // Select rendersystem
    Ogre::Root::getSingleton().initialise(false, "RainbruRPG blah");
    Ogre::RenderSystemList* list=Ogre::Root::getSingleton().getAvailableRenderers();
    Ogre::Root::getSingleton().setRenderSystem((*list->begin()));
    Ogre::LogManager::getSingleton().createLog("Ogre.log", true, false, true);
    Ogre::Root::getSingleton().addResourceLocation("../../../data/", "FileSystem");
    Ogre::Root::getSingleton().getRenderSystem()->createRenderWindow("a", 20, 20, false);

    setupOgre();
    cout << "Calling loadTexture fot the first time" << endl;
    TextureManager::getSingleton().setDefaultNumMipmaps(5);
    t = m_instance->loadTexture("main.bmp");
  }
  catch(const Ogre::RenderingAPIException e){
    cout << "Meuuuuuuuuuuuh" << endl;
  }
  CPPUNIT_ASSERT(!t.isNull());
}

void DrawableTest::testLoadTextureThrow()
{
  setupOgre();
  m_instance->loadTexture("UnbelievableTextureNameThatShouldNotBeFound");
}

void DrawableTest::setupOgre()
{
  mRoot = &Ogre::Root::getSingleton();
  
}


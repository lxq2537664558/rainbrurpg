/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file DrawableTest.cpp
  * A test case for ogreGui's Drawable 
  *
  * \note These tests are only for Drawable without Ogre. For Drawable tests
  *       needing Ogre, please see DrawableTestWithOgre.
  *
  */

#include "Drawable.hpp"
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

/// Initialization wrapper for Ogre::Rectangle
void drawable_test_set_rectangle(Ogre::Rectangle* r, int x1, int y1, int x2, int y2)
{
  r->left   = x1;
  r->top    = y1;
  r->right  = x2;
  r->bottom = y2;
}


Drawable* setup_Drawable()
{
  return new Drawable(NULL, RECT);
}

void teardown_Drawable(Drawable* d)
{
  delete d;
}

/// Test if the parent is correctly set by the constructor
BOOST_AUTO_TEST_CASE( test_drawable_parent )
{
  Drawable d1(NULL, RECT);
  BOOST_ASSERT( d1.getParent() == NULL);
  Drawable d2(&d1, RECT);
  BOOST_ASSERT( d2.getParent() != NULL);
  BOOST_ASSERT( d2.getParent() == &d1);
}

/// Test the dirty flag
BOOST_AUTO_TEST_CASE( test_drawable_dirty_flag )
{
  // At startup, dirty should be true
  Drawable* instance = setup_Drawable();
  BOOST_ASSERT( instance->isDirty());
  teardown_Drawable(instance);
}

/// Test the dirty propagation property
BOOST_AUTO_TEST_CASE( test_drawable_dirty_propagation )
{
  // No segfault if parent is NULL ?
  Drawable* d1=setup_Drawable();
  d1->setDirty(true);
  
  // Propagation test
  d1->setDirty(false);
  BOOST_ASSERT( d1->isDirty() == false);
  Drawable d2(d1, RECT);      // Creating a child
  d2.setDirty(true);     // Parent should be dirty now
  BOOST_ASSERT( d1->isDirty() == true);
  d2.setDirty(false);     // Parent should also be dirty
  BOOST_ASSERT( d1->isDirty() == true);
  teardown_Drawable(d1);
}

/// Test the correct computation of absolute position
BOOST_AUTO_TEST_CASE( test_drawable_compute_absolute )
{
  Rectangle r1;
  drawable_test_set_rectangle(&r1, 50, 50 ,100 ,100);
  Drawable d(NULL, r1);
  d.compute(20, 30, r1); // to call computeAbsolute
  Rectangle r2 = d.getAbsolute();
  BOOST_ASSERT( r2.left == r1.left + 20);
  BOOST_ASSERT( r2.right == r1.right + 20);
  BOOST_ASSERT( r2.top == r1.top + 30);
  BOOST_ASSERT( r2.bottom == r1.bottom + 30);
}

/// First test of scissor adjustement
BOOST_AUTO_TEST_CASE( test_drawable_adjust_scissor_1 )
{
  Rectangle r1;
  drawable_test_set_rectangle(&r1, 50, 50 ,100 ,100);
  Drawable d(NULL, r1);
  
  // First test : chop all
  Rectangle s1;
  drawable_test_set_rectangle(&s1, 70, 75 ,80 ,85);
  d.compute(0, 0, s1); // to call computeAbsolute
  Rectangle r2 = d.getScissor();
  BOOST_ASSERT( r2.left   == 70);
  BOOST_ASSERT( r2.right  == 80);
  BOOST_ASSERT( r2.top    == 75);
  BOOST_ASSERT( r2.bottom == 85);
}

/// Second test of scissor adjustement
BOOST_AUTO_TEST_CASE( test_drawable_adjust_scissor_2 )
{
  Rectangle r1;
  drawable_test_set_rectangle(&r1, 50, 50 ,100 ,100);
  Drawable d(NULL, r1);

  // First test : chop none
  Rectangle s1;
  drawable_test_set_rectangle(&s1, 30, 35 ,110 ,115);
  d.compute(0, 0, s1); // to call computeAbsolute
  Rectangle r2 = d.getScissor();
  BOOST_ASSERT( r2.left   == 50);
  BOOST_ASSERT( r2.right  == 100);
  BOOST_ASSERT( r2.top    == 50);
  BOOST_ASSERT( r2.bottom == 100);
}

/// Test the drawable's skin name propagation from parent
BOOST_AUTO_TEST_CASE( test_drawable_skin_name_1 )
{
  Rectangle r1;
  drawable_test_set_rectangle(&r1, 50, 50 ,100 ,100);
  Drawable parent(NULL, r1, "DummySkinName");
  Drawable child(&parent, r1);
  BOOST_ASSERT( parent.getSkinName() == child.getSkinName());
}

/// Test the drawable's skin name non-propagation from parent
BOOST_AUTO_TEST_CASE( test_drawable_skin_name_2 )
{
  Rectangle r1;
  drawable_test_set_rectangle(&r1, 50, 50 ,100 ,100);
  Drawable parent(NULL, r1, "DummySkinName");
  Drawable child(&parent, r1, "OtherskinName");
  BOOST_ASSERT( parent.getSkinName() != child.getSkinName());
}


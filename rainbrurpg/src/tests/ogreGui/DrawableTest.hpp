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

#ifndef DRAWABLE_TEST_H
#define DRAWABLE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>
#include <sstream>
#include <iostream>

#include <Drawable.hpp>
#include <OgreRectangle.h>

using namespace std;
using namespace Ogre;
using namespace RainbruRPG::OgreGui;

#define RECT Rectangle()

/** A test case for ogreGui's Drawable
  *
  */
template<class TESTEDCLASS> 
class DrawableTest : public CPPUNIT_NS::TestFixture 
{
  CPPUNIT_TEST_SUITE( DrawableTest );

  CPPUNIT_TEST( testParent );
  CPPUNIT_TEST( testDirty );
  CPPUNIT_TEST( testDirtyPropagation );
  CPPUNIT_TEST( testComputeAbsolute );
  CPPUNIT_TEST( testAdjustScissor1 );
  CPPUNIT_TEST( testAdjustScissor2 );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the caption widget
    *
    */
  TESTEDCLASS	*m_instance;
  
public:
  /** Return the number of test cases
    *
    * \return Currently always return 1
    *
    */
  int countTestCases () const{ return 1;  }
  
  /** Creates a new instance to test
    *
    */
  void setUp(){ 
    this->m_instance = new TESTEDCLASS(NULL, RECT); 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_instance; 
  }
  
  // Test if the parent is correctly set by the constructor
  void testParent(){ 
    Drawable d1(NULL, RECT);
    CPPUNIT_ASSERT( d1.getParent() == NULL);
    Drawable d2(&d1, RECT);
    CPPUNIT_ASSERT( d2.getParent() != NULL);
    CPPUNIT_ASSERT( d2.getParent() == &d1);
  }

  // Test the dirty flag
  void testDirty(){ 
    // At startup, dirty should be true
    CPPUNIT_ASSERT( m_instance->isDirty());
    
  }

  // Test the dirty propagation property
  void testDirtyPropagation(){ 
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

  void testComputeAbsolute(){ 
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

  void testAdjustScissor1(){ 
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

  void testAdjustScissor2(){ 
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

  void setRectangle(Rectangle* r, int x1, int y1, int x2, int y2){
    r->left   = x1;
    r->top    = y1;
    r->right  = x2;
    r->bottom = y2;
  }
};


#endif // DRAWABLE_TEST_H

/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

#ifndef SCROLLING_PANEL_TEST_H
#define SCROLLING_PANEL_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <menu.h>
#include <logger.h>

#include <string>

using namespace std;

/** A test fixture for the ScrollingPanel class
  *
  */
template<class TESTEDCLASS> 
class ScrollingPanelTest : public CPPUNIT_NS::TestFixture 
{
  /// Declares the ScrollingPanelTest test fixture
  CPPUNIT_TEST_SUITE( ScrollingPanelTest );

    /// Launches the testScrollingPanelLogicalSize() test
    CPPUNIT_TEST( testScrollingPanelLogicalSize );
    /// Launches the testScrollingPanelPhysicalSize() test
    CPPUNIT_TEST( testScrollingPanelPhysicalSize );
    /// Launches the testScrollingPanelXOffset() test
    CPPUNIT_TEST( testScrollingPanelXOffset );
    /// Launches the testScrollingPanelYOffset() test
    CPPUNIT_TEST( testScrollingPanelYOffset );
    /// Launches the testScrollingPanelGoDown() test
    CPPUNIT_TEST( testScrollingPanelGoDown );
    /// Launches the testScrollingPanelGoLeft() test
    CPPUNIT_TEST( testScrollingPanelGoLeft );
    /// Launches the testScrollingPanelGoRight() test
    CPPUNIT_TEST( testScrollingPanelGoRight );
    /// Launches the testScrollingPanelGoUp() test
    CPPUNIT_TEST( testScrollingPanelGoUp );

  /// Terminates the tests
  CPPUNIT_TEST_SUITE_END();
protected:
  /** The tested ScrollingPanel instance */
  TESTEDCLASS	*m_caption;
  
public:
  /** Return the number of test case
    *
    * \return Always 1
    *
    */
  int countTestCases () const{
    return 1;
  }

  /** Construct the tested instance
    *
    */
  void setUp(){ 
    this->m_caption = new TESTEDCLASS; 
  }
  
  /** Deletes the tested instance
    *
    */
  void tearDown(){ 
    delete this->m_caption; 
  }
  
  /** Tests the setLogicalSize function
    *
    */
  void testScrollingPanelLogicalSize(){ 
    int w=10;
    int h=12;
    this->m_caption->setLogicalSize(w, h);

    int w2=this->m_caption->getLogicalWidth();
    int h2=this->m_caption->getLogicalHeight();
 
    CPPUNIT_ASSERT( w==w2 && h==h2 );
  }

  /** Tests the setPhysicalSize function
    *
    */
  void testScrollingPanelPhysicalSize(){ 
    int w=10;
    int h=12;
    this->m_caption->setPhysicalSize(w, h);

    int w2=this->m_caption->getPhysicalWidth();
    int h2=this->m_caption->getPhysicalHeight();
 
    CPPUNIT_ASSERT( w==w2 && h==h2 );
  }

  /** Tests the setXOffset function
    *
    */
  void testScrollingPanelXOffset(){
    int x=14;
    this->m_caption->setXOffset(x);
    int x2=this->m_caption->getXOffset();

    CPPUNIT_ASSERT( x==x2 );
  }

  /** Tests the setYOffset function
    *
    */
  void testScrollingPanelYOffset(){
    int y=15;
    this->m_caption->setYOffset(y);
    int y2=this->m_caption->getYOffset();

    CPPUNIT_ASSERT( y==y2 );
  }

  /** Tests the goDown function
    *
    */
  void testScrollingPanelGoDown(){
    this->m_caption->setLogicalHeight(40);
    this->m_caption->setPhysicalHeight(20);
    int y=8;
    this->m_caption->setYOffset(y);
    this->m_caption->goDown();
    int y2=this->m_caption->getYOffset();
    CPPUNIT_ASSERT( y2==++y );
  }

  /** Tests the goUp function
    *
    */
  void testScrollingPanelGoUp(){
    this->m_caption->setLogicalHeight(40);
    this->m_caption->setPhysicalHeight(20);
    int y=16;
    this->m_caption->setYOffset(y);
    this->m_caption->goUp();
    int y2=this->m_caption->getYOffset();
    CPPUNIT_ASSERT( y2==--y );
  }

  /** Tests the goLeft function
    *
    */
  void testScrollingPanelGoLeft(){
    this->m_caption->setLogicalWidth(40);
    this->m_caption->setPhysicalWidth(20);
    int x=10;
    this->m_caption->setXOffset(x);
    this->m_caption->goLeft();
    int x2=this->m_caption->getXOffset();
    CPPUNIT_ASSERT( x2==--x );
  }

  /** Tests the goRight function
    *
    */
  void testScrollingPanelGoRight(){
    this->m_caption->setLogicalWidth(40);
    this->m_caption->setPhysicalWidth(20);
    int x=12;
    this->m_caption->setXOffset(x);
    this->m_caption->goRight();
    int x2=this->m_caption->getXOffset();
    CPPUNIT_ASSERT( x2==++x );
  }
};


#endif // SCROLLING_PANEL_TEST_H

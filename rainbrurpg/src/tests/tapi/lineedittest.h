/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file lineedittest.h
  * Implements the unit tests of the LineEdit class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef LINEEDIT_TEST_H
#define LINEEDIT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

//#include <caption.h>

#include <string>

using namespace std;


/** A test class for TerminalAPI's LineEdit widget
  *
  */
template<class TESTEDCLASS> 
class LineEditTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the LineEdit test 
  CPPUNIT_TEST_SUITE( LineEditTest );

  /** Tests the LineEdit's caption
    *
    * \sa testLineEditCaption
    *
    */
  CPPUNIT_TEST( testLineEditCaption );

  /** Tests the LineEdit's x position
    *
    * \sa testLineEditX
    *
    */
  CPPUNIT_TEST( testLineEditX );

  /** Tests the LineEdit's y position
    *
    * \sa testLineEditY
    *
    */
  CPPUNIT_TEST( testLineEditY );

  /** Tests the LineEdit's width
    *
    * \sa testLineEditWidth
    *
    */
  CPPUNIT_TEST( testLineEditWidth );

  /** Tests the LineEdit's height
    *
    * \sa testLineEditHeight
    *
    */
  CPPUNIT_TEST( testLineEditHeight );

  /** Tests the LineEdit's hasfocus
    *
    * \sa testLineEditHasFocus
    *
    */
  CPPUNIT_TEST( testLineEditHasFocus );

  /** Tests the LineEdit's hasfocus
    *
    * \sa testLineEditHasntFocus
    *
    */
  CPPUNIT_TEST( testLineEditHasntFocus );

  /** Tests the LineEdit's can take focus
    *
    * \sa testLineEditCanTakeFocus
    *
    */
  CPPUNIT_TEST( testLineEditCanTakeFocus );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the LineEdit widget
    *
    */
  TESTEDCLASS	*m_instance;
  
public:
  /** Return the number of test cases
    *
    * \return Currently always return 1
    *
    */
  int countTestCases () const{
    return 1;
  }
  
  /** Creates a new instance to test
    *
    */
  void setUp(){ 
    this->m_instance = new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_instance; 
  }
  
  /** Tests the LineEdit caption
    *
    * It simply set a new text to the LineEdit and test if the 
    * string given by Caption::getText() is the same.
    *
    */
  void testLineEditCaption(){ 
    string t="TestCaption";
    this->m_instance->setText(t);
    string ret=this->m_instance->getText();
    CPPUNIT_ASSERT( t == ret );
  }

  /** Tests the LineEdit x position
    *
    * It simply set a new x value to the LineEdit and test if the 
    * string given by Caption::getX() is the same.
    *
    */
  void testLineEditX(){ 
    int x=1;
    this->m_instance->setX(x);
    int ret=this->m_instance->getX();
    CPPUNIT_ASSERT( x==ret );
  }

  /** Tests the LineEdit y position
    *
    * It simply set a new y value to the LineEdit and test if the 
    * string given by Caption::getY() is the same.
    *
    */
  void testLineEditY(){ 
    int y=2;
    this->m_instance->setY(y);
    int ret=this->m_instance->getY();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the LineEdit width
    *
    * It simply set a new width value to the LineEdit and test if the 
    * string given by Caption::getWidth() is the same.
    *
    */
  void testLineEditWidth(){ 
    int y=3;
    this->m_instance->setWidth(y);
    int ret=this->m_instance->getWidth();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the LineEdit height
    *
    * It simply set a new height value to the LineEdit and test if the 
    * string given by Caption::getHeight() is the same.
    *
    */
  void testLineEditHeight(){ 
    int y=4;
    this->m_instance->setHeight(y);
    int ret=this->m_instance->getHeight();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the LineEdit Focus
    *
    * It simply set a new focus value to the LineEdit and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testLineEditHasFocus(){
    this->m_instance->setFocus(true);
    CPPUNIT_ASSERT( this->m_instance->getFocus() );

  }

  /** Tests the LineEdit Focus
    *
    * It simply set a new focus value to the LineEdit and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testLineEditHasntFocus(){
    this->m_instance->setFocus(false);
    CPPUNIT_ASSERT( !this->m_instance->getFocus() );
  }

  /** Tests if the label can take focus
    *
    * The LineEdit widget should be able to take focus
    *
    */
  void testLineEditCanTakeFocus(){
    CPPUNIT_ASSERT( this->m_instance->canHaveFocus());
  }

};


#endif // LINEEDIT_TEST_H

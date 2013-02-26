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

/** \file labeltest.h
  * Implements the unit tests of the Label class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef LABEL_TEST_H
#define LABEL_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

//#include <caption.h>

#include <string>
#include <cstring> // For strcmp

using namespace std;


/** A test class for TerminalAPI's  Label widget
  *
  */
template<class TESTEDCLASS> 
class LabelTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the Label test 
  CPPUNIT_TEST_SUITE( LabelTest );

  /** Tests the Label's caption
    *
    * \sa testLabelCaption
    *
    */
  CPPUNIT_TEST( testLabelCaption );

  /** Tests the Label's X position
    *
    * \sa testLabelX
    *
    */
  CPPUNIT_TEST( testLabelX );

  /** Tests the Label's Y position
    *
    * \sa testLabelY
    *
    */
  CPPUNIT_TEST( testLabelY );

  /** Tests the Label's width
    *
    * \sa testLabelWidth
    *
    */
  CPPUNIT_TEST( testLabelWidth );

  /** Tests the Label's height
    *
    * \sa testLabelHeight
    *
    */
  CPPUNIT_TEST( testLabelHeight );

  /** Tests the Label's focus
    *
    * \sa testLabelHasFocus
    *
    */
  CPPUNIT_TEST( testLabelHasFocus );

  /** Tests the Label's focus
    *
    * \sa testLabelHasntFocus
    *
    */
  CPPUNIT_TEST( testLabelHasntFocus );

  /** Tests the Label's canTakeFocus
    *
    * \sa testLabelCanTakeFocus
    *
    */
  CPPUNIT_TEST( testLabelCanTakeFocus );

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
  
  /** Tests the Label caption
    *
    * It simply set a new text to the Label and test if the 
    * string given by Caption::getText() is the same.
    *
    */
  void testLabelCaption(){ 
    std::string t="TestCaption";
    this->m_instance->setText(t);
    string ret = m_instance->getText();
    CPPUNIT_ASSERT( t == ret );
  }

  /** Tests the Label x position
    *
    * It simply set a new x value to the Label and test if the 
    * string given by Caption::getX() is the same.
    *
    */
  void testLabelX(){ 
    int x=1;
    this->m_instance->setX(x);
    int ret=this->m_instance->getX();
    CPPUNIT_ASSERT( x==ret );
  }

  /** Tests the Label y position
    *
    * It simply set a new y value to the Label and test if the 
    * string given by Caption::getY() is the same.
    *
    */
  void testLabelY(){ 
    int y=2;
    this->m_instance->setY(y);
    int ret=this->m_instance->getY();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the Label width
    *
    * It simply set a new width value to the Label and test if the 
    * string given by Caption::getWidth() is the same.
    *
    */
  void testLabelWidth(){ 
    int y=3;
    this->m_instance->setWidth(y);
    int ret=this->m_instance->getWidth();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the Label height
    *
    * It simply set a new height value to the Label and test if the 
    * string given by Caption::getHeight() is the same.
    *
    */
  void testLabelHeight(){ 
    int y=4;
    this->m_instance->setHeight(y);
    int ret=this->m_instance->getHeight();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the Label Focus
    *
    * It simply set a new focus value to the Label and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testLabelHasFocus(){
    this->m_instance->setFocus(true);
    CPPUNIT_ASSERT( this->m_instance->getFocus() );

  }

  /** Tests the Label Focus
    *
    * It simply set a new focus value to the Label and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testLabelHasntFocus(){
    this->m_instance->setFocus(false);
    CPPUNIT_ASSERT( !this->m_instance->getFocus() );
  }

  /** Tests if the label can take focus
    *
    * The Label widget should not be able to take focus
    *
    */
  void testLabelCanTakeFocus(){
    CPPUNIT_ASSERT( !this->m_instance->canHaveFocus());
  }

};


#endif // LABEL_TEST_H

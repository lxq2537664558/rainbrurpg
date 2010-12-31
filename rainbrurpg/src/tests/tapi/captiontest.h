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

/** \file captiontest.h
  * Implements the unit tests of the Caption class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef CAPTION_TEST_H
#define CAPTION_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <caption.h>

#include <string>

using namespace std;

/** A test class for TerminalAPI caption widget
  *
  */
template<class TESTEDCLASS> 
class CaptionTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the caption test 
  CPPUNIT_TEST_SUITE( CaptionTest );

  /** Tests the caption's text
    *
    * \sa testCaptionText
    *
    */
  CPPUNIT_TEST( testCaptionText );

  /** Tests the caption's type
    *
    * \sa testCaptionType
    *
    */
  CPPUNIT_TEST( testCaptionType );

  /** Tests the caption's height
    *
    * \sa testCaptionHeight
    *
    */
  CPPUNIT_TEST( testCaptionHeight );

  /** Tests the caption's width
    *
    * \sa testCaptionWidth
    *
    */
  CPPUNIT_TEST( testCaptionWidth );

  /** Tests the xoffset caption value
    *
    * \sa testCaptionXOffset
    *
    */
  CPPUNIT_TEST( testCaptionXOffset );

  /** Tests the yoffset caption value
    *
    * \sa testCaptionYOffset
    *
    */
  CPPUNIT_TEST( testCaptionYOffset );

  /** Tests the xpos caption value
    *
    * \sa testCaptionXpos
    *
    */
  CPPUNIT_TEST( testCaptionXpos );

  /** Tests the ypos caption value
    * 
    * \sa testCaptionYPos
    *
    */
  CPPUNIT_TEST( testCaptionYPos );

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
  int countTestCases(){
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
  
  /** Tests the Caption text field
    *
    * It simply set a new text to the Caption and test if the 
    * string given by Caption::getText() is the same.
    *
    */
  void testCaptionText(){ 
    std::string t="TestString";
    this->m_instance->setText(t);
    std::string ret=this->m_instance->getText();
    int cmp=t.compare(ret);
    CPPUNIT_ASSERT( cmp==0 );
  }

  /** Tests the Caption type field
    *
    * It simply set a new type to the Caption and test if the 
    * type given by Caption::getType() is the same.
    *
    */
  void testCaptionType(){ 
    RainbruRPG::Terminal::tCaptionType t=RainbruRPG::Terminal::SCROLLED;
    this->m_instance->setType(t);
    CPPUNIT_ASSERT( this->m_instance->getType()==t );
  }

  /** Tests the Caption height field
    *
    * It simply set a new height to the Caption and test if the 
    * type given by Caption::getHeight() is the same.
    *
    */
  void testCaptionHeight(){
    int h=12;
    this->m_instance->setHeight(h);
    CPPUNIT_ASSERT( this->m_instance->getHeight()==h );
  }

  /** Tests the Caption width field
    *
    * It simply set a new width to the Caption and test if the 
    * type given by Caption::getWidth() is the same.
    *
    */
  void testCaptionWidth(){
    int h=10;
    this->m_instance->setWidth(h);
    CPPUNIT_ASSERT( this->m_instance->getWidth()==h );
  }

  /** Tests the Caption xOffset field
    *
    * It simply set a new yOffset  to the Caption and test if the 
    * type given by Caption::getXOffset() is the same.
    *
    */
  void testCaptionXOffset(){
    int h=4;
    this->m_instance->setXOffset(h);
    CPPUNIT_ASSERT( this->m_instance->getXOffset()==h );
  }

  /** Tests the Caption yOffset field
    *
    * It simply set a new yOffset  to the Caption and test if the 
    * type given by Caption::getYOffset() is the same.
    *
    */
  void testCaptionYOffset(){
    int h=5;
    this->m_instance->setYOffset(h);
    CPPUNIT_ASSERT( this->m_instance->getYOffset()==h );
  }

  /** Tests the Caption xPos field
    *
    * It simply set a new xPos  to the Caption and test if the 
    * type given by Caption::getXPos() is the same.
    *
    */
  void testCaptionXpos(){
    int h=65;
    this->m_instance->setXPos(h);
    CPPUNIT_ASSERT( this->m_instance->getXPos()==h );
  }

  /** Tests the Caption yPos field
    *
    * It simply set a new yPos  to the Caption and test if the 
    * type given by Caption::getYPos() is the same.
    *
    */
  void testCaptionYPos(){
    int h=64;
    this->m_instance->setYPos(h);
    CPPUNIT_ASSERT( this->m_instance->getYPos()==h );
  }
};


#endif // CAPTION_TEST_H

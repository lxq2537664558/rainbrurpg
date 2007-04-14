/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

#ifndef PUSHBUTTON_TEST_H
#define PUSHBUTTON_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>

using namespace std;

int PushButtonTestAction(){
  return 225;
}

/** A test fixture for PushButton
  *
  */
template<class TESTEDCLASS> 
class PushButtonTest : public CPPUNIT_NS::TestFixture 
{
  /// Declares the ScrollingPanelTest test fixture
  CPPUNIT_TEST_SUITE( PushButtonTest );
    /// Launches the testPushButtonCanHaveFocus() test
    CPPUNIT_TEST( testPushButtonCanHaveFocus );
    /// Launches the testPushButtonEmptyAction() test
    CPPUNIT_TEST( testPushButtonEmptyAction );
    /// Launches the testPushButtonFireAction() test
    CPPUNIT_TEST( testPushButtonFireAction );
    /// Launches the testPushButtonSetFocus() test
    CPPUNIT_TEST( testPushButtonSetFocus );
    /// Launches the testPushButtonHeight() test
    CPPUNIT_TEST( testPushButtonHeight );
    /// Launches the testPushButtonWidth() test
    CPPUNIT_TEST( testPushButtonWidth );
    /// Launches the testPushButtonText() test
    CPPUNIT_TEST( testPushButtonText );
    /// Launches the testPushButtonX() test
    CPPUNIT_TEST( testPushButtonX );
    /// Launches the testPushButtonY() test
    CPPUNIT_TEST( testPushButtonY );
    /// Launches the testPushButtonPosition() test
    CPPUNIT_TEST( testPushButtonPosition );
    /// Launches the testPushButtonSize() test
    CPPUNIT_TEST( testPushButtonSize );
  /// Terminates the tests
  CPPUNIT_TEST_SUITE_END();

protected:
  /** The tested PushButton instance */
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
  
  /** Construct the etsted instance
    *
    */
  void setUp(){ 
    this->m_caption = new TESTEDCLASS; 
  }
  
  /** Deletes the etsted instance
    *
    */
  void tearDown(){ 
    delete this->m_caption; 
  }
  
  /** Tests the canHaveFocus
    *
    * A PushButton should return true.
    * 
    */
  void testPushButtonCanHaveFocus(){ 
    bool ret=this->m_caption->canHaveFocus();
    CPPUNIT_ASSERT( ret );
  }

  /** Fires the event and check if it returns -1
    *
    * If none pointer function was set, int MenuItem::fireAction()
    * should return -1.
    *
    */
  void testPushButtonEmptyAction(){
    int ret=this->m_caption->fireAction();
    CPPUNIT_ASSERT( ret==-1 );

  }

  /** Sets an action modifying a static var and fires the action to test
    * if the static var was modified
    *
    */
  void testPushButtonFireAction(){
    this->m_caption->setAction(&PushButtonTestAction);
    int ret=this->m_caption->fireAction();
    CPPUNIT_ASSERT( ret==225 );
  }

  /** Test the setFocus function
    *
    * It sets the focus state to true and check if the change was ok
    */
  void testPushButtonSetFocus(){
    this->m_caption->setFocus(true);
    int ret=this->m_caption->getFocus();
    CPPUNIT_ASSERT( ret );
  }

  /** Tests the height field
    *
    */
  void testPushButtonHeight(){
    int i=25;
    this->m_caption->setHeight(i);
    int ret=this->m_caption->getHeight();
    CPPUNIT_ASSERT( ret==i );
  }

  /** Tests the width field
    *
    */
  void testPushButtonWidth(){
    int i=15;
    this->m_caption->setWidth(i);
    int ret=this->m_caption->getWidth();
    CPPUNIT_ASSERT( ret==i );
  }

  /** Tests the setText field
    *
    */
  void testPushButtonText(){
    const char* t="PushButtonText";
    this->m_caption->setText(t);
    const char* t2=this->m_caption->getText();
    int ret=strcmp(t, t2);
    CPPUNIT_ASSERT( ret==0 );
  }

  /** Tests the x position
    *
    */
  void testPushButtonX(){
    int i=16;
    this->m_caption->setX(i);
    int ret=this->m_caption->getX();
    CPPUNIT_ASSERT( ret==i );
  }

  /** Tests the y position
    *
    */
  void testPushButtonY(){
    int i=16;
    this->m_caption->setY(i);
    int ret=this->m_caption->getY();
    CPPUNIT_ASSERT( ret==i );
  }

  /** Tests the setPosition
    *
    */
  void testPushButtonPosition(){
    int x=4;
    int y=53;
    this->m_caption->setPosition(x,y);
    int x2=this->m_caption->getX();
    int y2=this->m_caption->getY();
    CPPUNIT_ASSERT( x==x2 && y==y2 );
  }

  /** Tests the setSize
    *
    */
  void testPushButtonSize(){
    int w=14;
    int h=43;
    this->m_caption->setSize(w,h);
    int w2=this->m_caption->getWidth();
    int h2=this->m_caption->getHeight();
    CPPUNIT_ASSERT( w==w2 && h==h2 );
  }
};


#endif // PUSHBUTTON_TEST_H

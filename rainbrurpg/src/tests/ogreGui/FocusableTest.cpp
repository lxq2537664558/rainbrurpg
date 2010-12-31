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

#include "FocusableTest.hpp"

// Registers the fixture to the registry
CPPUNIT_TEST_SUITE_REGISTRATION( FocusableTest );
  
/** Creates a new instance to test
  *
  */
void FocusableTest::setUp()
{ 
    this->m_instance = new Focusable(true); 
  }
  
/** Delete the current tested instance
 *
 */
void FocusableTest::tearDown()
{ 
  delete this->m_instance; 
}

/** Test if the constructor correctly set members
  *
  */
void FocusableTest::testConstructor()
{
  // Test if this tested instance is focusable
  CPPUNIT_ASSERT( m_instance->canTakeFocus() == true);
  CPPUNIT_ASSERT( m_instance->hasFocus() == false);

  // Test of a non-focusable object
  Focusable f(false);
  CPPUNIT_ASSERT( f.canTakeFocus() == false);
  CPPUNIT_ASSERT( f.hasFocus() == false);
}

/** Tests if we can change the canTakeFocus value
  *
  */
void FocusableTest::testCanTakeFocus()
{
  m_instance->setCanTakeFocus(false);
  CPPUNIT_ASSERT( m_instance->canTakeFocus() == false);

  m_instance->setCanTakeFocus(true);
  CPPUNIT_ASSERT( m_instance->canTakeFocus() == true);

}

/** Tests if all events are consumed by default
  *
  */
void FocusableTest::testConsumedEvents()
{
  OIS::KeyEvent ke(NULL, OIS::KC_A, 0); // A default KeyEvent

  CPPUNIT_ASSERT( m_instance->keyPressed(ke) == false);
  CPPUNIT_ASSERT( m_instance->keyReleased(ke) == false);
  
  OIS::MouseEvent me(NULL, OIS::MouseState());
  CPPUNIT_ASSERT( m_instance->mouseMoved(me) == false);

  OIS::MouseButtonID mb = OIS::MB_Right;
  CPPUNIT_ASSERT( m_instance->mousePressed(me, mb) == false);
  CPPUNIT_ASSERT( m_instance->mouseReleased(me, mb) == false);
}

/// Test the focus status
void FocusableTest::testFocus()
{
  // Should be false by default
  CPPUNIT_ASSERT( m_instance->hasFocus() == false);

  m_instance->setFocus(true);
  CPPUNIT_ASSERT( m_instance->hasFocus() == true);

  m_instance->setFocus(false);
  CPPUNIT_ASSERT( m_instance->hasFocus() == false);

}

/// Tests the focus status of a non-focusable object
void FocusableTest::testNonFocusableFocus()
{
  // The current instance is focusable by default
  m_instance->setFocus(true);
  CPPUNIT_ASSERT( m_instance->hasFocus() == true);

  // Setting canTakeFocus to false should set focus to false
  m_instance->setCanTakeFocus(false);
  CPPUNIT_ASSERT( m_instance->hasFocus() == false);

  // Setting focus to a non-focusable object should not work
  m_instance->setFocus(true);
  CPPUNIT_ASSERT( m_instance->hasFocus() == false);

}

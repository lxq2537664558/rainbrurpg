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

#include "ContainerTest.hpp"

// Registers the fixture to the registry
CPPUNIT_TEST_SUITE_REGISTRATION( ContainerTest );

/// Setup the tested Container instance
void ContainerTest::setUp()
{
  m_instance = new Container(NULL, "TestedContainer", 0, 0, 10, 10);
}

/// Delete the tested Container instance
void ContainerTest::tearDown()
{
  delete m_instance;
}

/// Tests that an empty container always returns \c false
void ContainerTest::testEmpty()
{
  bool ret;
  OIS::KeyEvent ke(NULL, OIS::KC_A, 0);

  ret = m_instance->keyPressed( ke );
  CPPUNIT_ASSERT( ret == false);

  ret = m_instance->keyReleased( ke );
  CPPUNIT_ASSERT( ret == false);
}

/// Test with a Focusable
void ContainerTest:: testTrueFocusable()
{
  bool ret;
  OIS::KeyEvent ke(NULL, OIS::KC_A, 0);

  // Widget is a true focusable by default
  Widget w(NULL, "test widget", 0, 0, 10, 10);
  m_instance->push_back(&w);

  // Should always return false because focused widget
  // didn't change
  ret = m_instance->keyPressed( ke );
  CPPUNIT_ASSERT( ret == false);

  ret = m_instance->keyReleased( ke );
  CPPUNIT_ASSERT( ret == false);

  // Focus the added widget
  m_instance->focusNext();

  ret = m_instance->keyPressed( ke );
  CPPUNIT_ASSERT( ret == false);

  ret = m_instance->keyReleased( ke );
  CPPUNIT_ASSERT( ret == false);
  
}

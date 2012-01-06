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

/** \file FocusableTest.cpp
  * A test case for ogreGui's Focusable
  *
  */

#include "Focusable.hpp"

#include <boost/test/unit_test.hpp>

// Do not use namespace Ogre for Rectangle and win32 name conflicts
using namespace RainbruRPG::OgreGui;

Focusable* setup_Focusable()
{
  return new Focusable(true);
}

void teardown_Focusable(Focusable* d)
{
  delete d;
}

/// Test if the constructor correctly set members
BOOST_AUTO_TEST_CASE( test_focuable_constructor )
{
  Focusable* instance = setup_Focusable();
  // Test if this tested instance is focusable
  BOOST_ASSERT( instance->canTakeFocus() == true);
  BOOST_ASSERT( instance->hasFocus() == false);

  // Test of a non-focusable object
  Focusable f(false);
  BOOST_ASSERT( f.canTakeFocus() == false);
  BOOST_ASSERT( f.hasFocus() == false);
  teardown_Focusable(instance);
}

/// Tests if we can change the canTakeFocus value
BOOST_AUTO_TEST_CASE( test_focuable_CanTakeFocus )
{
  Focusable* instance = setup_Focusable();
  instance->setCanTakeFocus(false);
  BOOST_ASSERT( instance->canTakeFocus() == false);

  instance->setCanTakeFocus(true);
  BOOST_ASSERT( instance->canTakeFocus() == true);
  teardown_Focusable(instance);
}

/// Tests if all events are consumed by default
BOOST_AUTO_TEST_CASE( test_focuable_ConsumedEvents )
{
  Focusable* instance = setup_Focusable();
  OIS::KeyEvent ke(NULL, OIS::KC_A, 0); // A default KeyEvent

  BOOST_ASSERT( instance->keyPressed(ke) == false);
  BOOST_ASSERT( instance->keyReleased(ke) == false);
  
  OIS::MouseEvent me(NULL, OIS::MouseState());
  BOOST_ASSERT( instance->mouseMoved(me) == false);

  OIS::MouseButtonID mb = OIS::MB_Right;
  BOOST_ASSERT( instance->mousePressed(me, mb) == false);
  BOOST_ASSERT( instance->mouseReleased(me, mb) == false);
  teardown_Focusable(instance);
}

/// Test the focus status
BOOST_AUTO_TEST_CASE( test_focuable_Focus )
{
  Focusable* instance = setup_Focusable();

  // Should be false by default
  BOOST_ASSERT( instance->hasFocus() == false);

  instance->setFocus(true);
  BOOST_ASSERT( instance->hasFocus() == true);

  instance->setFocus(false);
  BOOST_ASSERT( instance->hasFocus() == false);

  teardown_Focusable(instance);
}

/// Tests the focus status of a non-focusable object
BOOST_AUTO_TEST_CASE( test_focuable_NonFocusableFocus )
{
  Focusable* instance = setup_Focusable();

  // The current instance is focusable by default
  instance->setFocus(true);
  BOOST_ASSERT( instance->hasFocus() == true);

  // Setting canTakeFocus to false should set focus to false
  instance->setCanTakeFocus(false);
  BOOST_ASSERT( instance->hasFocus() == false);

  // Setting focus to a non-focusable object should not work
  instance->setFocus(true);
  BOOST_ASSERT( instance->hasFocus() == false);

  teardown_Focusable(instance);
}

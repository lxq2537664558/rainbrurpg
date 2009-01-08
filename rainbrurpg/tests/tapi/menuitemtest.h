/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file menuitemtest.h
  * Implements the unit tests of the MenuItem class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef MENUITEM_TEST_H
#define MENUITEM_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <menu.h>
#include <logger.h>

#include <string>

using namespace std;

/** A function that is used to be a menu action
  *
  * As the menu action is a function pointer, it need a function.
  *
  * \return Always 255.
  *
  */
int MenuItemTestAction(){
  return 255;
}

 
/** A test class for TerminalAPI MenuItem
  *
  */
template<class TESTEDCLASS> 
class MenuItemTest : public CPPUNIT_NS::TestFixture 
{
  /// Declares the ScrollingPanelTest test fixture
  CPPUNIT_TEST_SUITE( MenuItemTest );

    /// Launches the testMenuItemName() test
    CPPUNIT_TEST( testMenuItemName );
    /// Launches the testMenuItemEmptyAction() test
    CPPUNIT_TEST( testMenuItemEmptyAction );
    /// Launches the testMenuItemFireAction() test
    CPPUNIT_TEST( testMenuItemFireAction );

  /// Terminates the tests
  CPPUNIT_TEST_SUITE_END();

protected:
  /** The tested MenuItem instance */
  TESTEDCLASS	*m_instance;
  
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
    this->m_instance = new TESTEDCLASS; 
  }
  
  /** Deletes the tested instance
    *
    */
  void tearDown(){ 
    delete this->m_instance; 
  }
  
  /** Tests the name field
    *
    * It sets a new name to the menuItem and check with getName
    * if it was set correctly
    *
    */
  void testMenuItemName(){ 
    const char* name="MenuItemName";
    this->m_instance->setName(name);
    int ret=strcmp( this->m_instance->getName(), name);
    CPPUNIT_ASSERT( ret==0 );
  }

  /** Fires the event and check if it returns -1
    *
    * If none pointer function was set, int MenuItem::fireAction()
    * should return -1.
    *
    */
  void testMenuItemEmptyAction(){
    int ret=this->m_instance->fireAction();
    CPPUNIT_ASSERT( ret==-1 );
  }

  /** Sets an action modifying a static var and fires the action to test
    * if the static var was modified
    *
    */
  void testMenuItemFireAction(){
    this->m_instance->setAction(&MenuItemTestAction);
    int ret=this->m_instance->fireAction();
    CPPUNIT_ASSERT( ret==255 );
  }

};


#endif // MENUITEM_TEST_H

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

/** \file menutest.h
  * Implements the unit tests of the Menu class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef MENU_TEST_H
#define MENU_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <menuitem.h>
#include <logger.h>

#include <string>

using namespace std;

/** A testFixture for TerminalAPI's Menu class
  *
  */
template<class TESTEDCLASS> 
class MenuTest : public CPPUNIT_NS::TestFixture 
{
  /// Declares the ScrollingPanelTest test fixture
  CPPUNIT_TEST_SUITE( MenuTest );

    /// Launches the testMenuAddItem() test
    CPPUNIT_TEST( testMenuAddItem );
    /// Launches the testMenuName() test
    CPPUNIT_TEST( testMenuName );
    /// Launches the testMenuWidth() test
    CPPUNIT_TEST( testMenuWidth );

  /// Terminates the tests
  CPPUNIT_TEST_SUITE_END();

protected:
  /** The tested Menu instance */
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
  
  /** Tests the Menu addItem function
    *
    * It simply adds a menuItem with the addItem function
    * and test id it was add with height.
    *
    */
  void testMenuAddItem(){ 
    this->m_instance->addItem(new MenuItem("MenuItemTest"));
    unsigned int ret=this->m_instance->itemCount();
    CPPUNIT_ASSERT( ret==1 );
  }

  /** Tests the Menu name field
    *
    */
  void testMenuName(){ 
    string name="MenuNameTest";
    this->m_instance->setName(name.c_str());
    string name2=this->m_instance->getName();
    CPPUNIT_ASSERT( name == name2 );
  }

  /** Tests the Menu width field
    *
    */
  void testMenuWidth(){ 
    string name="MenuNameTestWidth";
    int nameLen= name.size();
    this->m_instance->addItem(new MenuItem(name.c_str()));
    int l=this->m_instance->getWidth();
    CPPUNIT_ASSERT( nameLen==l );
  }


};


#endif // MENU_TEST_H

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
  
  /** Tests the Menu addItem function
    *
    * It simply adds a menuItem with the addItem function
    * and test id it was add with height.
    *
    */
  void testMenuAddItem(){ 
    this->m_caption->addItem(new MenuItem("MenuItemTest"));
    unsigned int ret=this->m_caption->itemCount();
    CPPUNIT_ASSERT( ret==1 );
  }

  /** Tests the Menu name field
    *
    */
  void testMenuName(){ 
    const char* name="MenuNameTest";
    this->m_caption->setName(name);
    const char* name2=this->m_caption->getName();
    int ret=strcmp(name, name2);
    CPPUNIT_ASSERT( ret==0 );
  }

  /** Tests the Menu width field
    *
    */
  void testMenuWidth(){ 
    char* name="MenuNameTestWidth";
    int nameLen=strlen(name);
    this->m_caption->addItem(new MenuItem(name));
    int l=this->m_caption->getWidth();
    CPPUNIT_ASSERT( nameLen==l );
  }


};


#endif // MENU_TEST_H

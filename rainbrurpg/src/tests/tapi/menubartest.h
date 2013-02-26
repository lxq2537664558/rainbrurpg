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

/** \file menubartest.h
  * Implements the unit tests of the MenuBar class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef MENUBAR_TEST_H
#define MENUBAR_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <menu.h>
#include <logger.h>

#include <string>

using namespace std;


/** A test class for TerminalAPI MenuBar widget
  *
  */
template<class TESTEDCLASS> 
class MenuBarTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the caption test 
  CPPUNIT_TEST_SUITE( MenuBarTest );

  /** Tests the addMenu MenuBar function
    * 
    * \sa testMenuBarAddMenu
    *
    */
  CPPUNIT_TEST( testMenuBarAddMenu );

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
  
  /** Tests the addMenu function
    *
    * It simply adds a menu with the addMenu function
    * and test if it was add with getSize().
    *
    */
  void testMenuBarAddMenu(){ 
    this->m_instance->addMenu(new Menu("MenuTest"));
    unsigned int ret=this->m_instance->getSize();
    CPPUNIT_ASSERT( ret==1 );
  }

};


#endif // MENUBAR_TEST_H

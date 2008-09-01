/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

/** \file terminalapptest.h
  * Implements the unit tests of the TerminalApp class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef TERMINALAPP_TEST_H
#define TERMINALAPP_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <menu.h>
#include <logger.h>
#include <window.h>
#include <menubar.h>

#include <string>

using namespace std;
using namespace RainbruRPG::Terminal;


/** A test class for TerminalApp
  *
  * It tests the TerminalApp class.
  *
  */
template<class TESTEDCLASS> 
class TerminalAppTest : public CPPUNIT_NS::TestFixture 
{
  /// Declare the TerminalApp test fixture
  CPPUNIT_TEST_SUITE( TerminalAppTest );

    /// Launch the testTerminalAppAddWindow() test
    CPPUNIT_TEST( testTerminalAppAddWindow );
    /// Launch the testTerminalGetMenuBar() test
    CPPUNIT_TEST( testTerminalGetMenuBar );

  /// Ends the tests
  CPPUNIT_TEST_SUITE_END();

protected:
  /** The tested instance of TerminalApp */
  TESTEDCLASS	*m_caption;
  
public:

  /** Return the number of testcase
    *
    * \return Always 1
    */ 
  int countTestCases () const{
    return 1;
  }
  
  /** Initialize the tested instance
    *
    */
  void setUp(){ 
    this->m_caption = new TESTEDCLASS; 
  }
  
  /** Delete the tested instance
    *
    */
  void tearDown(){ 
    delete this->m_caption; 
  }
  
  /** Tests the addWindow function
    *
    */
  void testTerminalAppAddWindow(){ 
    unsigned int wn=this->m_caption->windowCount();
    this->m_caption->addWindow(new Window());
    unsigned int wn2=this->m_caption->windowCount();
    CPPUNIT_ASSERT( wn2==++wn );
  }

  /** Tests the getMenuBar function
    *
    */
  void testTerminalGetMenuBar(){
    this->m_caption->setMenubar(new MenuBar());
    MenuBar* mb=this->m_caption->getMenubar();
    CPPUNIT_ASSERT( mb!=NULL );
  }
};


#endif // TERMINALAPP_TEST_H

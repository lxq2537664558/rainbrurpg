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

/** \file infodialogtest.h
  * Implements the unit tests of the InfoDialog class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef INFODIALOG_TEST_H
#define INFODIALOG_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

//#include <caption.h>

#include <string>

using namespace std;

/** A test class for TerminalAPI InfoDialog widget
  *
  */
template<class TESTEDCLASS> 
class InfoDialogTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the InfoDialog test 
  CPPUNIT_TEST_SUITE( InfoDialogTest );

  /** Tests the InfoDialog's message
    *
    * \sa testInfoDialogMessage
    *
    */
  CPPUNIT_TEST( testInfoDialogMessage );

  /** Tests the InfoDialog's title
    *
    * \sa testInfoDialogTitle
    *
    */
  CPPUNIT_TEST( testInfoDialogTitle );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the InfioDialog widget
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
  
  /** Tests the IndoDialog message field
    *
    * It simply set a new message and test with getMessage() if it
    * was correctly set.
    *
    */
  void testInfoDialogMessage(){ 
    std::string t="TestMessage";
    this->m_instance->setMessage(t);
    std::string ret=this->m_instance->getMessage();
    int cmp=t.compare(ret);
    CPPUNIT_ASSERT( cmp==0 );
  }

  /** Tests the IndoDialog title field
    *
    * It simply set a new title and test with getTitle() if it
    * was correctly set.
    *
    */
  void testInfoDialogTitle(){
    std::string t="TestTitle";
    this->m_instance->setTitle(t);
    std::string ret=this->m_instance->getTitle();
    int cmp=t.compare(ret);
    CPPUNIT_ASSERT( cmp==0 );
  }
};


#endif // INFODIALOG_TEST_H

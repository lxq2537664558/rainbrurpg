/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file labeltest.h
  * Implements the unit tests of the Label class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef DESERIALIZATION_ERROR_TEST_H
#define DESERIALIZATION_ERROR_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>
#include <sstream>
#include <iostream>

#include <DeserializationErrorList.hpp>

using namespace std;
using namespace RainbruRPG::OgreGui;


/** A test class for TerminalAPI's  Label widget
  *
  */
template<class TESTEDCLASS> 
class DeserializationErrorTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the Label test 
  CPPUNIT_TEST_SUITE( DeserializationErrorTest );

  CPPUNIT_TEST( testAdd );
  CPPUNIT_TEST( testError );

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
  int countTestCases () const{ return 1;  }
  
  /** Creates a new instance to test
    *
    */
  void setUp(){ 
    this->m_instance = new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ delete this->m_instance; }
  
  void testAdd(){ 
    CPPUNIT_ASSERT( m_instance->size()==0 );
    CPPUNIT_ASSERT( m_instance->empty() );
    m_instance->add("MyUniqueName", BAD_UNIQUE_NAME, "Message");
    CPPUNIT_ASSERT( m_instance->size()==1 );
    CPPUNIT_ASSERT( m_instance->empty()==false );
  }

  void testError(){ 
    DeserializationError de1("MyUniqueName", BAD_UNIQUE_NAME, "Message");
    CPPUNIT_ASSERT(de1.widgetUniqueName == "MyUniqueName");
    CPPUNIT_ASSERT(de1.errorType == BAD_UNIQUE_NAME);
    CPPUNIT_ASSERT(de1.message == "Message");
  }
};


#endif // DESERIALIZATION_ERROR_TEST_H

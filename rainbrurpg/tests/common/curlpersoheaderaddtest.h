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

/** \file curlpersoheaderaddtest.h
  * Implements the unit test for the CurlPersoHeaderAdd class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  * - 19 jul 2007 : Starting implementation
  *
  */

#ifndef CURL_PERSO_HEADER_ADD_TEST_H
#define CURL_PERSO_HEADER_ADD_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <curlserverdelete.h>
#include <string>

#include "virtualserver.h"

using namespace std;

/** A test class for CurlPersoHeaderAdd
  *
  */
template<class TESTEDCLASS> 
class CurlPersoHeaderAddTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( CurlPersoHeaderAddTest );

  /** Tests the initial values
    *
    * \sa testInitialValues
    *
    */
  CPPUNIT_TEST(testInitialValues);

  /** Tests the perso name
    *
    * \sa testName
    *
    */
  CPPUNIT_TEST(testName);

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the tested class
    *
    */
  TESTEDCLASS	*m_instance;
  
public:
  /** Return the number of test cases
    *
    * \return Currently always return 1
    *
    */
  int countTestCases(){
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

  /** Tests if the initial values are as expected
    *
    */
  void testInitialValues(){
    std::string name=this->m_instance->getName();
    CPPUNIT_ASSERT(name=="");
  }

  /** Tests the perso name
    *
    * Simply change the name with setName() and test with getName() if
    * it was correctly changed.
    *
    */
  void testName(){
    std::string name="New name";
    this->m_instance->setName(name);

    std::string name2=this->m_instance->getName();
    CPPUNIT_ASSERT(name==name2);
  }
};


#endif // CURL_PERSO_HEADER_ADD_TEST_H

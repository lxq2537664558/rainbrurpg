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

/** \file curlfiletoxmltest.h
  * Implements the unit test for the CurlFileToXml class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  * - 04 may 2007 : Starting implementation
  *
  */

#ifndef CURL_FILE_TO_XML_TEST_H
#define CURL_FILE_TO_XML_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <curlfiletoxml.h>

#include <string>

using namespace std;

/** A test class for common/CurlFileToXml
  *
  */
template<class TESTEDCLASS> 
class CurlFileToXmlTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( CurlFileToXmlTest );

  /** Tests the default server response
    *
    * \sa testInitialServerResponse
    *
    */
  CPPUNIT_TEST( testInitialServerResponse );

  /** Tests the default custom error message
    *
    * \sa testInitialCustomErrorMessaeg
    *
    */
  CPPUNIT_TEST( testInitialCustomErrorMessaeg );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the class to test
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
  
  /** Tests the default server response
    *
    * It should be -1.
    *
    */
  void testInitialServerResponse(){
    long l=this->m_instance->getServerResponse();
    CPPUNIT_ASSERT( l==-1 );
  }

  /** Tests the initial custome error message
    *
    * It should be an empty string.
    *
    */
  void testInitialCustomErrorMessaeg(){
    const char* ret=this->m_instance->getCustomErrorMessage();
    int cmp=strcmp(ret, "");
    CPPUNIT_ASSERT( cmp==0 );

  }
};


#endif // CURL_FILE_TO_XML_TEST_H

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

/* Modifications :
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

  /** Tests the filename
    *
    * \sa testFilename
    *
    */
  CPPUNIT_TEST( testFilename );

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
  TESTEDCLASS	*m_caption;
  
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
    this->m_caption = new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_caption; 
  }
  
  /** Tests the filename
    *
    * It simply set a new text and test if the 
    * string given by getFilename() is the same.
    *
    */
  void testFilename(){ 
    const char* t="filename";
    this->m_caption->setFilename(t);
    const char* ret=this->m_caption->getFilename();
    int cmp=strcmp(ret, t);
    CPPUNIT_ASSERT( cmp==0 );
  }

  /** Tests the default server response
    *
    * It should be -1.
    *
    */
  void testInitialServerResponse(){
    long l=this->m_caption->getServerResponse();
    CPPUNIT_ASSERT( l==-1 );
  }

  /** Tests the initial custome error message
    *
    * It should be an empty string.
    *
    */
  void testInitialCustomErrorMessaeg(){
    const char* ret=this->m_caption->getCustomErrorMessage();
    int cmp=strcmp(ret, "");
    CPPUNIT_ASSERT( cmp==0 );

  }
};


#endif // CURL_FILE_TO_XML_TEST_H
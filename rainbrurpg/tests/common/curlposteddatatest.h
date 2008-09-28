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

/** \file curlposteddatatest.h
  * Implements the unit test for the CurlPostedData class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  * - 12 may 2007 : Starting implementation
  *
  */

#ifndef CURL_POSTED_DATA_TEST_H
#define CURL_POSTED_DATA_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <caption.h>

#include <string>

using namespace std;

/** A test class for CurlPostedData
  *
  */
template<class TESTEDCLASS> 
class CurlPostedDataTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( CurlPostedDataTest );

  /** Tests the addKey function
    *
    * \sa testAddKey
    *
    */
  CPPUNIT_TEST( testAddKey );

  /** Tests the setValue/getValue functions
    *
    * \sa testValueChar
    *
    */
  CPPUNIT_TEST( testValueChar );

  /** Tests the setValue/getValue functions
    *
    * \sa testValueString
    *
    */
  CPPUNIT_TEST( testValueString );

  /** Tests the computed data
    *
    * \sa testComputeData1
    *
    */
  CPPUNIT_TEST( testComputeData1 );

  /** Tests the computed data
    *
    * \sa testComputeData2
    *
    */
  CPPUNIT_TEST( testComputeData2 );

  /** Tests inexistant key
    *
    * \sa testInexistantKey
    *
    */
  CPPUNIT_TEST( testInexistantKey );

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
  
  /** Tests the addKey function
    *
    * It simply adds a new key to the CurlPostedData
    * and test if the keyCount was incremented.
    *
    */
  void testAddKey(){ 
    int nbKeys=m_instance->keyCount();
    m_instance->addKey("TestKey");

    int nbKeys2=this->m_instance->keyCount();
    CPPUNIT_ASSERT( nbKeys2==++nbKeys  );
  }

  /** Test the values
    *
    * It set a value to the key and test if we can get it this the
    * getValue function.
    *
    */
  void testValueChar(){
    const char* val2="exampleValue";
    m_instance->addKey("TestKey");
    m_instance->setValue("TestKey", val2);
    const char* val=m_instance->getValue("TestKey");
    CPPUNIT_ASSERT(strcmp(val, val2)==0);
  }

  /** Test the values
    *
    * It set a value to the key and test if we can get it this the
    * getValue function.
    *
    */
  void testValueString(){
    std::string val2="exampleValue";
    m_instance->addKey("TestKey");
    m_instance->setValue("TestKey", val2);
    const char* val=m_instance->getValue("TestKey");
    CPPUNIT_ASSERT(val2==val);
  }

  /** Tests the computed data of one key
    *
    * Sets key and value and test the computeData.
    *
    */
  void testComputeData1(){
    m_instance->addKey("TestKey");
    m_instance->setValue("TestKey", "TestValue");
    std::string computed=m_instance->getComputedData();
    CPPUNIT_ASSERT(computed=="TestKey=TestValue");
  }

  /** Tests the computed data of two key
    *
    * Sets keys and values and test the computeData.
    *
    */
  void testComputeData2(){
    m_instance->addKey("TestKey");
    m_instance->setValue("TestKey", "TestValue");
    m_instance->addKey("TestKey2");
    m_instance->setValue("TestKey2", "TestValue2");
    std::string computed=m_instance->getComputedData();
    CPPUNIT_ASSERT(computed=="TestKey=TestValue&TestKey2=TestValue2");

  }

  /** Tests an inexistant key content
    *
    * The returned string should be empty.
    *
    */
  void testInexistantKey(){
    const char* computed=m_instance->getValue("InexistantKey");
    CPPUNIT_ASSERT(strcmp(computed, "")==0);

  }
};


#endif // CURL_POSTED_DATA_TEST_H

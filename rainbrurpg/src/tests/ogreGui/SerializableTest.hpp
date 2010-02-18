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

#ifndef SERIALIZABLE_TEST_H
#define SERIALIZABLE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>
#include <sstream>
#include <iostream>

#include <logger.h>
#include <Serializable.hpp>
#include <DeserializationErrorList.hpp>

using namespace std;


/** A test class for TerminalAPI's  Label widget
  *
  */
template<class TESTEDCLASS> 
class SerializableTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the Label test 
  CPPUNIT_TEST_SUITE( SerializableTest );

  CPPUNIT_TEST( testUniqueName );
  CPPUNIT_TEST( testSerialize );
  CPPUNIT_TEST( testDeserialize );
  CPPUNIT_TEST( testEqual );
  CPPUNIT_TEST( testNotEqual );
  CPPUNIT_TEST( testSeekg );
  CPPUNIT_TEST( testEqualPtr );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the caption widget
    *
    */
  TESTEDCLASS	*m_instance;
  DeserializationErrorList* del;
  
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
    this->m_instance = new TESTEDCLASS("Name"); 
    this->m_instance->setUniqueName("Parent");
    
    del = new DeserializationErrorList();
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_instance; 
    delete del;
  }
  
  void testUniqueName(){ 
    std::string t="Parent";
    this->m_instance->setUniqueName(t);
    string ret = m_instance->getUniqueName();
    CPPUNIT_ASSERT( ret == "Parent/Name" );
  }

  void testSerialize(){ 
    ostringstream oss;
    bool result = this->m_instance->serialize(oss);
    CPPUNIT_ASSERT( result == true );
  }

  void testDeserialize(){ 
    stringstream oss;
    this->m_instance->setUniqueName("testDeserializeParent");
    bool result = this->m_instance->serialize(oss);
    CPPUNIT_ASSERT( result == true );

    // Deserialize with another class
    TESTEDCLASS* test1 = new TESTEDCLASS("Name"); 
    test1->setUniqueName("testDeserializeParent");
    result = test1->deserialize(oss, del);
    CPPUNIT_ASSERT( result == true );
    delete test1;

    // Deserialization with different unique name
    TESTEDCLASS* test2 = new TESTEDCLASS("OtherName"); 
    test2->setUniqueName("testDeserializeParent");
    result = test2->deserialize(oss, del);
    //The two following should be false
    CPPUNIT_ASSERT( result == false );  
    CPPUNIT_ASSERT( oss.str() != test2->getUniqueName());
    delete test2;
  }

  void testEqual(){ 
    stringstream oss;
    this->m_instance->setUniqueName("testEqualParent");
    bool result = this->m_instance->serialize(oss);
    CPPUNIT_ASSERT( result == true );

    // Deserialize with another class
    TESTEDCLASS* test1 = new TESTEDCLASS("Name"); 
    test1->setUniqueName("testEqualParent");
    result = test1->deserialize(oss, del);
    CPPUNIT_ASSERT( result == true );
    /* Force using the operator== overload of Serializable
     *
     * Here, I must derefence m_instance and test1 which are pointer.
     * C++ seems to test the pointers, and it is not the same object.
     * So the assertion fails. 
     *
     */
    bool equal = (*m_instance) == (*test1);
    CPPUNIT_ASSERT(equal );
    delete test1;
  }

  void testNotEqual(){ 
    // Test a non equal assert (with operator==
    TESTEDCLASS* test1 = new TESTEDCLASS("Name"); 
    test1->setUniqueName("testNOT_EqualParent");
    bool not_equal = (*m_instance) == (*test1); // See test below
    CPPUNIT_ASSERT(!not_equal);
    delete test1;

    // Test a non equal assert (with operator !=)
    LOGI("Starting testNotEqual");
    TESTEDCLASS* test2 = new TESTEDCLASS("Name"); 
    test2->setUniqueName("testNOT_EqualParent");
    bool equal = (*m_instance) != (*test2); // See test below
    CPPUNIT_ASSERT(equal);
    delete test2;
  }

  /** Test is checkUniqueName correcktly seek back
    * 
    * When we deserialize an object, it first check if the unique name
    * in the stream is the same. If that fails, the object should
    * seek back to the Unique name in the stream to allow next widget
    * to extract it.
    *
    */
  void testSeekg(){ 
    // Create a stream with dummy value;
    stringstream oss;
    streampos pos, pos2;

    oss << string("Parent/Name") << STRING_SEPARATOR;
    oss << string("Dummy/UniqueName") << STRING_SEPARATOR;

    // Deserialization should work
    bool result = this->m_instance->deserialize(oss, del);
    CPPUNIT_ASSERT( result == true );


    // Deserialization shouldn't work
    pos = oss.tellg();
    bool result2 = this->m_instance->deserialize(oss, del);
    CPPUNIT_ASSERT( result2 != true );
    pos2 = oss.tellg();
    CPPUNIT_ASSERT( pos == pos2 ); // Should rewind
  }

  void testEqualPtr(){ 
    this->m_instance->setUniqueName("testEqualParent");

    // Deserialize with another class
    TESTEDCLASS* test1 = new TESTEDCLASS("Name"); 
    test1->setUniqueName("testEqualParent");
    CPPUNIT_ASSERT( m_instance->equal(test1));
    delete test1;

    // Deserialize with another class
    TESTEDCLASS* test2 = new TESTEDCLASS("OtherName"); 
    test2->setUniqueName("testEqualParent");
    CPPUNIT_ASSERT( !m_instance->equal(test2));
    delete test2;
  }

};


#endif // SERIALIZABLE_TEST_H

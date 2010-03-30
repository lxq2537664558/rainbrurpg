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

#include "SerializableTest.hpp"

// Registers the fixture to the registry
CPPUNIT_TEST_SUITE_REGISTRATION( SerializableTest );

  /** Creates a new instance to test
    *
    */
void SerializableTest::setUp(){ 
  this->m_instance = new Serializable("Name"); 
  this->m_instance->setUniqueName("Parent");
}

/** Delete the current tested instance
  *
  */
void SerializableTest::tearDown(){ 
  delete this->m_instance; 
}

void SerializableTest::testUniqueName(){ 
    std::string t="Parent";
    this->m_instance->setUniqueName(t);
    string ret = m_instance->getUniqueName();
    CPPUNIT_ASSERT( ret == "Parent/Name" );
}

void SerializableTest::testEqual(){ 
  stringstream oss;
  this->m_instance->setUniqueName("testEqualParent");
  bool result=true;
  /*  bool result = this->m_instance->serialize(oss);
  CPPUNIT_ASSERT( result == true );
  */
  // Deserialize with another class
  Serializable* test1 = new Serializable("Name"); 
  test1->setUniqueName("testEqualParent");
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


void SerializableTest::testNotEqual(){ 
  // Test a non equal assert (with operator==
  Serializable* test1 = new Serializable("Name"); 
  test1->setUniqueName("testNOT_EqualParent");
  bool not_equal = (*m_instance) == (*test1); // See test below
  CPPUNIT_ASSERT(!not_equal);
  delete test1;
  
  // Test a non equal assert (with operator !=)
  LOGI("Starting testNotEqual");
  Serializable* test2 = new Serializable("Name"); 
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
void SerializableTest::testSeekg(){ 
  // Create a stream with dummy value;
  stringstream oss;
  streampos pos, pos2;
  
  oss << string("Parent/Name") << STRING_SEPARATOR;
  oss << string("Dummy/UniqueName") << STRING_SEPARATOR;
  
  pos2 = oss.tellg();
  CPPUNIT_ASSERT( pos == pos2 ); // Should rewind
}

void SerializableTest::testEqualPtr(){ 
  this->m_instance->setUniqueName("testEqualParent");

  // Deserialize with another class
  Serializable* test1 = new Serializable("Name"); 
  test1->setUniqueName("testEqualParent");
  CPPUNIT_ASSERT( m_instance->equal(test1));
  delete test1;

  // Deserialize with another class
  Serializable* test2 = new Serializable("OtherName"); 
  test2->setUniqueName("testEqualParent");
  CPPUNIT_ASSERT( !m_instance->equal(test2));
  delete test2;
}

/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file SerializableTest.cpp
  * A test case for ogreGui's Serializable
  *
  */

#include "Serializable.hpp"

#include <boost/test/unit_test.hpp>

#include <logger.h>

using namespace RainbruRPG::OgreGui;

Serializable* setup_Serializable(const std::string vName="Name")
{
  return new Serializable(vName);
}

void teardown_Serializable(Serializable* d)
{
  delete d;
}

/// Test the uniqueName creation
BOOST_AUTO_TEST_CASE( test_serializable_UniqueName )
{
  Serializable* instance = setup_Serializable();
  std::string t="Parent";
  instance->setUniqueName(t);
  string ret = instance->getUniqueName();
  BOOST_ASSERT( ret == "Parent/Name" );
  teardown_Serializable( instance );
}

/// Test the equality operator \c operator==
BOOST_AUTO_TEST_CASE( test_serializable_Equal )
{
  Serializable* instance = setup_Serializable();
  stringstream oss;
  instance->setUniqueName("testEqualParent");
  bool result=true;

  // Deserialize with another class
  Serializable* test1 = new Serializable("Name"); 
  test1->setUniqueName("testEqualParent");
  BOOST_ASSERT( result == true );
  /* Force using the operator== overload of Serializable
   *
   * Here, I must derefence instance and test1 which are pointer.
   * C++ seems to test the pointers, and it is not the same object.
   * So the assertion fails. 
   *
   */
  bool equal = (*instance) == (*test1);
  BOOST_ASSERT(equal );
  delete test1;
  teardown_Serializable( instance );
}

/** Test non equal Serializable both with \c operator==
  * and \c operator!=
  *
  */
BOOST_AUTO_TEST_CASE( test_serializable_NotEqual )
{
  Serializable* instance = setup_Serializable();

  // Test a non equal assert (with operator==
  Serializable* test1 = new Serializable("Name"); 
  test1->setUniqueName("testNOT_EqualParent");
  bool not_equal = (*instance) == (*test1); // See test below
  BOOST_ASSERT(!not_equal);
  delete test1;
  
  // Test a non equal assert (with operator !=)
  Serializable* test2 = new Serializable("Name"); 
  test2->setUniqueName("testNOT_EqualParent");
  bool equal = (*instance) != (*test2); // See test below
  BOOST_ASSERT(equal);
  delete test2;

  teardown_Serializable( instance );
}

/** Test if checkUniqueName correctly seek back
  * 
  * When we deserialize an object, it first check if the unique name
  * in the stream is the same. If that fails, the object should
  * seek back to the Unique name in the stream to allow next widget
  * to extract it.
  *
  */
BOOST_AUTO_TEST_CASE( test_serializable_Seekg )
{
  // Create a stream with dummy value;
  stringstream oss;
  streampos pos, pos2;
  
  oss << string("Parent/Name") << STRING_SEPARATOR;
  oss << string("Dummy/UniqueName") << STRING_SEPARATOR;
  
  pos2 = oss.tellg();
  BOOST_ASSERT( pos == pos2 ); // Should rewind
}

/// Test with equal pointers
BOOST_AUTO_TEST_CASE( test_serializable_EqualPtr )
{
  Serializable* instance = setup_Serializable();
  instance->setUniqueName("testEqualParent");

  // Deserialize with another class
  Serializable* test1 = new Serializable("Name"); 
  test1->setUniqueName("testEqualParent");
  BOOST_ASSERT( instance->equal(test1));
  delete test1;

  // Deserialize with another class
  Serializable* test2 = new Serializable("OtherName"); 
  test2->setUniqueName("testEqualParent");
  BOOST_ASSERT( !instance->equal(test2));
  delete test2;

  teardown_Serializable( instance );
}

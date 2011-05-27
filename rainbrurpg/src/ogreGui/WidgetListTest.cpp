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

/** \file WidgetListTest.cpp
  * A test case for OgreGui's WidgetList.
  *
  */

#include <WidgetList.hpp>

//#define BOOST_TEST_MODULE ContainerTest
#include <boost/test/unit_test.hpp>

using namespace RainbruRPG::OgreGui;

WidgetList* setup_WidgetList()
{
  return new WidgetList("TestList" );
}

void teardown_WidgetList(WidgetList* vWidgetList)
{
  delete vWidgetList;
}

/// Tests the WidgetList::empty() function
BOOST_AUTO_TEST_CASE( test_WidgetList_empty )
{
  WidgetList* instance = setup_WidgetList();
  BOOST_ASSERT( instance->empty() == true );
  teardown_WidgetList( instance );
}

/// Tests the push_back() function
BOOST_AUTO_TEST_CASE( test_WidgetList_PushBack )
{
  WidgetList* instance = setup_WidgetList();
  instance->push_back(new Widget(NULL, "Name", 0, 0, 10, 10));
  BOOST_ASSERT( instance->size() == 1 );
  BOOST_ASSERT( instance->empty() == false );
  teardown_WidgetList( instance );
}

/// Tests the WidgetList unique name
BOOST_AUTO_TEST_CASE( test_WidgetList_UniqueName )
{
  WidgetList* instance = setup_WidgetList();
  vector<string> names;
  int idx = 0;

  // instance name is "TestList"
  instance->push_back(new Widget(NULL, "Child1", 0, 0, 10, 10));
  instance->push_back(new Widget(NULL, "Child2", 0, 0, 10, 10));
  instance->push_back(new Widget(NULL, "Child3", 0, 0, 10, 10));
  instance->push_back(new Widget(NULL, "Child4", 0, 0, 10, 10));
  instance->push_back(new Widget(NULL, "Child5", 0, 0, 10, 10));
  instance->setUniqueName("Parent");
  string ret = instance->getUniqueName();

  // Get childs name
  tWidgetList list = instance->getList();
  tWidgetList::const_iterator iter;
  
  for (iter = list.begin(); iter != list.end(); iter++){
    names.push_back( (*iter)->getUniqueName() );
  }

  // Test
  BOOST_ASSERT( ret == "Parent/TestList" );
  BOOST_ASSERT( names[0] == "Parent/TestList/Child1" );
  BOOST_ASSERT( names[1] == "Parent/TestList/Child2" );
  BOOST_ASSERT( names[2] == "Parent/TestList/Child3" );
  BOOST_ASSERT( names[3] == "Parent/TestList/Child4" );
  BOOST_ASSERT( names[4] == "Parent/TestList/Child5" );
  teardown_WidgetList( instance );
}

/// Tests the focusNext function
BOOST_AUTO_TEST_CASE( test_WidgetList_FocusNext )
{
  WidgetList* instance = setup_WidgetList();
  // Creating widgets (canTakeFocus true by default)
  Widget w1(NULL, "Child1", 0, 0, 10, 10);
  Widget w2(NULL, "Child1", 0, 0, 10, 10);  
  w2.setCanTakeFocus(false);
  Widget w3(NULL, "Child1", 0, 0, 10, 10);
  w3.setCanTakeFocus(false);
  Widget w4(NULL, "Child1", 0, 0, 10, 10);

  // Adding them to list
  instance->push_back( &w1 );
  instance->push_back( &w2 );
  instance->push_back( &w3 );
  instance->push_back( &w4 );

  // Test of focusNext()
  Widget* fw = instance->focusNext();
  BOOST_ASSERT( fw == &w1 );

  Widget* fw2 = instance->focusNext();
  BOOST_ASSERT( fw2 == &w4 );

  Widget* fw3 = instance->focusNext();
  BOOST_ASSERT( fw3 == NULL );

  // At the end of the list, should return first focusable element
  Widget* fw4 = instance->focusNext();
  BOOST_ASSERT( fw4 == &w1 );
  teardown_WidgetList( instance );
}

/// Tests the focusPrevious function
BOOST_AUTO_TEST_CASE( test_WidgetList_FocusPrevious )
{
  WidgetList* instance = setup_WidgetList();
  // Creating widgets (canTakeFocus true by default)
  Widget w1(NULL, "Child1", 0, 0, 10, 10);
  Widget w2(NULL, "Child1", 0, 0, 10, 10);  
  w2.setCanTakeFocus(false);
  Widget w3(NULL, "Child1", 0, 0, 10, 10);
  w3.setCanTakeFocus(false);
  Widget w4(NULL, "Child1", 0, 0, 10, 10);

  // Adding them to list
  instance->push_back( &w1 );
  instance->push_back( &w2 );
  instance->push_back( &w3 );
  instance->push_back( &w4 );

  // Test of focusPrevious()
  Widget* fw = instance->focusPrevious();
  BOOST_ASSERT( fw == &w4 );

  Widget* fw2 = instance->focusPrevious();
  BOOST_ASSERT( fw2 == &w1 );

  Widget* fw3 = instance->focusPrevious();
  BOOST_ASSERT( fw3 == NULL );

  // At the end of the list, should return first focusable element
  Widget* fw4 = instance->focusPrevious();
  BOOST_ASSERT( fw4 == &w4 );
  teardown_WidgetList( instance );
}

/// Test the focusNext and focusPrevious functions together
BOOST_AUTO_TEST_CASE( test_WidgetList_FocusMixed )
{
  WidgetList* instance = setup_WidgetList();
  // Creating widgets (canTakeFocus true by default)
  Widget w1(NULL, "Child1", 0, 0, 10, 10);
  Widget w2(NULL, "Child1", 0, 0, 10, 10);  
  w2.setCanTakeFocus(false);
  Widget w3(NULL, "Child1", 0, 0, 10, 10);
  w3.setCanTakeFocus(false);
  Widget w4(NULL, "Child1", 0, 0, 10, 10);

  // Adding them to list
  instance->push_back( &w1 );
  instance->push_back( &w2 );
  instance->push_back( &w3 );
  instance->push_back( &w4 );

  // Test of focusPrevious()
  Widget* fw = instance->focusNext();
  BOOST_ASSERT( fw == &w1 );

  Widget* fw2 = instance->focusPrevious();
  BOOST_ASSERT( fw2 == &w4 );

  Widget* fw3 = instance->focusPrevious();
  BOOST_ASSERT( fw3 == &w1 );

  Widget* fw4 = instance->focusPrevious();
  BOOST_ASSERT( fw4 == NULL );
  teardown_WidgetList( instance );
}

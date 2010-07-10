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

#include "WidgetListTest.hpp"

#include <vector>

// Registers the fixture to the registry
CPPUNIT_TEST_SUITE_REGISTRATION( WidgetListTest );

/// Create the tested instance
void WidgetListTest::setUp(){
  m_instance = new WidgetList("TestList");
}

/// Destroy the tested instance
void WidgetListTest::tearDown(){
  delete m_instance;
}

/// Simply test if a newly created list is empty
void WidgetListTest::testNew(){
  CPPUNIT_ASSERT( m_instance->size() == 0 );
}

/// Tests the WidgetList::empty() function
void WidgetListTest::testEmpty(){
  CPPUNIT_ASSERT( m_instance->empty() == true );
}

/// Tests the push_back() function
void WidgetListTest::testPushBack(){
  m_instance->push_back(new Widget(NULL, "Name", 0, 0, 10, 10));
  CPPUNIT_ASSERT( m_instance->size() == 1 );
  CPPUNIT_ASSERT( m_instance->empty() == false );
  
}

/// Tests the WidgetList unique name
void WidgetListTest::testUniqueName(){ 
  vector<string> names;
  int idx = 0;

  // m_instance name is "TestList"
  m_instance->push_back(new Widget(NULL, "Child1", 0, 0, 10, 10));
  m_instance->push_back(new Widget(NULL, "Child2", 0, 0, 10, 10));
  m_instance->push_back(new Widget(NULL, "Child3", 0, 0, 10, 10));
  m_instance->push_back(new Widget(NULL, "Child4", 0, 0, 10, 10));
  m_instance->push_back(new Widget(NULL, "Child5", 0, 0, 10, 10));
  m_instance->setUniqueName("Parent");
  string ret = m_instance->getUniqueName();

  // Get childs name
  tWidgetList list = m_instance->getList();
  tWidgetList::const_iterator iter;
  
  for (iter = list.begin(); iter != list.end(); iter++){
    names.push_back( (*iter)->getUniqueName() );
  }

  // Test
  CPPUNIT_ASSERT( ret == "Parent/TestList" );
  CPPUNIT_ASSERT( names[0] == "Parent/TestList/Child1" );
  CPPUNIT_ASSERT( names[1] == "Parent/TestList/Child2" );
  CPPUNIT_ASSERT( names[2] == "Parent/TestList/Child3" );
  CPPUNIT_ASSERT( names[3] == "Parent/TestList/Child4" );
  CPPUNIT_ASSERT( names[4] == "Parent/TestList/Child5" );
}

/// Tests the focusNext function
void WidgetListTest::testFocusNext(){
  // Creating widgets (canTakeFocus true by default)
  Widget w1(NULL, "Child1", 0, 0, 10, 10);
  Widget w2(NULL, "Child1", 0, 0, 10, 10);  
  w2.setCanTakeFocus(false);
  Widget w3(NULL, "Child1", 0, 0, 10, 10);
  w3.setCanTakeFocus(false);
  Widget w4(NULL, "Child1", 0, 0, 10, 10);

  // Adding them to list
  m_instance->push_back( &w1 );
  m_instance->push_back( &w2 );
  m_instance->push_back( &w3 );
  m_instance->push_back( &w4 );

  // Test of focusNext()
  Widget* fw = m_instance->focusNext();
  CPPUNIT_ASSERT( fw == &w1 );

  Widget* fw2 = m_instance->focusNext();
  CPPUNIT_ASSERT( fw2 == &w4 );

  Widget* fw3 = m_instance->focusNext();
  CPPUNIT_ASSERT( fw3 == NULL );

  // At the end of the list, should return first focusable element
  Widget* fw4 = m_instance->focusNext();
  CPPUNIT_ASSERT( fw4 == &w1 );
}

/// Tests the focusPrevious function
void WidgetListTest::testFocusPrevious(){
  // Creating widgets (canTakeFocus true by default)
  Widget w1(NULL, "Child1", 0, 0, 10, 10);
  Widget w2(NULL, "Child1", 0, 0, 10, 10);  
  w2.setCanTakeFocus(false);
  Widget w3(NULL, "Child1", 0, 0, 10, 10);
  w3.setCanTakeFocus(false);
  Widget w4(NULL, "Child1", 0, 0, 10, 10);

  // Adding them to list
  m_instance->push_back( &w1 );
  m_instance->push_back( &w2 );
  m_instance->push_back( &w3 );
  m_instance->push_back( &w4 );

  // Test of focusPrevious()
  Widget* fw = m_instance->focusPrevious();
  CPPUNIT_ASSERT( fw == &w4 );

  Widget* fw2 = m_instance->focusPrevious();
  CPPUNIT_ASSERT( fw2 == &w1 );

  Widget* fw3 = m_instance->focusPrevious();
  CPPUNIT_ASSERT( fw3 == NULL );

  // At the end of the list, should return first focusable element
  Widget* fw4 = m_instance->focusPrevious();
  CPPUNIT_ASSERT( fw4 == &w4 );
}

/// Test the focusNext and focusPrevious functions together
void WidgetListTest::testFocusMixed(){
  // Creating widgets (canTakeFocus true by default)
  Widget w1(NULL, "Child1", 0, 0, 10, 10);
  Widget w2(NULL, "Child1", 0, 0, 10, 10);  
  w2.setCanTakeFocus(false);
  Widget w3(NULL, "Child1", 0, 0, 10, 10);
  w3.setCanTakeFocus(false);
  Widget w4(NULL, "Child1", 0, 0, 10, 10);

  // Adding them to list
  m_instance->push_back( &w1 );
  m_instance->push_back( &w2 );
  m_instance->push_back( &w3 );
  m_instance->push_back( &w4 );

  // Test of focusPrevious()
  Widget* fw = m_instance->focusNext();
  CPPUNIT_ASSERT( fw == &w1 );

  Widget* fw2 = m_instance->focusPrevious();
  cout << fw2;
  CPPUNIT_ASSERT( fw2 == &w4 );

  Widget* fw3 = m_instance->focusPrevious();
  CPPUNIT_ASSERT( fw3 == &w1 );

  Widget* fw4 = m_instance->focusPrevious();
  CPPUNIT_ASSERT( fw4 == NULL );
}

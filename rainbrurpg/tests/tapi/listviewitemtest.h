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

/** \file listviewitemtest.h
  * Implements the unit tests of the ListViewItem class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef LISTVIEW_TEST_TEST_H
#define LISTVIEW_TEST_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>

using namespace std;

/** A etst suite for TerminalAPI ListViewItem
  *
  */
template<class TESTEDCLASS> 
class ListViewItemTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the ListView test 
  CPPUNIT_TEST_SUITE( ListViewItemTest );

  /** Tests the ListViewItem's addColumn function
    *
    * \sa testListItemAddColumn
    *
    */
  CPPUNIT_TEST( testListItemAddColumn );
  /** Tests the ListViewItem's getColumn function
    *
    * \sa testListItemGetColumn
    *
    */
  CPPUNIT_TEST( testListItemGetColumn );
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
  int countTestCases () const{
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
  
  /** Tests the addColumn function
    *
    * It simply add a column using the addColumn() function
    * and test if the columnCount function returns 1.
    */
  void testListItemAddColumn(){ 
    const char* cap="ColumnCaptionTest";
    this->m_instance->addColumn(cap);
    unsigned int count=this->m_instance->columnCount();
    CPPUNIT_ASSERT( count==1 );
  }

  /** Tests the getColumn function
    *
    * Adds a new column and test if the getColumn() function
    * return the same content.
    *
    */
  void testListItemGetColumn(){ 
    const char* cap="ColumnCaptionTest";
    this->m_instance->addColumn(cap);
    const char* colContent;
    colContent=this->m_instance->getColumn(0);
    int ret=strcmp(colContent, cap);
    CPPUNIT_ASSERT( ret==0 );
  }


};


#endif // LISTVIEW_TEST_TEST_H

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

#ifndef LISTVIEW_COLUMN_TEST_H
#define LISTVIEW_COLUMN_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>

using namespace std;

/** A test class for TerminalAPI's ListViewColumn
  *
  */
template<class TESTEDCLASS> 
class ListViewColumnTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the ListViewColumn test 
  CPPUNIT_TEST_SUITE( ListViewColumnTest );
  /** Tests the ListViewColumn caption value
    * 
    * \sa testListViewColumnCaption
    *
    */
  CPPUNIT_TEST( testListViewColumnCaption );
  /** Tests the ListViewColumn width value
    * 
    * \sa testListViewColumnWidth
    *
    */
  CPPUNIT_TEST( testListViewColumnWidth );
  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance that is tested
    *
    */
  TESTEDCLASS	*m_caption;
  
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
    this->m_caption = new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_caption; 
  }
  
  /** Tests the ListViewColumn's caption
    *
    *
    */
  void testListViewColumnCaption(){ 
    const char* cap="CaptionTest";
    this->m_caption->setCaption(cap);
    const char* cap2=this->m_caption->getCaption();
    CPPUNIT_ASSERT( strcmp(cap, cap2)==0 );
  }

  /** Tests the ListViewColumn's caption
    *
    */
  void testListViewColumnWidth(){ 
    int x=12;
    this->m_caption->setWidth(x);
    int ret=this->m_caption->getWidth();
    CPPUNIT_ASSERT( ret==x );
  }


};


#endif // LISTVIEW_COLUMN_TEST_H

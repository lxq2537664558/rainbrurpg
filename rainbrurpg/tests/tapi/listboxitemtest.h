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

#ifndef LISTBOXITEM_TEST_H
#define LISTBOXITEM_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>

using namespace std;

/** A test suite for TerminalAPI ListBoxItem
  *
  */
template<class TESTEDCLASS> 
class ListBoxItemTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the ListBoxItem test 
  CPPUNIT_TEST_SUITE( ListBoxItemTest );
  /** Tests the ListBoxItem's caption
    *
    * \sa testListBoxItemCaption
    *
    */
  CPPUNIT_TEST( testListBoxItemCaption );
  /** Tests the ListBoxItem's toggle
    *
    * \sa testListBoxItemToggle
    *
    */
  CPPUNIT_TEST( testListBoxItemToggle );
  /** Tests the ListBoxItem's check
    *
    * \sa testListBoxItemCheck
    *
    */
  CPPUNIT_TEST( testListBoxItemCheck );
  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();
protected:
  /** An instance of the ListBoxItem widget
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
  
  /** Tests the caption of a ListBoxItem
    *
    * It simply set a new caption and tests if it is correctly
    * changed by a call to getCaption()
    *
    */
  void testListBoxItemCaption(){ 
    std::string c="CaptionTest";
    this->m_caption->setCaption(c.c_str());
    string c2=this->m_caption->getCaption();
    CPPUNIT_ASSERT( c == c2 );
  }

  /** Tests the toggle function
    * 
    * By default check is false. We call Toggle and test is check is true, then
    * toggle again to know if check is false
    *
    */
  void testListBoxItemToggle(){
    this->m_caption->toggle();
    CPPUNIT_ASSERT( this->m_caption->isChecked() );

    this->m_caption->toggle();
    CPPUNIT_ASSERT( !this->m_caption->isChecked() );

  }

  /** Tests the setChecked() function
    *
    * Call setChecked(true) and tests isChecked()
    *
    */
  void testListBoxItemCheck(){
    this->m_caption->setChecked(true);
    CPPUNIT_ASSERT( this->m_caption->isChecked() );

  }


};


#endif // LISTBOXITEM_TEST_H

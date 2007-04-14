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

#ifndef LISTBOX_TEST_H
#define LISTBOX_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>

using namespace std;


/** A test class for TerminalAPI ListBox widget
  *
  */
template<class TESTEDCLASS> 
class ListBoxTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the caption test 
  CPPUNIT_TEST_SUITE( ListBoxTest );
  /** Tests the listbox caption value
    * 
    * \sa testListBoxCaption
    *
    */
  CPPUNIT_TEST( testListBoxCaption );
  /** Tests the listbox X value
    * 
    * \sa testListBoxX
    *
    */
  CPPUNIT_TEST( testListBoxX );
  /** Tests the listbox Y value
    * 
    * \sa testListBoxY
    *
    */
  CPPUNIT_TEST( testListBoxY );
  /** Tests the listbox width value
    * 
    * \sa testListBoxWidth
    *
    */
  CPPUNIT_TEST( testListBoxWidth );
  /** Tests the listbox height value
    * 
    * \sa testListBoxHeight
    *
    */
  CPPUNIT_TEST( testListBoxHeight );
  /** Tests the listbox hasfocus value
    * 
    * \sa testListBoxHasFocus
    *
    */
  CPPUNIT_TEST( testListBoxHasFocus );
  /** Tests the listbox has focus value
    * 
    * \sa testListBoxHasntFocus
    *
    */
  CPPUNIT_TEST( testListBoxHasntFocus );
  /** Tests the listbox canTakeFocus value
    * 
    * \sa testListBoxCanTakeFocus
    *
    */
  CPPUNIT_TEST( testListBoxCanTakeFocus );
  /** Tests the listbox position value
    * 
    * \sa testListBoxPosition
    *
    */
  CPPUNIT_TEST( testListBoxPosition );
  /** Tests the listbox addItem function
    * 
    * \sa testListBoxAddItem
    *
    */
  CPPUNIT_TEST( testListBoxAddItem );

  /** Tests the listbox drawCaption value
    * 
    * \sa testListBoxAddItem
    *
    */
  CPPUNIT_TEST( testListBoxDrawCaption );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();
protected:
  /** An instance of the ListBox widget
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
  
  /** Tests the ListBox caption
    *
    * It simply set a new text to the ListBox and test if the 
    * string given by Caption::getText() is the same.
    *
    */
  void testListBoxCaption(){ 
    const char* t="TestCaption";
    this->m_caption->setText(t);
    const char* ret=this->m_caption->getText();
    int cmp=strcmp(t, ret);
    CPPUNIT_ASSERT( cmp==0 );
  }

  /** Tests the ListBox x position
    *
    * It simply set a new x value to the ListBox and test if the 
    * string given by Caption::getX() is the same.
    *
    */
  void testListBoxX(){ 
    int x=1;
    this->m_caption->setX(x);
    int ret=this->m_caption->getX();
    CPPUNIT_ASSERT( x==ret );
  }

  /** Tests the ListBox y position
    *
    * It simply set a new y value to the ListBox and test if the 
    * string given by Caption::getY() is the same.
    *
    */
  void testListBoxY(){ 
    int y=2;
    this->m_caption->setY(y);
    int ret=this->m_caption->getY();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the ListBox width
    *
    * It simply set a new width value to the ListBox and test if the 
    * string given by Caption::getWidth() is the same.
    *
    */
  void testListBoxWidth(){ 
    int y=3;
    this->m_caption->setWidth(y);
    int ret=this->m_caption->getWidth();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the ListBox height
    *
    * It simply set a new height value to the ListBox and test if the 
    * string given by Caption::getHeight() is the same.
    *
    */
  void testListBoxHeight(){ 
    int y=4;
    this->m_caption->setHeight(y);
    int ret=this->m_caption->getHeight();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the ListBox Focus
    *
    * It simply set a new focus value to the ListBox and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testListBoxHasFocus(){
    this->m_caption->setFocus(true);
    CPPUNIT_ASSERT( this->m_caption->getFocus() );

  }

  /** Tests the ListBox Focus
    *
    * It simply set a new focus value to the ListBox and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testListBoxHasntFocus(){
    this->m_caption->setFocus(false);
    CPPUNIT_ASSERT( !this->m_caption->getFocus() );
  }

  /** Tests if the label can take focus
    *
    * The ListBox widget should be able to take focus
    *
    */
  void testListBoxCanTakeFocus(){
    CPPUNIT_ASSERT( this->m_caption->canHaveFocus());
  }

  /** Tests the setPosition function
    *
    * It simply calls setPosition() and tests if getX()
    * and getY() return the same values.
    *
    */
  void testListBoxPosition(){
    int x=25;
    int y=76;
    this->m_caption->setPosition(x, y);
    int x2= this->m_caption->getX();
    int y2= this->m_caption->getY();
    CPPUNIT_ASSERT(x==x2 && y==y2);
  }

  /** Adds an item and test if the itemCount is 1
    *
    */
  void testListBoxAddItem(){
    this->m_caption->addItem("testItem");
    unsigned itemCount=this->m_caption->itemCount();
    CPPUNIT_ASSERT(itemCount==1);
  }

  /** Set the drawCaption to false and tests if it is really false
    *
    */
  void testListBoxDrawCaption(){
    this->m_caption->setDrawCaption(false);
    CPPUNIT_ASSERT(!this->m_caption->getDrawCaption());
  }
};


#endif // LINEEDIT_TEST_H

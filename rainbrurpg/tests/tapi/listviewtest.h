#ifndef LISTVIEW_TEST_H
#define LISTVIEW_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <listviewitem.h>
#include <listviewcolumn.h>

#include <string>
#include <iostream>

using namespace std;
using namespace RainbruRPG::Terminal;

/** A test class for TerminalAPI::ListView widget
  *
  *
  */
template<class TESTEDCLASS> 
class ListViewTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the ListView test 
  CPPUNIT_TEST_SUITE( ListViewTest );
  /** Tests the ListView's caption
    *
    * \sa testListViewCaption
    *
    */
  CPPUNIT_TEST( testListViewCaption );
  /** Tests the ListView's X
    *
    * \sa testListViewX
    *
    */
  CPPUNIT_TEST( testListViewX );
  /** Tests the ListView's Y
    *
    * \sa testListViewY
    *
    */
  CPPUNIT_TEST( testListViewY );
  /** Tests the ListView's width
    *
    * \sa testListViewWidth
    *
    */
  CPPUNIT_TEST( testListViewWidth );
  /** Tests the ListView's height
    *
    * \sa testListViewHeight
    *
    */
  CPPUNIT_TEST( testListViewHeight );
  /** Tests the ListView's focus
    *
    * \sa testListViewCanTakeFocus
    *
    */
  CPPUNIT_TEST( testListViewCanTakeFocus );
  /** Tests the ListView's focus
    *
    * \sa testListViewHasFocus
    *
    */
  CPPUNIT_TEST( testListViewHasFocus );
  /** Tests the ListView's focus
    *
    * \sa testListViewHasntFocus
    *
    */
  CPPUNIT_TEST( testListViewHasntFocus );
  /** Tests the ListView's position
    *
    * \sa testListViewPosition
    *
    */
  CPPUNIT_TEST( testListViewPosition );
  /** Tests the ListView's size
    *
    * \sa testListViewSize
    *
    */
  CPPUNIT_TEST( testListViewSize );
  /** Tests the ListView's drawCaption
    *
    * \sa testListViewDrawCaption
    *
    */
  CPPUNIT_TEST( testListViewDrawCaption );
  /** Tests the ListView's AddItem
    *
    * \sa testListViewAddItem
    *
    */
  CPPUNIT_TEST( testListViewAddItem );
  /** Tests the ListView's addColumn
    *
    * \sa testListViewAddColumn
    *
    */
  CPPUNIT_TEST( testListViewAddColumn );
  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the tested class
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
  
  /** Tests the ListView caption
    *
    * It simply set a new text to the ListView and test if the 
    * string given by Caption::getText() is the same.
    *
    */
  void testListViewCaption(){ 
    const char* t="TestCaption";
    this->m_caption->setCaption(t);
    const char* ret=this->m_caption->getCaption();
    int cmp=strcmp(t, ret);
    CPPUNIT_ASSERT( cmp==0 );
  }

  /** Tests the ListView x position
    *
    * It simply set a new x value to the ListView and test if the 
    * string given by Caption::getX() is the same.
    *
    */
  void testListViewX(){ 
    int x=1;
    this->m_caption->setX(x);
    int ret=this->m_caption->getX();
    CPPUNIT_ASSERT( x==ret );
  }

  /** Tests the ListView y position
    *
    * It simply set a new y value to the ListView and test if the 
    * string given by Caption::getY() is the same.
    *
    */
  void testListViewY(){ 
    int y=2;
    this->m_caption->setY(y);
    int ret=this->m_caption->getY();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the ListView width
    *
    * It simply set a new width value to the ListView and test if the 
    * string given by Caption::getWidth() is the same.
    *
    */
  void testListViewWidth(){ 
    int y=3;
    this->m_caption->setWidth(y);
    int ret=this->m_caption->getWidth();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the ListView height
    *
    * It simply set a new height value to the ListView and test if the 
    * string given by Caption::getHeight() is the same.
    *
    */
  void testListViewHeight(){ 
    int y=4;
    this->m_caption->setHeight(y);
    int ret=this->m_caption->getHeight();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the ListView Focus
    *
    * It simply set a new focus value to the ListView and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testListViewHasFocus(){
    this->m_caption->setFocus(true);
    CPPUNIT_ASSERT( this->m_caption->getFocus() );

  }

  /** Tests the ListView Focus
    *
    * It simply set a new focus value to the ListView and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testListViewHasntFocus(){
    this->m_caption->setFocus(false);
    CPPUNIT_ASSERT( !this->m_caption->getFocus() );
  }

  /** Tests if the label can take focus
    *
    * The ListView widget should be able to take focus
    *
    */
  void testListViewCanTakeFocus(){
    CPPUNIT_ASSERT( this->m_caption->canHaveFocus());
  }

  /** Tests the setPosition function
    *
    */
  void testListViewPosition(){
    int x=12;
    int y=15;
    this->m_caption->setPosition(x, y);
    int x2=this->m_caption->getX();
    int y2=this->m_caption->getY();
    CPPUNIT_ASSERT( x==x2&&y==y2);
  }

  /** Tests the setSize() function
    *
    */
  void testListViewSize(){
    int w=22;
    int h=35;
    this->m_caption->setSize(w, h);
    int w2=this->m_caption->getWidth();
    int h2=this->m_caption->getHeight();
    CPPUNIT_ASSERT( w==w2 && h==h2);
  }

  /** Tests the drawCaption function
    *
    */
  void testListViewDrawCaption(){
    bool b=!this->m_caption->getDrawCaption();
    this->m_caption->setDrawCaption(b);
    CPPUNIT_ASSERT(this->m_caption->getDrawCaption()==b );
  }

  /** Tests the addItem function
    *
    */
  void testListViewAddItem(){
    unsigned int i=this->m_caption->itemCount();
    this->m_caption->addItem(new ListViewItem());
    unsigned int i2=this->m_caption->itemCount();
    CPPUNIT_ASSERT(i2==++i);

  }

  /** Tests the addColumn function
    *
    */
  void testListViewAddColumn(){
    unsigned int i=this->m_caption->columnCount();
    this->m_caption->addColumn(new ListViewColumn());
    unsigned int i2=this->m_caption->columnCount();
    CPPUNIT_ASSERT(i2==++i);

  }
};


#endif // LABEL_TEST_H
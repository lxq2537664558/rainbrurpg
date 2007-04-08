#ifndef LINEEDIT_TEST_H
#define LINEEDIT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

//#include <caption.h>

#include <string>

using namespace std;


/** A test class for TerminalAPI's LineEdit widget
  *
  */
template<class TESTEDCLASS> 
class LineEditTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the LineEdit test 
  CPPUNIT_TEST_SUITE( LineEditTest );

  /** Tests the LineEdit's caption
    *
    * \sa testLineEditCaption
    *
    */
  CPPUNIT_TEST( testLineEditCaption );

  /** Tests the LineEdit's x position
    *
    * \sa testLineEditX
    *
    */
  CPPUNIT_TEST( testLineEditX );

  /** Tests the LineEdit's y position
    *
    * \sa testLineEditY
    *
    */
  CPPUNIT_TEST( testLineEditY );

  /** Tests the LineEdit's width
    *
    * \sa testLineEditWidth
    *
    */
  CPPUNIT_TEST( testLineEditWidth );

  /** Tests the LineEdit's height
    *
    * \sa testLineEditHeight
    *
    */
  CPPUNIT_TEST( testLineEditHeight );

  /** Tests the LineEdit's hasfocus
    *
    * \sa testLineEditHasFocus
    *
    */
  CPPUNIT_TEST( testLineEditHasFocus );

  /** Tests the LineEdit's hasfocus
    *
    * \sa testLineEditHasntFocus
    *
    */
  CPPUNIT_TEST( testLineEditHasntFocus );

  /** Tests the LineEdit's can take focus
    *
    * \sa testLineEditCanTakeFocus
    *
    */
  CPPUNIT_TEST( testLineEditCanTakeFocus );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the LineEdit widget
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
  
  /** Tests the LineEdit caption
    *
    * It simply set a new text to the LineEdit and test if the 
    * string given by Caption::getText() is the same.
    *
    */
  void testLineEditCaption(){ 
    const char* t="TestCaption";
    this->m_caption->setText(t);
    const char* ret=this->m_caption->getText();
    int cmp=strcmp(t, ret);
    CPPUNIT_ASSERT( cmp==0 );
  }

  /** Tests the LineEdit x position
    *
    * It simply set a new x value to the LineEdit and test if the 
    * string given by Caption::getX() is the same.
    *
    */
  void testLineEditX(){ 
    int x=1;
    this->m_caption->setX(x);
    int ret=this->m_caption->getX();
    CPPUNIT_ASSERT( x==ret );
  }

  /** Tests the LineEdit y position
    *
    * It simply set a new y value to the LineEdit and test if the 
    * string given by Caption::getY() is the same.
    *
    */
  void testLineEditY(){ 
    int y=2;
    this->m_caption->setY(y);
    int ret=this->m_caption->getY();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the LineEdit width
    *
    * It simply set a new width value to the LineEdit and test if the 
    * string given by Caption::getWidth() is the same.
    *
    */
  void testLineEditWidth(){ 
    int y=3;
    this->m_caption->setWidth(y);
    int ret=this->m_caption->getWidth();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the LineEdit height
    *
    * It simply set a new height value to the LineEdit and test if the 
    * string given by Caption::getHeight() is the same.
    *
    */
  void testLineEditHeight(){ 
    int y=4;
    this->m_caption->setHeight(y);
    int ret=this->m_caption->getHeight();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the LineEdit Focus
    *
    * It simply set a new focus value to the LineEdit and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testLineEditHasFocus(){
    this->m_caption->setFocus(true);
    CPPUNIT_ASSERT( this->m_caption->getFocus() );

  }

  /** Tests the LineEdit Focus
    *
    * It simply set a new focus value to the LineEdit and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testLineEditHasntFocus(){
    this->m_caption->setFocus(false);
    CPPUNIT_ASSERT( !this->m_caption->getFocus() );
  }

  /** Tests if the label can take focus
    *
    * The LineEdit widget should be able to take focus
    *
    */
  void testLineEditCanTakeFocus(){
    CPPUNIT_ASSERT( this->m_caption->canHaveFocus());
  }

};


#endif // LINEEDIT_TEST_H

#ifndef LABEL_TEST_H
#define LABEL_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

//#include <caption.h>

#include <string>

using namespace std;


/** A test class for TerminalAPI's  Label widget
  *
  */
template<class TESTEDCLASS> 
class LabelTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the Label test 
  CPPUNIT_TEST_SUITE( LabelTest );

  /** Tests the Label's caption
    *
    * \sa testLabelCaption
    *
    */
  CPPUNIT_TEST( testLabelCaption );

  /** Tests the Label's X position
    *
    * \sa testLabelX
    *
    */
  CPPUNIT_TEST( testLabelX );

  /** Tests the Label's Y position
    *
    * \sa testLabelY
    *
    */
  CPPUNIT_TEST( testLabelY );

  /** Tests the Label's width
    *
    * \sa testLabelWidth
    *
    */
  CPPUNIT_TEST( testLabelWidth );

  /** Tests the Label's height
    *
    * \sa testLabelHeight
    *
    */
  CPPUNIT_TEST( testLabelHeight );

  /** Tests the Label's focus
    *
    * \sa testLabelHasFocus
    *
    */
  CPPUNIT_TEST( testLabelHasFocus );

  /** Tests the Label's focus
    *
    * \sa testLabelHasntFocus
    *
    */
  CPPUNIT_TEST( testLabelHasntFocus );

  /** Tests the Label's canTakeFocus
    *
    * \sa testLabelCanTakeFocus
    *
    */
  CPPUNIT_TEST( testLabelCanTakeFocus );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the caption widget
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
  
  /** Tests the Label caption
    *
    * It simply set a new text to the Label and test if the 
    * string given by Caption::getText() is the same.
    *
    */
  void testLabelCaption(){ 
    char* t="TestCaption";
    this->m_caption->setText(t);
    char* ret=this->m_caption->getText();
    int cmp=strcmp(t, ret);
    CPPUNIT_ASSERT( cmp==0 );
  }

  /** Tests the Label x position
    *
    * It simply set a new x value to the Label and test if the 
    * string given by Caption::getX() is the same.
    *
    */
  void testLabelX(){ 
    int x=1;
    this->m_caption->setX(x);
    int ret=this->m_caption->getX();
    CPPUNIT_ASSERT( x==ret );
  }

  /** Tests the Label y position
    *
    * It simply set a new y value to the Label and test if the 
    * string given by Caption::getY() is the same.
    *
    */
  void testLabelY(){ 
    int y=2;
    this->m_caption->setY(y);
    int ret=this->m_caption->getY();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the Label width
    *
    * It simply set a new width value to the Label and test if the 
    * string given by Caption::getWidth() is the same.
    *
    */
  void testLabelWidth(){ 
    int y=3;
    this->m_caption->setWidth(y);
    int ret=this->m_caption->getWidth();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the Label height
    *
    * It simply set a new height value to the Label and test if the 
    * string given by Caption::getHeight() is the same.
    *
    */
  void testLabelHeight(){ 
    int y=4;
    this->m_caption->setHeight(y);
    int ret=this->m_caption->getHeight();
    CPPUNIT_ASSERT( y==ret );
  }

  /** Tests the Label Focus
    *
    * It simply set a new focus value to the Label and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testLabelHasFocus(){
    this->m_caption->setFocus(true);
    CPPUNIT_ASSERT( this->m_caption->getFocus() );

  }

  /** Tests the Label Focus
    *
    * It simply set a new focus value to the Label and test if the 
    * string given by Caption::hasFocus() is the same.
    *
    */
  void testLabelHasntFocus(){
    this->m_caption->setFocus(false);
    CPPUNIT_ASSERT( !this->m_caption->getFocus() );
  }

  /** Tests if the label can take focus
    *
    * The Label widget should not be able to take focus
    *
    */
  void testLabelCanTakeFocus(){
    CPPUNIT_ASSERT( !this->m_caption->canHaveFocus());
  }

};


#endif // LABEL_TEST_H

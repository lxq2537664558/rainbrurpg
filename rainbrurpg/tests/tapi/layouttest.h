#ifndef LAYOUT_TEST_H
#define LAYOUT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <caption.h>

#include <string>

using namespace std;

/** A test class for TerminalAPI layout
  *
  */
template<class TESTEDCLASS> 
class LayoutTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the Layout test 
  CPPUNIT_TEST_SUITE( LayoutTest );

  /** Tests the Layout's xOrigin
    *
    * \sa 
    *
    */
  CPPUNIT_TEST( testLaoutXOrigin );

  /** Tests the Layout's yOrigin
    *
    * \sa 
    *
    */
  CPPUNIT_TEST( testLaoutYOrigin );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the Layout widget
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
  
  /** Tests the Layout x origin
    *
    * Set a new value to xOrigin, get it and
    * test if it was changed correctly.
    *
    */
  void testLaoutXOrigin(){ 
    int x=10;
    this->m_caption->setXOrigin(x);
    int ret=this->m_caption->getXOrigin();
    CPPUNIT_ASSERT( ret==x );
  }

  /** Tests the layout y origin
    *
    * Set a new value to yOrigin, get it and
    * test if it was changed correctly.
    *
    */
  void testLaoutYOrigin(){ 
    int x=12;
    this->m_caption->setYOrigin(x);
    int ret=this->m_caption->getYOrigin();
    CPPUNIT_ASSERT( ret==x );
  }


};


#endif // LAYOUT_TEST_H

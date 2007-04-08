#ifndef FREELAYOUT_TEST_H
#define FREELAYOUT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <caption.h>

#include <string>

using namespace std;

/** A class to test TerminalAPI FreeLayout widget
  *
  */
template<class GAMECLASS> 
class FreeLayoutTest : public CPPUNIT_NS::TestFixture 
{
  /// The entry macro of the FreeLayout test
  CPPUNIT_TEST_SUITE( FreeLayoutTest );

  /** The FreeLaout XOrigin test definition
    *
    * \sa testFreeLaoutXOrigin
    *
    */
  CPPUNIT_TEST( testFreeLaoutXOrigin );

  /** The FreeLaout YOrigin test definition
    *
    * \sa testFreeLaoutYOrigin
    *
    */
  CPPUNIT_TEST( testFreeLaoutYOrigin );
  /// The end macro of the FreeLayout test
  CPPUNIT_TEST_SUITE_END();
protected:
  /// The working instance
  GAMECLASS	*m_caption;
  
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
    this->m_caption = new GAMECLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_caption; 
  }
  
  /** Tests the Caption text field
    *
    * It simply set a new text to the Caption and test if the 
    * string given by Caption::getText() is the same.
    *
    */
  void testFreeLaoutXOrigin(){ 
    int x=10;
    this->m_caption->setXOrigin(x);
    int ret=this->m_caption->getXOrigin();
    CPPUNIT_ASSERT( ret==x );
  }

  /** Tests the Caption text field
    *
    * It simply set a new text to the Caption and test if the 
    * string given by Caption::getText() is the same.
    *
    */
  void testFreeLaoutYOrigin(){ 
    int x=12;
    this->m_caption->setYOrigin(x);
    int ret=this->m_caption->getYOrigin();
    CPPUNIT_ASSERT( ret==x );
  }


};


#endif // FREELAYOUT_TEST_H

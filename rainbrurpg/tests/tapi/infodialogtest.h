#ifndef INFODIALOG_TEST_H
#define INFODIALOG_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

//#include <caption.h>

#include <string>

using namespace std;

/** A test class for TerminalAPI InfoDialog widget
  *
  */
template<class TESTEDCLASS> 
class InfoDialogTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the InfoDialog test 
  CPPUNIT_TEST_SUITE( InfoDialogTest );

  /** Tests the InfoDialog's message
    *
    * \sa testInfoDialogMessage
    *
    */
  CPPUNIT_TEST( testInfoDialogMessage );

  /** Tests the InfoDialog's title
    *
    * \sa testInfoDialogTitle
    *
    */
  CPPUNIT_TEST( testInfoDialogTitle );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the InfioDialog widget
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
  
  /** Tests the IndoDialog message field
    *
    * It simply set a new message and test with getMessage() if it
    * was correctly set.
    *
    */
  void testInfoDialogMessage(){ 
    std::string t="TestMessage";
    this->m_caption->setMessage(t);
    std::string ret=this->m_caption->getMessage();
    int cmp=t.compare(ret);
    CPPUNIT_ASSERT( cmp==0 );
  }

  /** Tests the IndoDialog title field
    *
    * It simply set a new title and test with getTitle() if it
    * was correctly set.
    *
    */
  void testInfoDialogTitle(){
    std::string t="TestTitle";
    this->m_caption->setTitle(t);
    std::string ret=this->m_caption->getTitle();
    int cmp=t.compare(ret);
    CPPUNIT_ASSERT( cmp==0 );
  }
};


#endif // INFODIALOG_TEST_H
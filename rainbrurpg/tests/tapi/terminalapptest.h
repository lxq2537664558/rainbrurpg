#ifndef TERMINALAPP_TEST_H
#define TERMINALAPP_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <menu.h>
#include <logger.h>
#include <window.h>
#include <menubar.h>

#include <string>

using namespace std;
using namespace RainbruRPG::Terminal;


/** A test class for TerminalApp
  *
  * It tests the TerminalApp class.
  *
  */
template<class TESTEDCLASS> 
class TerminalAppTest : public CPPUNIT_NS::TestFixture 
{
  /// Declare the TerminalApp test fixture
  CPPUNIT_TEST_SUITE( TerminalAppTest );

    /// Launch the testTerminalAppAddWindow() test
    CPPUNIT_TEST( testTerminalAppAddWindow );
    /// Launch the testTerminalGetMenuBar() test
    CPPUNIT_TEST( testTerminalGetMenuBar );

  /// Ends the tests
  CPPUNIT_TEST_SUITE_END();

protected:
  /** The tested instance of TerminalApp */
  TESTEDCLASS	*m_caption;
  
public:

  /** Return the number of testcase
    *
    * \return Always 1
    */ 
  int countTestCases () const{
    return 1;
  }
  
  /** Initialize the tested instance
    *
    */
  void setUp(){ 
    this->m_caption = new TESTEDCLASS; 
  }
  
  /** Delete the tested instance
    *
    */
  void tearDown(){ 
    delete this->m_caption; 
  }
  
  /** Tests the addWindow function
    *
    */
  void testTerminalAppAddWindow(){ 
    unsigned int wn=this->m_caption->windowCount();
    this->m_caption->addWindow(new Window());
    unsigned int wn2=this->m_caption->windowCount();
    CPPUNIT_ASSERT( wn2==++wn );
  }

  /** Tests the getMenuBar function
    *
    */
  void testTerminalGetMenuBar(){
    this->m_caption->setMenubar(new MenuBar());
    MenuBar* mb=this->m_caption->getMenubar();
    CPPUNIT_ASSERT( mb!=NULL );
  }
};


#endif // TERMINALAPP_TEST_H

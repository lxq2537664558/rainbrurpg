#ifndef MENUITEM_TEST_H
#define MENUITEM_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <menu.h>
#include <logger.h>

#include <string>

using namespace std;

/** A function that is used to be a menu action
  *
  * As the menu action is a function pointer, it need a function.
  *
  * \return Always 255.
  *
  */
int MenuItemTestAction(){
  return 255;
}

 
/** A test class for TerminalAPI MenuItem
  *
  */
template<class TESTEDCLASS> 
class MenuItemTest : public CPPUNIT_NS::TestFixture 
{
  /// Declares the ScrollingPanelTest test fixture
  CPPUNIT_TEST_SUITE( MenuItemTest );

    /// Launches the testMenuItemName() test
    CPPUNIT_TEST( testMenuItemName );
    /// Launches the testMenuItemEmptyAction() test
    CPPUNIT_TEST( testMenuItemEmptyAction );
    /// Launches the testMenuItemFireAction() test
    CPPUNIT_TEST( testMenuItemFireAction );

  /// Terminates the tests
  CPPUNIT_TEST_SUITE_END();

protected:
  /** The tested MenuItem instance */
  TESTEDCLASS	*m_caption;
  
public:
  /** Return the number of test case
    *
    * \return Always 1
    *
    */
  int countTestCases () const{
    return 1;
  }
  
  /** Construct the tested instance
    *
    */
  void setUp(){ 
    this->m_caption = new TESTEDCLASS; 
  }
  
  /** Deletes the tested instance
    *
    */
  void tearDown(){ 
    delete this->m_caption; 
  }
  
  /** Tests the name field
    *
    * It sets a new name to the menuItem and check with getName
    * if it was set correctly
    *
    */
  void testMenuItemName(){ 
    const char* name="MenuItemName";
    this->m_caption->setName(name);
    int ret=strcmp( this->m_caption->getName(), name);
    CPPUNIT_ASSERT( ret==0 );
  }

  /** Fires the event and check if it returns -1
    *
    * If none pointer function was set, int MenuItem::fireAction()
    * should return -1.
    *
    */
  void testMenuItemEmptyAction(){
    int ret=this->m_caption->fireAction();
    CPPUNIT_ASSERT( ret==-1 );
  }

  /** Sets an action modifying a static var and fires the action to test
    * if the static var was modified
    *
    */
  void testMenuItemFireAction(){
    this->m_caption->setAction(&MenuItemTestAction);
    int ret=this->m_caption->fireAction();
    CPPUNIT_ASSERT( ret==255 );
  }

};


#endif // MENUITEM_TEST_H

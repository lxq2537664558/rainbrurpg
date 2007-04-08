#ifndef LISTVIEW_TEST_TEST_H
#define LISTVIEW_TEST_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <string>

using namespace std;

/** A etst suite for TerminalAPI ListViewItem
  *
  */
template<class TESTEDCLASS> 
class ListViewItemTest : public CPPUNIT_NS::TestFixture 
{
  /// Start the ListView test 
  CPPUNIT_TEST_SUITE( ListViewItemTest );

  /** Tests the ListViewItem's addColumn function
    *
    * \sa testListItemAddColumn
    *
    */
  CPPUNIT_TEST( testListItemAddColumn );
  /** Tests the ListViewItem's getColumn function
    *
    * \sa testListItemGetColumn
    *
    */
  CPPUNIT_TEST( testListItemGetColumn );
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
  
  /** Tests the addColumn function
    *
    * It simply add a column using the addColumn() function
    * and test if the columnCount function returns 1.
    */
  void testListItemAddColumn(){ 
    const char* cap="ColumnCaptionTest";
    this->m_caption->addColumn(cap);
    unsigned int count=this->m_caption->columnCount();
    CPPUNIT_ASSERT( count==1 );
  }

  /** Tests the getColumn function
    *
    * Adds a new column and test if the getColumn() function
    * return the same content.
    *
    */
  void testListItemGetColumn(){ 
    const char* cap="ColumnCaptionTest";
    this->m_caption->addColumn(cap);
    const char* colContent;
    colContent=this->m_caption->getColumn(0);
    int ret=strcmp(colContent, cap);
    CPPUNIT_ASSERT( ret==0 );
  }


};


#endif // LISTVIEW_TEST_TEST_H

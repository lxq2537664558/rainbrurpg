/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file itemlistfiletest.h
  * Implements the unit tests of the ItemListFile class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef _ITEM_LIST_FILE_H_
#define _ITEM_LIST_FILE_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <hashpassword.h>
#include <string>
#include <fstream>
#include <cstdio>  // For the remove() function
#include <logger.h>

using namespace std;

/** Defines the name of the file created for test */
#define ILF_TEST_FILE_NAME "itemlistfiletest.txt"

/** Defines the name of the file that do not exist */
#define ILF_TEST_INEXIST_FILE_NAME "itemlistfiletest_that_do_not_exist.txt"

/** Defines the end of line in the created files */
#define ILF_CRLF "\n"

/** Defines the header of most created files 
  * 
  * This macro is used both to test commentaries and to add a header telling
  * the user he can remove this file.
  *
  */
#define ILF_TEST_HEADER "#"ILF_CRLF \
                        "# This file was generated for unit test"ILF_CRLF \
                        "# from the ItemListFile's test suite."ILF_CRLF     \
                        "#"ILF_CRLF     \
                        "# You can safely remove it."ILF_CRLF     \
                        "#"

/** Defines a file containing only empty lines*/
#define ILF_TEST_EMPTYLINES ILF_TEST_HEADER""ILF_CRLF \
                            ""ILF_CRLF \
                            ""ILF_CRLF \
                            ""ILF_CRLF 

/** Defines a file containing space-only lines*/
#define ILF_TEST_SPACEONLY ILF_TEST_HEADER""ILF_CRLF \
                           "   "ILF_CRLF \
                           "  "ILF_CRLF \
                           ""ILF_CRLF 


/** Defines a file containing a sharp item*/
#define ILF_TEST_SHARPITEM ILF_TEST_HEADER""ILF_CRLF \
                           " # This is not a comment"ILF_CRLF \
                           ""ILF_CRLF 

/** The item that should be found */
#define ILF_TEST_MUSTBEFOUND_ITEM "An_item_that_must_be_found"

/** The item that should not be found */
#define ILF_TEST_MUSTNOTBEFOUND_ITEM "An_item_that_should_not_be_found"

/** Defines a file containing a sharp item*/
#define ILF_TEST_MUSTBEFOUND ILF_TEST_HEADER""ILF_CRLF \
                             ILF_TEST_MUSTBEFOUND_ITEM""ILF_CRLF \
                             ""ILF_CRLF 

/** A test class for ItemListFile
  *
  */
template<class TESTEDCLASS> 
class ItemListFileTest : public CPPUNIT_NS::TestFixture{

  /// Start the test 
  CPPUNIT_TEST_SUITE( ItemListFileTest );

  /** Tests with a file that does not exist */
  CPPUNIT_TEST( testInexistFile );

  /** Tests with a file that contains only comments lines */
  CPPUNIT_TEST( testOnlyComments );

  /** Tests with a file that contains only empty lines */
  CPPUNIT_TEST( testEmptyLines );

  /** Tests with a file that contains only space characters lines */
  CPPUNIT_TEST( testSpaceOnly );

  /** Tests with sharp not in first character */
  CPPUNIT_TEST( testSharpItem );

  /** Tests with sharp not in first character */
  CPPUNIT_TEST( testAddItem );

  /** Tests exist with an empty parameter */
  CPPUNIT_TEST( testExistEmpty );

  /** Tests exist with an existing item */
  CPPUNIT_TEST( testExistFound );

  /** Tests exist with an inexisting item */
  CPPUNIT_TEST( testExistNotFound );

  /** Tests if the file was correctly deleted */
  CPPUNIT_TEST( testFileDeleted );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the tested class   */
  TESTEDCLASS	*m_instance;
  
private:
  /** Create the temporary test file and init the ItemListFile instance with */
  void createTestFile(const std::string& content){
    // scope with std namespace cause ofstream is ambiguous
    std::ofstream filestr(ILF_TEST_FILE_NAME);
    filestr << content << endl;
    filestr.close();

    this->m_instance->load(ILF_TEST_FILE_NAME);
  }

  /** Delete the temporary test file and reset the ItemListFile instance */
  void deleteTestFile(void){
    remove(ILF_TEST_FILE_NAME);

    this->m_instance->reset();
  }

public:
  /** Return the number of test cases
    *
    * \return Currently always return 1
    *
    */
  int countTestCases(void){
    return 1;
  }

  /** Creates a new instance to test    */
  void setUp(void){ 
    this-> m_instance= new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance  */
  void tearDown(void){ 
    delete this->m_instance; 
  }

  /** Try to load an inexisting file */
  void testInexistFile(void){
    this->m_instance->load(ILF_TEST_INEXIST_FILE_NAME);
    CPPUNIT_ASSERT( this->m_instance->getItemList().size() == 0);

  }

  /** Test with a file containing only comments */
  void testOnlyComments(void){
    createTestFile(ILF_TEST_HEADER);
    CPPUNIT_ASSERT( this->m_instance->getItemList().size() == 0);
    deleteTestFile();
  }

  /** Try to load a file filled with empty files */
  void testEmptyLines(void){
    createTestFile(ILF_TEST_EMPTYLINES);
    CPPUNIT_ASSERT( this->m_instance->getItemList().size() == 0);
    deleteTestFile();
  }

  /** Try to load a file filled with space-only files */
  void testSpaceOnly(void){
    createTestFile(ILF_TEST_SPACEONLY);
    CPPUNIT_ASSERT( this->m_instance->getItemList().size() == 2);
    deleteTestFile();
  }

  /** Test a file with a sharp that is not the first character
    *
    * This should be an item
    *
    */
  void testSharpItem(void){
    createTestFile(ILF_TEST_SHARPITEM);
    CPPUNIT_ASSERT( this->m_instance->getItemList().size() == 1);
    deleteTestFile();
  }

  /** Test that the addItem function works */
  void testAddItem(void){
    createTestFile(ILF_TEST_HEADER);
    int lsize = this->m_instance->getItemList().size();

    // Adding an item
    this->m_instance->addItem("A_New_Item");
    int new_size = this->m_instance->getItemList().size();
    CPPUNIT_ASSERT( new_size == lsize + 1 );
    
    // Adding a comment
    this->m_instance->addItem("# A comment");
    new_size = this->m_instance->getItemList().size();
    CPPUNIT_ASSERT( new_size == lsize + 1 );

    deleteTestFile();

  }

  /** Test the exists() function with emprt string parameter */
  void testExistEmpty(void){
    // Test also with empty lines
    createTestFile(ILF_TEST_HEADER);
    CPPUNIT_ASSERT( this->m_instance->exists("") == false);
    deleteTestFile();

    // Test also with empty lines
    createTestFile(ILF_TEST_EMPTYLINES);
    CPPUNIT_ASSERT( this->m_instance->exists("") == false);
    deleteTestFile();

  }

  /** Test the exists() function with an item that should be found */
  void testExistFound(void){
    createTestFile(ILF_TEST_MUSTBEFOUND);
    CPPUNIT_ASSERT( m_instance->exists(ILF_TEST_MUSTBEFOUND_ITEM) == true);
    deleteTestFile();
  }

  /** Test the exists() function with an item that should not be found */
  void testExistNotFound(void){
    createTestFile(ILF_TEST_MUSTBEFOUND);
    CPPUNIT_ASSERT( m_instance->exists(ILF_TEST_MUSTNOTBEFOUND_ITEM)==false);
    deleteTestFile();
  }

  /** Test if the temporary file called ILF_TEST_FILE_NAME was
    * correctly deleted
    *
    */
  void testFileDeleted(void){
    // Test if the file exist
    std::ifstream filestr(ILF_TEST_FILE_NAME, ios::in );
    CPPUNIT_ASSERT( filestr.fail() );
  }
};
#endif // _ITEM_LIST_FILE_H_


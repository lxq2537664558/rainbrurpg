/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

/** \file hashfiletest.h
  * Unittests of HashFile class
  *
  * Modifications :
  * - 26 aug 2008 : Starting implementation
  *
  */

#ifndef _HASH_FILE_TEST_H_
#define _HASH_FILE_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <hashfile.h>
#include <string>
#include <iostream>
#include <fstream>
#include <cstdio>

/** \def HASHFILE_TEST_FILENAME
  * The filename of the file to test
  *
  */
#define HASHFILE_TEST_FILENAME "hashfiletest.txt"

/** \def HASHFILE_TEST_CONTENT
  * The content of the file to test
  *
  */
#define HASHFILE_TEST_CONTENT "RainbruRPG-tests datafile \n \
                               You can safely remove this file. "

/** \def HASHFILE_TEST_INEXIST
  * The name of a file that do not exist.
  *
  */
#define HASHFILE_TEST_INEXIST  "file_that_do_not_exist.txt"

/** \def HASHFILE_TEST_RESULT
  * The SHA1 hashsum of the file named HASHFILE_TEST_FILENAME
  *
  */
#define HASHFILE_TEST_RESULT   "8872BC06954B0A689C39600FE9F2695D20776DE3"

/** A test class for GlobalURI
  *
  * The goal of this test is to create a file named HASHFILE_TEST_FILENAME
  * containing HASHFILE_TEST_CONTENT. Then we compute its hashsum using
  * the HashFile class and test its result with the HASHFILE_TEST_RESULT
  * value.
  *
  * We also test that HashFile return an empty string for a file that
  * do not exist.
  *
  */
template<class TESTEDCLASS> 
class HashFileTest : public CPPUNIT_NS::TestFixture{

  /// Start the test 
  CPPUNIT_TEST_SUITE( HashFileTest );

  /** Tests with a file that does not exist
    *
    * \sa testInexistFile
    *
    */
  CPPUNIT_TEST( testInexistFile );

  /** Tests with a real file
    *
    * \sa testRealFile
    *
    */
  CPPUNIT_TEST( testRealFile );


  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the tested class   */
  TESTEDCLASS	*m_instance;
  
public:
  /** Return the number of test cases
    *
    * \return Currently always return 1
    *
    */
  int countTestCases(void){
    return 1;
  }

  /** Creates a new instance to test
    *
    */
  void setUp(void){ 
    this-> m_instance= new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(void){ 
    delete this->m_instance; 
  }

  /** Test with an inexisting file */
  void testInexistFile(void){
    string res = this->m_instance->getHashSum(HASHFILE_TEST_INEXIST);
    CPPUNIT_ASSERT( res.empty());
  }

  /** Test with an existing file */
  void testRealFile(void){
    // Create the tested file
    std::ofstream os(HASHFILE_TEST_FILENAME ); 
    os << HASHFILE_TEST_CONTENT;
    os.close();
    
    string res = this->m_instance->getHashSum(HASHFILE_TEST_FILENAME);
    CPPUNIT_ASSERT( res == HASHFILE_TEST_RESULT);

    // Remove file
    int removeRes = remove(HASHFILE_TEST_FILENAME);
    CPPUNIT_ASSERT(removeRes == 0);
    
  }


};

#endif // _HASH_FILE_TEST_H_

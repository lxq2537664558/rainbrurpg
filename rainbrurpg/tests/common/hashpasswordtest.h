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

/** \file hashpasswordtest.h
  * Implements the unit tests of the HashPassword class
  *
  * Modifications :
  * - 28 aug 2008 : Starting implementation
  *
  */

#ifndef _HASH_PASSWORD_TEST_H_
#define _HASH_PASSWORD_TEST_H_

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <hashpassword.h>
#include <string>
#include <logger.h>

/** Defines a single char password */
#define HPT_SINGLE_CHAR     "A"
/** Defines the hashsum of the sigle char password */ 
#define HPT_SINGLE_CHAR_SUM "DA39A3EE5E6B4B0D3255BFEF95601890AFD80709"

/** Defines the <em>real</em> password */
#define HPT_SINGLE_PWD      "12aM86pz72Vr"
/** Defines the  hashsum of the <em>real</em> password */
#define HPT_SINGLE_PWD_SUM  "053709605543B100BC1902C51968BFA747875B33"
/** Should we log the <em>real</em> password hashsum */
#define HPT_SINGLE_PWD_LOG  false

/** A test class for GlobalURI
  *
  */
template<class TESTEDCLASS> 
class HashPasswordTest : public CPPUNIT_NS::TestFixture{

  /// Start the test 
  CPPUNIT_TEST_SUITE( HashPasswordTest );

  /** Tests a compare test
    *
    * \sa testCompareOk
    *
    */
  CPPUNIT_TEST( testCompareOk );

  /** Tests a compare test
    *
    * \sa testCompareFailed
    *
    */
  CPPUNIT_TEST( testCompareFailed );

  /** Tests with a file that does not exist
    *
    * \sa testEmptyInstr
    *
    */
  CPPUNIT_TEST( testEmptyInstr );

  /** Tests with a single character password
    *
    * \sa testOneChar
    *
    */
  CPPUNIT_TEST( testOneChar );


  /** Tests with a real password
    *
    * \sa testComplete
    *
    */
  CPPUNIT_TEST( testComplete );

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

  /** Test the HashPassword::compare() function with values that should be ok
    *
    */
  void testCompareOk(void){
    bool bres = this->m_instance->compare("aaa", "aaa");
    CPPUNIT_ASSERT( bres );
    
  }

  /** Test the HashPassword::compare() function with values that should fail
    *
    */
  void testCompareFailed(void){
    bool bres = this->m_instance->compare("aaa", "aab");
    CPPUNIT_ASSERT( !bres );
  }

  /** Test the encryption of an empty password
    *
    * HashPassword should return an empty string
    *
    */
  void testEmptyInstr(void){
    string res = this->m_instance->encryptString("");
    CPPUNIT_ASSERT( res.empty());
  }

  /** Test a password of one char lenght
    *
    * It is tested bacause there was a SEGFAULT with one char
    * before a bugfix.
    *
    */
  void testOneChar(void){
    string res = this->m_instance->encryptString(HPT_SINGLE_CHAR);
    LOGI(res.c_str());
    bool bres = this->m_instance->compare(res.c_str(), HPT_SINGLE_CHAR_SUM);
    CPPUNIT_ASSERT( bres );

  }

  /** Test with a real password
    *
    * This function can use logger to print debug information if
    * \ref HPT_SINGLE_PWD_LOG is defined as \c true.
    *
    */
  void testComplete(void){
    string res = this->m_instance->encryptString(HPT_SINGLE_PWD);

    if (HPT_SINGLE_PWD_LOG){
      LOGCATS("Hashsum for '");
      LOGCATS(HPT_SINGLE_PWD);
      LOGCATS("' is ");
      LOGCATS(res.c_str());
      LOGCAT();
    }

    bool bres = this->m_instance->compare(res.c_str(), HPT_SINGLE_PWD_SUM);
    CPPUNIT_ASSERT( bres );
    
  }
};

#endif // _HASH_PASSWORD_TEST_H_

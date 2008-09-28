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

/** \file curlaccountdeletetest.h
  * Implements the unit test for the CurlAccountDelete class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  * - 21 apr 2007 : Implementation
  *
  */

#ifndef CURL_ACCOUNT_DELETE_TEST_H
#define CURL_ACCOUNT_DELETE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <clientconnect.h>
#include <curlaccountadd.h>
#include <curlaccountdelete.h>
#include <curlaccountconfirmmail.h>
#include <curlaccounttoggleblacklist.h>
#include <string>

#include "virtualaccount.h"

using namespace std;
using namespace RainbruRPG::Network::Ident;

/** A test class for CurlAccountDelete
  *
  */
template<class TESTEDCLASS> 
class CurlAccountDeleteTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( CurlAccountDeleteTest );

  /** Try to delete an inexistant account
    *
    * \sa testInexistant
    *
    */
  CPPUNIT_TEST( testInexistant );

  /** Adds the virtual account
    *
    * \sa testAddAccount
    *
    */
  CPPUNIT_TEST( testAddAccount );

  /** Deletes the created account
    *
    * \sa testDeleteAccount
    *
    */
  CPPUNIT_TEST( testDeleteAccount );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the CurlAccountAdd class
    *
    */
  TESTEDCLASS	*m_instance;
  
public:
  /** Return the number of test cases
    *
    * \return Currently always return 1
    *
    */
  int countTestCases(){
    return 1;
  }

  /** Creates a new instance to test
    *
    */
  void setUp(){ 
    this->m_instance = new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_instance; 
  }

  /** Try to delete an inexistant account
    *
    * The boolean value return by perform should be \c false. If we
    * try to delete an inexistant account, the perform() function will
    * fail.
    *
    */
  void testInexistant(){
    this->m_instance->setName(CLIENT_NAME);
    bool bret=this->m_instance->perform();
    CPPUNIT_ASSERT( bret==false);

  }

  /** Add the test account
    *
    * The perform() result is tested to be sure the account is correctly 
    * added
    *
    */
  void testAddAccount(){
    CurlAccountAdd cca;
    cca.setName(CLIENT_NAME);
    cca.setPassword(CLIENT_PWD);
    cca.setMail(CLIENT_MAIL);
    bool bret=cca.perform();
    CPPUNIT_ASSERT( bret==true);

    tCurlAccountAddReturn ret=cca.getResponse();
    CPPUNIT_ASSERT( ret==CAA_SUCCESS);

  }

  /** Delete the test account
    *
    * The perform() return should be \c true
    *
    */
  void testDeleteAccount(){
    this->m_instance->setName(CLIENT_NAME);
    bool bret=this->m_instance->perform();
    CPPUNIT_ASSERT( bret==true);

  }

};

#endif // CURL_ACCOUNT_DELETE_TEST_H

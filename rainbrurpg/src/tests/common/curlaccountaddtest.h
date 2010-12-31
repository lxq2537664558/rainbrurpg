/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file curlaccountaddtest.h
  * Implements the unit test for the CurlAccountAdd class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  * - 06 mar 2007 : Implementation
  *
  */

#ifndef CURL_ACCOUNT_ADD_TEST_H
#define CURL_ACCOUNT_ADD_TEST_H

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

/** A test class for CurlAccountAdd
  *
  */
template<class TESTEDCLASS> 
class CurlAccountAddTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( CurlAccountAddTest );

  /** Tests the initial response
    *
    * \sa testInitialResponse
    *
    */
  CPPUNIT_TEST( testInitialResponse );

  /** Tests the empty name response
    *
    * \sa testEmptyName
    *
    */
  CPPUNIT_TEST( testEmptyName );

  /** Tests the empty password response
    *
    * \sa testEmptyPassword
    *
    */
  CPPUNIT_TEST( testEmptyPassword );

  /** Tests a mail address with missing at sign
    *
    * \sa testMissingAt
    *
    */
  CPPUNIT_TEST( testMissingAt );

  /** Tests a mail address with missing dot
    *
    * \sa testMissingDot
    *
    */
  CPPUNIT_TEST( testMissingDot );

  /** Adds an account for following tests 
    *
    * \sa testAddAccount
    *
    */
  CPPUNIT_TEST( testAddAccount );

  /** Tests with an existing account 
    *
    * \sa testExists
    *
    */
  CPPUNIT_TEST( testExists );

  /** Tests with an existing mail
    *
    * \sa testMailExists
    *
    */
  CPPUNIT_TEST( testMailExists );

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

  /** Test the initial value of the response
    *
    * Before calling CurlAccountAdd::perform(), the returned value 
    * should be CAA_UNDEFINED.
    *
    */
  void testInitialResponse(){
    tCurlAccountAddReturn ret=this->m_instance->getResponse();
    CPPUNIT_ASSERT( ret== CAA_UNDEFINED);

  }

  /** Tries to add an account with empty name
    *
    * The CurlAccountAdd::perform() function should fail and the 
    * response should be CAA_EMPTY_NAME.
    *
    */
  void testEmptyName(){
    this->m_instance->setName("");
    bool bret=this->m_instance->perform();
    CPPUNIT_ASSERT( !bret);

    tCurlAccountAddReturn ret=this->m_instance->getResponse();
    CPPUNIT_ASSERT( ret==CAA_EMPTY_NAME);

  }

  /** Tries to add an account with empty password
    *
    * The perform() function should fail and the response should be
    * CAA_EMPTY_PWD
    *
    */
  void testEmptyPassword(){
   this->m_instance->setName(CLIENT_NAME);
    bool bret=this->m_instance->perform();
    CPPUNIT_ASSERT( !bret);

    tCurlAccountAddReturn ret=this->m_instance->getResponse();
    CPPUNIT_ASSERT( ret==CAA_EMPTY_PWD);

  }

  /** Tries to add an account with empty mail
    *
    * The perform() function should fail and the response should be
    * CAA_EMPTY_MAIL
    *
    */
  void testEmptyMail(){
    this->m_instance->setName(CLIENT_NAME);
    this->m_instance->setPassword(CLIENT_PWD);
    bool bret=this->m_instance->perform();
    CPPUNIT_ASSERT( !bret);

    tCurlAccountAddReturn ret=this->m_instance->getResponse();
    CPPUNIT_ASSERT( ret==CAA_EMPTY_MAIL);

  }

  /** Try to add an account with an invalid mail adress
    *
    * The at (@) sign of the mail adress is missing.
    * The perform() function should fail and the response should be
    * CAA_MAIL_SIGN_AT
    *
    */
  void testMissingAt(){
    this->m_instance->setName(CLIENT_NAME);
    this->m_instance->setPassword(CLIENT_PWD);
    this->m_instance->setMail(CLIENT_MAIL_EAT);
    bool bret=this->m_instance->perform();
    CPPUNIT_ASSERT( !bret);

    tCurlAccountAddReturn ret=this->m_instance->getResponse();
    CPPUNIT_ASSERT( ret==CAA_MAIL_SIGN_AT);
  }

  /** Try to add an account with an invalid mail adress
    *
    * The dot (.) sign of the mail adress is missing.
    * The perform() function should fail and the response should be
    * CAA_MAIL_SIGN_DOT
    *
    */
  void testMissingDot(){
    this->m_instance->setName(CLIENT_NAME);
    this->m_instance->setPassword(CLIENT_PWD);
    this->m_instance->setMail(CLIENT_MAIL_EDOT);
    bool bret=this->m_instance->perform();
    CPPUNIT_ASSERT( !bret);

    tCurlAccountAddReturn ret=this->m_instance->getResponse();
    CPPUNIT_ASSERT( ret==CAA_MAIL_SIGN_DOT);
  }

  /** Add a valid account
    *
    * This test may add a valid account for next steps.
    * The perform() function should return \c true and the response 
    * should be CAA_SUCCESS
    *
    */
  void testAddAccount(){
    this->m_instance->setName(CLIENT_NAME);
    this->m_instance->setPassword(CLIENT_PWD);
    this->m_instance->setMail(CLIENT_MAIL);
    bool bret=this->m_instance->perform();
    CPPUNIT_ASSERT( bret==true);

    tCurlAccountAddReturn ret=this->m_instance->getResponse();
    CPPUNIT_ASSERT( ret==CAA_SUCCESS);
  }

  /** Remove the previously added account
    *
    * The account added by the testAddAccount() function is removed here.
    *
    */
  void testDeleteAccount(){
    CurlAccountDelete cad;
    cad.setName(CLIENT_NAME);
    bool bret=cad.perform();
    CPPUNIT_ASSERT( bret==true);
  }

  /** Tests if an account exists
    *
    * Try to add an account with an already in use name. The
    * returned value should be CAA_EXISTS.
    *
    */
  void testExists(){
    this->m_instance->setName(CLIENT_NAME);
    this->m_instance->setPassword(CLIENT_PWD);
    this->m_instance->setMail(CLIENT_MAIL_EDOT);
    bool bret=this->m_instance->perform();
    CPPUNIT_ASSERT( !bret);

    tCurlAccountAddReturn ret=this->m_instance->getResponse();
    CPPUNIT_ASSERT( ret==CAA_EXISTS);

  }

  /** Tests if the submitted mail exists
    *
    * Try to add an account with new name but existing mail adress. The
    * returned value should be CAA_MAIL_INUSE.
    *
    */
  void testMailExists(){
    this->m_instance->setName(CLIENT_NAME2);
    this->m_instance->setPassword(CLIENT_PWD);
    this->m_instance->setMail(CLIENT_MAIL);
    bool bret=this->m_instance->perform();
    CPPUNIT_ASSERT( !bret);

    tCurlAccountAddReturn ret=this->m_instance->getResponse();
    CPPUNIT_ASSERT( ret==CAA_MAIL_INUSE);
  }
};

#endif // CURL_ACCOUNT_ADD_TEST_H

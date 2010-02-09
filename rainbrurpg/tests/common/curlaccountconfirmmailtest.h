/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file curlaccountconfirmmailtest.h
  * Implements the unit test for the CurlAccountConfirmMail class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  * - 06 aug 2007 : Fix a bug
  * - 15 mar 2007 : Implementation
  *
  */
#ifndef CURL_ACCOUNT_CONFIRM_MAIL_TEST_H
#define CURL_ACCOUNT_CONFIRM_MAIL_TEST_H

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

/** A test class for CurlAccountConfirmMail
  *
  * We test the setName and getName functions with a default value
  * and a setted name.
  *
  * We must use a virtual account to test this curl-based class.
  * We first use the virtual account. Its mail shouldn't confirmed and
  * we test it.
  *
  * We then confirm the mail address and test the connection if the
  * error changed.
  *
  */
template<class TESTEDCLASS> 
class CurlAccountConfirmMailTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( CurlAccountConfirmMailTest );

  /// Register the testDefaultName function
  CPPUNIT_TEST( testDefaultName );

  /// Register the testAddAccount function
  CPPUNIT_TEST( testAddAccount );
  /// Register the testMailNotConfirmed function
  CPPUNIT_TEST( testMailNotConfirmed );
  /// Register the testMailIsConfirmed function
  CPPUNIT_TEST( testMailIsConfirmed );
  /// Register the testDeleteAccount function
  CPPUNIT_TEST( testDeleteAccount );


  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the caption widget
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

  /** Add a valid account
    *
    * This test may add a valid account for next steps.
    * The perform() function should return \c true and the response 
    * should be CAA_SUCCESS
    *
    */
  void testAddAccount(){
    CurlAccountAdd caa;

    caa.setName(CLIENT_NAME);
    caa.setPassword(CLIENT_PWD);
    caa.setMail(CLIENT_MAIL);
    bool bret=caa.perform();
    CPPUNIT_ASSERT( bret==true);

    tCurlAccountAddReturn ret=caa.getResponse();
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

  /** Tests if the submitted mail exists
    *
    */
  void testMailNotConfirmed(){
    ClientConnect cc(CLIENT_NAME, CLIENT_PWD);
    tClientConnectReturn ret=cc.getResponse();

    CPPUNIT_ASSERT( ret==CCR_EMAIL_NOT_VALIDATED);
  }

  /** Cout a tClientConnectReturn value
    *
    * \param ccr The item to cout
    *
    */
  void coutClientConnectReturn(tClientConnectReturn ccr){
    const char* ret;

    switch(ccr){
    case CCR_SUCCESS:
      ret="CCR_SUCCESS";
      break;
    case CCR_INEXISTANT_USER:
      ret="CCR_INEXISTANT_USER";
      break;
    case CCR_WRONG_PWD:
      ret="CCR_WRONG_PWD";
      break;
    case CCR_EMAIL_NOT_VALIDATED:
      ret="CCR_EMAIL_NOT_VALIDATED";
      break;
    case CCR_BLACKLIST:
      ret="CCR_BLACKLIST";
      break;
    case CCR_UNKNOWN_ERROR:
      ret="CCR_UNKNOWN_ERROR";
      break;

    }

    cout << ret;

  }

  /** Test the default value of the name key
    *
    */
  void testDefaultName(){
    const char* name=this->m_instance->getName();
    CPPUNIT_ASSERT( strcmp(name, "")==0);

  }

  /** Confirm the mail adress and test it
    *
    */
  void testMailIsConfirmed(){
    this->m_instance->setName(CLIENT_NAME);
    bool bret=this->m_instance->perform();
    CPPUNIT_ASSERT( bret==true);


    ClientConnect cc(CLIENT_NAME, CLIENT_PWD);
    tClientConnectReturn ret=cc.getResponse();
    CPPUNIT_ASSERT( ret==CCR_SUCCESS);
  }

};

#endif // CURL_ACCOUNT_CONFIRM_MAIL_TEST_H

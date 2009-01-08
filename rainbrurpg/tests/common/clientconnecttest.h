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

/** \file clientconnecttest.h
  * Implements the unit test for the ClientConnect class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  * - 07 mar 2007 : Creates virtualaccount.h
  * - 02 mar 2007 : Implementation
  *
  */
#ifndef CLIENT_CONNECT_TEST_H
#define CLIENT_CONNECT_TEST_H

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

/** A test class for ClientConnect
  *
  * The tests are oriented through tClientConnectReturn.
  *
  */
template<class TESTEDCLASS> 
class ClientConnectTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( ClientConnectTest );

  /** Tests the ClientConnect's constructor default values
    *
    * \sa testStartup
    *
    */
  CPPUNIT_TEST( testStartup );

  /** Tests the returned value if the client is inexistant
    *
    * \sa testInexistant
    *
    */
  CPPUNIT_TEST( testInexistant );

  /** Add the account needed for the following tests
    *
    * \sa addAccount
    *
    */
  CPPUNIT_TEST( addAccount );

  /** Try to connect a client if its email address is not validated
    *
    * \sa testEmail
    *
    */
  CPPUNIT_TEST( testEmail );

  /** Try to connect a client with a wrong password
    *
    * \sa testWrongPassword
    *
    */
  CPPUNIT_TEST( testWrongPassword );

  /** Try to connect a blacklisted client
    *
    * \sa testBlacklist
    *
    */
  CPPUNIT_TEST( testBlacklist );

  /** Connect a correct client
    *
    * \sa testSuccess
    *
    */
  CPPUNIT_TEST( testSuccess );

  /** Delete the account previously created for test purpose
    *
    * \sa delAccount
    *
    */
  CPPUNIT_TEST( delAccount );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the tested class
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

  /** Creates a new instance for test purpose
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

  /** Test an inexistant client connection
    *
    * The client's name is defined by the CLIENT_NAME preprocessor macro.
    * The response of ClientConnect may be CCR_INEXISTANT_USER.
    *
    */
  void testInexistant(){
    tClientConnectReturn ret=this->m_instance->connect(CLIENT_NAME, "");
    CPPUNIT_ASSERT( ret==CCR_INEXISTANT_USER );

    if (ret!=CCR_INEXISTANT_USER){
      cout << "return is :"<< returnToString(ret) << endl;
    }
  }

  /** Test the startup tClientConnectReturn status
    *
    * The startup status may be CCR_UNKNOWN_ERROR.
    *
    */
  void testStartup(){
    tClientConnectReturn ret=this->m_instance->getResponse();
    CPPUNIT_ASSERT( ret==CCR_UNKNOWN_ERROR );
  }

  /** Add a virtual account to be sure it exists
    * 
    * This account is cerated cause it is needed for following tests.
    *
    */
  void addAccount(){
    CurlAccountAdd cpa;
    cpa.setName( CLIENT_NAME );
    cpa.setPassword( CLIENT_PWD );
    cpa.setMail( CLIENT_MAIL );
    CPPUNIT_ASSERT( cpa.perform() );

  }

  /** Delete the virtual account created for test purpose
    * 
    */
  void delAccount(){
    CurlAccountDelete cpd;
    cpd.setName( CLIENT_NAME );
    CPPUNIT_ASSERT( cpd.perform() );

  }

  /** Tests the CCR_EMAIL_NOT_VALIDATED response
    *
    * Before testing the CCR_EMAIL_NOT_VALIDATED response, we must create 
    * an account
    * with curlPlayerAdd with a known password. It is done 
    * by the addAccount() method. We can then test the 
    * connection to this account with an incorrect password.
    *
    * After testing the mail confirmation lack, we can confirm the 
    * mail with the CurlAccountConfirmMail class.
    * 
    */
  void testEmail(){

    tClientConnectReturn ret=this->m_instance
      ->connect(CLIENT_NAME, CLIENT_WRONG_PWD);
    CPPUNIT_ASSERT( ret==CCR_EMAIL_NOT_VALIDATED );

    CurlAccountConfirmMail cacm;
    cacm.setName(CLIENT_NAME);
    bool performConfirmMail=cacm.perform();
    CPPUNIT_ASSERT( performConfirmMail );
  }

  /** Tests the CCR_WRONG_PWD response
    *
    * Before testing the CCR_WRONG_PWD response, we must create an account
    * with curlPlayerAdd with a known password. We can then test the 
    * connection to this account with an incorrect password.
    *
    */
  void testWrongPassword(){

    tClientConnectReturn ret=this->m_instance
      ->connect(CLIENT_NAME, CLIENT_WRONG_PWD);

    if (ret!=CCR_WRONG_PWD){
      std::string msg= "return is :";
      msg+= returnToString(ret);
      msg+=", should be CCR_WRONG_PWD";
      LOGE(msg.c_str());

    }

    CPPUNIT_ASSERT( ret==CCR_WRONG_PWD );

    // We set this account on blacklist
    CurlAccountToggleBlacklist catb;
    catb.setName(CLIENT_NAME);
    bool performToggleBlacklist=catb.perform();
    CPPUNIT_ASSERT( performToggleBlacklist );

  }

  /** Tests if the player is in blacklist
    *
    * The account should be in blacklist since the testWrongPassword
    * method.
    *
    */
  void testBlacklist(){
    tClientConnectReturn ret=this->m_instance
      ->connect(CLIENT_NAME, CLIENT_PWD);
    CPPUNIT_ASSERT( ret==CCR_BLACKLIST );

    if (ret!=CCR_BLACKLIST){
      cout << "return is :"<< returnToString(ret) << endl;
    }

    // We set this account off blacklist
    CurlAccountToggleBlacklist catb;
    catb.setName(CLIENT_NAME);
    bool performToggleBlacklist=catb.perform();
    CPPUNIT_ASSERT( performToggleBlacklist );

  }

  /** At this point, the client connection must succeed
    *
    */
  void testSuccess(){
    tClientConnectReturn ret=this->m_instance
      ->connect(CLIENT_NAME, CLIENT_PWD);
    CPPUNIT_ASSERT( ret==CCR_SUCCESS );

  }
  /** Get a string from a tClientConnectReturn strucure
    *
    * \param ret The structure to get a string from
    *
    * \return A string literal from the given tClientConnectReturn
    *
    */
  std::string returnToString(tClientConnectReturn ret){
    std::string s;
    switch(ret){
    case CCR_INEXISTANT_USER:
      s="CCR_INEXISTANT_USER";
      break;

    case CCR_UNKNOWN_ERROR :
      s="CCR_UNKNOWN_ERROR";
      break;

    case CCR_WRONG_PWD:
      s="CCR_WRONG_PWD";
      break;

    case CCR_EMAIL_NOT_VALIDATED:
      s="CCR_EMAIL_NOT_VALIDATED";
      break;

    case CCR_BLACKLIST:
      s="CCR_BLACKLIST";
      break;

    case CCR_SUCCESS:
      s="CCR_SUCCESS";
      break;

    }
    return s;
  }

};


#endif // CLIENT_CONNECT_TEST_H

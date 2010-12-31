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

/** \file curlaccounttoggleblacklisttest.h
  * Implements the unit test for the CurlAccountTogleBlackList class
  *
  * Modifications :
  * - 12 jan 2009 : testInitialValue and testFinalValue now tests for a 
  *          non NULL account.
  * - 27 aug 2008 : Single file documentation.
  *
  */

#ifndef CURL_ACCOUNT_TOGGLE_BLACKLIST_TEST_H
#define CURL_ACCOUNT_TOGGLE_BLACKLIST_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <curlaccounttoggleblacklist.h>
#include <curlaccountadd.h>
#include <curlaccountdelete.h>
#include <xmlaccountlist.h>
#include <string>
#include <taccountlist.h>

#include "virtualaccount.h"

using namespace std;
using namespace RainbruRPG::Gui;
using namespace RainbruRPG::Network::Ident;

/** A test class for CurlAccountToggleBlacklist
  *
  */
template<class TESTEDCLASS> 
class CurlAccountToggleBlacklistTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( CurlAccountToggleBlacklistTest );

  /** Creates a test account
    *
    * \sa testCreateAccount
    *
    */
  CPPUNIT_TEST( testCreateAccount );

  /** Test the initial blacklist value
    *
    * \sa testInitialValue
    *
    */
  CPPUNIT_TEST( testInitialValue );

  /** Toggle the blacklist status of the virtual account
    *
    * \sa testToggle
    *
    */
  CPPUNIT_TEST( testToggle );

  /** Test the new value
    *
    * \sa testFinalValue
    *
    */
  CPPUNIT_TEST( testFinalValue );

  /** Delete the virtual account
    *
    * \sa testDeleteAccount
    *
    */
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
  
  /** Create a virtual account used for tests purpose
    *
    */
  void testCreateAccount(){ 
    CurlAccountAdd caa;

    caa.setName(CLIENT_NAME);
    caa.setPassword(CLIENT_PWD);
    caa.setMail(CLIENT_MAIL);
    bool bret=caa.perform();
    CPPUNIT_ASSERT( bret==true);

    tCurlAccountAddReturn ret=caa.getResponse();
    CPPUNIT_ASSERT( ret==CAA_SUCCESS);
  }

  /** Test the initial blacklist value of the newly created account
    *
    */
  void testInitialValue(){
    xmlAccountList xal;
    tAccountListItem *it=xal.getAccount(CLIENT_NAME);
    if (it != NULL){
      CPPUNIT_ASSERT( it->blacklist==false);
    }
    else{
      // We add a unit test we know it will failed to tell
      // an error occured
      CPPUNIT_ASSERT( false);
    }
  }

  /** Try to toggle the blacklist status of an account
    *
    */
  void testToggle(){
    CurlAccountToggleBlacklist catb;
    catb.setName(CLIENT_NAME);
    bool bret=catb.perform();
    CPPUNIT_ASSERT( bret==true);

  }

  /** Tests the blacklist status of the added client 
    *
    * Uses xmlAccountList to retrieve the blacklist status of the client
    *
    */
  void testFinalValue(){
    xmlAccountList xal;
    tAccountListItem *it=xal.getAccount(CLIENT_NAME);
    if (it != NULL){
      CPPUNIT_ASSERT( it->blacklist==true);
    }
    else{
      // We add a unit test we know it will failed to tell
      // an error occured
      CPPUNIT_ASSERT( false);
    }
  }

  /** Delete the added account
    *
    */
  void testDeleteAccount(){
    CurlAccountDelete cad;
    cad.setName(CLIENT_NAME);
    bool bret=cad.perform();
    CPPUNIT_ASSERT( bret==true);
  }


};


#endif // CURL_ACCOUNT_TOGGLE_BLACKLIST_TEST_H

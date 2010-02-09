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

/** \file ftpclienttest.h
  * Implements the unit test for the FtpClient class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  * - 10 mar 2008 : Starting implementation
  *
  */

#ifndef FTP_CLIENT_TEST_H
#define FTP_CLIENT_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <ftpclient.h>
#include <string>

using namespace std;

/** A test class for the FTP client
  *
  * \todo Waiting for FTP server to be console-based to test
  *       file transfer related functions
  *
  */
template<class TESTEDCLASS> 
class FtpClientTest : public CPPUNIT_NS::TestFixture{

  /// Start the test 
  CPPUNIT_TEST_SUITE( FtpClientTest );

  /** Tests the default values
    *
    * \sa testDefaultValues
    *
    */
  CPPUNIT_TEST( testDefaultValues );

  /** Tests a connection failure
    *
    * \sa testConnectFailed
    *
    */
  CPPUNIT_TEST( testConnectFailed );

  /** Tests that the data channel cannot be opened
    *
    * \sa testOpenDataChannelFailed
    *
    */
  CPPUNIT_TEST( testOpenDataChannelFailed );

  /** Tests values after a call to connectToHost()
    *
    * \sa testConnectValues
    *
    */
  CPPUNIT_TEST( testConnectValues );


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
  int countTestCases(){
    return 1;
  }

  /** Creates a new instance to test
    *
    */
  void setUp(){ 
    this-> m_instance= new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_instance; 
  }

  /** Tests the default values
    *
    */
  void testDefaultValues(){

    CPPUNIT_ASSERT( m_instance->isControlChannelConnected()==false );
    CPPUNIT_ASSERT( m_instance->isDataChannelConnected()==false );
    CPPUNIT_ASSERT( m_instance->getHostIp()=="");
    CPPUNIT_ASSERT( m_instance->getHostUniqueName()=="");
    CPPUNIT_ASSERT( m_instance->getHostPort()==0);

    RainbruRPG::Network::tTransferType tt;
    tt=m_instance->getTransferType();
    CPPUNIT_ASSERT( tt==FTT_ASCII );
  }

  /** Tests a connection that should fail
    *
    * No servers should exist to this adress : 127.0.0.1:0.
    *
    */
  void testConnectFailed(){
    bool success=m_instance->connectToHost("127.0.0.1", 0, "AAA");
    CPPUNIT_ASSERT( success==false  );
  }

  /** The connection should failed
    *
    */
  void testOpenDataChannelFailed(){
    bool success=m_instance->openDataChannel();
    CPPUNIT_ASSERT( success==false );
  }

  /** Test the values change
    *
    * First, we call FtpClient::ConnectToHost() with arbitrary values and
    * test with accessor if these are change.
    *
    */
  void testConnectValues(){
    m_instance->connectToHost("127.0.0.2", 1122, "BBB");

    CPPUNIT_ASSERT( m_instance->getHostIp()=="127.0.0.2");
    CPPUNIT_ASSERT( m_instance->getHostUniqueName()=="BBB");
    CPPUNIT_ASSERT( m_instance->getHostPort()==1122);

  }

};

#endif // FTP_CLIENT_TEST_H

/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

/* Modifications :
 * - 12 may 2007 : Starting implementation
 *
 */

#ifndef CURL_SERVER_ADD_TEST_H
#define CURL_SERVER_ADD_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <caption.h>

#include <string>

using namespace std;

/** A test class for CurlServerAdd
  *
  */
template<class TESTEDCLASS> 
class CurlServerAddTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( CurlServerAddTest );

  /** Tests the setName function
    *
    * \sa testNameChar
    *
    */
  CPPUNIT_TEST( testNameChar );

  /** Tests the setName function
    *
    * \sa testNameString
    *
    */
  CPPUNIT_TEST( testNameString );

  /** Tests the IP adress
    *
    * \sa testIPChar
    *
    */
  CPPUNIT_TEST( testIPChar );

  /** Tests the IP adress
    *
    * \sa testIPString
    *
    */
  CPPUNIT_TEST( testIPString );

  /** Tests the Port adress
    *
    * \sa testPortChar
    *
    */
  CPPUNIT_TEST( testPortChar );

  /** Tests the Port adress
    *
    * \sa testPortString
    *
    */
  CPPUNIT_TEST( testPortString );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the tested class
    *
    */
  TESTEDCLASS	*m_csa;
  
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
    this->m_csa = new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_csa; 
  }
  
  /** Tests the name (const char* version)
    *
    * Set a new name and test if getName() return the same
    * text.
    *
    */
  void testNameChar(){ 
    const char* serverName="ServerName";
    this->m_csa->setName(serverName);
    const char* name=this->m_csa->getName();
    CPPUNIT_ASSERT( strcmp( serverName,name)==0  );
  }


  /** Tests the name (std::string version)
    *
    * Set a new name and test if getName() return the same
    * text.
    *
    */
  void testNameString(){
    std::string serverName="ServerName";
    this->m_csa->setName(serverName);
    const char* name=this->m_csa->getName();
    CPPUNIT_ASSERT( serverName==name );

  }

  /** Tests the IP adress (const char* version)
    *
    * Set a new IP address and test if getIpAdress() return the same
    * text.
    *
    */
  void testIPChar(){
    const char* serverIp="ServerName";
    this->m_csa->setIpAddress(serverIp);
    const char* ip=this->m_csa->getIpAddress();
    CPPUNIT_ASSERT( strcmp( serverIp, ip )==0  );
  }

  /** Tests the IP adress (std::string version)
    *
    * Set a new IP address and test if getIpAdress() return the same
    * text.
    *
    */
  void testIPString(){
    std::string serverIp="ServerName";
    this->m_csa->setIpAddress(serverIp);
    const char* ip=this->m_csa->getIpAddress();
    CPPUNIT_ASSERT( serverIp == ip  );
  }

  /** Tests the port (const char* version)
    *
    * Set a new port and test if getPortAdress() return the same
    * text.
    *
    */
  void testPortChar(){
    const char* serverPort="ServerName";
    this->m_csa->setPort(serverPort);
    const char* port=this->m_csa->getPort();
    CPPUNIT_ASSERT( strcmp( serverPort, port )==0  );
  }

  /** Tests the port (std::string version)
    *
    * Set a new port and test if getPortAdress() return the same
    * text.
    *
    */
  void testPortString(){
    std::string serverPort="ServerName";
    this->m_csa->setPort(serverPort);
    const char* port=this->m_csa->getPort();
    CPPUNIT_ASSERT( serverPort == port );
  }


};


#endif // CURL_SERVER_ADD_TEST_H

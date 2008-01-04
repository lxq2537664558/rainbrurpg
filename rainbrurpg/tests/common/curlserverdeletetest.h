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

/* Modifications :
 * - 22 may 2007 : Starting implementation
 *
 */

#ifndef CURL_SERVER_DELETE_TEST_H
#define CURL_SERVER_DELETE_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <curlserveradd.h>
#include <string>

#include "virtualserver.h"

using namespace std;

/** A test class for CurlServerDelete
  *
  */
template<class TESTEDCLASS> 
class CurlServerDeleteTest : public CPPUNIT_NS::TestFixture 
{

  /// Start the test 
  CPPUNIT_TEST_SUITE( CurlServerDeleteTest );

  /** Tests the initial values
    *
    * \sa testDefaultValue
    *
    */
  CPPUNIT_TEST(testDefaultValue);

  /** Tests the setName, const char* version 
    *
    * \sa testNameChar
    *
    */
  CPPUNIT_TEST(testNameChar);

  /** Tests the setName, std::string version 
    *
    * \sa testNameString
    *
    */
  CPPUNIT_TEST(testNameString);

  /** Adds a virtual server
    *
    * \sa testAddVirtual
    *
    */
  CPPUNIT_TEST(testAddVirtual);

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** An instance of the tested class
    *
    */
  TESTEDCLASS	*m_csd;
  
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
    this->m_csd = new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(){ 
    delete this->m_csd; 
  }
  
  /** Tests the initial values
    *
    * The server name should be "".
    *
    */
  void testDefaultValue(){
    const char* serverName=this->m_csd->getName(); 
    CPPUNIT_ASSERT( strcmp( serverName,"")==0  );
  }

  /** Tests the name (const char* version)
    *
    * Set a new name and test if getName() return the same
    * text.
    *
    */
  void testNameChar(){ 
    const char* serverName="ServerName";
    this->m_csd->setName(serverName);
    const char* name=this->m_csd->getName();
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
    this->m_csd->setName(serverName);
    const char* name=this->m_csd->getName();
    CPPUNIT_ASSERT( serverName==name );
  }

  /** Adds a virtual server 
    *
    * Use the local instance of CurlServerAdd to add the server defined
    * in virtualserver.h then remove it with CurlServerDelete.
    *
    */
  void testAddVirtual(){
    CurlServerAdd csa;
    csa.setName(SERVER_NAME);
    csa.setIpAddress(SERVER_IP);
    csa.setPort(SERVER_PORT);
    csa.setMaxClients(SERVER_MAX_CLIENTS);
    csa.setDescription(SERVER_DESC);
    csa.setTechNote(SERVER_TECH_NOTE);

    bool addServerSuccess=csa.perform();
    CPPUNIT_ASSERT( addServerSuccess );

    this->m_csd->setName(SERVER_NAME);
    bool deleteServerSuccess=this->m_csd->perform();
    CPPUNIT_ASSERT( deleteServerSuccess );
  }
};


#endif // CURL_SERVER_DELETE_TEST_H

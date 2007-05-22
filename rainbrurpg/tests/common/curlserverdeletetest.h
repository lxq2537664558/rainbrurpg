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

  /** Adds a virtual server 
    *
    * Use the local instance of CurlServerAdd to add the server defined
    * in virtualserver.h then remove it with CurlServerDelete.
    *
    */
  void testAddVirtual(){
    this->m_csa->setName(SERVER_NAME);
    this->m_csa->setIpAddress(SERVER_IP);
    this->m_csa->setPort(SERVER_PORT);
    this->m_csa->setMaxClients(SERVER_MAX_CLIENTS);
    this->m_csa->setDescription(SERVER_DESC);
    this->m_csa->setTechNote(SERVER_TECH_NOTE);

    bool addServerSuccess=this->m_csa->perform();
    CPPUNIT_ASSERT( addServerSuccess );

    CurlServerDelete csd;
    csd.setName(SERVER_NAME);
    bool deleteServerSuccess=csd.perform();
    CPPUNIT_ASSERT( deleteServerSuccess );


  }
};


#endif // CURL_SERVER_DELETE_TEST_H

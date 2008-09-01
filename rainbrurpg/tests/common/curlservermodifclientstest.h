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

/** \file curlservermodifclientstest.h
  * Implements the unit test for the CurlServerModifClients class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  * - 14 feb 2008 : Starting implementation
  *
  */

#ifndef CURL_SERVER_MODIF_CLIENT_H
#define CURL_SERVER_MODIF_CLIENT_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <curlserverdelete.h>
#include <xmlserverlist.h>
#include <string>

#include "virtualserver.h"

using namespace std;
using namespace RainbruRPG::Network::Ident;

/** A test class for CurlServerAdd
  *
  */
template<class TESTEDCLASS> 
class CurlServerModifClientsTest : public CPPUNIT_NS::TestFixture{

  /// Start the test 
  CPPUNIT_TEST_SUITE( CurlServerModifClientsTest );

  /** Tests creation of a virtual server
    *
    * \sa createVirtualServer
    *
    */
  CPPUNIT_TEST( createVirtualServer );

  /** Tests the initial client number
    *
    * \sa testInitialClientCount
    *
    */
  CPPUNIT_TEST( testInitialClientCount );

  /** Tests the client number after adding a client
    *
    * \sa testNewClientCount
    *
    */
  CPPUNIT_TEST( testNewClientCount );

  /** Tests a negative client number
    *
    * \sa testNegativeClientCount
    *
    */
  CPPUNIT_TEST( testNegativeClientCount );

  /** Deletes the virtual server
    *
    * \sa deleteVirtualServer
    *
    */
  CPPUNIT_TEST( deleteVirtualServer );

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
  
  /** Create a virtual server to be tested
    *
    */
  void createVirtualServer(){
    CurlServerAdd csa;
    csa.setName(SERVER_NAME);
    csa.setIpAddress(SERVER_IP);
    csa.setPort(SERVER_PORT);
    csa.setMaxClients(SERVER_MAX_CLIENTS);
    csa.setDescription(SERVER_DESC);
    csa.setTechNote(SERVER_TECH_NOTE);

    bool addServerSuccess=csa.perform();
    CPPUNIT_ASSERT( addServerSuccess );

  }

  /** Delete the virtual server added to be tested
    *
    */
  void deleteVirtualServer(){
    CurlServerDelete csd;
    csd.setName(SERVER_NAME);
    bool deleteServerSuccess=csd.perform();
    CPPUNIT_ASSERT( deleteServerSuccess );
  }

  /** Get the actual client number of the virtual server and test if it is 0
    *
    */
  void testInitialClientCount(){
    xmlServerList xsl;
    ServerListItem* sli=xsl.getServerByName(SERVER_NAME);
    CPPUNIT_ASSERT( sli!=NULL );

    unsigned int actClient=sli->getActClients();
    CPPUNIT_ASSERT( actClient==0 );

  }

  /** Modif the actVlient number and test it
    *
    */
  void testNewClientCount(){
    // Modify actClient for the virtual server
    m_instance->setName(SERVER_NAME);
    m_instance->setActClients(5);
    bool modifSuccess=m_instance->perform();
    CPPUNIT_ASSERT( modifSuccess );
    
    xmlServerList xsl;
    ServerListItem* sli=xsl.getServerByName(SERVER_NAME);
    CPPUNIT_ASSERT( sli!=NULL );

    unsigned int actClient=sli->getActClients();
    CPPUNIT_ASSERT( actClient==5 );


  }

  /** Set a negative client number and test if it is 0
    *
    * \sa CurlServerModifClients::setActClients
    *
    */
  void testNegativeClientCount(){
    // Modify actClient for the virtual server
    m_instance->setName(SERVER_NAME);
    m_instance->setActClients(-20);
    bool modifSuccess=m_instance->perform();
    CPPUNIT_ASSERT( modifSuccess );
    
    xmlServerList xsl;
    ServerListItem* sli=xsl.getServerByName(SERVER_NAME);
    CPPUNIT_ASSERT( sli!=NULL );

    unsigned int actClient=sli->getActClients();
    CPPUNIT_ASSERT( actClient==0 );

  }

};

#endif // CURL_SERVER_MODIF_CLIENT_H

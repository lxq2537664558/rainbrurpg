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
 * - 19 jul 2007 : uniqueName and type added
 * - 12 may 2007 : Starting implementation
 *
 */

#ifndef CURL_SERVER_ADD_TEST_H
#define CURL_SERVER_ADD_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <curlserverdelete.h>
#include <string>

#include "virtualserver.h"

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

  /** Tests the Port address
    *
    * \sa testPortChar
    *
    */
  CPPUNIT_TEST( testPortChar );

  /** Tests the Port address
    *
    * \sa testPortString
    *
    */
  CPPUNIT_TEST( testPortString );

  /** Tests the FTP control channel
    *
    * \sa testFtpChar
    *
    */
  CPPUNIT_TEST( testFtpChar );

  /** Tests the FTP control channel
    *
    * \sa testFtpString
    *
    */
  CPPUNIT_TEST( testFtpString );

  /** Tests the maxClients value
    *
    * \sa testMaxClientsChar
    *
    */
  CPPUNIT_TEST( testMaxClientsChar );

  /** Tests the maxClients value
    *
    * \sa testMaxClientsString
    *
    */
  CPPUNIT_TEST(testMaxClientsString  );

  /** Tests the description value
    *
    * \sa testDescriptionChar
    *
    */
  CPPUNIT_TEST( testDescriptionChar );

  /** Tests the description value
    *
    * \sa testDescriptionString
    *
    */
  CPPUNIT_TEST(testDescriptionString  );

  /** Tests the technical note value
    *
    * \sa testTechNoteChar
    *
    */
  CPPUNIT_TEST( testTechNoteChar );

  /** Tests the technical note value
    *
    * \sa testTechNoteString
    *
    */
  CPPUNIT_TEST(testTechNoteString  );

  /** Tests the initial values
    *
    * \sa testInitialValues
    *
    */
  CPPUNIT_TEST(testInitialValues  );

  /** Adds a virtual server
    *
    * \sa testAddVirtual
    *
    */
  CPPUNIT_TEST(testAddVirtual);

  /** Tests the server's UniqueName
    *
    * \sa testUniqueName
    *
    */
  CPPUNIT_TEST(testUniqueName);

  /** Tests the server's type
    *
    * \sa testType
    *
    */
  CPPUNIT_TEST(testType);


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


  /** Tests the maxClients (const char* version)
    *
    * Set a new maxClients value and test if getMaxClients() return the same
    * text.
    *
    */
  void testMaxClientsChar(){
    const char* maxClients="ServerName";
    this->m_csa->setMaxClients(maxClients);
    const char* mc=this->m_csa->getMaxClients();
    CPPUNIT_ASSERT( strcmp( maxClients, mc )==0  );
  }

  /** Tests the maxClients (std::string version)
    *
    * Set a new maxClients value and test if setMaxClients() return the same
    * text.
    *
    */
  void testMaxClientsString(){
    std::string maxClients="ServerName";
    this->m_csa->setMaxClients(maxClients);
    const char* mc=this->m_csa->getMaxClients();
    CPPUNIT_ASSERT( maxClients==mc );
  }

  /** Tests the description (const char* version)
    *
    * Set a new description and test if getDescription() return the same
    * text.
    *
    */
  void testDescriptionChar(){
    const char* description="ServerName";
    this->m_csa->setDescription(description);
    const char* desc=this->m_csa->getDescription();
    CPPUNIT_ASSERT( strcmp( description, desc )==0  );
  }

  /** Tests the description (std::string version)
    *
    * Set a new description and test if getDescription() return the same
    * text.
    *
    */
  void testDescriptionString(){
    std::string description="ServerName";
    this->m_csa->setDescription(description);
    const char* desc=this->m_csa->getDescription();
    CPPUNIT_ASSERT( description==desc );
  }

  /** Tests the technical note value (const char* version)
    *
    * Set a new technical note and test if getTechNote() return the same
    * text.
    *
    */
  void testTechNoteChar(){
    const char* tech="ServerName";
    this->m_csa->setTechNote(tech);
    const char* tn=this->m_csa->getTechNote();
    CPPUNIT_ASSERT( strcmp( tech, tn )==0  );
  }

  /** Tests the technical note value (std::string version)
    *
    * Set a new technical note and test if getTechNote() return the same
    * text.
    *
    */
  void testTechNoteString(){
    std::string tech="ServerName";
    this->m_csa->setTechNote(tech);
    const char* tn=this->m_csa->getTechNote();
    CPPUNIT_ASSERT( tech==tn );
  }

  /** Tests the initial values
    *
    * It should be ""
    *
    */
  void testInitialValues(){
    const char* name=this->m_csa->getName();
    const char* ip=this->m_csa->getIpAddress();
    const char* port=this->m_csa->getPort();
    const char* ftp=this->m_csa->getFtpPort();
    const char* maxClients=this->m_csa->getMaxClients();
    const char* desc=this->m_csa->getDescription();
    const char* techNote=this->m_csa->getTechNote();
    long serverLong=this->m_csa->getServerResponse();
    const char* errMsg=this->m_csa->getCustomErrorMessage();

    std::string uniqueName=this->m_csa->getUniqueName();
      std::string type=this->m_csa->getType();

    CPPUNIT_ASSERT( strcmp(name, "")==0 );
    CPPUNIT_ASSERT( strcmp(ip, "")==0 );
    CPPUNIT_ASSERT( strcmp(port, "")==0 );
    CPPUNIT_ASSERT( strcmp(ftp, "")==0 );
    CPPUNIT_ASSERT( strcmp(maxClients, "")==0 );
    CPPUNIT_ASSERT( strcmp(desc, "")==0 );
    CPPUNIT_ASSERT( strcmp(techNote, "")==0 );
    CPPUNIT_ASSERT( serverLong==-1 );
    CPPUNIT_ASSERT( strcmp(errMsg, "")==0 );

    CPPUNIT_ASSERT( uniqueName=="" );
    CPPUNIT_ASSERT( type=="" );
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

  /** Tests the Ftp control channel value (const char* version)
    *
    * Set a new Ftp control channel and test if getFtpPort() return the same
    * text.
    *
    */
  void testFtpChar(){
    const char* ftp="ServerName";
    this->m_csa->setFtpPort(ftp);
    const char* ftp2=this->m_csa->getFtpPort();
    CPPUNIT_ASSERT( strcmp( ftp, ftp2 )==0  );

  }

  /** Tests the Ftp control channel value (std::string version)
    *
    * Set a new Ftp control channel and test if getFtpPort() return the same
    * text.
    *
    */
  void testFtpString(){
    std::string ftp="ServerName";
    this->m_csa->setFtpPort(ftp);
    const char* ftp2=this->m_csa->getFtpPort();
    CPPUNIT_ASSERT( ftp==ftp2 );

  }

  /** Tests the UniqueName value
    *
    * Set a new UniqueName and test if getUniqueName() return the same
    * text.
    *
    */
  void testUniqueName(){
    std::string un="ServerUniqueName";
    this->m_csa->setUniqueName(un);
    std::string un2=this->m_csa->getUniqueName();
    CPPUNIT_ASSERT( un==un2 );
  }

  /** Tests the Type value
    *
    * Set a new Type and test if getType() return the same
    * text.
    *
    */
  void testType(){
    std::string st="ServerType";
    this->m_csa->setType(st);
    std::string st2=this->m_csa->getType();
    CPPUNIT_ASSERT( st==st2 );
  }

};


#endif // CURL_SERVER_ADD_TEST_H

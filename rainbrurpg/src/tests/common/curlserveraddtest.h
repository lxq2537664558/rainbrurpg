/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file curlserveraddtest.h
  * Implements the unit test for the CurlServerAdd class
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
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
  
  /** Tests the name (const char* version)
    *
    * Set a new name and test if getName() return the same
    * text.
    *
    */
  void testNameChar(){ 
    const char* serverName="ServerName";
    this->m_instance->setName(serverName);
    const char* name=this->m_instance->getName();
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
    this->m_instance->setName(serverName);
    const char* name=this->m_instance->getName();
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
    this->m_instance->setIpAddress(serverIp);
    const char* ip=this->m_instance->getIpAddress();
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
    this->m_instance->setIpAddress(serverIp);
    const char* ip=this->m_instance->getIpAddress();
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
    this->m_instance->setPort(serverPort);
    const char* port=this->m_instance->getPort();
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
    this->m_instance->setPort(serverPort);
    const char* port=this->m_instance->getPort();
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
    this->m_instance->setMaxClients(maxClients);
    const char* mc=this->m_instance->getMaxClients();
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
    this->m_instance->setMaxClients(maxClients);
    const char* mc=this->m_instance->getMaxClients();
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
    this->m_instance->setDescription(description);
    const char* desc=this->m_instance->getDescription();
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
    this->m_instance->setDescription(description);
    const char* desc=this->m_instance->getDescription();
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
    this->m_instance->setTechNote(tech);
    const char* tn=this->m_instance->getTechNote();
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
    this->m_instance->setTechNote(tech);
    const char* tn=this->m_instance->getTechNote();
    CPPUNIT_ASSERT( tech==tn );
  }

  /** Tests the initial values
    *
    * It should be ""
    *
    */
  void testInitialValues(){
    const char* name=this->m_instance->getName();
    const char* ip=this->m_instance->getIpAddress();
    const char* port=this->m_instance->getPort();
    const char* ftp=this->m_instance->getFtpPort();
    const char* maxClients=this->m_instance->getMaxClients();
    const char* desc=this->m_instance->getDescription();
    const char* techNote=this->m_instance->getTechNote();
    long serverLong=this->m_instance->getServerResponse();
    const char* errMsg=this->m_instance->getCustomErrorMessage();

    std::string uniqueName=this->m_instance->getUniqueName();
      std::string type=this->m_instance->getType();

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

    this->m_instance->setName(SERVER_NAME);
    this->m_instance->setIpAddress(SERVER_IP);
    this->m_instance->setPort(SERVER_PORT);
    this->m_instance->setMaxClients(SERVER_MAX_CLIENTS);
    this->m_instance->setDescription(SERVER_DESC);
    this->m_instance->setTechNote(SERVER_TECH_NOTE);

    bool addServerSuccess=this->m_instance->perform();
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
    this->m_instance->setFtpPort(ftp);
    const char* ftp2=this->m_instance->getFtpPort();
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
    this->m_instance->setFtpPort(ftp);
    const char* ftp2=this->m_instance->getFtpPort();
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
    this->m_instance->setUniqueName(un);
    std::string un2=this->m_instance->getUniqueName();
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
    this->m_instance->setType(st);
    std::string st2=this->m_instance->getType();
    CPPUNIT_ASSERT( st==st2 );
  }

};


#endif // CURL_SERVER_ADD_TEST_H

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
 * - 15 mar 2008 : Starting implementation
 *
 */

#ifndef GLOBAL_URI_TEST_H
#define GLOBAL_URI_TEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/portability/Stream.h>

#include <globaluri.h>
#include <string>

using namespace std;

/** A test class for GlobalURI
  *
  */
template<class TESTEDCLASS> 
class GlobalUriTest : public CPPUNIT_NS::TestFixture{

  /// Start the test 
  CPPUNIT_TEST_SUITE( GlobalUriTest );

  /** Tests values of admin website adress
    *
    * \sa testAdminAdress
    *
    */
  CPPUNIT_TEST( testAdminAdress );

  /** Tests values of XML adress
    *
    * \sa testXmlAdress
    *
    */
  CPPUNIT_TEST( testXmlAdress );

  /** Tests the name of a user file
    *
    * \sa testUserFile
    *
    */
  CPPUNIT_TEST( testUserFile );

  /** Tests the share directory function
    *
    * \sa testShareFile
    *
    */
  CPPUNIT_TEST( testShareFile );

  /** Tests the upload directory function
    *
    * \sa testUploadFile
    *
    */
  CPPUNIT_TEST( testUploadFile );

  /** Tests the quarantine directory function
    *
    * \sa testQuarantineFile
    *
    */
  CPPUNIT_TEST( testQuarantineFile );

  /** Tests the downloaded files function
    *
    * \sa testDownloadedFile
    *
    */
  CPPUNIT_TEST( testDownloadedFile );

  /** Tests the config file list size
    *
    * \sa testConfigFileListSize
    *
    */
  CPPUNIT_TEST( testConfigFileListSize );

  /** Tests the config file list filename
    *
    * \sa testConfigFileFilename
    *
    */
  CPPUNIT_TEST( testConfigFileFilename );

  /** Tests if config file exist
    *
    * \sa testAllConfigFilesExist
    *
    */
  CPPUNIT_TEST( testAllConfigFilesExist );

  /// The CppUnit test end macro
  CPPUNIT_TEST_SUITE_END();

protected:
  /** Get inital values of directory for userDir, adminSite and xmlSite
    *
    */
  void initValues(void){
    userDir       = m_instance->getUserDir();
    adminSite     = m_instance->getAdminSite();
    xmlSite       = m_instance->getXmlSite();
    shareDir      = m_instance->getShareDir();
    uploadDir     = m_instance->getUploadDir();
    quarantineDir = m_instance->getQuarantineDir();
  }

  /** An instance of the tested class   */
  TESTEDCLASS	*m_instance;
  
  /** The user HOME directory 
    *
    * This directory is <code>$HOME/.RainbruRPG/</code>.
    *
    */
  std::string userDir;
  /** The base of a administration web site address */
  std::string adminSite;
  /** Where are the most xml files */
  std::string xmlSite;
  /** Shared files directory name */
  std::string shareDir;
  /** Uploaded files directory name */
  std::string uploadDir;
  /** Quarantine files directory name */
  std::string quarantineDir;

public:
  /** Return the number of test cases
    *
    * \return Currently always return 1
    *
    */
  int countTestCases(void){
    return 1;
  }

  /** Creates a new instance to test
    *
    */
  void setUp(void){ 
    this-> m_instance= new TESTEDCLASS; 
  }
  
  /** Delete the current tested instance
    *
    */
  void tearDown(void){ 
    delete this->m_instance; 
  }

  /** Tests the getAdminAdress() function
    *
    */
  void testAdminAdress(void){
    initValues();
    std::string filename="aaa.bbb";
    std::string result=adminSite+filename;
    std::string rep=this->m_instance->getAdminAdress(filename);
    CPPUNIT_ASSERT( rep==result);
  }

  /** Tests the getXmlAdress() function
    *
    */
  void testXmlAdress(void){
    initValues();
    std::string filename="aaa.bbb";
    std::string result=xmlSite+filename;
    std::string rep=this->m_instance->getXmlAdress(filename);
    CPPUNIT_ASSERT( rep==result);
  }

  /** Tests the getUserDirFile() function
    *
    */
  void testUserFile(void){
    initValues();
    std::string filename="aaa.bbb";
    std::string result=userDir+filename;
    std::string rep=this->m_instance->getUserDirFile(filename);
    CPPUNIT_ASSERT( rep==result);
  }

  /** Tests the getShareFile() function
    *
    */
  void testShareFile(void){
    initValues();
    std::string filename = "aaa.bbb";
    std::string result=shareDir + filename;
    std::string rep=this->m_instance->getShareFile(filename);
    CPPUNIT_ASSERT( rep==result);
  }

  /** Tests the getUploadFile() function
    *
    */
  void testUploadFile(void){
    initValues();
    std::string filename = "aaa.bbb";
    std::string result=uploadDir + filename;
    std::string rep=this->m_instance->getUploadFile(filename);
    CPPUNIT_ASSERT( rep==result);

  }

  /** Tests the getQuarantineFile() function
    *
    */
  void testQuarantineFile(void){
    initValues();
    std::string filename = "aaa.bbb";
    std::string result=quarantineDir + filename;
    std::string rep=this->m_instance->getQuarantineFile(filename);
    CPPUNIT_ASSERT( rep==result);

  }
  /** Tests the getDownloadFile() function
    *
    */
  void testDownloadedFile(void){
    std::string userDir    = this->m_instance->getUserDir();
    std::string uniqueName = "uuuuuuuuuuuu";
    std::string filename   = "aaa.bbb";

    std::string result = userDir + "downloaded/" + uniqueName + "/" + filename;

    std::string rep=this->m_instance
      ->getDownloadFile( filename, uniqueName, false );

    std::string msg="rep="+rep+"; result="+result+";";

    CPPUNIT_ASSERT( rep==result);

  }

  /** Test if the size of config file list is correct
    *
    */
  void testConfigFileListSize(void){
    unsigned int size1 = this->m_instance->getConfigFilesCount();
    tInstalledConfigFilesList lst = this->m_instance
      ->getInstallConfigFilesList();

    CPPUNIT_ASSERT( size1==lst.size());
  }

  /** Test if filename and absolute filename are correct
    *
    */
  void testConfigFileFilename(void){
    std::string fn;
    userDir = m_instance->getUserDir();
    tInstalledConfigFilesList::const_iterator iter;
    tInstalledConfigFilesList lst = this->m_instance
      ->getInstallConfigFilesList();
    
    for (iter=lst.begin(); iter!=lst.end(); iter++){
      fn = userDir + (*iter)->filename;
      CPPUNIT_ASSERT( (*iter)->absoluteFileName == fn );
    }
  }

  /** Test if all config files exist
    *
    */
  void testAllConfigFilesExist(void){
    bool allExist = true;

    tInstalledConfigFilesList::const_iterator iter;
    tInstalledConfigFilesList lst = this->m_instance
      ->getInstallConfigFilesList();

    for (iter=lst.begin(); iter!=lst.end(); iter++){
      if (!(*iter)->exists){
	allExist = false;
      }
    }

    CPPUNIT_ASSERT( allExist );

  }

};

#endif // GLOBAL_URI_TEST_H

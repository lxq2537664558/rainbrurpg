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

/** \file globaluri.cpp
  * Implements a class used to get full file names with path
  *
  */

#include "globaluri.h"
#include "include_boost.h"


#include "../config.h"

// WARNING : Uses this namespace alias to avoid compilation error
namespace fs = boost::filesystem;

/** The default constructor
  *
  * It initalize the base website according to the definition of the
  * WEBSITE_DEBUG macro.
  *
  */
RainbruRPG::Network::GlobalURI::GlobalURI():
  mConfigFilesCount(0){

#ifdef WEBSITE_DEBUG
  adminSite="http://127.0.0.1/rpg/admin/";
  xmlSite="http://127.0.0.1/rpg/metadata/";
  LOGW("Using the local website (127.0.0.1)");
#else //WEBSITE_DEBUG
  adminSite="http://rainbru.free.fr/rpg/admin/";
  xmlSite="http://rainbru.free.fr/rpg/metadata/";
  LOGI("Using the real website");
#endif //WEBSITE_DEBUG

  shareDir = USER_INSTALL_PREFIX;
  shareDir+="/share/RainbruRPG/";

  homeSetup();

  uploadDir     = userDir + "uploaded/";
  quarantineDir = userDir + "quarantine/";
}

/** The default destructor
  *
  *
  */
RainbruRPG::Network::GlobalURI::~GlobalURI(){
  mInstalledFileList.clear();
}

/** Get an adress on the administration site
  *
  * \param file The filename to get
  *
  * \return the complete URI of the given adress on the administration 
  *         website
  */
std::string RainbruRPG::Network::GlobalURI::
getAdminAdress(const std::string& file)const{


  ostringstream oss;
  oss << this->adminSite;
  oss << file;

  return oss.str();
}

/** Get an adress on the xml site
  *
  * \param file The filename to get
  *
  * \return the complete URI of the given adress on the xml 
  *         website
  */
std::string RainbruRPG::Network::GlobalURI::
getXmlAdress(const std::string& file)const{

  std::string s;
  s=this->xmlSite;
  s+=file;

  return s;
}

/** Get a file in the user home/user/.RainbruRPG directory
  *
  * Calling getUserDirFile(essai.txt) gives /home/user/.RainbruRPG/essai.txt
  *
  * \param file The filename without path
  *
  */
std::string RainbruRPG::Network::GlobalURI::
getUserDirFile(const std::string& file)const{

  LOGI("GlobalURI::getUserDirFile called");
  ostringstream oss;
  oss << this->userDir;
  oss << file;

  LOGCATS("returned value is '");
  LOGCATS(oss.str().c_str());
  LOGCATS("'");
  LOGCAT();

  return oss.str();
}

/** Sets up the HOME/.RainbruRPG/ directory
  *
  * \todo Makes this function working on Win32
  *
  */
void RainbruRPG::Network::GlobalURI::homeSetup(){
  // Get RainbruRPG user's directory
  userDir=getenv("HOME");
  userDir+="/.RainbruRPG/";
  LOGCATS("Setting user's HOME directory to'");
  LOGCATS(userDir.c_str());
  LOGCATS("'");
  LOGCAT();

  // Creating directory if inexists
  fs::path homePath(userDir.c_str(), 
				   fs::native);
  LOGCATS("Boost path returns '");
  LOGCATS(homePath.string().c_str());
  LOGCATS("'");
  LOGCAT();

  bool ex=fs::exists( homePath );
  if (ex){
    LOGI("Home directory alerady exists");
  }
  else{
    LOGI("Home directory doesn't exists, creating it");
    fs::create_directory( homePath );
  }

  // Copying necessary files
  installConfigFile("options.xml");
  installConfigFile("languages.xml");
  installConfigFile("ogre.cfg");
  installConfigFile("objects.xml");
  installConfigFile("server.xml");
  installConfigFile("file_extensions.accepted");
  installConfigFile("file_extensions.refused");
}

/** Get the $PREFIX/share/RainbruRPG/??? file
  *
  * A file name with or without subdirectory name
  *
  * \return The absolute URI to the given file
  *
  */
std::string RainbruRPG::Network::GlobalURI::
getShareFile(const std::string& file)const{
  LOGI("GlobalURI::getShareFile called");
  // Copying necessary files
  std::string s=shareDir;
  s+=file;

  fs::path test( s,fs::native);
  if (!fs::exists(test)){
    LOGW("The given file doesn't exist");
  }

  return s;
}

/** Test if a file exists and install it if it doesn't
  *
  * Copy the given filename from $PREFIX/share/config to 
  * $HOME/.RainbruRPG/config
  *
  * \param filename The name of the file to install
  *
  */
void RainbruRPG::Network::GlobalURI::
installConfigFile(const std::string& filename){
  // Increment internal configuration files count
  mConfigFilesCount++;

  tInstalledConfigFilesListItem* it=new tInstalledConfigFilesListItem();
  it->filename = filename;

  // The $PREFIX/share... filename
  std::string s=USER_INSTALL_PREFIX;
  s+="/share/RainbruRPG/config/";
  s+=filename;

  // The $PREFIX/.RainbruRPG... filename
  std::string s2=userDir;
  s2+=filename;
  it->absoluteFileName = s2;

  // The boost path
  fs::path optionXmlPath( s, 
	fs::native);
  fs::path userOptionXmlPath( s2, 
	fs::native);

  // Need to be installed
  if (!fs::exists(userOptionXmlPath)){
    std::string msg=filename;
    msg+=" not found, copying it from $PREFIX/share";
    LOGW(msg.c_str());

    fs::copy_file(optionXmlPath, userOptionXmlPath);
    it->needCreation=true;
  }
  else{
    std::string msg2=filename;
    msg2+=" found in user directory";
    LOGI(msg2.c_str());
    it->needCreation=false;
  }

  // Exists ?
  if (fs::exists(userOptionXmlPath)){
    it->exists=true;
  }
  else{
    it->exists=false;
  }

  // Adding to list
  mInstalledFileList.push_back(it);

}

/** Get the absolute filename of a file upload on the server and approved
  *
  * \param s Only the file name
  *
  * \return The path and the filename
  *
  */
std::string RainbruRPG::Network::GlobalURI::
getUploadFile(const std::string& s)const{
  std::string ret=uploadDir+s;

  // Create the directory if not exist
  fs::path p(uploadDir, fs::native);
  if(!fs::exists(p)){
    LOGW("uploaded/ directory does not exist, creating it");
    // If the uploaded directory does not exist, create it
    fs::create_directory(p);
  }

  return ret;
}

/** Get the absolute filename of a file upload on the server but not yet 
  * approved
  *
  * \param s Only the file name
  *
  * \return The path and the filename
  *
  */
std::string RainbruRPG::Network::GlobalURI::
getQuarantineFile(const std::string& s)const{
  LOGI("GlobalURI::getQuarantineFile called");
  std::string ret=quarantineDir+s;

  // Create the directory if not exist
  fs::path p(quarantineDir, fs::native);
  if(!fs::exists(p)){
    LOGW("quarantine/ directory does not exist, creating it");
    // If the uploaded directory does not exist, create it
    fs::create_directory(p);
  }

  return ret;
}

/** Get the absolute filename of a file you download from a server
  *
  * In the local filesystem of the client, we can download some files
  * with the same filename from different servers. We need a unique directory
  * for each server that is 
  * <code>$HOME/.RainbruRPG/downloaded/$UNIQUE_NAME</code>. If this directory
  * does not exist, this function create it.
  *
  * \note If the directory doesn't exist, it is created only if  
  *       <var>createIfMissing</var> is \c true (it's default value). 
  *       This feature should only be used in unit tests.
  *
  * \param s               Only the file name
  * \param sun             The server unique name
  * \param createIfMissing Create the unique name directory only if \c true
  *
  * \return The path and the filename
  *
  */
std::string RainbruRPG::Network::GlobalURI::
getDownloadFile(const std::string& s, const std::string& sun, 
		bool createIfMissing)const{

  std::string dir, dirWoSun;
  std::string ret=userDir;
  ret+="downloaded/";
  dirWoSun=ret;
  ret+=sun;
  dir=ret;
  ret+="/";
  ret+=s;

  // Test if the unique directory exists
  fs::path p(dir, fs::native);
  fs::path p2(dirWoSun, fs::native);
  if(fs::exists(p)){
    if (fs::is_directory(p)){
      LOGI("Downloaded/ directory exists");

    }
  }
  else{
    // If the downloaded directory does not exist, create it
    if (!fs::exists(p2)){
	fs::create_directory(p2);
	LOGW("Downloaded/ directory does not exist, creating it");
    }
  }

  if (createIfMissing){
    // Create the unique name server directory
    fs::create_directory(p);
  }
  else{
    LOGW("Missing unique directory not created (createIfMissing=false)");
  }

  return ret;
}

/** Get the current user RainbruRPG directory
  *
  * Should be the user directory plus \c /.RainbruRPG/
  *
  */
const std::string& RainbruRPG::Network::GlobalURI::getUserDir(void)const{
  return this->userDir;
}

/** Get the Admin website URL base
  *
  * This value can change according to the WEBSITE_DEBUG macro.
  *
  */
const std::string& RainbruRPG::Network::GlobalURI::getAdminSite(void)const{
  return this->adminSite;
}

/** Get the XML files URL base
  *
  * This value can change according to the WEBSITE_DEBUG macro.
  *
  */
const std::string& RainbruRPG::Network::GlobalURI::getXmlSite(void)const{
  return this->xmlSite;
}

/** Get the shared files directory
  *
  * This is \c $USER_INSTALL_PREFIX$/share/RainbruRPG/.
  *
  */
const std::string& RainbruRPG::Network::GlobalURI::getShareDir(void)const{
  return shareDir;
}

/** Get the upload files directory
  *
  * This is \c $userDir$/uploaded/"
  *
  * \sa \ref RainbruRPG::Network::GlobalURI::userDir "userDir"
  *
  */
const std::string& RainbruRPG::Network::GlobalURI::getUploadDir(void)const{
  return uploadDir;
}

/** Get the quarantine directory 
  *
  * This is \c $userDir$/quarantine/"
  *
  * \sa \ref RainbruRPG::Network::GlobalURI::userDir "userDir"
  *
  */
const std::string& RainbruRPG::Network::GlobalURI::getQuarantineDir(void)const{
  return quarantineDir;
}

/** Get the value of the internal configuration files count
  *
  * This function is mainly used for unit test to see if the 
  * getInstallConfigFilesList() list size is correct.
  *
  * \return The number of installed config file
  *
  */
unsigned int RainbruRPG::Network::GlobalURI::getConfigFilesCount(void){
  return this->mConfigFilesCount;
}

/** Get the list of installed config files
  *
  * \return The list as constant
  *
  */
const RainbruRPG::Network::tInstalledConfigFilesList& 
RainbruRPG::Network::GlobalURI::getInstallConfigFilesList(void)const{
  return this->mInstalledFileList;
}

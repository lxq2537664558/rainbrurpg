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

#include "globaluri.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/path.hpp"

/** The default constructor
  *
  * It initalize the base website according to the definition of the
  * WEBSITE_DEBUG macro.
  *
  */
RainbruRPG::Network::GlobalURI::GlobalURI(){

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

  uploadDir=userDir+"uploaded/";

}

/** The default destructor
  *
  *
  */
RainbruRPG::Network::GlobalURI::~GlobalURI(){

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
  boost::filesystem::path homePath(userDir.c_str(), 
				   boost::filesystem::native);
  LOGCATS("Boost path returns '");
  LOGCATS(homePath.string().c_str());
  LOGCATS("'");
  LOGCAT();

  bool ex=boost::filesystem::exists( homePath );
  if (ex){
    LOGI("Home directory alerady exists");
  }
  else{
    LOGI("Home directory doesn't exists, creating it");
    boost::filesystem::create_directory( homePath );
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

  boost::filesystem::path test( s,boost::filesystem::native);
  if (!boost::filesystem::exists(test)){
    LOGW("The given file doesn't exist");
  }

  return s;
}

/** Test a file and install it if it doesn't
  *
  * Copy the given filename from $PREFIX/share/config to 
  * $HOME/.RainbruRPG/config
  *
  * \param filename The name of the file to install
  *
  */
void RainbruRPG::Network::GlobalURI::
installConfigFile(const std::string& filename){
  // The $PREFIX/share... filename
  std::string s=USER_INSTALL_PREFIX;
  s+="/share/RainbruRPG/config/";
  s+=filename;

  // The $PREFIX/.RainbruRPG... filename
  std::string s2=userDir;
  s2+=filename;

  // The boost path
  boost::filesystem::path optionXmlPath( s, 
	boost::filesystem::native);
  boost::filesystem::path userOptionXmlPath( s2, 
	boost::filesystem::native);

  if (!boost::filesystem::exists(userOptionXmlPath)){
    std::string msg=filename;
    msg+=" not found, copying it from $PREFIX/share";
    LOGW(msg.c_str());

    boost::filesystem::copy_file(optionXmlPath, userOptionXmlPath);
  }
  else{
    std::string msg2=filename;
    msg2+=" found in user directory";
    LOGI(msg2.c_str());
  }
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
  boost::filesystem::path p(uploadDir, boost::filesystem::native);
  if(!boost::filesystem::exists(p)){
    LOGW("uploaded/ directory does not exist, creating it");
    // If the uploaded directory does not exist, create it
    boost::filesystem::create_directory(p);
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
  std::string dir;
  std::string ret=userDir;
  ret+="quarantine/";
  dir=ret;
  ret+=s;


  // Create the directory if not exist
  boost::filesystem::path p(dir, boost::filesystem::native);
  if(boost::filesystem::exists(p)){
    if (boost::filesystem::is_directory(p)){
      LOGI("quarantine/ directory exists");

    }
  }
  else{
    LOGW("quarantine/ directory does not exist, creating it");
    // If the uploaded directory does not exist, create it
    boost::filesystem::create_directory(p);
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
  * \param s Only the file name
  * \param sun The server unique name
  *
  * \return The path and the filename
  *
  */
std::string RainbruRPG::Network::GlobalURI::
getDownloadFile(const std::string& s, const std::string& sun)const{
  std::string dir, dirWoSun;
  std::string ret=userDir;
  ret+="downloaded/";
  dirWoSun=ret;
  ret+=sun;
  dir=ret;
  ret+="/";
  ret+=s;

  // Test if the unique directory exists
  boost::filesystem::path p(dir, boost::filesystem::native);
  boost::filesystem::path p2(dirWoSun, boost::filesystem::native);
  if(boost::filesystem::exists(p)){
    if (boost::filesystem::is_directory(p)){
      LOGI("Downloaded/ directory exists");

    }
  }
  else{
    LOGW("Downloaded/ directory does not exist, creating it");
    // If the downloaded directory does not exist, create it
    if (!boost::filesystem::exists(p2)){
      boost::filesystem::create_directory(p2);
    }
    // Crete the unique name server directory
    boost::filesystem::create_directory(p);
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

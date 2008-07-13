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
 * - 17 mar 2008 : InstalledFileList implementation
 * - 15 mar 2008 : Adding some functions for unit test
 *                 Passing existing function const
 * - 09 jul 2007 : Tests if downloaded directory exists
 * - 01 jul 2007 : Switch to const std::string&
 * - 21 jun 2007 : FTP related function added
 *
 */

#ifndef GLOBAL_URI_H
#define GLOBAL_URI_H

#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>
#include <list>

#include "logger.h"
#include "config.h"

#ifdef RAINBRU_RPG_DEBUG
#  define WEBSITE_DEBUG
#endif

using namespace std;
using namespace boost::filesystem;

namespace RainbruRPG{
  namespace Network {

    /** An installed configuration file
      *
      * Defines an item contained in the installed configuration file
      * list as returned by the
      * \ref RainbruRPG::Network::GlobalURI::getInstallConfigFilesList
      * "getInstallConfigFilesList" function.
      *
      * \note <var>needCreation</var> tells if this file was created in
      *       the last call of \ref RainbruRPG::Network::GlobalURI::homeSetup
      *       "homeSetup()"
      *
      * \note <var>exists</var> should always be \c true because its value
      *       is defined after creating file if needed.
      *
      * \sa \ref RainbruRPG::Network::tInstalledConfigFilesList
      *     "tInstalledConfigFilesList"
      *
      */
    typedef struct {
      std::string filename;         //!< The filename without path
      std::string absoluteFileName; //!< The absolute filename (contains path)
      bool needCreation;            //!< Did this file need to be created ?
      bool exists;                  //!< Last exist test
    }tInstalledConfigFilesListItem;

    /** A simple STL list of tInstalledConfigFilesListItem pointers 
      *
      * Defines the installed configuration file
      * list as returned by the
      * \ref RainbruRPG::Network::GlobalURI::getInstallConfigFilesList
      * "getInstallConfigFilesList()" function.
      *
      */
    typedef list<tInstalledConfigFilesListItem*> tInstalledConfigFilesList;

    /** A class to get the uri of a page, according to the website adress or
      * to get a directory
      *
      * \section Web_sec Website related functions
      *
      * If the macro \c WEBSITE_DEBUG is defined, we use a local website
      * (127.0.0.1), otherwise, we use the production website
      * (rainbru.free.fr). 
      *
      * Use getAdminAdress() to get an administration php file
      * mostly used by the \ref RainbruRPG::Network::Ident::CurlSubmitForm 
      * "CurlSubmitForm" interface. Use 
      * getXmlAdress() to get the adress of a xml files (used 
      * by \ref RainbruRPG::Network::Ident::CurlFileToXml 
      * "CurlFileToXml").
      *
      * \section Local_sec Local filesystem related functions
      *
      * This class is also used to get a local file. getShareFile(std::string)
      * give the absolute name of a file in <code>$PREFIX/share</code> (i.e. 
      * <code>/usr/local/share</code> by default) and 
      * getUserDirFile(std::string) give
      * a configuration file in the user's home directory.
      *
      * GlobalURI makes sure some files are in the 
      * <code>$HOME/.RainbruRPG/</code> by 
      * copying it from <code>$PREFIX/share/conf/</code> if it does not 
      * exists. All this stuff is made by the homeSetup() method.
      *
      * 
      * \section server_approval_sec Server's approval
      *
      * When a file is uploaded to a server by an editor, the server's 
      * administrator \b must approve the files before a client can 
      * download them. The editor can use it but the client could fail
      * to start playing on this world. It is know as quarantine. A place
      * where the files can be used before approval.
      *
      * \section installed_config_files_list_sec Installed configuration 
      * files list
      *
      * This feature was originally implemented for unit tests purpose. The
      * homeSetup() function uses installConfigFile() to copy a file from
      * the \c $PREFIX$/share/ directory to the 
      * <code>$HOME$/.RainbruRPG/config/</code>
      * and a list of these files is created. The getConfigFilesCount() is
      * an internal count, used to test file list size. The 
      * getInstallConfigFilesList() function returns this list.
      *
      */
    class GlobalURI{
    public:
      GlobalURI();
      ~GlobalURI();

      const std::string& getUserDir(void)const;
      const std::string& getAdminSite(void)const;
      const std::string& getXmlSite(void)const;
      const std::string& getShareDir(void)const;
      const std::string& getUploadDir(void)const;
      const std::string& getQuarantineDir(void)const;

      std::string getAdminAdress(const std::string&)const;
      std::string getXmlAdress(const std::string&)const;

      std::string getUserDirFile(const std::string&)const;
      std::string getShareFile(const std::string&)const;

      std::string getUploadFile(const std::string&)const;
      std::string getQuarantineFile(const std::string&)const;
      std::string getDownloadFile(const std::string&, const std::string&, 
				  bool createIfMissing=true)const;

      unsigned int getConfigFilesCount(void);
      const tInstalledConfigFilesList& getInstallConfigFilesList(void)const;

    private:
      void installConfigFile(const std::string&);
      void homeSetup();

      /** The base of a administration web site address */
      std::string adminSite;
      /** Where are the most xml files */
      std::string xmlSite;
      /** The user HOME directory 
        *
	* This directory is <code>$HOME/.RainbruRPG/</code>.
	*
	*/
      std::string userDir;
      /** The \c /usr/share based RainbruRGP directory */
      std::string shareDir;

      /** The directory of uploaded files */
      std::string uploadDir;
      
      /** The directory of files in quarantine */
      std::string quarantineDir;
      
      /** Internal count of installed configuration files  */
      unsigned int mConfigFilesCount;
      
      /** The list of installed configuration files */
      tInstalledConfigFilesList mInstalledFileList;
   };
  }
}

#endif // GLOBAL_URI_H

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
 * - 01 jul 2007 : Switch to const std::string&
 * - 21 jun 2007 : FTP related function added
 *
 */

#ifndef GLOBAL_URI_H
#define GLOBAL_URI_H

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <stdlib.h>

#include "logger.h"

#define WEBSITE_DEBUG

using namespace std;

namespace RainbruRPG{
  namespace Network {

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
      * to start playing on this world.
      *
      */
    class GlobalURI{
    public:
      GlobalURI();
      ~GlobalURI();

      std::string getAdminAdress(const std::string&);
      std::string getXmlAdress(const std::string&);

      std::string getUserDirFile(const std::string&);
      std::string getShareFile(const std::string&);

      std::string getUploadFile(const std::string&);
      std::string getQuarantineFile(const std::string&);
      std::string getDownloadFile(const std::string&, const std::string&);


    private:
      void installConfigFile(const std::string&);
      void homeSetup();

      /** Tha base of a administration web site address */
      std::string adminSite;
      /** Where are the most xml files */
      std::string xmlSite;
      /** The user HOME directory 
        *
	* This directory is <code>$HOME/.RainbruRPG/</code>.
	*
	*/
      std::string userDir;
   };
  }
}

#endif // GLOBAL_URI_H

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
      * If the macro WEBSITE_DEBUG is defined, we use a local website
      * (127.0.0.1), otherwise, we use the production website
      * (rainbru.free.fr). 
      *
      * Use getAdminAdress(const char*) to get an administration php file
      * mostly used by the CurlSubmitForm interface. Use 
      * getXmlAdress(const char*) to get the adress of a xml files (used 
      * by CurlGetFileToXml).
      *
      * \section Local_sec Local filesystem related functions
      *
      * This class is also used to get a local file. getShareFile(std::string)
      * give the absolute name of a file in $PREFIX/share (i.e. 
      * /usr/local/share by default) and getUserDirFile(std::string) give
      * a configuration file in the user's home directory.
      *
      * GlobalURI makes sure some files are in the $HOME/.RainbruRPG/ by 
      * copying it from $PREFIX/share/conf/ if it does not exists. All
      * this stuff is made by the homeSetup() method.
      *
      *
      */
    class GlobalURI{
    public:
      GlobalURI();
      ~GlobalURI();

      const char* getAdminAdress(const char*)const;
      const char* getXmlAdress(const char*)const;

      std::string getUserDirFile(std::string) const;
      std::string getShareFile(std::string) const;

      /** Get the absolute filename of a file upload on the server
        *
	* \param s Only the file name
	*
	* \return The path and the filename
	*
	*/
      std::string getUploadFile(std::string s) const;

      /** Get the absolute filename of a file you download from a server
        *
	* \param s Only the file name
	* \param sun The server Unique name
	*
	* \return The path and the filename
	*
	*/
      std::string getDownloadFile(std::string s, std::string sun) const;


    private:
      void installConfigFile(const std::string&);
      void homeSetup();

      /** Tha base of a administration web site address */
      std::string adminSite;
      /** Where are the most xml files */
      std::string xmlSite;
      /** The user HOME directory */
      std::string userDir;
   };
  }
}

#endif // GLOBAL_URI_H

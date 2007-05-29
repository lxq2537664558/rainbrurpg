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
 * - 30 may 2007 : Adding the FTP control channel port
 *
 */

#ifndef XML_SERVER_CONFIGURATION_H
#define XML_SERVER_CONFIGURATION_H

#include "serverconfiguration.h"
#include "tinyxml.h"

#include <string>

namespace RainbruRPG{
  namespace Server{

    /** A class used to save the server configuration
      *
      * The constructor simply try to load the xmlfile.
      * You must then call save(ServerConfiguration*) or 
      * load(ServerConfiguration*) according to the usage.
      *
      */
    class xmlServerConf{
    public:
      xmlServerConf();
      ~xmlServerConf();

      bool load(ServerConfiguration*);
      bool save(ServerConfiguration*);

    private:
      const char* getServerName();
      const char* getServerDesc();
      const char* getTechNote();
      const char* getIpAdress();
      bool getMode(const char*);
      bool getPlayMode();
      bool getEditMode();
      bool getFloodMode();

      const char* getOption(const char*);
      const char* getDbValue(const char*)const;

      int getPort();
      int getMaxClient();

      void setServerName(const std::string&);
      void setDescription(const std::string&);
      void setTechNote(const std::string&);
      void setServerMode(bool, bool, bool);
      void setServerOption(const std::string&, int, int );

      const std::string& getDbHostName()const;
      const std::string& getDbName()const;
      const std::string& getDbUserName()const;
      const std::string& getDbUserPwd()const;

      void setDatabase(const std::string&,const std::string&,
		       const std::string&,const std::string&);

      /** The name of the xml file to open */
      std::string filename;
      /** The global xml document pointer */
      TiXmlDocument *doc;
      /** A global pointer to the \c ServerConfig xml node */
      TiXmlElement *root;
      /** Is the xml file correctly loaded */
      bool correctlyLoaded;
    };

  }
}

#endif // XML_SERVER_CONFIGURATION_H

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
 * - 14 apr 2007 : Adding database connection options
 *
 */
#ifndef SERVER_CONFIGURATION_H
#define SERVER_CONFIGURATION_H

#include <string>

namespace RainbruRPG{
  namespace Server{

    /** The data needed for the configuration of the server
      *
      * The server can accept only several types of connection. The 
      * playMode status is used by the players. The editMode is the mode
      * used to connect the editor and the floodMode is used by the 
      * netflooder.
      *
      * The ConfigDialog is the GUI for modifying the values of
      * an instance of this class.
      *
      */
    class ServerConfiguration{
    public:
      ServerConfiguration();

      void setName(const std::string&);
      void setDesc(const std::string&);
      void setTechNote(const std::string&);
      void setPlayMode(bool);
      void setEditMode(bool);
      void setFloodMode(bool);
      void setIpAdress(const std::string&);
      void setPort(int);
      void setMaxClient(int);

      const std::string& getName()const;
      const std::string& getDesc()const;
      const std::string& getTechNote()const;
      bool getPlayMode();
      bool getEditMode();
      bool getFloodMode();
      const std::string& getIpAdress()const;
      int getPort();
      int getMaxClient();

      void setHostName(const std::string&);
      void setDatabaseName(const std::string&);
      void setUserName(const std::string&);
      void setPassword(const std::string&);

      const std::string& getHostName()const;
      const std::string& getDatabaseName()const;
      const std::string& getUserName()const;
      const std::string& getPassword()const;

    private:
      /** The name of the server */
      std::string name;
      /** The description of the server */
      std::string description;
      /** The technical note */
      std::string techNote;

      /** Is this server accept player connection ? */
      bool playMode;
      /** Is this server accept editor connection ? */
      bool editMode;
      /** Is this server accept netflooder connection ? */
      bool floodMode;

      /** The ip adress */
      std::string ipAdress;
      /** The server's port  */
      int port;
      /** The maximum number of clients allowed in this server */
      int maxClient;

      /** The hostname of the Postgres server */
      std::string dbHostName;
      /** The database name */
      std::string dbDatabaseName;
      /** The username used for database connection */
      std::string dbUserName;
      /** The password  used for database connection */
      std::string dbPassword;

    };

  }
}

#endif // SERVER_CONFIGURATION_H

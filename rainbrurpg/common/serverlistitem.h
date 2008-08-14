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

/** \file serverlistitem.h
  * Defines an item used in the tServerList
  *
  * Modifications :
  * - 08 aug 2008 : Documentation update
  * - 04 aug 2007 : Starting implementation 
  *
  */

#include <string>

#ifndef _SERVER_LIST_ITEM_H_
#define _SERVER_LIST_ITEM_H_

/** Defines the initial value of server's type
  *
  * This should not be in type enumeration. To be able to tell
  * if it was an error.
  *
  */
#define SERVER_TYPE_INITIAL_VALUE 9999

using namespace std;

namespace RainbruRPG{
  namespace Network {
    namespace Ident {

      /** Defines an item used in the tServerList
        *
	* It represents a server as it appears in the \c servers.xml
	* on the adminsite. It is returned by xmlServerList.
	*
	* Most of the integer members can be got in the std::string form.
	* getOccupationStr() is a function that gives you a directly
	* usable occupation string.
	*
	*/
      class ServerListItem{
      public:
	ServerListItem();
	~ServerListItem();

	void setCreationDate(const std::string&);
	void setName(const std::string&);
	void setUniqueName(const std::string&);
	void setDescription(const std::string&);
	void setIpAddress(const std::string&);
	void setUdpPort(const std::string&);
	void setFtpPort(const std::string&);
	void setTechNote(const std::string&);
	void setMaxClients(const std::string&);
	void setActClients(const std::string&);
	void setType(const std::string&);

	const std::string& getName();

	unsigned int getType();
	unsigned int getActClients();
	unsigned int getMaxClients();

	std::string getMaxClientsStr();
	std::string getActClientsStr();
	std::string getTypeStr();
	std::string getOccupationStr();
	std::string getIpAddress();

 	const std::string& getCreationDate();
 	const std::string& getUniqueName();
 	const std::string& getDescription();
 	const std::string& getTechNote();

	int getUdpPort();
	int getFtpPort();
	std::string getUdpPortStr();
	std::string getFtpPortStr();

     private:
	/** The creation date/time */
 	std::string creation; 
	/** The server's name */
	std::string name;       
	/** The unique name */
	std::string uniqueName; 
	/** The type 
	  *
	  * Actually, the supported types are :
	  * -# Fantasy;
	  * -# Contemporary;
	  * -# Futuristic;
	  * -# Post-apocalyptic.
	  *
	  */
	unsigned int type;     
	/** The description */
	std::string description;
	/** The IP address */
	std::string ipAddress; 
	/** The UDP port */
	int udpPort;  
	/** The FTP control channel port */
	int ftpPort;   
	/** The technical note */
	std::string techNote;
	/** Maximum allowed connection */
	unsigned int maxClients;
	/** Actual number of connected clients */
	unsigned int actClients;


      };
    }
  }
}

#endif // _SERVER_LIST_ITEM_H_

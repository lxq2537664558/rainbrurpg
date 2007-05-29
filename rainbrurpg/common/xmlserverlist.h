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
 * - 29 may 2007 : Adding the 'ftp' key
 *
 */

#ifndef XML_SERVER_LIST_H
#define XML_SERVER_LIST_H

#include <iostream>
#include <string>
#include <list>
#include <logger.h>
#include <tinyxml.h>

#include "tnotelist.h"
#include "xmltimestamp.h"
#include "curlfiletoxml.h"
#include "stringconv.h"

using namespace std;
using namespace RainbruRPG::Gui;

namespace RainbruRPG{
  namespace Network {
    namespace Ident {

      /** A server structure like it appears in the servers.xml
        *
	*
	*/
      struct tServerListItem{
	std::string creation;    //!< The date of creation
	const char* name;        //!< The name of the server
	const char* description; //!< The description
	const char* ipAdress;    //!< The ip adress
	const char* port;        //!< The UDP port
	const char* ftp;         //!< The FTP control channel port 
	const char* techNote;    //!< The technical note
	unsigned int maxClients; //!< Maximum allowed connection
	unsigned int actClients; //!< Actual number of connected clients
      };

      /** A stl list of tServerListItem
        *
	*/
      typedef std::list<tServerListItem*> tServerList;

      /** The return of the AddServer function */
      enum tAddServerReturn{
	ASR_CREATED,           //<! The server is successfully created
	ASR_INVALID_NAME,      //<! The name is not correct
	ASR_INVALID_IP,        //<! The ip adress is not correct
	ASR_INVALID_PORT,      //<! The port is not correct
	ASR_EXISTS             //<! The name is already in use
      };

      /** Read the XML file of the Servers list
        *
	* A server list is maintained in the administration site. This list
	* is used by the clients to get the IP adress and other informations
	* about server contact them.
	*
	* It gets the server list from the administration site using a
	* GlobalURI instance and uses the CurlFileToXml functions to retrieve
	* the file.
	*
	* \sa CurlServerAdd, CurlServerDelete
	*
	*/
      class xmlServerList : public CurlFileToXml{
      public:
	xmlServerList();
	~xmlServerList();

	tServerList* getServerList();
	bool isServerExisting(const char*);

	tServerListItem* getServerByName(const char*);
	bool refresh();

      private:
	const char* getXMLTextFromName(TiXmlElement*, const char*);

	/** The global xml document pointer */
	TiXmlDocument *doc;
	/** A global pointer to the \c ServerList xml node */
	TiXmlElement *root;

      };
    }
  }
}

#endif // XML_SERVER_LIST_H

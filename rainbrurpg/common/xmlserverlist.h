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

/** \file xmlserverlist.h
  * Declares a class that read the server list
  *
  * Modifications :
  * - 12 jan 2009 : Added contructor initializers to avoid segfault
  * - 11 aug 2008 : Single file documentation
  * - 28 jun 2007 : Adding the 'uniqueName' and 'type' keys
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
#include "serverlistitem.h"
#include "stringconv.h"

using namespace std;
using namespace RainbruRPG::Gui;

namespace RainbruRPG{
  namespace Network {
    namespace Ident {

      /** A stl list of ServerListItem
        *
	*/
      typedef std::list<ServerListItem*> tServerList;

      /** The return of the xmlServerList::AddServer() function */
      enum tAddServerReturn{
	ASR_CREATED,           //<! The server is successfully created
	ASR_INVALID_NAME,      //<! The name is not correct
	ASR_INVALID_IP,        //<! The ip adress is not correct
	ASR_INVALID_PORT,      //<! The port is not correct
	ASR_EXISTS             //<! The name is already in use
      };

      /** Read the XML file of the Servers list
        *
	* If the xml file is modified (server added or removed) do
	* not forget to call the refresh() function.
	*
	* A server list is maintained in the administration site. This list
	* is used by the clients to get the IP adress and other informations
	* about server to contact them.
	*
	* It gets the server list from the administration site using a
	* GlobalURI instance and uses the CurlFileToXml functions to retrieve
	* the file.
	*
	* \sa CurlServerAdd, CurlServerDelete, 
	*     \ref RainbruRPG::Network::Ident::CurlServerModifClients
	*     "CurlServerModifClients"
	*
	*/
      class xmlServerList : public CurlFileToXml{
      public:
	xmlServerList();
	~xmlServerList();

	tServerList* getServerList();
	bool isServerExisting(const char*);

	ServerListItem* getServerByName(const char*);
	bool refresh();

      private:
	/** The global xml document pointer */
	TiXmlDocument *doc;
	/** A global pointer to the \c ServerList xml node */
	TiXmlElement *root;

      };
    }
  }
}

#endif // XML_SERVER_LIST_H

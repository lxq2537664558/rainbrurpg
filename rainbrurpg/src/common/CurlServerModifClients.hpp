/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file curlservermodifclients.h
  * Defines a class to modify connected clients number of a server
  *
  * Modifications :
  * - 28 mar 2009 : Now uses gettext
  * - 05 aug 2008 : File documentation added
  *
  */

#ifndef CURL_SERVER_MODIF_CLIENTS_H
#define CURL_SERVER_MODIF_CLIENTS_H

#include <string>
#include <GlobalUri.hpp>
#include <CurlSubmitForm.hpp>
#include <xmlserverlist.h>
#include <stringconv.h>

#include "rainbrudef.h" // For the gettext stuff

using namespace std;
using namespace RainbruRPG::Core;
using namespace RainbruRPG::Network;

namespace RainbruRPG {
  namespace Network {
    namespace Ident {

      /** Change the current connected clients number
        * 
	* When a new client connection is accepted or when
	* a client leave the server, the server uses this class to submit
	* a actual client number change to the administration site.
	*
	* The posted keys are :
	* - name : The name of the server
	* - actClients : The actual number of client connected
	* 
	* This class is only used to modify the actual connected client 
	* number, to get this information please see 
	* \ref RainbruRPG::Network::Ident::xmlServerList "xmlServerList"
	*
	* \note If you set a negative client number, it will be 0.
	*
	*/
      class CurlServerModifClients : public CurlSubmitForm{
      public:
	CurlServerModifClients();
	~CurlServerModifClients();

	void setName(const char*);
	void setName(const std::string&);

	void setActClients(int);

      protected:
	virtual bool controlBefore();
	virtual bool controlAfter();

      private:
	/** The xmlPlayerList used to deal with the xml file */
	xmlServerList* xml;
      };

    }
  }
}

#endif // CURL_SERVER_MODIF_CLIENTS_H

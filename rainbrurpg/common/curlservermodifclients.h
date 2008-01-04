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

#ifndef CURL_SERVER_MODIF_CLIENTS_H
#define CURL_SERVER_MODIF_CLIENTS_H

#include <string>
#include <globaluri.h>
#include <curlsubmitform.h>
#include <xmlserverlist.h>
#include <stringconv.h>

using namespace std;
using namespace RainbruRPG::Core;
using namespace RainbruRPG::Network;

namespace RainbruRPG {
  namespace Network {
    namespace Ident {

      /** Submits a change server's actClients to the administration site
        * 
	* It is used when a new client connection is accepted or when
	* a client leave the server.
	*
	* The posted keys are :
	* - name : The name of the server
	* - actClients : The actual number of client connected
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

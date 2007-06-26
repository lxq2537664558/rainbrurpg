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
 * - 26 jun 2007 : Adding 'uniqueName' and 'type'
 * - 28 may 2007 : Adding the 'ftp' key
 *
 */

#ifndef CURL_SERVER_ADD_H
#define CURL_SERVER_ADD_H

#include <string>
#include <globaluri.h>
#include <curlsubmitform.h>
#include <xmlserverlist.h>

using namespace std;
using namespace RainbruRPG::Network;

namespace RainbruRPG {
  namespace Network {
    namespace Ident {

      /** Submits a add server to the administration site
        * 
	* Each server that is started must be registered in the administation
	* site. This class is used to add a server to the administration site.
	*
	* \section posted_keys Posted keys
	*
	* The posted keys are :
	* - name : The name of the server
	* - ip : The public IP adress of the server in the form x.x.x.x
	* - port : The UDP listening port
	* - ftp  : The FTP control channel port
	* - maxClients : The maximum number of clients allowed 
	* - description : The description of the server
	* - technote : a possibly empty technical note
	*
	* The timestamp posted key is automatically filled by the current
	* data/time.
	* 
	* \section server_listening_ports Listening ports
	*
	* A server needs two ports. The UDP port is used to action-based 
	* network packets. The FTP control channel port is a TCP port used
	* by clients to store and retrieve files in the server. The FTP 
	* data channel is always <code>contol_chanel-1</code>. If you are 
	* behind a firewall, you must setup port forwarding for 
	* control channel (TCP), data channel (TCP) and the UDP port.
	*
	* \sa xmlServerList, CurlServerDelete
	*
	*/
      class CurlServerAdd : public CurlSubmitForm{
      public:
	CurlServerAdd();
	~CurlServerAdd();

	void setName(const char*);
	void setIpAddress(const char*);
	void setPort(const char*);
	void setFtpPort(const char*);
	void setMaxClients(const char*);
	void setDescription(const char*);
	void setTechNote(const char*);

	void setName(const std::string&);
	void setIpAddress(const std::string&);
	void setPort(const std::string&);
	void setFtpPort(const std::string&);
	void setMaxClients(const std::string&);
	void setDescription(const std::string&);
	void setTechNote(const std::string&);

	void setUniqueName(const std::string&);
	void setType(const std::string&);

	const char* getName();
	const char* getIpAddress();
	const char* getPort();
	const char* getFtpPort();
	const char* getMaxClients();
	const char* getDescription();
	const char* getTechNote();

	const std::string& getUniqueName();
	const std::string& getType();

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

#endif // CURL_SERVER_ADD_H

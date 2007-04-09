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

#ifndef CURL_SERVER_DELETE_H
#define CURL_SERVER_DELETE_H

#include <string>
#include <globaluri.h>
#include <curlsubmitform.h>
#include <xmlserverlist.h>

using namespace std;
using namespace RainbruRPG::Network;

namespace RainbruRPG {
  namespace Network {
    namespace Ident {

      /** Submits a delete server to the administration site
        * 
	* The posted keys are :
	* - name : The name of the server to delete
	* 
	*/
      class CurlServerDelete : public CurlSubmitForm{
      public:
	CurlServerDelete();
	~CurlServerDelete();

	void setName(const char*);
	void setName(const std::string&);

      protected:
	virtual bool controlBefore();
	virtual bool controlAfter();


      };
    }
  }
}

#endif // CURL_SERVER_DELETE_H
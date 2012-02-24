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

/** \file httpresponse.cpp
  * Implements a class that return a string from an HTTP status code
  *
  */

#include "HttpResponse.hpp"

/** The default constructor 
  *
  * It fills the HttpMessageMap with the kown HTTP status code and 
  * messages.
  */
RainbruRPG::Network::HttpResponse::HttpResponse(){
  LOGI("Creating the HttpResponse stl map");
  // Creating the map

  msgMap=new HttpMessageMap();

  // ========= The success status codes
  RESPADD(200, _("Ok : The request was fulfilled"));
  RESPADD(201, _("Created : The POST request was successful"));
  RESPADD(202, _("Accepted : The request has been accepted for processing, "
		 "but the processing has not been completed"));
  RESPADD(203, _("Partial Information : A GET command returned "
		 "metainformation that is not a definitive set of the object "
		 "from a server with a copy of the object"));
  RESPADD(204, _("No Response : Server has received the request but there is "
		 "no information to send back, and the client should stay in "
		 "the same document view"));

  // ========= The redirection status codes
  RESPADD(301, _("Moved : The data requested has been assigned a new URI, the "
		 "change is permanent"));
  RESPADD(302, _("Found : The data requested actually resides under a "
		 "different URL, however, the redirection may be altered on "
		 "occasion")); 
  RESPADD(303, _("Method : The client may go try another network address. In "
		 "this case, a different method may be used too, rather than "
		 "GET"));
  RESPADD(304, _("Not Modified : If the client has done a conditional GET and "
		 "access is allowed, but the document has not been modified"));

  // ========= The client's error status codes
  RESPADD(400, _("Bad request : The request had bad syntax or was inherently "
		 "impossible to be satisfied"));
  RESPADD(401, _("Unauthorized : The client should retry the request with a "
		 "suitable Authorization header"));
  RESPADD(402, _("PaymentRequired : The client may retry the request with a "
		 "suitable ChargeTo header"));
  RESPADD(403, _("Forbidden : The request is for something forbidden. "
		 "Authorization will not help"));
  RESPADD(404, _("Not found : The server has not found anything matching "
		 "the URI given"));

  // ========= The server's error status codes
  RESPADD(500, _("Internal Error : The server encountered an unexpected "
		 "condition which prevented it from fulfilling the request"));
  RESPADD(501, _("Not implemented : The server does not support the facility "
		 "required"));
  RESPADD(502, _("Service temporarily overloaded : The server cannot process "
		 "the request due to a high load (whether HTTP servicing or "
		 "other requests). The implication is that this is a "
		 "temporary condition which maybe alleviated at other times"));
  RESPADD(503, _("Gateway timeout : This is equivalent to Internal Error 500, "
		 "but in the case of a server which is in turn accessing some "
		 "other service, this indicates that the respose from the "
		 "other service did not return within a time that the gateway "
		 "was prepared to wait"));

}

/** The default destructor 
  *
  */
RainbruRPG::Network::HttpResponse::~HttpResponse(){
  msgMap->clear();
  delete msgMap;
  msgMap=NULL;
}

/** Get the message corresponding to the given status code
  *
  * It search the given status code in the map. Returns the message if 
  * it was  find, otherwise, return "" and send a warning log.
  *
  * \param l The status code you want to get
  * 
  * \return The message if the status code was found, otherwise returns
  *         "".
  */
const char* RainbruRPG::Network::HttpResponse::getMessage(long l){
  HttpMessageMapIterator iter = msgMap->find(l); 
  if (iter != msgMap->end()){

    ostringstream o;
    o << iter->first << " " << iter->second;
    return o.str().c_str();
  } 
  else{
    LOGW(_("The requested http status code is not in list. Returning empty "
	   "message"));
    return "";
  }
}

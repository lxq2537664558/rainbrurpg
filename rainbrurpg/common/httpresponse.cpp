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

/** \file httpresponse.cpp
  * Implements a class that return a string from an HTTP status code
  *
  */

#include "httpresponse.h"

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

  msgMap->insert(HttpMessagePair(200, "OK : The request was fulfilled"));

  //  a=NULL;
  msgMap->insert(HttpMessagePair(201, "CREATED : The POST request was "
	 "successful"));
  msgMap->insert(HttpMessagePair(202, "Accepted : The request has been "
	 "accepted for processing, but the processing has not been "
	 "completed"));
  msgMap->insert(HttpMessagePair(203, "Partial Information : A GET command "
        "returned metainformation that is not a definitive set of the "
        "object from a server with a copy of the object"));
  msgMap->insert(HttpMessagePair(204, " No Response : Server has received "
        "the request but there is no information to send back, and the "
	"client should stay in the same document view"));

  // ========= The redirection status codes

  msgMap->insert(HttpMessagePair(301, "Moved : The data requested has been "
        "assigned a new URI, the change is permanent"));
  msgMap->insert(HttpMessagePair(302, "Found : The data requested actually "
        "resides under a different URL, however, the redirection may be "
        "altered on occasion")); 
  msgMap->insert(HttpMessagePair(303, "Method : The client may go try "
        "another network address. In this case, a different method may be "
        "used too, rather than GET"));
  msgMap->insert(HttpMessagePair(304, "Not Modified : If the client has done "
        "a conditional GET and access is allowed, but the document has "
        "not been modified"));


  // ========= The client's error status codes

  msgMap->insert(HttpMessagePair(400, "Bad request : The request had bad "
        "syntax or was inherently impossible to be satisfied"));
  msgMap->insert(HttpMessagePair(401, "Unauthorized : The client should "
        "retry the request with a suitable Authorization header"));
  msgMap->insert(HttpMessagePair(402, "PaymentRequired : The client may "
        "retry the request with a suitable ChargeTo header"));
  msgMap->insert(HttpMessagePair(403, "Forbidden : The request is for "
        "something forbidden. Authorization will not help"));
  msgMap->insert(HttpMessagePair(404, "Not found : The server has not "
        "found anything matching the URI given"));

  // ========= The server's error status codes

  msgMap->insert(HttpMessagePair(500, "Internal Error : The server "
        "encountered an unexpected condition which prevented it from "
        "fulfilling the request"));
  msgMap->insert(HttpMessagePair(501, "Not implemented : The server does "
        "not support the facility required"));
  msgMap->insert(HttpMessagePair(502, "Service temporarily overloaded : The "
        "server cannot process the request due to a high load (whether HTTP "
        "servicing or other requests). The implication is that this is a "
        "temporary condition which maybe alleviated at other times"));
  msgMap->insert(HttpMessagePair(503, "Gateway timeout : This is equivalent "
        "to Internal Error 500, but in the case of a server which is in "
        "turn accessing some other service, this indicates that the "
        "respose from the other service did not return within a time that "
        "the gateway was prepared to wait"));

  
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
    LOGW("The requested http status code is not in list");
    return "";
  }
}

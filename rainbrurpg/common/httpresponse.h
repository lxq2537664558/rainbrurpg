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

/** \file httpresponse.h
  * Declares types and class that return string from an HTTP status code
  *
  * Modifications :
  * - 01 apr 2009 : Using gettext and the RESPADD macro
  * - 04 aug 2008 : Single file documentation
  *
  * \todo Uses C++ string instead of C-style null terminated string
  *
  */

#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H


#include <string>
#include <map>
#include <iostream>
#include <sstream>

#include "logger.h"
#include "rainbrudef.h" // For the gettext stuff

/** A shortcut macro to add a message */
#define RESPADD(ID,MSG) (msgMap->insert(HttpMessagePair(ID, MSG)))

using namespace std;

namespace RainbruRPG {
  namespace Network {


    /** A stl map of long/const char*
      *
      */
    typedef map<long, const char*>   HttpMessageMap;

    /** A shortcut for the HttpMessageMap iterator
      *
      */
    typedef HttpMessageMap::iterator HttpMessageMapIterator;

    /** The pair type which are added to the HttpMessageMap
      *
      */
    typedef pair<long, const char*>  HttpMessagePair;


    /** This class give the error message correponding to an http 
      *	status code.
      *
      * HTTP servers always return numeric status code. This codes
      * determines what's happen and with the code, you can now
      * the error typt.
      *
      * - 200->299 : Success
      * - 300->399 : Redirection
      * - 400->499 : Client's error
      * - 500->599 : Server's error
      *
      * This class returns a human readable message for a given http 
      * status code. Simply call getMessage(long) to get the corresponding
      * message.
      */
    class HttpResponse{
    public:
      HttpResponse();
      ~HttpResponse();

      const char* getMessage(long);

    private:
      /** The map used to stored the status code/message pairs.
        *
	*/
      HttpMessageMap* msgMap;
    };

  }
}

#endif  // HTTP_RESPONSE_H

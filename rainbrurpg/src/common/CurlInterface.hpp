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

/** \file curlinterface.h
  * Defines a common base for all libcUrl based classes
  * 
  * Modifications :
  * - 29 mar 2009 : Now using gettext 
  * - 03 aug 2007 : removing default write function
  * - 29 jul 2007 : setFilename and getFilename removed
  * - 03 mar 2007 : Some functions become protected :
  *                   setDefaultWriteFunction, setWrittenData, setWriteFunction
  *	           
  * - 25 feb 2007 : Documentation updates
  *
  */

#ifndef CURL_INTERFACE
#define CURL_INTERFACE

#include <curl/curl.h>
#include <sstream>
#include <string>
#include <vector>

#include "rainbrudef.h"
#include "Logger.hpp"

using namespace std;

namespace RainbruRPG {
  namespace Network {
    namespace Ident {

      /** A super class for all libcurl-based interface.
        *
	* The standard way to subclass it is to create some functions and
	* some internal values and to call perform().
	*
	* Example : The CurlAccountAdd class has setPlayerName(), setPassword()
	* ... We will call init(), the set??? functions and call the perform() 
	* function.
	*
	* After you have performed a libcurl operation, you can get the 
	* HTTP server response with the getServerResponse() function. It
	* returns a long that can be used with HttpResponse to get a 
	* human-readable message. If the HTTP server answer do not help you,
	* you can have another message with getCustomErrorMessage() that
	* give you an in-context error message.
	*
	* \sa CurlGetFile, CurlSubmitForm, HttpResponse
	*/
      class CurlInterface{
      public:
	CurlInterface();
	virtual ~CurlInterface();

	/** Make all the work needed 
	  *
	  *
	  */
	virtual bool perform()=0;


	long getServerResponse();
	const char* getCustomErrorMessage();

      protected:
	virtual bool init();
	virtual bool cleanup();

	void setWriteFunction(void*);
	void setCustomErrorMessage(const char*);

	/** Makes sure the action can be perform
	  *
	  * An example, if you add a player, make sure the player does
	  * not already exist.
	  */
	virtual bool controlBefore()=0;

	/** Makes sure the action has been correctly done
	  *
	  * An example, if you add a player, make sure the player has
	  * been correctly added.
	  */
	virtual bool controlAfter()=0;

	/** libcurl handle structure
	  *
	  */
	CURL * handle;
	/** The filename or the url to get
	  *
	  * This field is used as the filename to get or the url of 
	  * the form to submit.
	  */
	std::string filename;

	/** This value must pass to true if a custom writedata 
	  * function is set
	  */
	bool overrideWriteData;

	/** The response of the server to the last perform
	  *
	  * It is the server response : 404 says Page not found... The
	  * default value is set in CurlInterface's default constructor :
	  * -1. This value indicates that no server action was performed.
	  * 
	  * First test this value, and if you get -1, see customErrorMessage.
	  */
	long serverResponse;

	/** If an error occured during a custom operation, fill in this message
	  *
	  * Do not set this directly. Use setCustomErrorMessage instead which
	  * test if a message already exits.
	  */
	const char* customErrorMessage;
      };

    }
  }
}



#endif // CURL_INTERFACE


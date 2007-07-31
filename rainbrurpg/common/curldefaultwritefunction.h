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

#ifndef CURL_DEFAULT_WRITE_FUNCTION
#define CURL_DEFAULT_WRITE_FUNCTION

// to prevent multiple definitions of the writeData function
#  ifndef DO_NOT_INCLUDE_WRITE_DATA

#include <curl/curl.h>
#include <iostream>
#include <fstream>
#include "logger.h"

namespace RainbruRPG {
  namespace Network {
    namespace Ident {


      /** The default curl write function
        *
	* It simply writes the given server-side file to a local file
	* called \c curlget.xml . The server-side data could be sent
	* by server in multiple packet, so the file is opened in
	* append mode.
	*
	* \param buffer A libcurl internally used parameter
	* \param size A libcurl internally used parameter
	* \param nmemb A libcurl internally used parameter
	* \param userp A libcurl internally used parameter
	*
	* \sa CurlGetFile
	*
	* \return The value of nmemb
	*
	*/
      size_t writeData(void *buffer, size_t size, size_t nmemb, void *userp){
	LOGI("Using the default writedata Function.");

	std::ofstream outfile ("curlget.xml", ios::out|ios::app);

	if (outfile){
	  outfile << (char*)buffer <<endl;
	}
	else{
	  LOGE("An error occured while opening curlget.txt.");
	}
	outfile.close();
	return nmemb;
      }
    }
  }
}
#  endif// DO_NOT_INCLUDE_WRITE_DATA

#endif //CURL_DEFAULT_WRITE_FUNCTION


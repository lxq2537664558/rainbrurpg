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

/* Modification :
 * - 31 jul 2007 : Remove curlget.xml
 * - 02 mar 2007 : Using LOGCAT() instead of cout
 *
 */

#ifndef CURL_GET_FILE
#define CURL_GET_FILE


#include <curl/curl.h>

#define DO_NOT_INCLUDE_WRITE_DATA

#include "curlinterface.h"
#include "httpresponse.h"

namespace RainbruRPG {
  namespace Network {
    namespace Ident {


      /** A class used to get a file with CURL library
        *
	*
	*/
      class CurlGetFile : public CurlInterface{
      public:
	virtual ~CurlGetFile();
	virtual bool perform();

      protected:
	virtual bool controlBefore ();
	virtual bool controlAfter ();
	bool writeToFile();
      };
    }
  }
}


#endif // CURL_GET_FILE

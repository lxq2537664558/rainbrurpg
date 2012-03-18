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

/** \file curlfiletoxml.h
  * Defines a class to get a file from curl and pass it to TinyXml
  *
  * Modifications :
  * - 26 mar 2009 : Now using gettext
  * - 16 jan 2009 : Adding a constructor initializer for the doc pointer
  * - 29 jul 2007 : getXMLTextFromName is now implemented here
  *
  */

#ifndef CURL_FILE_TO_XML
#define CURL_FILE_TO_XML

#include "CurlImport.hpp"
#include "CurlGetFile.hpp"
#include "RainbruDef.hpp" // For the gettext stuff

// Forward declarations
class TiXmlDocument;
class TiXmlElement;
// End of forward declarations

namespace RainbruRPG {
  namespace Network {
    namespace Ident {


      /** A class used to get a file and passed it on TinyXml 
        * Document
	*
	*/
      class CurlFileToXml : public CurlGetFile{
      public:
	CurlFileToXml();
	~CurlFileToXml();

	virtual bool perform();
	TiXmlDocument* getXmlDocument();

      protected:
	virtual bool controlBefore ();
	virtual bool controlAfter ();

	bool fileToxml();
 	const char* getXMLTextFromName(TiXmlElement*, const char*);

     private:
	/** The TinyXML document instance */
	TiXmlDocument *doc;
      };
    }
  }
}



#endif //CURL_FILE_TO_XML


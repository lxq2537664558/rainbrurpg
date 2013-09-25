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
 * - 02 mar 2007 : remove an #inchude "tplayerlist.h"
 */

#ifndef XML_PERSO_LIST_H
#define XML_PERSO_LIST_H

#include <iostream>
#include <string>
#include <list>
#include "tinyxml.h"
#include "loadbmp.h"

#include "tnotelist.h"
#include "xmltimestamp.h"

#include "tidentreturn.h"
#include "logger.h"
#include "curlfiletoxml.h"
#include "globaluri.h"

using namespace std;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Network {


      /** Provides an interface to the website-side character list
        *
	* It uses CurlFileToXml to et the character list and tinyxml to
	* reading it.
	*/
      class xmlPersoList{
      public:
	xmlPersoList();
	~xmlPersoList();

	bool refresh();
	const char* getNextId();

      private:
	void loadDocument(CurlFileToXml*);

	const char* getXMLTextFromName(TiXmlElement*, const char*);

	/** The global xml document pointer */
	TiXmlDocument *doc;
	/** A global pointer to the \c PlayerList xml node */
	TiXmlElement *root;

	/** Says if the document was correctly or not */
	bool correctlyLoaded;
      };

  }
}


#endif // XML_PERSO_LIST_H

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

/** \file xmlattributelist.h
  * Declares a class used to read the XML file of the attribute list
  *
  * Modifications :
  * - 28 apr 2009 : Using gettext compliant string
  * - 14 jan 2009 : refresh() now uses LOGCAT instead of a std::cout
  * - 11 aug 2008 : Single file documentation
  * - 02 mar 2007 : remove an <code>include "tplayerlist.h"</code>
  *
  */

#ifndef XML_ATTRBIBUTE_LIST_H
#define XML_ATTRBIBUTE_LIST_H

#include <iostream>
#include <string>
#include <list>
#include "tinyxml.h"
#include "LoadBmp.hpp"

#include "NoteList.hpp"
#include "xmltimestamp.h"

#include "tidentreturn.h"
#include "Logger.hpp"
#include "CurlFileToXml.hpp"
#include "GlobalUri.hpp"
#include "AttributeModifierList.hpp"

#include "RainbruDef.hpp" // For the gettext stuff

using namespace std;
using namespace RainbruRPG::Gui;

namespace RainbruRPG{
  namespace Network {
    namespace Ident {


      /** An attribute like it appears in the server-side XML file
        *
	*/
      struct tAttributeListItem {
	const char* name;     //!< The name of the attribute
	const char* cat;      //!< The category of this attribute
	const char* type;     //!< The type
 	const char* param1;   //!< The first parameter
 	const char* param2;   //!< The second parameter
 	const char* desc;     //!< The description
	AttributeModifierList modList; //!< The list of attributes's modifiers
     };

      /** A stl list of tAttributeListItem
        *
	*/
      typedef std::list<tAttributeListItem*> tAttributeList;

      /** Read the XML file of the attribute list
        *
	* It uses TinyXML to deal with the file.
	*/
      class xmlAttributeList : public CurlFileToXml{
      public:
	xmlAttributeList();
	~xmlAttributeList();

	tAttributeList* getAttributeList();


	tAttributeListItem* getAttribute(const char*);
	bool refresh();

      private:
	bool loadDocument(CurlFileToXml*);

	/** The global xml document pointer */
	TiXmlDocument *doc;
	/** A global pointer to the \c PlayerList xml node */
	TiXmlElement *root;

	/** Says if the document was correctly or not */
	bool correctlyLoaded;
      };

    }
  }
}


#endif // XML_ATTRBIBUTE_LIST_H

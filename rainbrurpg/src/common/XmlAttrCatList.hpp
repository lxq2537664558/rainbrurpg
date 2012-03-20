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

/** \file XmlAttrCatList.hpp
  * Declares a class used to read the XML file of the attribute categories list
  *
  * Modifications :
  * - 25 apr 2009 : Now uses gettext compliant strings
  * - 14 jan 2009 : refresh() now uses LOGCAT instead of a std::cout
  * - 11 aug 2008 : Single file documentation
  * - 01 apr 2007 : Documentation improvement
  * - 02 mar 2007 : remove an <code>include "tplayerlist.h"</code>
  */

#ifndef XML_ATTRB_CAT_LIST_H
#define XML_ATTRB_CAT_LIST_H

#include <iostream>
#include <string>
#include <list>
#include "tinyxml.h"
#include "LoadBmp.hpp"

#include "NoteList.hpp"
#include "XmlTimestamp.hpp"

#include "IdentificationReturn.hpp"
#include "Logger.hpp"
#include "CurlFileToXml.hpp"
#include "GlobalUri.hpp"

#include "RainbruDef.hpp" // For the gettext stuff

using namespace std;
using namespace RainbruRPG::Gui;

namespace RainbruRPG{
  namespace Network {
    namespace Ident {


      /** An attribute categorie like it appears in the server-side XML file
        *
	* It is used by the xmlAttrbCatList class in a STL list called
	* \ref RainbruRPG::Network::Ident::tAttrbCatList "tAttrbCatList".
	*
	* The tab field can have several meaning :
	* - \c Own means this category is drawn in its own tab;
	* - <i>Another tab's name</i> means that this category
	*   is drawn as a part of the named category.
	*
	* Each tAttrbCatListItem defines an attribute category containing
	* several character's attributes.
	*
	* \sa xmlAttrbCatList, tAttrbCatList
	*/
      struct tAttrbCatListItem {
	const char* name;     //!< The name of the category
	const char* desc;     //!< The description of the category
	const char* tab;      //!< The tab function
      };

      /** A stl list of tAttrbCatListItem
        *
	* It is used by the xmlAttrbCatList class to store all character's
	* attributes category found in the admin wabsite.
	*
	*/
      typedef std::list<tAttrbCatListItem*> tAttrbCatList;

      /** Read the XML file of the attribute categories list
        *
	* The character's attributes are grouped into category. As
	* the client GUI is dynamically created and we don't know how
	* many attributes can be drawn, each attribute are categorized.
	*
	* It uses TinyXML to deal with the XML file.
	*
	*/
      class xmlAttrbCatList : public CurlFileToXml{
      public:
	xmlAttrbCatList();
	~xmlAttrbCatList();

	tAttrbCatList* getAttrbCatList();

	tAttrbCatListItem* getAttrbCat(const char*);
	bool refresh();

      private:
	void loadDocument(CurlFileToXml*);

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


#endif //XML_ATTRB_CAT_LIST_H

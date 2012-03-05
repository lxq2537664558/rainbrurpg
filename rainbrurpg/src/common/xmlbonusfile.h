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

/** \file xmlbonusfile.h
  * Declares a BonusFile choice
  *
  * Modifications :
  * - 28 apr 2009 : Strings gettextized
  * - 14 jan 2009 : refresh() now uses LOGCAT instead of a std::cout
  * - 11 aug 2008 : Single file documentation
  * - 02 mar 2007 : remove an <code>include "tplayerlist.h"</code>
  *
  */

#ifndef XML_BONUS_FILE_H
#define XML_BONUS_FILE_H

#include <iostream>
#include <string>
#include <list>
#include "tinyxml.h"
#include "LoadBmp.hpp"

#include "tnotelist.h"
#include "xmltimestamp.h"

#include "tidentreturn.h"
#include "Logger.hpp"
#include "CurlFileToXml.hpp"
#include "GlobalUri.hpp"

#include "rainbrudef.h" // For the gettext stuff

using namespace std;
using namespace RainbruRPG::Gui;

namespace RainbruRPG{
  namespace Network {
    namespace Ident {


      /** A BonusFile choice like it appears in the server-side XML file
        *
	*/
      struct tBonusFileChoiceListItem {
	const char* name;     //!< The name of the choice
 	const char* desc;      //!< The tab function
     };

      /** A modifier like it appears in the server-side XML file
        *
	*/
      struct tBonusModifierListItem{
	const char* attrb;     //!< The attribute it modifies
 	const char* mod;      //!< The modifier value

      };

      /** A stl list of tAttrbCatListItem
        *
	*/
      typedef std::list<tBonusFileChoiceListItem*> tBonusFileChoiceList;

      /** A stl list of tBonusModifierListItem
        *
	*/
      typedef std::list<tBonusModifierListItem*> tBonusModifierList;

      /** Read a Bonus XML file
        *
	* It is different from the xmlBonusFileList. The xmlBonusFileList keep
	* all the BonusFile with a string identifier and a description.
	*
	* It uses TinyXML to deal with the file.
	*/
      class xmlBonusFile : public CurlFileToXml{
      public:
	xmlBonusFile(std::string);
	~xmlBonusFile();

	tBonusFileChoiceList* getChoiceList();
	tBonusModifierList* getModifierList(const char*);
	bool refresh();

      private:
	bool loadDocument(CurlFileToXml*);

	tBonusModifierList* makeModifierList(TiXmlElement*);
	/** The global xml document pointer */
	TiXmlDocument *doc;
	/** A global pointer to the \c PlayerList xml node */
	TiXmlElement *root;

	/** Says if the document was correctly or not */
	bool correctlyLoaded;
	/** The filename of the bonus file */
	std::string filename;
      };

    }
  }
}


#endif // XML_BONUS_FILE_H

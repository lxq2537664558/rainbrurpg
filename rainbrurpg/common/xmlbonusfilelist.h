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

/** \file xmlbonusfilelist.h
  * Declares a class that read a BonusFile XML list
  *
  * Modifications :
  * - 11 aug 2008 : Single file documentation
  * - 02 mar 2007 : remove an <code>include "tplayerlist.h"</code>
  */

#ifndef XML_BONUS_FILE_LIST_H
#define XML_BONUS_FILE_LIST_H

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
using namespace RainbruRPG::Gui;

namespace RainbruRPG{
  namespace Network {
    namespace Ident {


      /** An BonusFile like it appears in the server-side XML file
        *
	* This structure defines an entry in the tBonusFileList, which is 
	* used by the xmlBonusFileList class. I defines a BonusFile
	* header, not its content.
	* 
	* To have the content of a BonusFile, see xmlBonusFile.
	*
	*/
      struct tBonusFileListItem {
	const char* name;         //!< The name of the entry
	const char* filename;     //!< The filename of the xmlBonusFile
	const char* desc;         //!< The description of the entry
     };

      /** A stl list of tBonusFileListItem
        *
	* It is used by the xmlBonusFileList class to make a list of
	* available BonusFile.
	*
	* To have the content of a BonusFile, see xmlBonusFile.
	*
	*/
      typedef std::list<tBonusFileListItem*> tBonusFileList;

      /** Read a BonusFile XML list
        *
	* It is different from the xmlBonusFile. The xmlBonusFile read the
	* BonusFiles and make a list of choice. Here, we make a list of
	* available BonusFile.
	*
	* It uses TinyXML to deal with the xml file.
	*
	*/
      class xmlBonusFileList: public CurlFileToXml{
      public:
	xmlBonusFileList();
	~xmlBonusFileList();

	tBonusFileList* getBonusFileList();

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


#endif // XML_BONUS_FILE_LIST_H

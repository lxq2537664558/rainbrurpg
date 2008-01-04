/*
 *  Copyright 2006-2008 Jerome PASQUIER
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
 * - 19 jul 2007 : Implements a real perso list
 * - 02 mar 2007 : remove an #include "tplayerlist.h"
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

      /** A perso like it appears in the \c persos.xml file
        *
	* This structure is used in tPersoListItem.
	*
	*/
      typedef struct{
	const char* persoId;  //!< The perso Id
	const char* creation; //!< The perso creation timestamp
      }tPersoSubListItem;

      /** A STL list of tPersoSubListItem */
      typedef std::list<tPersoSubListItem*> tPersoSubList;

      /** A perso like it appears in the persos.xml file
        *
	* We keep the name of the player and a list of perso ID that
	* this player own.
	*
	*/
      typedef struct{
	const char* name;         //!< The name of the account that 
	                          //!< created these persos
	tPersoSubList persoList;  //!< The list of persos' ID
      }tPersoListItem;

      /** A STL list of tPersoListItem */
      typedef std::list<tPersoListItem*> tPersoList;

      /** Provides an interface to the website-side character list
        *
	* It uses CurlFileToXml to et the character list and tinyxml to
	* reading it.
	*/
      class xmlPersoList: public CurlFileToXml{
      public:
	xmlPersoList();
	~xmlPersoList();

	bool refresh();
	const char* getNextId();

	tPersoList* getPersoList();
	tPersoListItem* getAccountByName(const std::string&);

      private:
	void loadDocument(CurlFileToXml*);
	void feedPersoList(TiXmlElement*, tPersoListItem*);


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

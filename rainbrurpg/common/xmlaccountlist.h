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

/** \file xmlaccountlist.h
  * Declares a class used to read XML accounts file
  *
  * Modifications :
  * - 11 aug 2008 : Single file documentation
  * - 03 mar 2007 : Fix a blacklist status error
  * - 02 mar 2007 : renamed xmlaccountlist (was xmlplayerlist before)
  *         
  */

#ifndef XML_PLAYER_LIST_H
#define XML_PLAYER_LIST_H

#include <iostream>
#include <string>
#include <list>
#include "tinyxml.h"
#include "loadbmp.h"

#include "taccountlist.h"
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

      /** The return type of the addAccount() function
        *
	*/
      enum tAddAccountReturn{
	APR_CREATED,      //!< The player is successfully created
	APR_EXISTS,       //!< The player already exists
	APR_UNKNOWN,      //!< An unknown error occured
	APR_INVALID_MAIL, //!< The email is empty or invalid
	APR_EXISTING_MAIL //!< The mail adress is already in use
      };

      /** Read the XML file of the Account list
        *
	* If the xml file is modified (account added or removed) do
	* not forget to call the refresh() function.
	*
	* It provides a blacklist : each player can be placed in this
	* list to tell he can not play anymore. It can be an ultime
	* sanction when I saw the player can't stand the game's rules.
	*
	* Some notes can be added to a player. A note has a title and
	* a text. This feature is presented like a notepad, the notes
	* can be added, modified and definitively deleted.
	*
	* It uses TinyXML to deal with the file.
	*/
      class xmlAccountList : public CurlFileToXml{
      public:
	xmlAccountList();
	~xmlAccountList();

	RainbruRPG::Gui::tAccountList* getAccountList();
	RainbruRPG::Gui::tAccountListItem* getAccount(const char*);
	tNoteList* getAccountNoteList( const char* );
	bool isMailConfirmed(const char*);
	bool isAccountExisting(const char*);
	bool isMailExisting(const char*);
	bool refresh();

      private:
	bool isAccountNoteExisting(const char*, const char*);
	bool isValidMail(const char*);

	void loadDocument(CurlFileToXml*);

	/** The global xml document pointer */
	TiXmlDocument *doc;
	/** A global pointer to the \c AccountList xml node */
	TiXmlElement *root;

	/** Says if the document was correctly or not */
	bool correctlyLoaded;
      };

    }
  }
}


#endif // XML_PLAYER_LIST_H

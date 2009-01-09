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

/** \file taccountlist.h
  * Declares the account list as it can be found in administartion site
  *
  * Modifications :
  * - 11 aug 2008 : Single file documentation
  *
  */

#ifndef T_PLAYER_LIST_H
#define T_PLAYER_LIST_H

#include <string>
#include <list>

namespace RainbruRPG{
    namespace Gui{

      /** An account like it appears in the server-side XML file
        *
	* The validationId value is sent in the mail you
	* received when you create an account. This Id is used
	* in the confirmation form.
	*
	* The EMail is not validated if confirm is empty.
	*
	*/
      struct tAccountListItem {
	const char* name;     //!< The connection name of the player
	std::string creation; //!< The date of creation
	const char* password; //!< The password of this player
	bool blacklist;       //!< Is this player in blacklist
	const char* mail;     //!< The mail adress of the player
	std::string confirm;  //!< The date of confirmation of the
			      //   mail adress
        std::string validationId; //!< The ID used in validation mail
      };

      /** A STL list of tPlayerListItem
        *
	* This list is used to create an account list. You can
	* retrieve one by using xmlAccountList.
	*
	*/
      typedef std::list<tAccountListItem*> tAccountList;

    }
}

#endif // T_PLAYER_LIST_H

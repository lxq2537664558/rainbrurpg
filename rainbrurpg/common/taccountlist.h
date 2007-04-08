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

#ifndef T_PLAYER_LIST_H
#define T_PLAYER_LIST_H

#include <string>

namespace RainbruRPG{
    namespace Gui{

      /** An account like it appears in the server-side XML file
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
      };

      /** A stl list of tPlayerListItem
        *
	*/
      typedef std::list<tAccountListItem*> tAccountList;

    }
}

#endif // T_PLAYER_LIST_H

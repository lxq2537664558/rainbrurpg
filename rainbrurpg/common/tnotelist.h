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

/** \file tnotelist.h
  * Declares a player's notepad object and a list of them
  *
  * Modifications :
  * - 11 aug 2008 : Single file documentation
  * - 02 jan 2008 : GNU header added
  *
  */ 

#ifndef T_NOTE_LIST_H
#define T_NOTE_LIST_H

#include <list>

using namespace std;

namespace RainbruRPG{
    namespace Gui{

      /** It is a player's notepad object
       *
       */
      struct tNoteListItem{
	const char* title; //!< The title of the note
	const char* text;  //!< The text of the note
      };

      /** A STL list of notepad item
        *
	*/
      typedef std::list<tNoteListItem*> tNoteList;

    }
}
#endif // T_NOTE_LIST_H

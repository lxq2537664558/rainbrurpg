/*
 *  Copyright 2006 Jerome PASQUIER
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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */
#ifndef PLAYER_NOTEPAD
#define PLAYER_NOTEPAD

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/fl_ask.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Hold_Browser.H>

#include <string>

#include "logger.h"
#include "xmlplayerlist.h"
#include "tnotelist.h"

using namespace std;

namespace RainbruRPG{
    namespace Gui{
      /** The fltk dialog providing a player notepad
        *
	* The notepad is open only for a player. The player's name is
	* in the notepad's window title bar.
	*
	* To add a title, enter a title and the add button will be activated.
	* \image html notepad1.png
	*
	*/
      class PlayerNotePad : public Fl_Window {
      public:
	PlayerNotePad(const char*);
	~PlayerNotePad();

      private:
	void loadNoteList();
	void showNote(const char*);
	void refresh();
	void refreshKeep();
	void showNoneNote();

	static void cbClose(Fl_Widget *w, void *f);
	inline void i_cbClose();

	static void cbAddNote(Fl_Widget *w, void *f);
	inline void i_cbAddNote();

	static void cbDelNote(Fl_Widget *w, void *f);
	inline void i_cbDelNote();

	static void cbSaveNote(Fl_Widget *w, void *f);
	inline void i_cbSaveNote();

	static void cbTitleChange(Fl_Widget *w, void *f);
	inline void i_cbTitleChange();

	static void cbTextChange(Fl_Widget *w, void *f);
	inline void i_cbTextChange();

	static void cbNoteListe(Fl_Widget *w, void *f);
	inline void i_cbNoteListe();

	/** The input widget used to modify the note's title */
	Fl_Input* noteTitle;
	/** The add button */
	Fl_Button* addBtn;
	/** The save button */
	Fl_Button* saveBtn;
	/** The delete button */
	Fl_Button* delBtn;
	/** The input widget used to modify the note's text */
	Fl_Multiline_Input* noteText;
	/**  The player's title list used to select which note to work
	  *  with 
	  */
	Fl_Hold_Browser* hbNoteList;

	/** The player's name the constructor is called with */
	const char* playerName;

	/** I use the unmodified title to know wich note i must
	  * save. If the title is changed, i test with this one.
	  */
	const char* modifiedNoteTitle;

	/** The STL list of player's note */
	tNoteList* noteList;

	/** If true, we are in an existing note so if we modify, we
	  * can activate the save button. If false, we have not
	  * selected a note so it is a new note : the add button is
	  * activated
	  */
	bool existingNote;
      };

  }
}

#endif // PLAYER_NOTEPAD

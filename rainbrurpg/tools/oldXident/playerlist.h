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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */
#ifndef PLAYER_LIST
#define PLAYER_LIST

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Multiline_Output.H>
#include <list>
#include <logger.h>

#include <xmlplayerlist.h>
#include <curlplayerdelete.h>

#include "addplayer.h"
#include "tplayerlist.h"
#include "playernotepad.h"
#include "showcurlerror.h"

using namespace std;

class AddPlayer;

namespace RainbruRPG{
    namespace Gui{

      /** The fltk playerlist panel
        *
	* It creates a panel to work on players in fltk
	* environment. It shows a player's name list that can be
	* selected.
	*
	* The player list if none player is selected
	* \image html playerlist1.png
	*
	* If we select a player
	* \image html playerlist2.png
	*/
      class PlayerList : public Fl_Group {
      public:
	PlayerList(int, int, int, int);
	~PlayerList();

	void refresh();
	void refreshKeep();

      private:
	static void cbAddPlayer(Fl_Widget *w, void *f);
	inline void i_cbAddPlayer();

	static void cbDelPlayer(Fl_Widget *w, void *f);
	inline void i_cbDelPlayer();

	static void cbShowPlayer(Fl_Widget *w, void *f);
	inline void i_cbShowPlayer();

	static void cbBlacklist(Fl_Widget *w, void *f);
	inline void i_cbBlacklist();

	static void cbNotepad(Fl_Widget *w, void *f);
	inline void i_cbNotepad();

	static void cbConfirm(Fl_Widget *w, void *f);
	inline void i_cbConfirm();

	void loadPlayerList();
	void showPlayer(tPlayerListItem*);
	void showNonePlayer();

	/** The fltk list widget used to store the player's name */
	Fl_Hold_Browser *hbList;

	/** The fltk output widget used to print the blacklist status
	  * of the selected player
	  */
	Fl_Output* floBlacklist;

	/** The tlk output widget used to print the creation date of
	  * the player 
	  */
	Fl_Output* floCreationDate;
	/** The tlk output widget used to print the mail adress of
	  * the player 
	  */
	Fl_Output* floMail;

	/** The tlk output widget used to print the date of confirmation of
	  * the mail adresse the player 
	  */
	Fl_Output* floMailConfirmation;

	/** The fltk output widget used to print the password hashsum status
	  * of the selected player
	  */
	Fl_Multiline_Output* floPwdHash;
	/** The \c delete status */
	Fl_Button* delBtn;
	/** The password button */
	Fl_Button* pwdBtn;
	/** The blacklist button */
	Fl_Button* blkBtn;
	/** The notpad button */
	Fl_Button* notBtn;
	/** The mail adress confirmation button */
	Fl_Button* confirmBtn;
	/** The locking messager */
	Fl_Group* flgFlag;

	/** A global pointer to the AddPlayer fltk dialog */
	AddPlayer *ap;
	/** A global pointer to the player list */
	tPlayerList* pl;
      };

  }
}

#endif // PLAYER_LIST


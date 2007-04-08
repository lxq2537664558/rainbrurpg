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
#ifndef ADD_PLAYER_WINDOW
#define ADD_PLAYER_WINDOW

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/fl_ask.H>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <logger.h>

#include <curlplayeradd.h>
#include <xmlplayerlist.h>
#include <hashpassword.h>

#include "showcurlerror.h"


using namespace std;
using namespace RainbruRPG::Network::Ident;


namespace RainbruRPG{
    namespace Gui{

      class PlayerList;

      /** A dialog used to create a new player
        *
	* \image html addplayer1.png
	*
	* The only field to feed is the name of the player, the
	* password can not be chosen, it is rolled randomly. The \c
	* roll button can roll a new password.
	*
	* The name of the player must contains at least 4 letters and
	* must be unique.
	*/
      class AddPlayer : public Fl_Window {
      public:
	AddPlayer(PlayerList*);
	~AddPlayer();

	void roll();

      private:
	static void cbRoll(Fl_Widget *w, void *f);
	inline void i_cbRoll();

	static void cbCancel(Fl_Widget *w, void *f);
	inline void i_cbCancel();

	static void cbOk(Fl_Widget *w, void *f);
	inline void i_cbOk();

	int random(int);
	void razDialog();

	/** The input widget used to enter the new player's name */
	Fl_Input* name;
	/** The input widget used to enter the new player's mail adress */
	Fl_Input* mail;
	/** The output widget used to show the rolled password */
	Fl_Output* password;
	/** A string used for the password generation */
	string cars;
	/** I keep it to do a refresh */
	PlayerList* playerList;
      };

  }
}

#endif // ADD_PLAYER_WINDOW

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

#include "addplayer.h"

#include "playerlist.h"


/** The default constructor
  *
  * The parameter must be no-NULL because it is used to refresh the
  * player list.
  *
  * \param pl The not NULL instance of PlayerList calling this dialog.
  */
RainbruRPG::Gui::AddPlayer::AddPlayer(PlayerList* pl)
                          :Fl_Window( 400, 300, "Create a player") {

  playerList=pl;

  srand( (unsigned) time( NULL ));
  cars="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    name =new Fl_Input( 100, 20, 100, 30, "Name");
    password =new Fl_Output( 100, 60, 100, 30, "Password");
    mail =new Fl_Input( 100, 100, 250, 30, "Mail adress");

    Fl_Button* cancelBtn = new Fl_Button( 10, 260, 100, 30, "Cancel" );
    Fl_Button* rollBtn = new Fl_Button( 200-55, 260, 100, 30, "Roll" );
    Fl_Button* okBtn = new Fl_Button( 400-110, 260, 100, 30, "OK" );

  end();

  cancelBtn->callback(cbCancel, this);
  rollBtn->callback(cbRoll, this);
  okBtn->callback(cbOk, this);
  this->set_modal();

  this->show();
  roll();
}

/** The default destructor 
  *
  */
RainbruRPG::Gui::AddPlayer::~AddPlayer(){
  name       =NULL;
  password   =NULL;
  playerList =NULL;
}

/** The static callback for the note's text multiline input
  *
  * It simply calls the i_cbRoll() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::AddPlayer::cbRoll(Fl_Widget *w, void *f){
  ( (AddPlayer*)f )->i_cbRoll();
}

/** The callback of the roll button
  *
  * It simply calls the roll() method.
  */
void RainbruRPG::Gui::AddPlayer::i_cbRoll(){
  roll();
}

/** The static callback for the note's text multiline input
  *
  * It simply calls the i_cbCancel() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::AddPlayer::cbCancel(Fl_Widget *w, void *f){
  ( (AddPlayer*)f )->i_cbCancel();
}

/** The callback of the cancel button
  *
  * It calls the razDialog() and the hide() methods.
  */
void RainbruRPG::Gui::AddPlayer::i_cbCancel(){
  LOGI("Hidding AddPlayer dialog");
  this->razDialog();
  this->hide();
}

/** The static callback for the note's text multiline input
  *
  * It simply calls the i_cbOk() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::AddPlayer::cbOk(Fl_Widget *w, void *f){
  ( (AddPlayer*)f )->i_cbOk();
}

/** The callback of the OK button
  *
  * It tests if the name has at least 4 character and create the
  * player with xmlPlayerList. If the name already exists, it can not
  * create it.
  */
void RainbruRPG::Gui::AddPlayer::i_cbOk(){
  CurlPlayerAdd tpa;
  tpa.setPostedData("name", name->value());
  tpa.setPostedPwd("pwd", password->value());
  tpa.setPostedData("mail", mail->value());

  bool success=tpa.perform();

  if (!success)
    ShowCurlError::showError(&tpa);

  playerList->refresh();
  this->hide();
}

/** Randomly generate a new password
  *
  * I use the cars string, initialized in the constructor with letters
  * and numbers. I randomly take a character in the cars string and
  * concatenate them to obtain a string of 8 random charachers. It
  * uses the random(int) function to get a random integer.
  *
  */
void RainbruRPG::Gui::AddPlayer::roll(){
  // We take a random number between 0 and cars.lenght()-1

  string mdp;

  for (int j=0; j<8; j++){
    int i=random(cars.length());
    char c = cars[i];
    mdp+=c;
  }
  password->value( mdp.c_str() );
}

/** Returns a random integer between 0 and \c max
  *
  * \param max the upper limit of the random number.
  * \return An integer between 0 and the integer parameter.
  */
int RainbruRPG::Gui::AddPlayer::random(int max){
  int a=(int) ((float)max * (float)rand() / (float)RAND_MAX);
  return a;
}

/** Make the dialog empty
  * 
  */
void RainbruRPG::Gui::AddPlayer::razDialog(){
  name->value("");
  mail->value("");
}

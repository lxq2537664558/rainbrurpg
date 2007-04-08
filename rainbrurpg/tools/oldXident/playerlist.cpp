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
#include "playerlist.h"

/** The default sized constructor of the player list
  *
  * This class is derived from a fltk Fl_Group. 
  *
  * \param x The x position of the player list fltk group
  * \param y The y position of the player list fltk group
  * \param w The width of the player list fltk group
  * \param h The height of the player list fltk group
  */
RainbruRPG::Gui::PlayerList::PlayerList(int x, int y, int w, int h)
                    :Fl_Group(x, y, w, h, "Player list") {

    this->box(FL_SHADOW_BOX);
  
    hbList=new Fl_Hold_Browser(x+10, y+10, 200, h-20 );
    
    floBlacklist=new Fl_Output(x+320, y+10, 150, 20, "BlackList");
    floCreationDate=new Fl_Output( x+320, y+30, 250, 20, "Creation date");
    floPwdHash=new Fl_Multiline_Output (x+320, y+50, 320, 20, "Password");
    floMail=new Fl_Output( x+320, y+70, 250, 20, "Mail adress");
    floMailConfirmation=new Fl_Output( x+400, y+90, 250, 20, 
					"Mail confirmation's date");

    confirmBtn= new Fl_Button(x+320, y+110, 300, 30, 
			      "Mail adress confirmation is done" );

    Fl_Button *addBtn= new Fl_Button(x+w-110, y+10, 100, 30, "Add" );
    delBtn= new Fl_Button(x+w-110, y+10+35, 100, 30, "Delete" );
    pwdBtn= new Fl_Button(x+w-110, y+10+70, 100, 30, "New pwd" );
    blkBtn= new Fl_Button(x+w-110, y+10+105, 100, 30, "Blacklist" );
    notBtn= new Fl_Button(x+w-110, y+10+165, 100, 30, "Notepad" );

  this->end();
  
  delBtn->deactivate();
  pwdBtn->deactivate();
  blkBtn->deactivate();
  notBtn->deactivate();
  confirmBtn->deactivate();

  addBtn->callback(cbAddPlayer, this);
  delBtn->callback(cbDelPlayer, this);
  hbList->callback(cbShowPlayer, this);
  blkBtn->callback(cbBlacklist, this);
  notBtn->callback(cbNotepad, this);
  confirmBtn->callback(cbConfirm, this);

  loadPlayerList();
}

/** The default destructor
  *
  */
RainbruRPG::Gui::PlayerList::~PlayerList(){
  hbList=NULL;

  floBlacklist=NULL;
  floPwdHash=NULL;
  floCreationDate=NULL;
  floMail=NULL;
  floMailConfirmation=NULL;

  delBtn=NULL;
  pwdBtn=NULL;
  blkBtn=NULL;
  notBtn=NULL;
  ap=NULL;
  pl=NULL;

  if (ap!=NULL){
    delete ap;
    ap=NULL;
  }
  if (pl!=NULL){
    delete pl;
    pl=NULL;
  }
}

/** The static callback for the add player button
  *
  * It simply calls the i_cbAddPlayer() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerList::cbAddPlayer(Fl_Widget *w, void *f){
  ( (PlayerList*)f )->i_cbAddPlayer();
}

/** The inline callback for the add player button
  *
  * It instanciates the AddPlayer class if it is equal to \c
  * NULL. If it already exists, it simply shows it and call roll() again.
  *
  */
void RainbruRPG::Gui::PlayerList::i_cbAddPlayer(){
  if (ap==NULL){
    ap=new AddPlayer( this );
  }
  else{
    ap->show();
    ap->roll();
  }
}

/** Load the player list and feed the player's name list
  *
  * It uses xmlPlayerList to get the player list. After a call to this
  * method, the pl tPlayerList pointer should contains the player list.
  */
void RainbruRPG::Gui::PlayerList::loadPlayerList(){
  tPlayerList::const_iterator iter;
 
  pl= new tPlayerList();

  xmlPlayerList xmlPl;
  pl=xmlPl.getPlayerList();
  
  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){
      hbList->add( (*iter)->name );
    }
  }
}

/** The static callback for the player name Hold_Browser
  *
  * It simply calls the i_cbShowPlayer() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerList::cbShowPlayer(Fl_Widget *w, void *f){
  ( (PlayerList*)f )->i_cbShowPlayer();
}

/** Call the showPlayer method for the currently selected player
  *
  */
void RainbruRPG::Gui::PlayerList::i_cbShowPlayer(){
  tPlayerList::const_iterator iter;

  showNonePlayer();

  // get the selected item
  int sel=hbList->value();


  // An item is selected
  if (sel>0){
    //get the text of this item
    const char* str= hbList->text(sel);
    

    // Iterate through the tPlayerList
    if (pl){
      for (iter=pl->begin(); iter != pl->end(); iter++){
	const char* tname=(*iter)->name;
	// If the two names are the same
	if(strcmp(str, tname)==0){
	  showPlayer((*iter));
	}
      }
    }
  }
  else // None player is selected
    showNonePlayer();

}

/** Feed the fltk display widgets with the player's information
  *
  * The player passed in parameter will be used to feed the form.
  *
  * \param i The player to show.
  *
  */
void RainbruRPG::Gui::PlayerList::showPlayer(tPlayerListItem* i){

  if (i->blacklist)
    floBlacklist->value("yes");
  else
    floBlacklist->value("no");

  floPwdHash->value(i->password);
  floCreationDate->value(i->creation.c_str());
  floMail->value(i->mail);
  floMailConfirmation->value(i->confirm.c_str());
  // The confirmation button

  xmlPlayerList xmlPl;
  if(!xmlPl.isMailConfirmed( i->name ))
    confirmBtn->activate();

  // The other buttons
  delBtn->activate();
  pwdBtn->activate();
  blkBtn->activate();
  notBtn->activate();
}

/** Feed the form with empty values
  *
  * Reset the fltk widgets as if no player was shown.
  *
  */
void RainbruRPG::Gui::PlayerList::showNonePlayer(){
  floBlacklist->value("");
  floPwdHash->value("");
  floCreationDate->value("");
  floMail->value("");
  floMailConfirmation->value("");

  delBtn->deactivate();
  pwdBtn->deactivate();
  blkBtn->deactivate();
  notBtn->deactivate();
  confirmBtn->deactivate();

}

/** The static callback for the delete button
  *
  * It simply calls the i_cbDelPlayer() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerList::cbDelPlayer(Fl_Widget *w, void *f){
  ( (PlayerList*)f )->i_cbDelPlayer();
}

/** Delete the currently selected player
  *
  */
void RainbruRPG::Gui::PlayerList::i_cbDelPlayer(){
  int sel=hbList->value();

  if (sel>0){
    //get the text of this item
    const char* plName= hbList->text(sel);

    // Delete the player through curl
    CurlPlayerDelete tpa;
    tpa.setPostedData("name", plName);
    
    bool success=tpa.perform();
    
    if (!success)
      ShowCurlError::showError(&tpa);
    
    this->refresh();

  }
}

/** Refresh the information but do not restore the selected player
  *
  */
void RainbruRPG::Gui::PlayerList::refresh(){
  LOGI("Refresh Playerlist");
  showNonePlayer();
  hbList->clear();
  loadPlayerList();

}

/** The static callback for the blacklist button
  *
  * It simply calls the i_cbBlacklist() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerList::cbBlacklist(Fl_Widget *w, void *f){
  ( (PlayerList*)f )->i_cbBlacklist();
}

/** Toggles the blacklist state of the currently selected player
  * 
  */
void RainbruRPG::Gui::PlayerList::i_cbBlacklist(){

}

/** Refresh the information and keep the selected player selected
  *
  */
void RainbruRPG::Gui::PlayerList::refreshKeep(){
 // store the selected item id
  int sel=hbList->value();

  refresh();

  // restore the stored and shown tiem
  hbList->select(sel);
  i_cbShowPlayer();
}

/** The static callback for the notepad button
  *
  * It simply calls the i_cbNotepad() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerList::cbNotepad(Fl_Widget *w, void *f){
  ( (PlayerList*)f )->i_cbNotepad();
}

/** Shows the notepad of the currently selected player
  *
  */
void RainbruRPG::Gui::PlayerList::i_cbNotepad(){
  LOGI("Player notepad shown");
 // get the selected item
  int sel=hbList->value();

  // An item is selected
  if (sel>0){
    //get the text of this item
    const char* plName= hbList->text(sel);

    PlayerNotePad* plnp=new PlayerNotePad( plName );
  }
}

/** The static callbackfor the mail confirmation button
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  *
  */
void RainbruRPG::Gui::PlayerList::cbConfirm(Fl_Widget *w, void *f){
  ( (PlayerList*)f )->i_cbConfirm();
}

/** The inline callback for the mail confirmation button
  *
  *
  */
void RainbruRPG::Gui::PlayerList::i_cbConfirm(){

}


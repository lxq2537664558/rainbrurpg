
#include "playernotepad.h"

/** A constructor with the playername
  *
  * The player will be added to the window title
  */
RainbruRPG::Gui::PlayerNotePad::PlayerNotePad(const char* plName)
                               :Fl_Window(740,480) {

  string s=plName;
  s+="'s notepad";
  this->label(s.c_str());
  playerName=plName;
  existingNote=false;

    hbNoteList=new Fl_Hold_Browser(10, 10, 250, 430, 
						"Notes List");

    noteTitle= new Fl_Input(270, 10, 450, 20);
    noteText =new Fl_Multiline_Input(270, 40, 450, 400 );

    Fl_Button* closeBtn=new Fl_Button(270, 445,100, 30, "Close");
    addBtn=new Fl_Button(380, 445,100, 30, "Add");
    delBtn=new Fl_Button(490, 445,100, 30, "delete");
    saveBtn=new Fl_Button(600, 445,100, 30, "Save");

  this->end();

  addBtn->deactivate();
  delBtn->deactivate();
  saveBtn->deactivate();

  noteTitle->when(FL_WHEN_CHANGED);
  noteTitle->callback( cbTitleChange, this );

  noteText->when(FL_WHEN_CHANGED);
  noteText->callback( cbTextChange, this );

  closeBtn->callback( cbClose, this );
  addBtn->callback(cbAddNote, this );
  hbNoteList->callback(cbNoteListe, this );
  delBtn->callback(cbDelNote, this );
  saveBtn->callback(cbSaveNote, this );

  loadNoteList();
  this->show();
}

/** The default destructor
  *
  */
RainbruRPG::Gui::PlayerNotePad::~PlayerNotePad(){
  noteTitle=NULL;
  addBtn=NULL;
  saveBtn=NULL;
  delBtn=NULL;
  noteText=NULL;
  hbNoteList=NULL;
  noteList=NULL;
}

/** The static callback for the close button
  *
  * It simply calls the i_cbClose() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerNotePad::cbClose(Fl_Widget *w, void *f){
  ( (PlayerNotePad*)f )->i_cbClose();
}

/** The callbacl for the close button
  *
  * It calls the hide() fltk function
  *
  */
void RainbruRPG::Gui::PlayerNotePad::i_cbClose(){
  this->hide();
}

/** The static callback for the titleNote input field
  *
  * It simply calls the i_cbTitleChange() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerNotePad::cbTitleChange(Fl_Widget *w, void *f){
  ( (PlayerNotePad*)f )->i_cbTitleChange();
}

/** Activate or deactivatee the Add bouton according to the title emptiness
  *
  */
void RainbruRPG::Gui::PlayerNotePad::i_cbTitleChange(){
  if (existingNote){
      saveBtn->activate();
  }
  else{
    if (strlen(noteTitle->value())>0)
      addBtn->activate();
    else
      addBtn->deactivate();
  }
}

/** The static callback for the add button
  *
  * It simply calls the i_cbAddNote() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerNotePad::cbAddNote(Fl_Widget *w, void *f){
  ( (PlayerNotePad*)f )->i_cbAddNote();
}

/** Add a note to the current player
  *
  * It calls the xmlPlayerList::addPlayerNote() method.
  */
void RainbruRPG::Gui::PlayerNotePad::i_cbAddNote(){

}

/** Loads the note list for this player
  *
  * It calls the xmlPlayerList::getPlayerNoteList() function.
  */
void RainbruRPG::Gui::PlayerNotePad::loadNoteList(){

}

/** The static callback for the note's title list
  *
  * It simply calls the i_cbNoteListe() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerNotePad::cbNoteListe(Fl_Widget *w, void *f){
  ( (PlayerNotePad*)f )->i_cbNoteListe();
}

/** The callback of the note list
  *
  */
void RainbruRPG::Gui::PlayerNotePad::i_cbNoteListe(){
  // get the selected item
  int sel=hbNoteList->value();

  saveBtn->deactivate();

  // An item is selected
  if (sel>0){
    //get the text of this item
    const char* str= hbNoteList->text(sel);
    showNote(str);
    delBtn->activate();
    existingNote=true;
  }
  else{
    showNoneNote();
    delBtn->deactivate();
    existingNote=false;
  }

}

/** Shows a note defined by its title
  *
  * \param noteTitle The title of the note to be shown.
  */
void RainbruRPG::Gui::PlayerNotePad::showNote(const char* noteTitle){
  tNoteList::const_iterator iter;

  if (this->noteList){

    for (iter=noteList->begin(); iter != noteList->end(); iter++){
      if (strcmp((*iter)->title,noteTitle)==0){
	// Keep the original title in case it is changed
	modifiedNoteTitle=(*iter)->title;
	this->noteTitle->value((*iter)->title);
	noteText->value((*iter)->text);
      }
    }
  }
}

/** Refresh the note list
  *
  * It calls showNoneNote(), clears the hbNoteList and loadNoteList().
  *
  */
void RainbruRPG::Gui::PlayerNotePad::refresh(){
  showNoneNote();
  hbNoteList->clear();
  loadNoteList();
}

/** Clears the forms as if no note has been selected
  *
  */
void RainbruRPG::Gui::PlayerNotePad::showNoneNote(){
  noteTitle->value("");
  noteText->value("");

}

/** The static callback for the note's text multiline input
  *
  * It simply calls the i_cbTextChange() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerNotePad::cbTextChange(Fl_Widget *w, void *f){
  ( (PlayerNotePad*)f )->i_cbTextChange();

}

/** The note's text multiline input widget's callback
  *
  * It activates the saveBtn button if existingNote is \c true (we are
  *modifying an existing note).
  */
void RainbruRPG::Gui::PlayerNotePad::i_cbTextChange(){
  if (existingNote){
      saveBtn->activate();
  }
}

/** The static callback for the delete button
  *
  * It simply calls the i_cbDelNote() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerNotePad::cbDelNote(Fl_Widget *w, void *f){
  ( (PlayerNotePad*)f )->i_cbDelNote();
}

/** Delete a paleyer's note after a confirmation dialog
  *
  */
void RainbruRPG::Gui::PlayerNotePad::i_cbDelNote(){

}

/** The static callback for the save button
  *
  * It simply calls the i_cbSaveNote() method.
  *
  * \param w A parameter used internally by fltk
  * \param f A parameter used internally by fltk
  */
void RainbruRPG::Gui::PlayerNotePad::cbSaveNote(Fl_Widget *w, void *f){
  ( (PlayerNotePad*)f )->i_cbSaveNote();
}

/** Save a modified note
  *
  * It simpky calls xmlPlayerList::savePlayerNote().
  */
void RainbruRPG::Gui::PlayerNotePad::i_cbSaveNote(){

}

/** Refresh the list and keep selected the already selected note
  *
  */
void RainbruRPG::Gui::PlayerNotePad::refreshKeep(){
 // store the selected item id
  int sel=hbNoteList->value();

  refresh();

  // restore the stored and shown tiem
  hbNoteList->select(sel);
  i_cbNoteListe();
  hbNoteList->take_focus();
}

/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file languageselector.cpp
  * Implementation of the client's language selector
  *
  *
  */

#include <iostream>

#include "languageselector.h"
#include <Options.hpp>
#include <XmlOptions.hpp>

/** Defines the Fox-toolkit event mapping
  *
  */
FXDEFMAP(RainbruRPG::Gui::LanguageSelector) LanguageSelectorMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LanguageSelector::ID_BUTTON, 
	    RainbruRPG::Gui::LanguageSelector::onNotImplemented),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LanguageSelector::ID_CHANGE_SNAP, 
	    RainbruRPG::Gui::LanguageSelector::onChangeLanguage),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LanguageSelector::ID_BTN_CANCEL, 
	    RainbruRPG::Gui::LanguageSelector::onCancelClicked),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LanguageSelector::ID_BTN_OK, 
	    RainbruRPG::Gui::LanguageSelector::onOkClicked),

};

/** Declares the implementation of the class
  *
  */
FXIMPLEMENT(RainbruRPG::Gui::LanguageSelector,FXDialogBox,
	    LanguageSelectorMap,ARRAYNUMBER(LanguageSelectorMap));


/** Default constructor
  *
  * \param a The current instance of FXApp.
  *
  */
RainbruRPG::Gui::LanguageSelector::LanguageSelector(FXApp * a)
  :FXDialogBox(a,"Language selection"){ 

  // A common width for the Cancel and Ok buttons
  FXint buttonWidth=103;

  // frame construction
  FXVerticalFrame *root = new FXVerticalFrame(this, LAYOUT_FILL_Y|
					      LAYOUT_FIX_HEIGHT);
  root->setHeight(60);

  // The language combo box
  FXComboBox* cbLang=new FXComboBox( root, 24, this, ID_CHANGE_SNAP, 
			    COMBOBOX_STATIC||LAYOUT_FIX_WIDTH|LAYOUT_RIGHT,
				     0, 0, 160 );
  feedComboBox(cbLang);

  // The button frame
  FXHorizontalFrame *frame = new FXHorizontalFrame(root, LAYOUT_FILL_X|LAYOUT_FILL_Y);
  frame->setPadLeft(0);
  frame->setPadRight(0);

  FXButton* btnCancel=new FXButton(frame, "Cancel", NULL, this, 
			  ID_BTN_CANCEL, BUTTON_NORMAL|LAYOUT_FIX_WIDTH);
  btnCancel->setWidth(buttonWidth);

  FXButton* btnOk=new FXButton(frame, "Ok", NULL, this, 
			  ID_BTN_OK, BUTTON_NORMAL|LAYOUT_FIX_WIDTH);
  btnOk->setWidth(buttonWidth);

}


/** Default destructor
  *
  */
RainbruRPG::Gui::LanguageSelector::~LanguageSelector(){
}


/** A method needed by the FOX-toolkit
  *
  */
void RainbruRPG::Gui::LanguageSelector::create(){
  FXDialogBox::create();
  show(PLACEMENT_SCREEN);
}

/** An event receiver used during development
  *
  * The widgets that send a usefull signal that have unimplemented
  * event handler are connected to this to avoid compilation errors.
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LanguageSelector::onNotImplemented(FXObject * o,
							FXSelector s,
							void* v){
  LOGW("This slot is not implemented");
  return 1;

}

/** The language combo box change callback
  *
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LanguageSelector::onChangeLanguage(FXObject *o,
							 FXSelector s,
							 void* v)
{
  LOGI("The language combo box changed");
  return 1;
}


/** The the language combobox with the language list
  *
  * \param cb The combobox to feed
  *
  */
void RainbruRPG::Gui::LanguageSelector::feedComboBox(FXComboBox* cb){
  xmlLanguage l;
  tLanguageList* ll=l.getLanguageList();

  // An empty item
  cb->appendItem("", NULL);


  // Create constant iterator for list.
  tLanguageList::const_iterator iter;
  // Iterate through list and output each element.
  for (iter=ll->begin(); iter != ll->end(); ++iter){
    FXint sel=cb->appendItem((*iter)->getComboText(), (*iter));

    // Select the newly created item if it is the current one (LastUsed)
    if ((*iter)->isCurrent()){
      cb->setCurrentItem(sel);
    }
  }

  // Setting the droplist size
  if (ll->size()>10){
    cb->setNumVisible(10);
  }
  else{
    cb->setNumVisible(ll->size());
  }
}

/** The Cancel button clicked callback
  *
  * Send the ID_CANCEL to this dialog to close it and return \c false.
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LanguageSelector::
onCancelClicked(FXObject *o,FXSelector s,void* v){
  LOGI("Cancel button clicked");
  handle(this,FXSEL(SEL_COMMAND,ID_CANCEL),NULL);
}

/** The OK button clicked callback
  *
  * Send the ID_ACCEPT to this dialog to close it and return \c true.
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LanguageSelector::
onOkClicked(FXObject *o,FXSelector s,void* v){
  LOGI("OK button clicked");
  handle(this,FXSEL(SEL_COMMAND,ID_ACCEPT),NULL);
}



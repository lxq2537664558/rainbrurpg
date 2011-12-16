/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

#include "ercreateperso.h"
#include "screenshotmanager.h"
#include "gscreateperso.h"

#include <sstream>


/** The default constructor
  *
  * It sets choiceSelected to false;
  *
  */
RainbruRPG::Events::erCreatePerso::erCreatePerso(){
  choiceSelected=false;
  isPresel=false;
}

/** The event Receiver main loop
  *
  * \param event The event
  */
bool RainbruRPG::Events::erCreatePerso::OnEvent(SEvent event){

  if (event.EventType == EET_GUI_EVENT){
    s32 id = event.GUIEvent.Caller->getID();
    IGUIEnvironment* env=GameEngine::getSingleton().getIrrlichtGui();
    irr::IrrlichtDevice * device  = GameEngine::getSingleton().
                                    getIrrlichtDevice();


    IGUIElement *root= env->getRootGUIElement();
    if (!root)
      LOGW("Failed to get IGUIEnvironment root element");

    // Mouse events
    switch(event.GUIEvent.EventType){
		  
      /*
	If a button was clicked, it could be one of 'our'
	three buttons. If it is the first, we shut down the engine.
	If it is the second, we create a little window with some 
	text on it. We also add a string to the list box to log
	what happened. And if it is the third button, we create
	a file open dialog, and add also this as string to the list box.
	That's all for the event receiver.
      */
    case EGET_BUTTON_CLICKED:

      if (id == 101){ //Create account bouton
	LOGI("CREATE button has been clicked");

	// Get the user edit box content
	if (root){
	  controlBefore(root);
	}

	return true;
      }
      else if (id == 102){ //roll bouton
	LOGI("ROLL button was clicked");
	roll(root, this);
	return true;
      }
      else if (id == 103){ //cancel bouton
	LOGI("CANCEL creation window button was clicked");
	GameEngine::getSingleton().changeState(ST_PERSO_LIST);
	return true;
      }
      else if (id == 10001){ //OK
	LOGI("OK button was clicked");
	if (controlBefore(root)){
	  if (changeButtonId!=-1){
	    if (winSelect){
	      LOGI("Removing winSelect");
	      winSelect->setVisible(false);
	      winSelect->remove();
	    }
	    
	    IGUIElement* guiE=root->getElementFromId(changeButtonId, true);
	    if (guiE!=0){
	      if (guiE->getType()!= 1){ // WIDGET_TYPE
		LOGW("The changeButtonId is not a button id");
	      }
	      LOGI("The 'change' button caption should have change");
	      cout << "[ercreateperso.cpp::107]listBoxVal=" <<listBoxVal<<endl;
	      stringw valw=StringConv::getSingleton().stow(listBoxVal);
	      this->removePreselectionModidifers();
	      guiE->setText(valw.c_str()); 
	      this->changePersoFormModifier();
	    }
	    else{
	      LOGW("Cannot get the 'change' button : getElementFromId failed");
	    }
	    
	  }
	  else{
	    LOGW("Cannot get the 'change' button : changeButtonId=-1");
	  }
	} // if (controlBefore(root))
	else{
	  LOGW("ControlBefore failed");
	  env->addMessageBox (L"Creation failed", 
			      L"You must make a choice.");

	}
      }
      else if (id == 10002){ //Cancel
	LOGI("CANCEL select window button was clicked");
	if (winSelect){
	  LOGI("Removing winSelect");
	  winSelect->setVisible(false);
	  winSelect->remove();
	}

      }
      else{
	handleBonusFileButton(id, root, this);
      }
      break;

    case EGET_LISTBOX_CHANGED:
      if (id == 10000){ //Choices listbox
	showChoice(event.GUIEvent.Caller);
	return true;
      }
      break;
    }
  }
  
  return false;

}

/** Get the levelGet value
  *
  * \return The levelGet value
  */
int RainbruRPG::Events::erCreatePerso::getLevelGet(){
  return levelGet;
}

/** Get the levelAvail value
  *
  * \return The levelAvail value
  */
int RainbruRPG::Events::erCreatePerso::getLevelAvail(){
  return levelAvail;
}

/** Set the levelGet value
  *
  * \param i The new levelGet value
  */
void RainbruRPG::Events::erCreatePerso::setLevelGet( int i ){
  levelGet=i;
}

/** Set the levelAvail value
  *
  * \param i The new levelAvail value
  */
void RainbruRPG::Events::erCreatePerso::setLevelAvail( int i){
  levelAvail=i;
}


/** Makes some control before creating perso
  *
  * It simply returns the value of choiceSelected.
  *
  * \param root the root IGUIElement as return by 
  *        IGUIEnvironment::getRootGUIElement()
  *
  * \return true if the controls are passed, false it they fail.
  */
bool RainbruRPG::Events::erCreatePerso::controlBefore(IGUIElement* root){
  return choiceSelected;
}

/** Makes a new roll for RandomLvl perso attributes
  *
  * This class is static to get access to thegsCreatePerso::getHandlerList()
  * function.
  *
  * The tThis pointer get access to the current erCreatePerso instance but 
  * none test is done, so if this pointer is NULL, this cause a segfault.
  *
  * \param root The root IGUIElement pointer
  * \param tThis A pointer to the current erCreatePerso instance
  */
void RainbruRPG::Events::erCreatePerso::roll(IGUIElement* root,
					     erCreatePerso* tThis){
  LOGI("Rolling new perso");

  IGUIElement* guiE;
  stringw win;

  int lGet=0;
  int lAvail=0;
  int ran=0;

  AttrbHandlerList* handlerList=gsCreatePerso::getHandlerList();

  AttrbHandlerList::const_iterator iter;
    // Iterate through list and output each element.
    for (iter=handlerList->begin(); iter != handlerList->end(); iter++){
      ran=getRandomInteger(RANDOM_LVL_MIN,RANDOM_LVL_MAX );
      win=StringConv::getSingleton().itow(ran);
      lGet+=ran;
      lAvail+=10;

      if (  (*iter)->type== AT_RANDOM_LVL){
	guiE=root->getElementFromId((*iter)->irrId, true);
	if (guiE)
	  guiE->setText(win.c_str());
	else
	  LOGE("Cannot change AT_RANDOM_LVL text");
      }

    }

  tThis->setLevelGet(lGet);
  tThis->setLevelAvail(lAvail);
  // Get the level get/total static text
  guiE=root->getElementFromId(10000, true);

  ostringstream oss;
  oss << "Levels (get/total available) : ";
  oss << lGet;
  oss << "/";
  oss << lAvail;

  stringw wi=StringConv::getSingleton().stow(oss.str());
  guiE->setText(wi.c_str());
}

/** Get a random integer number between the range
  *
  * \param minRange The returned int will never been inferior to this.
  * \param maxRange The returned int will never been superior to this.
  *
  * \return A random integer number between and including minRange 
  *         and maxRange
  */
int RainbruRPG::Events::erCreatePerso::getRandomInteger(int minRange, 
						      int maxRange ){

  return (rand()%(maxRange-minRange))+minRange;
}


/** Get the tBonusFileListItem of a BonusFile by its name
  *
  * It takes tBonusFileListItem from the BonusFileList class by the param1
  * of the attribute.
  *
  * \param n The name of the BonusFile to get description
  *
  * \return NULL if non was found
  */
tBonusFileListItem* RainbruRPG::Events::erCreatePerso::
getBonusFileDesc(const char* n){
  LOGI("erCreatePerso::getBonusFileDesc");
  tBonusFileListItem* ret;
  bool found=false;

  xmlBonusFileList xmlBfl;

  tBonusFileList* bfl=xmlBfl.getBonusFileList();

  tBonusFileList::const_iterator iter;

  // Iterate through list and output each element.
  for (iter=bfl->begin(); iter != bfl->end(); iter++){
    if (strcmp((*iter)->name, n)==0){
      ret=(*iter);
      found=true;
    }

  }
  if (!found){
    LOGW("Enable to found the BonusFile description");
    cout << "search key " << n << endl;
    return NULL;
  }
  else{
    return ret;
  }
}

/** Show a selected choice
  *
  * Modifies the value of choiceSelected.
  *
  * \param guiE typically the SEvent.GUIEvent.Caller
  *
  */
void RainbruRPG::Events::erCreatePerso::showChoice(gui::IGUIElement* guiE){
  LOGI("A new choice was clicked");

  IGUIListBox* listBox=(IGUIListBox*)guiE;
  if (listBox){
    s32 sel=listBox->getSelected();
    if (sel!=-1){
      choiceSelected=true;
      const wchar_t* swSelCaption=listBox->getListItem(sel);
      stringw temp(swSelCaption);
      listBoxVal=StringConv::getSingleton().wtos(temp);
      const char* selCaption=listBoxVal.c_str();
      stringw swSelDesc=getChoiceDesc(selCaption);
      stChoiceDesc->setText(swSelDesc.c_str());
      this->showChoiceModifiers(selCaption);
    }
    else{
      choiceSelected=false;
    }
  }
  else{
    LOGE("Enable to cast IGUIListBox");
  }
}

/** Get the choice description by the choice name
  *
  * \param name The name of the choice you want the description
  */
stringw RainbruRPG::Events::erCreatePerso::getChoiceDesc(const char* name){
  bool found=false;

  stringw descw=L"";
  tBonusFileChoiceList::const_iterator iter;

  for (iter=choiceList->begin(); iter != choiceList->end(); iter++){
    if (strcmp(name, (*iter)->name)==0){
      descw=StringConv::getSingleton().stow((*iter)->desc);
      found=true;
    }
  }

  if (!found){
    LOGW("Enable to found the choice description");
  }

  return descw;
}

/** Fill the lbModifiersList listbox with choiceName's modifiers 
  *
  *
  *
  * \param choiceName The name of the selected choice
  */
void RainbruRPG::Events::erCreatePerso::
showChoiceModifiers(const char* choiceName){
  LOGI("showChoiceModifiers called");

  ostringstream oss;
  stringw namew;

  lbModifiersList->clear();

  tBonusModifierList* bml= xmlBf->getModifierList(choiceName);

  tBonusModifierList::const_iterator iter;

  for (iter=bml->begin(); iter != bml->end(); iter++){
    oss.str("");
    oss << (*iter)->attrb << "       "<<(*iter)->mod;
    namew=StringConv::getSingleton().stow(oss.str());
    lbModifiersList->addItem(namew.c_str());
  }
}

/** Changes the character creation form modifider
  *
  * In the main form, near the attribute name, is a StaticText
  * that must show the modifier applied to this attribute.
  * 
  * Its color must be green for + and red for -.
  */
void RainbruRPG::Events::erCreatePerso::changePersoFormModifier(){
  LOGI("Calling erCreatePerso::changePersoFormModifier");
  stringw tw;

  // Get the modifiers of the last selected choice
  tBonusModifierList* bml= xmlBf->getModifierList(listBoxVal.c_str());
  tBonusModifierList::const_iterator iterMod;

  AttrbHandlerList* handlerList=gsCreatePerso::getHandlerList();
  AttrbHandlerList::const_iterator iterHa;


  // Iterates thru all the modifier
  for (iterMod=bml->begin(); iterMod != bml->end(); iterMod++){
    // (*iterMod)->attrb is the name of the attribte to modify
    // (*iterMod)->mod is the modifier value


    // Iterate through list of handlerevent
    for (iterHa=handlerList->begin(); iterHa!= handlerList->end(); iterHa++){
      // We must test if it is a RandomLevel
      if ((*iterHa)->type==AT_RANDOM_LVL){
	// Its name is in (*iterHa)->item->name
 	// To add a modifier (*iterHa)->item->modList->addModifier()

	// We have the good attribute
	if (strcmp((*iterHa)->item->name, (*iterMod)->attrb)==0){
	  // We had this modifier
	  (*iterHa)->item->modList.addModifier((*iterMod)->mod);
	  LOGI("Adding a modifier");
	}
	
      }
     }
  }


  // The graphic update
    for (iterHa=handlerList->begin(); iterHa!= handlerList->end(); iterHa++){
      // We must test if it is a RandomLevel
      if ((*iterHa)->type==AT_RANDOM_LVL){
	// Its name is in (*iterHa)->item->name
 	// To add a modifier (*iterHa)->item->modList->getTotal()

	// We have the good attribute
	  // We had this modifier
	  //	  (*iterHa)->item->modList.addModifier((*iterMod)->mod);
	  //	  LOGI("Adding a modifier");

	  //(*iterHa)->id

	  IGUIEnvironment* env=GameEngine::getSingleton().getIrrlichtGui();
	  IGUIElement *root= env->getRootGUIElement();
	  IGUIElement *guiE=root->getElementFromId((*iterHa)->irrId+1000, 
						   true);

	  LOGI("Changing a randomlvl modifier's value");

	  std::string t=(*iterHa)->item->modList.getTotalString();
	  cout << "Value is now " << t << endl;
	  tw=StringConv::getSingleton().stow(t);
	  guiE->setText(tw.c_str());

      }
     }
}

/** Handle the BonusFile button click action
  *
  * If a BonusFile button was clicked, it set changeButtonId to the button 
  * Id and call createChoiceWindow() with a pointer to the corresponding
  * AttrbHandlerListItem.
  *
  * \param id The Irrlicht id of the event caller
  * \param root The Irrlicht root GUI element
  * \param tThis A pointer to this instance.
  *
  * \return \c true if the event is handle.
  */
bool RainbruRPG::Events::erCreatePerso::
handleBonusFileButton(s32 id, IGUIElement* root, erCreatePerso* tThis){
  bool ret=false;
  AttrbHandlerList* handlerList=gsCreatePerso::getHandlerList();

  AttrbHandlerList::const_iterator iter;

  // Iterate through list
  for (iter=handlerList->begin(); iter != handlerList->end(); iter++){
    if ((*iter)->irrId==id){
     if (  (*iter)->type== AT_BONUS_FILE){
       LOGI("A BonusFile button was clicked");
       changeButtonId=id;

       IGUIListBox* lb=tThis->createChoiceWindow((*iter));
       tThis->choicePreselection( id,(*iter), lb);
    }
     ret=true;
    }
  }
  return ret;
}

/** Creates the Choice selection popup window
  *
  * \param h The tPersoAttrbHandler of the BonusFile to show
  *
  * \return The IGUIListBox of all the choice of the BonusFile
  */
IGUIListBox* RainbruRPG::Events::erCreatePerso::
createChoiceWindow(tPersoAttrbHandler* h){
  IGUIEnvironment* env=GameEngine::getSingleton().getIrrlichtGui();

  ostringstream oss;
  oss << h->item->name << " selection";

  tBonusFileListItem* item = this->getBonusFileDesc(h->item->param1);

  // Get the title and the description
  stringw title=StringConv::getSingleton().stow(oss.str());
  stringw wdesc=StringConv::getSingleton().stow(item->desc);

  // Create the window
  winSelect= env->addWindow( rect<s32>( 10,10, 450, 250), true, 
			 	    title.c_str(), 0, -1);


  // create the description static text
  env->addStaticText(wdesc.c_str(), rect<s32>(15,25,435,60), 
			false, true, winSelect );

  // Get bonus file choices
  xmlBf=new xmlBonusFile(item->filename);
  choiceList=xmlBf->getChoiceList();
  tBonusFileChoiceList::const_iterator iter;

  IGUIListBox*lb=env->addListBox( rect<s32>( 15, 70, 100, 200), 
				  winSelect, 10000, true);
  stringw namew;

  // If it is a choice
  for (iter=choiceList->begin(); iter != choiceList->end(); iter++){
    namew=StringConv::getSingleton().stow((*iter)->name);
    lb->addItem(namew.c_str());
  }

  // A empty choice description static text
  stChoiceDesc=env->addStaticText(L"Please make a choice", 
				  rect<s32>(110,70,435,100), 
				  false, true, winSelect );

  // An emply listbox for modifiers list
  lbModifiersList=env->addListBox(rect<s32>( 110, 110, 435, 200),
				  winSelect, -1, true);

  // The cancel and OK buttons
  env->addButton(rect<s32>(50,210,150,230), winSelect, 10001, L"OK" );
  env->addButton(rect<s32>(290,210,390,230), winSelect, 10002, L"Cancel" );

  return lb;

}


/** Handle the preselection of a choice
  *
  * First, we get the caller buttin caption. We also need the BonusFile
  * fiename to test if the caption is a choice.
  *
  * \param id The id of the caller
  * \param h The tPersoAttrbHandler of the attribute
  * \param listBox The widget containing all the choice of the BonusFile
  */
void RainbruRPG::Events::erCreatePerso::
choicePreselection( s32 id, tPersoAttrbHandler* h, IGUIListBox* listBox){
  IGUIEnvironment* env=GameEngine::getSingleton().getIrrlichtGui();
  IGUIElement *root= env->getRootGUIElement();
  IGUIElement *guiE=root->getElementFromId(id, true);

  // it is a preselection
  bool presel=false;

  // Get the button caption
  stringw caption;
  caption=guiE->getText();
  std::string s=StringConv::getSingleton().wtos(caption);

  cout << "guiE caption :" << preselName << endl;
  // Get the choiceList
  choiceList=xmlBf->getChoiceList();
  
  //  stringw namew;
  tBonusFileChoiceList::const_iterator iter;

  s32 idPresel=0;

  for (iter=choiceList->begin(); iter != choiceList->end(); iter++){
    if (strcmp((*iter)->name, s.c_str())==0){
      LOGI("The choice preselection was found");
      cout << "preselection found :" << (*iter)->name << endl;
      presel=true;
      preselName=(*iter)->name;
    }
    else{
      if (!presel)
	idPresel++;
    }
  }

  // Get the listbox
  if (presel){
    // We keep this preselection
    LOGI("====== Setting PRESEL ========");

    listBox->setSelected(idPresel);
    showChoiceModifiers(preselName.c_str());

    isPresel=true;
  }
  else{
    LOGW("No preselection found");
  }
 
}

/** Remove the preselection modifiers if needed
  *
  * It uses isPresel to know if a presel exists.
  *
  *
  */
void RainbruRPG::Events::erCreatePerso::removePreselectionModidifers(){

  if(isPresel){
   cout << "erCreatePerso::removePreselectionModidifers::Presel name" << preselName << endl;
   isPresel=false;
    LOGI("Removing preselection modifiers");
    //  const char* preselName;

    stringw tw;

    // Get the modifiers of the last selected choice
    tBonusModifierList* bml= xmlBf->getModifierList(preselName.c_str());
    tBonusModifierList::const_iterator iterMod;
    
    AttrbHandlerList* handlerList=gsCreatePerso::getHandlerList();
    AttrbHandlerList::const_iterator iterHa;
    
    
    // Iterates thru all the modifier
    for (iterMod=bml->begin(); iterMod != bml->end(); iterMod++){
      // (*iterMod)->attrb is the name of the attribte to modify
      // (*iterMod)->mod is the modifier value
      
      
      // Iterate through list of handlerevent
      for (iterHa=handlerList->begin(); iterHa!= handlerList->end(); iterHa++){
	// We must test if it is a RandomLevel
	if ((*iterHa)->type==AT_RANDOM_LVL){
	  // Its name is in (*iterHa)->item->name
	  // To add a modifier (*iterHa)->item->modList->addModifier()
	  
	  // We have the good attribute
	  if (strcmp((*iterHa)->item->name, (*iterMod)->attrb)==0){
	    // We had this modifier
	    (*iterHa)->item->modList.addModifierInverse((*iterMod)->mod);
	    LOGI("Removing a modifier");
	  }
	  
	}
      }
    }
  }
}

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

#include <iostream>

#include "launcheroptions.h"
#include "options.h"
#include <xmloptions.h>

#include "config.h"

FXDEFMAP(RainbruRPG::Gui::LauncherOptions) LauncherOptionsMap[]={
  //____Message_Type_____________ID_______________Message_Handler_______
  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LauncherOptions::ID_BUTTON, 
	    RainbruRPG::Gui::LauncherOptions::onNotImplemented),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LauncherOptions::ID_BTN_CANCEL, 
	    RainbruRPG::Gui::LauncherOptions::onCancelClick),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LauncherOptions::ID_BTN_OK, 
	    RainbruRPG::Gui::LauncherOptions::onOkClick),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LauncherOptions::ID_BTN_OPTION, 
	    RainbruRPG::Gui::LauncherOptions::onOptionButtonClick),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LauncherOptions::ID_ATTRB_WIDGET, 
	    RainbruRPG::Gui::LauncherOptions::onAttributeChange),

  FXMAPFUNC(SEL_CHANGED, RainbruRPG::Gui::LauncherOptions::ID_ATTRB_STRING, 
	    RainbruRPG::Gui::LauncherOptions::onAttributeChange),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LauncherOptions::ID_NEW_SNAP, 
	    RainbruRPG::Gui::LauncherOptions::onNewSnapshot),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LauncherOptions::ID_SAVE_SNAP, 
	    RainbruRPG::Gui::LauncherOptions::onSaveSnapshot),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LauncherOptions::ID_CHANGE_SNAP, 
	    RainbruRPG::Gui::LauncherOptions::onChangeSnapshot),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LauncherOptions::ID_DEL_SNAP, 
	    RainbruRPG::Gui::LauncherOptions::onDeleteSnapshot),

  FXMAPFUNC(SEL_COMMAND, RainbruRPG::Gui::LauncherOptions::ID_CPY_SNAP, 
	    RainbruRPG::Gui::LauncherOptions::onCopySnapshot),



};

FXIMPLEMENT(RainbruRPG::Gui::LauncherOptions,FXDialogBox,
	    LauncherOptionsMap,ARRAYNUMBER(LauncherOptionsMap));



/** Default constructor
  *
  * \param a The current instance of FXApp.
  */
RainbruRPG::Gui::LauncherOptions::LauncherOptions(FXApp * a)
   :FXDialogBox(a,"RainbruRPG options editor", DECOR_TITLE|DECOR_CLOSE|DECOR_BORDER|DECOR_SHRINKABLE|DECOR_STRETCHABLE|DECOR_MENU, 100, 100, 
		800, 600, 10, 10, 10, 10, 4, 4){
 

  switchPanelId=0;

  // frame construction
  FXVerticalFrame *root = new FXVerticalFrame(this, LAYOUT_FILL_Y|
					      LAYOUT_FIX_HEIGHT);
  root->setHeight(580);

  FXHorizontalFrame *frame = new FXHorizontalFrame(root, LAYOUT_FILL_X|LAYOUT_FILL_Y);

  FXShutter* tab=new FXShutter( frame, NULL, 0, FRAME_SUNKEN|LAYOUT_FILL_Y|
				LAYOUT_FIX_WIDTH, 0, 0, 100);

  tab->setWidth(150);

  swi=new FXSwitcher(frame);


  // Constructs panels
  tOptionPanelList* panelList=OptionManager::getSingleton().getPanelList();
  tOptionPanelList::const_iterator iter;

  for (iter=panelList->begin(); iter != panelList->end(); iter++)  {
    addOptionPanel( tab, swi, (*iter) );
  }


  // Buttons
  FXHorizontalFrame *frBtn = new FXHorizontalFrame(root, LAYOUT_FILL_X|LAYOUT_BOTTOM);
  frBtn->setPadLeft(40);
  frBtn->setPadRight(40);

  FXButton* btnCancel=new FXButton(frBtn, "Cancel", NULL, this, 
			  ID_BTN_CANCEL, BUTTON_NORMAL|LAYOUT_FIX_WIDTH);

  FXButton* btnOK=new FXButton(frBtn, "OK", NULL, this, ID_BTN_OK, 
			       BUTTON_NORMAL|LAYOUT_RIGHT|LAYOUT_FIX_WIDTH);

  btnCancel->setWidth(120);
  btnOK->setWidth(120);

  // Status line
  FXStatusLine* stas=new FXStatusLine (root, NULL);
  stas->setLayoutHints(LAYOUT_FIX_HEIGHT|LAYOUT_FILL_X);
  stas->setHeight(20);

  //  snapshot panel
  FXGroupBox* snapGroup=new ::FXGroupBox(root, "Snapshots",GROUPBOX_NORMAL| FX::FRAME_SUNKEN|LAYOUT_FILL_X );

  FXHorizontalFrame *frSnap = new FXHorizontalFrame(snapGroup, LAYOUT_FILL_X|LAYOUT_BOTTOM);

  btnSaveSnap=new FXButton(frSnap, "Save", NULL, this, 
			  ID_SAVE_SNAP, BUTTON_NORMAL|LAYOUT_FIX_WIDTH);
  btnSaveSnap->setWidth(120);
  btnSaveSnap->disable();

  FXButton* btnNewSnap=new FXButton(frSnap, "New", NULL, this, 
			  ID_NEW_SNAP, BUTTON_NORMAL|LAYOUT_FIX_WIDTH);
  btnNewSnap->setWidth(120);

  FXButton* btnDelSnap=new FXButton(frSnap, "Delete", NULL, this, 
			  ID_DEL_SNAP, BUTTON_NORMAL|LAYOUT_FIX_WIDTH);
  btnDelSnap->setWidth(120);

  FXButton* btnCopySnap=new FXButton(frSnap, "Copy", NULL, this, 
			  ID_CPY_SNAP, BUTTON_NORMAL|LAYOUT_FIX_WIDTH);
  btnCopySnap->setWidth(120);


  // Snapdhot combobox
  createSnapCombo(frSnap);
}


/** Default destructor
  *
  */
RainbruRPG::Gui::LauncherOptions::~LauncherOptions(){
  //  delete wm_icon_small;
  //  delete wm_icon_big;
}


/** A method needed by the FOX-toolkit
  *
  */
void RainbruRPG::Gui::LauncherOptions::create(){
  FXDialogBox::create();
   show(PLACEMENT_DEFAULT );
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
  */
long RainbruRPG::Gui::LauncherOptions::onNotImplemented(FXObject * o,
							FXSelector s,
							void* v){
  LOGW("This slot is not implemented");
  return 1;

}


/** Loads an ICO icon from its filename
  *
  * \param filename The filename of the icon.
  *
  * \todo Test if this ICO loader accept relative and absolute path.
  *
  * \return The FOX designed icon
  */
FX::FXIcon* RainbruRPG::Gui::LauncherOptions::loadIcon(const char* filename){

  LOGCATS("Loading icon ");
  LOGCATS(filename);
  LOGCAT();

  std::string s=USER_INSTALL_PREFIX;
  s+="/share/RainbruRPG/data/fox/";
  s+=filename;

  FXIcon *ico=new FXICOIcon(getApp());

  if(ico){
    FXFileStream stream;
    if(stream.open(s.c_str(),FXStreamLoad)){
      ico->loadPixels(stream);
      stream.close();
      ico->create();
    }
  }

  return ico;
}

/** The Cancel button clicked event receiver
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LauncherOptions::
onCancelClick(FXObject *o,FXSelector s,void* v){
  std::cout << "Cancel" << std::endl;
  this->handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_CANCEL), NULL);

  return 1;
}

/** The OK button clicked event receiver
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LauncherOptions::
onOkClick(FXObject *o,FXSelector s,void* v){
   std::cout << "OK" << std::endl;
   this->handle(this, FXSEL(SEL_COMMAND, FXDialogBox::ID_ACCEPT), NULL);

   return 1;
}

/** Add an OptionPanel
  *
  * An OptionPanel is graphically represented by a FXShutterItem.
  *
  * \param tab The parent of the new FXShutterItem
  * \param com The the FXSwitcher used to create the OptionButton of this
  *            panel
  * \param op The OptionPanel to create the FXShutterItem with
  *
  * \return The newly created FXShutterItem representing the OptionPanel
  */
FXShutterItem* RainbruRPG::Gui::LauncherOptions::
addOptionPanel(FXShutter *tab,FXSwitcher* com, OptionPanel* op){

  FXShutterItem *item= new FXShutterItem(tab, op->getCaption());

  tOptionButtonList * btnList=op->getButtonList();

  tOptionButtonList::const_iterator iter;

  for (iter=btnList->begin(); iter != btnList->end(); iter++)  {
    addOptionButton( item, com, (*iter) );
  }

  return item;
}


/** Adds an OptionButton
  *
  * An option if graphically represented as a FXButton, created inside 
  * a FXSwitcher.
  *
  * \param it The corresponding FXShutterItem
  * \param com The parent FXSwitcher
  * \param btn The OptionButton to be created
  *
  * \return The FXMatrix used as parent of the OptionAttribute of the 
  *         OptionButton
  *
  */
FXComposite* RainbruRPG::Gui::LauncherOptions::
addOptionButton(FXShutterItem* it, FXSwitcher* com,
			     OptionButton* btn){

  FXuint opts=BUTTON_TOOLBAR|TEXT_BELOW_ICON|FRAME_THICK|FRAME_RAISED|
              LAYOUT_FILL_X|LAYOUT_TOP|LAYOUT_LEFT;

  FXButton *b=new FXButton(it->getContent(), btn->getCaption(), 
			    loadIcon( btn->getIconFilename()), this, 
			   ID_BTN_OPTION, opts);

  b->setBackColor(it->getBackColor());
  b->setTextColor(FXRGB(255, 255, 255));

  // The new layout (A panel caption and the attributeOptions
  FXVerticalFrame *panelCaption = new FXVerticalFrame(com, LAYOUT_FIX_HEIGHT);
  panelCaption->setHeight(50);

  FXLabel* label=new FXLabel(panelCaption,  btn->getCaption(), 
			     NULL,LAYOUT_FILL_X);

  label->setJustify( FX::JUSTIFY_CENTER_X );
  FXFont *fnt2=new FXFont( getApp(), "helvetica", 25);
  label->setFont(fnt2);


  FXMatrix* frMatrix=new FXMatrix(panelCaption, 2, 
		   LAYOUT_FIX_WIDTH|MATRIX_BY_COLUMNS|LAYOUT_BOTTOM, 0, 0, 0, 
				  0, DEFAULT_SPACING, DEFAULT_SPACING, 
				  DEFAULT_SPACING,DEFAULT_SPACING,  
				  DEFAULT_SPACING, 5);

  frMatrix->setWidth(600);

  btn->setFoxPanelId(switchPanelId++);


  // Adds the optionAttribute
  addOptionAttribute(frMatrix, btn);

  return frMatrix;

}

/** The OptionButton click callback
  *
  * \param o The FXButton that emit the signal
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LauncherOptions::
onOptionButtonClick(FXObject * o,FXSelector s,void* v){
  LOGI("You have clicked on an optionButton :");
  FXButton* b=(FXButton*)o;

  // Get the panel name
  FXWindow* win=b->getParent()->getParent()->getParent();
  FXShutterItem* si=(FXShutterItem*)win;
  FXString panelCaption=si->getButton()->getText();

  // Get the button name
  FXString buttonCaption=b->getText();

  OptionButton* btn=OptionManager::getSingleton().
    getButtonByName(panelCaption.text(), buttonCaption.text());

  if (!btn){
    LOGW("Cannot get the OptionButton :");
    LOGCATS(" Panel name :");
    LOGCATS(panelCaption.text());
    LOGCAT();
    LOGCATS(" Button name :");
    LOGCATS(buttonCaption.text());
    LOGCAT();

  }
  else{
    int sw=btn->getFoxPanelId();
    swi->setCurrent(sw);
  }

  return 1;
}


/** Draw a widget corresponding to a OptionAttribute
  *
  * \param parent The parent that receive the widget
  * \param button The OptionButton the attribute belongs to
  *
  */
void RainbruRPG::Gui::LauncherOptions::
addOptionAttribute(FXComposite* parent, OptionButton* button){

  tOptionAttributeList* lst=button->getAttributeList();
  tOptionAttributeList::const_iterator iter;

  for (iter=lst->begin(); iter != lst->end(); iter++)  {

    tOptionAttributeType type=(*iter)->getType();

    switch(type){
    case OAT_UNKNOWN:
      LOGW("Trying to create a OAT_UNKNOWN");
      break;
    case OAT_INTEGER:
      drawInteger( parent, (*iter) );
      break;
    case OAT_STRING :
      drawString( parent, (*iter) );
      break;
    case OAT_BOOLEAN:
      drawBoolean( parent, (*iter) );
      break;
    case OAT_FLOAT:
      LOGI("OAT_FLOAT Not Yet implemented");
      break;
    case OAT_FLOAT_RANGE:
      LOGI("OAT_FLOAT_RANGE Not Yet implemented");
      break;
    case OAT_INT_RANGE:
      LOGI("OAT_INT_RANGE Not Yet implemented");
      break;
    case OAT_LIST :
      drawList( parent, (*iter) );
      break;
    }
  }
}

/** Draw a spinner control corresponding to a OptionIntAttribute
  *
  * \param parent The parent that receive the widget
  * \param attrb The OptionAttribute to draw
  *
  */
void RainbruRPG::Gui::LauncherOptions::drawInteger(FXComposite* parent, 
						   OptionAttribute* attrb){

  FXLabel* lab=new FXLabel(parent, attrb->getName());
  FXSpinner *spin=new FXSpinner (parent, 4, this, ID_ATTRB_WIDGET);
  spin->setUserData(attrb);

  attrb->setWidget(spin);

  lab->setHelpText(attrb->getToolTip());
  spin->setHelpText(attrb->getToolTip());
}

/** Draw a text field corresponding to a OptionStringAttribute
  *
  * \param parent The parent that receive the widget
  * \param attrb The OptionAttribute to draw
  *
  */
void RainbruRPG::Gui::LauncherOptions::drawString(FXComposite* parent, 
						  OptionAttribute* attrb){
  FXLabel* lab=new FXLabel(parent, attrb->getName());
  FXTextField* tf=new FXTextField (parent, 20, this, ID_ATTRB_STRING);
  tf->setUserData(attrb);

  attrb->setWidget(tf);


  lab->setHelpText(attrb->getToolTip());
  tf->setHelpText(attrb->getToolTip());
}

/** Draw a check button corresponding to a OptionBoolAttribute
  *
  * \param parent The parent that receive the widget
  * \param attrb The OptionAttribute to draw
  *
  */
void RainbruRPG::Gui::LauncherOptions::drawBoolean(FXComposite*parent, 
						   OptionAttribute*attrb){

  FXLabel* lab=new FXLabel(parent, attrb->getName());
  FXCheckButton* check=new FXCheckButton (parent, "", this, ID_ATTRB_WIDGET);
  check->setUserData(attrb);

  attrb->setWidget(check);


  lab->setHelpText(attrb->getToolTip());
  check->setHelpText(attrb->getToolTip());

}

/** Draw a combobox corresponding to a OptionListAttribute
  *
  * \param parent The parent that receive the widget
  * \param attrb The OptionAttribute to draw
  *
  */
void RainbruRPG::Gui::LauncherOptions::drawList(FXComposite*parent, 
						OptionAttribute*attrb){

  OptionListAttribute* vList=(OptionListAttribute*)attrb;

  new FXLabel(parent, attrb->getName());

  FXComboBox *cb=new FXComboBox( parent, 31, this, ID_ATTRB_WIDGET, 
    COMBOBOX_STATIC||LAYOUT_FIX_WIDTH|LAYOUT_RIGHT,
					0, 0, 200 );

  cb->setUserData(attrb);

  cb->setNumVisible(vList->valueCount());

  attrb->setWidget(cb);


  // feed combo box
  tValueList* values=vList->getValueList();
  tValueList::const_iterator iter;

  for (iter=values->begin(); iter != values->end(); iter++)  {
    cb->appendItem((*iter));
  }
}


/** The event receiver of all attribute's widget
  *
  * Some wigdet must be treated separatly (FXCheckButton, FXSpinner...). 
  * we use o.getClassName() to test the class type.
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LauncherOptions::
onAttributeChange(FXObject * o,FXSelector s,void* v){
  LOGI("onAttributeChange called");

  // (const char*)v represente la valeur
  OptionManager::getSingleton().setDamage(true);
  btnSaveSnap->enable();


  FX::FXId* id=(FX::FXId*)o;
  if (id){
    OptionAttribute* attrb=(OptionAttribute*)id->getUserData();
    if (attrb){

      // We must test if the sender is a checkbutton
      // It is a special case
      if (strcmp("FXCheckButton", id->getClassName())==0){
	// We have a check button
	bool b=(bool)v;
	attrb->setValueStr(StringConv::getSingleton().btoc(b));
      }
      else if (strcmp("FXSpinner", id->getClassName())==0){
	int i=(int)v;
	attrb->setValueStr(StringConv::getSingleton().itoc(i));
      }
      else{
	attrb->setValueStr((const char*)v);
      }

      LOGCATS("Received OptionAttribute value : ");
      LOGCATS(attrb->getValueStr());
      LOGCAT();
    }
    else{
      LOGW("Cannot get a valid OptionAttribute");
    }
  } 

  return 1;
}

/** Graphically update the attribute content
  *
  * It simply calls OptionManager::update();
  * This method is called by Launcher::onOptionsButtonPressed() at
  * startup.
  *
  * \sa OptionManager::update()
  */
void RainbruRPG::Gui::LauncherOptions::update(){
  OptionManager::getSingleton().update();
}


/** The event receiver for new snapshot button
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LauncherOptions::
onNewSnapshot(FXObject *o, FXSelector s, void* v){

  LOGI("New snapshot");

  if (OptionManager::getSingleton().isDamage()){
    LOGI("Snapshot damaged");
    int i=FXMessageBox::question (getApp(), FX::MBOX_YES_NO, 
				  "Snapshot unsaved", 
				  "The current snapshot was modified.\n"
				  "Do you want to save it ?\n\n"
				  "If you choose No, all the changes you\n"
				  "made will be lost.");

  }
  FXString newName;
  bool str=FXInputDialog::getString (newName, this, "New snapshot", 
			    "Give a unique name for this new snapshot");

  if (str){
    if (newName.empty()){
      FXMessageBox::error(this, FX::MBOX_OK, "The snapshot cannot be created",
			  "You can not create a new snapshot with an "
			  "empty name.\n The snapshot is not created");
    }
    else{
      

      // Test if the new snapshot name is in use
      xmlOptions opts;
      if (opts.isSnapShotExists(newName.text())){
	FXMessageBox::error(this, FX::MBOX_OK, 
			    "The snapshot cannot be created",
			    "The name you entered is already used.\n "
			    "Please try another snapshot name.");

      }
      else{
	cbSnap->appendItem(newName);
	
	OptionManager::getSingleton().setAttributesDefaultValues();
	OptionManager::getSingleton().update();
	OptionManager::getSingleton().saveCurrentSnapshot(newName.text());
	refreshSnapCombo();
	selectSnapshot(newName.text());
      }
    }
  }

  return 1;
}

/** The event receiver for new snapshot button
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LauncherOptions::
onSaveSnapshot(FXObject *o,FXSelector s,void* v){

  OptionManager::getSingleton().saveCurrentSnapshot(cbSnap->getText().text());
  btnSaveSnap->disable();

  return 1;
}

/** Create and feed up the Snapshot combo
  *
  * \param parent The layout where we create the combo box
  *
  */
void RainbruRPG::Gui::LauncherOptions::createSnapCombo(FXComposite* parent){
  // The snapshots comboBox
  cbSnap=new FXComboBox( parent, 31, this, ID_CHANGE_SNAP, 
    COMBOBOX_STATIC||LAYOUT_FIX_WIDTH|LAYOUT_RIGHT,
					0, 0, 200 );

  refreshSnapCombo();

}

/** Select a snapshot by name
  *
  * \param c The name of the snapshot to select
  *
  */
void RainbruRPG::Gui::LauncherOptions::selectSnapshot(const char* c){
  FXint it= cbSnap->findItem(c);
  cbSnap->setCurrentItem(it);
}

/** The event receiver for the snapshot combo box
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LauncherOptions::
onChangeSnapshot(FXObject * o,FXSelector s,void* v){
  LOGI("Snapshot selected");

  OptionManager::getSingleton().loadSnapshot(cbSnap->getText().text());

  return 1;
}

/** The event receiver for the delete snapshot button
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LauncherOptions::
onDeleteSnapshot(FXObject * o,FXSelector s,void* v){
  int i=FXMessageBox::question (getApp(), FX::MBOX_YES_NO, 
				"Delete snapshot", 
				"Do you really want to definitively "
				"remove the current snapshot ?");
  
  
  if (i==MBOX_CLICKED_YES){
    OptionManager::getSingleton().deleteSnapshot(cbSnap->getText().text());
    refreshSnapCombo();

    OptionManager::getSingleton().loadSnapshot(cbSnap->getText().text());

    update();
  }
  else{
    LOGI("Delete snapshot cancelled");
  }

  return 1;
}

/** Refresh the snapshot combobox
  *
  * It clears the combobox and reload the snapshot list.
  *
  */
void RainbruRPG::Gui::LauncherOptions::refreshSnapCombo(){
  cbSnap->clearItems();

  // get the snapshot list
  tSnapshotList::const_iterator iter;
  xmlOptions xmlo;
  tSnapshotList* snapList=xmlo.getSnapshotList();


  // setting the number of visible elements
  int i=snapList->size();
  if (i>5) i=5;
  cbSnap->setNumVisible(i);

  // populate the combo box
  if (snapList){
    for (iter=snapList->begin(); iter != snapList->end(); iter++){
      cbSnap->appendItem((*iter));
    }
  }
  else{
    LOGW("Can not get a valid snapshot list");
  }
}

/** The event receiver for the copy snapshot button
  *
  * \param o Internally used by FOX
  * \param s Internally used by FOX
  * \param v Internally used by FOX
  *
  * \return Always 1
  *
  */
long RainbruRPG::Gui::LauncherOptions::
onCopySnapshot(FXObject * o,FXSelector s,void* v){
  FXString newName;
  bool str=FXInputDialog::getString (newName, this, "Copy snapshot", 
			    "Give a unique name for the new snapshot");

  if (str){
    if (newName.empty()){
      FXMessageBox::error(this, FX::MBOX_OK, "The snapshot cannot be created",
			  "You can not create a new snapshot with an "
			  "empty name.\n The snapshot is not created");
    }
    else{
      

      // Test if the new snapshot name is in use
      xmlOptions opts;
      if (opts.isSnapShotExists(newName.text())){
	FXMessageBox::error(this, FX::MBOX_OK, 
			    "The snapshot cannot be created",
			    "The name you entered is already used.\n "
			    "Please try another snapshot name.");

      }
      else{
	cbSnap->appendItem(newName);
       	OptionManager::getSingleton().saveCurrentSnapshot(newName.text());
	refreshSnapCombo();
	selectSnapshot(newName.text());
      }
    }
  }

  return 1;
}

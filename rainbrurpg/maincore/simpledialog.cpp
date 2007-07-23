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

/* This code was found in the official CEGUI wiki :
 * http://www.cegui.org.uk/wiki/index.php/DialogSystem
 */

#include "simpledialog.h"

SimpleDialog::SimpleDialog(){
  message="";
}

/** Initialize the dialog
  *
  * If parent is empty, the window will be non-modal. If parent contains
  * a correct window name (already loaded), this dialog will be modal.
  *
  * \param parent The parent Window's name
  *
  */
void SimpleDialog::initWindow(const CEGUI::String& parent){
  // Initialise the dialog
  using namespace CEGUI;
  WindowManager& winMgr = WindowManager::getSingleton();
  
  // Initialise the windowing system
  DialogSystem::initialise("dlgMessageBox", false, parent);

  /*    
  // Subscribe to widget events
  DialogSystem::bindEvent( "SimpleDialog_btnOk",		
			   PushButton::EventClicked, DSE_OK);
  DialogSystem::bindEvent( "SimpleDialog_btnCancel",	
			   PushButton::EventClicked, DSE_CANCEL);
  DialogSystem::bindEvent( "SimpleDialog_btnApply",	
			   PushButton::EventClicked, DSE_APPLY);
  
  // These events trigger a 'modified' event, activating the 'apply' button
  DialogSystem::bindEvent( "SimpleDialog_edtValue",	
			   Editbox::EventTextChanged,	DSE_MODIFIED);
  
  // Subscribe to window events
  // Pressing the 'X' button will behave as a cancel
  if (!parent.empty()){
    DialogSystem::bindEvent( parent, FrameWindow::EventCloseClicked,DSE_CANCEL);
    DialogSystem::bindEvent( parent, FrameWindow::EventKeyDown, DSE_ESCAPE);
  }
  */

}

/** Handle the load action by placing data into widgets
  *
  */
bool SimpleDialog::doLoad(){
  CEGUI::WindowManager::getSingleton().getWindow("SimpleDialog_edtValue")
    ->setText(dataString);

  return DialogSystem::doLoad(); 
}

/** Handle the save action by moving widget data into variables
  *
  */
bool SimpleDialog::doSave(){
  dataString = CEGUI::WindowManager::getSingleton()
    .getWindow("SimpleDialog_edtValue")->getText();

  return DialogSystem::doSave(); 
}

void SimpleDialog::setMessage(const CEGUI::String& mess){
  this->message=mess;
  CEGUI::WindowManager::getSingleton().getWindow("MessageText")->setText(mess);
}

const CEGUI::String& SimpleDialog::getMessage(void){
  return this->message;
}

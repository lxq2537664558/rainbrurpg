/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

#include "messagebox.h"

/** The default constructor
  *
  * Actually, this initialize only message and title with empty strings.
  *
  */
RainbruRPG::Gui::MessageBox::MessageBox(){
  message ="";
  title   ="";
}

/** Initialize the dialog
  *
  * If parent is empty, the window will be non-modal. If parent contains
  * a correct window name (already loaded), this dialog will be modal.
  *
  * \param parent The parent Window's name
  *
  */
void RainbruRPG::Gui::MessageBox::initWindow(const CEGUI::String& parent){
  // Initialise the dialog
  using namespace CEGUI;
  WindowManager& winMgr = WindowManager::getSingleton();
  
  // Initialise the windowing system
  DialogSystem::initialise("dlgMessageBox", false, parent);

  // Subscribe to widget events
  DialogSystem::bindEvent( "dlgMessageBox_btnOk",		
			   PushButton::EventClicked, DSE_OK);
  
  // Subscribe to window events
  // Pressing the 'X' button will behave as a cancel
  if (!parent.empty()){
    DialogSystem::bindEvent( parent, FrameWindow::EventCloseClicked,DSE_CANCEL);
    DialogSystem::bindEvent( parent, FrameWindow::EventKeyDown, DSE_ESCAPE);
  }

}

/** Handle the load action by placing data into widgets
  *
  */
bool RainbruRPG::Gui::MessageBox::doLoad(){
  /*  CEGUI::WindowManager::getSingleton().getWindow("MessageBox_edtValue")
    ->setText(dataString);
  */
  return DialogSystem::doLoad(); 
}

/** Handle the save action by moving widget data into variables
  *
  */
bool RainbruRPG::Gui::MessageBox::doSave(){
  /*  dataString = CEGUI::WindowManager::getSingleton()
    .getWindow("MessageBox_edtValue")->getText();
  */
  return DialogSystem::doSave(); 
}

/** Changes the message of the dialog
  * 
  * This should be called before showing the dialog.
  *
  * \param mess The new message text
  *
  * \sa getMessage()
  *
  */
void RainbruRPG::Gui::MessageBox::setMessage(const CEGUI::String& mess){
  this->message=mess;
  CEGUI::WindowManager::getSingleton().getWindow("MessageText")->setText(mess);
}

/** Get the message of the dialog
  *
  * \return The value of the MessageBox::message class member
  *
  * \sa setMessage(const CEGUI::String&)
  *
  */ 
const CEGUI::String& RainbruRPG::Gui::MessageBox::getMessage(void){
  return this->message;
}

/** Changes the title of the dialog
  * 
  * This should be called before showing the dialog.
  *
  * \param title The new title's text
  *
  * \sa getTitle()
  *
  */
void RainbruRPG::Gui::MessageBox::setTitle(const CEGUI::String& title){
  this->title=title;
  CEGUI::WindowManager::getSingleton().getWindow("dlgMessageBox")
    ->setText(title);
}

/** Get the title of the dialog
  *
  * \return The value of the MessageBox::title class member
  *
  * \sa setTitle(const CEGUI::String&)
  *
  */ 
const CEGUI::String& RainbruRPG::Gui::MessageBox::getTitle(void){
  return this->title;
}

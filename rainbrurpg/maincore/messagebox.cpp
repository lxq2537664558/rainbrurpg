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

/* This code was found in the official CEGUI wiki :
 * http://www.cegui.org.uk/wiki/index.php/DialogSystem
 */

#include "messagebox.h"

#include "gameengine.h"

#include <ogreGui/pushbutton.h>
#include <ogreGui/bgcallback.h>
#include <ogreGui/bgwindow.h>
#include <ogreGui/bggui.h>
#include <ogreGui/label.h>

#include <OGRE/OgreVector4.h>

/** The default constructor
  *
  * Actually, this initialize only message and title with empty strings.
  *
  */
RainbruRPG::Gui::RbMessageBox::RbMessageBox():
  message(""),
  title(""),
  width(300),
  height(100),
  mWin(NULL),
  caption(NULL)
{

}

/** Initialize the dialog
  *
  */
void RainbruRPG::Gui::RbMessageBox::initWindow(){
  // Center the dialog
  unsigned int rwWidth, rwHeight, posX, posY;
  rwWidth=GameEngine::getSingleton().getRenderWindow()->getWidth();
  rwHeight=GameEngine::getSingleton().getRenderWindow()->getHeight();

  posX=(rwWidth/2)-(width/2);
  posY=(rwHeight/2)-(height/2);

  // Initialise the dialog
  Vector4 winDim=Vector4(posX, posY, width, height);
  BetaGUI::GUI* gui=GameEngine::getSingleton().getOgreGui();
  title="Unset";
  mWin=new BetaGUI::Window(winDim, OWT_MOVE, title, gui, true, OSI_BETAGUI);
  gui->addDialog(mWin);

  /*  Vector4 labDim=Vector4(2, 24, width-20, 30);
  caption=new Label( labDim, "Unset", mWin );
  mWin->addWidget(caption);
  */
  Vector4 btnDim=Vector4( (width/2)-50, height-30, 100, 24 );
  PushButton* btnOk=new PushButton (btnDim, "OK", Callback(this), mWin);
  mWin->addWidget(btnOk);


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
void RainbruRPG::Gui::RbMessageBox::setMessage(const String& mess){
  this->message=mess;
  caption->setCaption(mess);
}

/** Get the message of the dialog
  *
  * \return The value of the RbMessageBox::message class member
  *
  * \sa setMessage(const CEGUI::String&)
  *
  */ 
const String& RainbruRPG::Gui::RbMessageBox::getMessage(void){
  return this->message;
}

/** Changes the title of the dialog
  * 
  * This should be called before showing the dialog.
  *
  * \param t The new title's text
  *
  * \sa getTitle()
  *
  */
void RainbruRPG::Gui::RbMessageBox::setTitle(const String& t){
  this->title=t;
  mWin->setTitle(t);
}

/** Get the title of the dialog
  *
  * \return The value of the RbMessageBox::title class member
  *
  * \sa setTitle(const CEGUI::String&)
  *
  */ 
const String& RainbruRPG::Gui::RbMessageBox::getTitle(void){
  return this->title;
}

/** Shows this message box
  *
  */
void RainbruRPG::Gui::RbMessageBox::show(void){
  mWin->setTransparency(0.7f);
  mWin->show();
}

/** Hides this message box
  *
  */
void RainbruRPG::Gui::RbMessageBox::hide(void){
  mWin->hide();
}

/** The callback od OgreGUI buttons
  *
  * \param ref The button that fires the event
  *
  */
void RainbruRPG::Gui::RbMessageBox::onButtonPress(Button *ref){
  this->hide();
}

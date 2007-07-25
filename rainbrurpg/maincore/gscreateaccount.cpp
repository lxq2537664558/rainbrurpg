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

#include "gscreateaccount.h"

#include <logger.h>

/** The default constructor
  *
  */
RainbruRPG::Core::gsCreateAccount::gsCreateAccount()
  :gsMenuBase(false){

  velocity=new vcConstant();
  translateTo(0.0f);
}

/** The destructor
  *
  */
RainbruRPG::Core::gsCreateAccount::~gsCreateAccount(){
  if (velocity){
    delete velocity;
    velocity=NULL;
  }
}

/** Initialize the game state
  *
  */
void RainbruRPG::Core::gsCreateAccount::init(){
  gsMenuBase::init();
  GuiManager::getSingleton().loadCEGUILayout("createAccount.layout");

  // Initialise the dialog parent
  this->rootWindowName="RainbruRPG/CreateAccount";

  setupCreateAccountMenu();
  setupTabOrder();
}

/** Resume the state after a pause() call or a state change
  *
  */
void RainbruRPG::Core::gsCreateAccount::resume(){
  Ogre::RenderWindow* rw=GameEngine::getSingleton().getRenderWindow();
  // GuiManager::getSingleton().createTitleOverlay(rw);
  GuiManager::getSingleton().loadCEGUILayout("createAccount.layout");
  setupCreateAccountMenu();

  // Initialise the dialog parent
  this->rootWindowName="RainbruRPG/CreateAccount";
  setupTabOrder();
}


/** The 'back' button callback
  *
  * \param evt The CEGUI event arguments
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsCreateAccount::
onBackClicked(const CEGUI::EventArgs& evt){

  GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GuiManager::getSingleton().removeCurrentCEGUILayout();

  GameEngine::getSingleton().changeState(ST_MENU_CONNECT);
  GuiManager::getSingleton().beginGuiFadeIn();


  return true;
}

/** Setup the callbacks
  *
  */
void RainbruRPG::Core::gsCreateAccount::setupCreateAccountMenu(){
  // Subscribe event
  CEGUI::Window* root=CEGUI::System::getSingleton().getGUISheet();

  // Root window
  CEGUI::Window* rainbruConnection=root->getChild("RainbruRPG/CreateAccount");
  // Back button
  CEGUI::Window* btnBack=rainbruConnection->getChild("RainbruRPG/CreateAccountWin/Back");
  if (btnBack){
    btnBack->setFont("Iconified-20");
    btnBack->subscribeEvent("Clicked", 
      CEGUI::Event::Subscriber(&gsCreateAccount::onBackClicked,this));

  }
  else{
    LOGW("Cannot get the 'Back' button");
  }

}

void RainbruRPG::Core::gsCreateAccount::setupTabOrder(){
  // Registering TabNavigation
  tabNav.clear();
  tabNav.setParent("RainbruRPG/CreateAccount");
  tabNav.addWidget("RainbruRPG/CreateAccount/Name");
  tabNav.addWidget("RainbruRPG/CreateAccount/Pwd");
  tabNav.addWidget("RainbruRPG/CreateAccount/RepPwd");
  tabNav.addWidget("RainbruRPG/CreateAccount/EMail");
  tabNav.addWidget("RainbruRPG/CreateAccount/Submit");
  tabNav.addWidget("RainbruRPG/CreateAccountWin/Back");
}

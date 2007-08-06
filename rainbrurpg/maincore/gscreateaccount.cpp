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

#include <curlaccountadd.h>
#include <logger.h>

#include "keyboardnavigation.h"

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
  CEGUI::Window* wca=root->getChild("RainbruRPG/CreateAccount");

  // Back button
  try{
    CEGUI::Window* btnBack=wca->getChild("RainbruRPG/CreateAccountWin/Back");
    btnBack->setFont("Iconified-20");
    btnBack->subscribeEvent(CEGUI::Window::EventMouseClick, 
      CEGUI::Event::Subscriber(&gsCreateAccount::onBackClicked,this));
  }
  catch(const CEGUI::Exception& e){
    LOGW("Cannot get the 'RainbruRPG/CreateAccountWin/Back' button");
  }

  // The submit button
  try{
    CEGUI::Window* win=wca->getChild("RainbruRPG/CreateAccountWin");
    CEGUI::Window* btnSbm=win->getChild("RainbruRPG/CreateAccount/Submit");
    btnSbm->subscribeEvent(CEGUI::Window::EventMouseClick, 
      CEGUI::Event::Subscriber(&gsCreateAccount::onSubmitClicked,this));
  }
  catch(const CEGUI::Exception& e){
    LOGW("Cannot get the 'RainbruRPG/CreateAccount/Submit' button");
  }

}

/** Setup the tabulation order 
  *
  * Clears the current tabNav instance, set its parent and
  * adds the widgets that will have focus.
  *
  * \sa tabNav, TabNavigation, gsMainMenu::setupTabOrder().
  *
  */
void RainbruRPG::Core::gsCreateAccount::setupTabOrder(){
  // Registering TabNavigation
  tabNav->clear();
  tabNav->setParent("RainbruRPG/CreateAccount");
  tabNav->addWidget("RainbruRPG/CreateAccount/Name");
  tabNav->addWidget("RainbruRPG/CreateAccount/Pwd");
  tabNav->addWidget("RainbruRPG/CreateAccount/RepPwd");
  tabNav->addWidget("RainbruRPG/CreateAccount/EMail");
  tabNav->addWidget("RainbruRPG/CreateAccount/Submit");
  tabNav->addWidget("RainbruRPG/CreateAccountWin/Back");
}

/** The Suibmit button callback
  *
  * Clicked by the user when he entered all required informations, it
  * submit the account creation to the admin site.
  *
  * \param evt The CEGUI event 
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsCreateAccount::
onSubmitClicked(const CEGUI::EventArgs& evt){
  LOGI("Submit button clicked");
  CEGUI::String name, pwd, repPwd, mail, mess, nextFocus;

  CEGUI::String err01="Account creation error";
  CEGUI::String parent="RainbruRPG/CreateAccountWin";

  try{
    // Get the window
    CEGUI::Window* root=CEGUI::System::getSingleton().getGUISheet();
    CEGUI::Window* wca=root->getChild("RainbruRPG/CreateAccount");
    CEGUI::Window* win=wca->getChild("RainbruRPG/CreateAccountWin");

    name=win->getChild("RainbruRPG/CreateAccount/Name")->getText();
    pwd=win->getChild("RainbruRPG/CreateAccount/Pwd")->getText();
    repPwd=win->getChild("RainbruRPG/CreateAccount/RepPwd")->getText();
    mail=win->getChild("RainbruRPG/CreateAccount/EMail")->getText();

    if (pwd!=repPwd){
      win->getChild("RainbruRPG/CreateAccount/RepPwd")->activate();
      GuiManager::getSingleton().showMessageBox(err01, 
        "Please correctly repeat the password",parent);
    }
    else{
      CurlAccountAdd caa;
      caa.setName(name.c_str());
      caa.setPassword(pwd.c_str());
      caa.setMail(mail.c_str());
 
      bool success=caa.perform();

      if (success){
	GuiManager::getSingleton().showMessageBox("Account succefully created", 
          "The account was correctly added. Before you are able to use "
          "it, you must activate it.\n\nPlease wait the activation "
          "mail.",parent);
      }
      else{
	tCurlAccountAddReturn ret=caa.getResponse();

	switch (ret){
	case CAA_EXISTS :
	  nextFocus="RainbruRPG/CreateAccount/Name";
	  mess="This account name is already used. Please choose another "
	    "identifier.";
	  break;
	case CAA_EMPTY_NAME:
	  nextFocus="RainbruRPG/CreateAccount/Name";
	  mess="Cannot create an account with empty name.";
	  break;
	case CAA_EMPTY_PWD:
	  nextFocus="RainbruRPG/CreateAccount/Pwd";
	  mess="Cannot create an account with empty password.";
	  break;
	case CAA_EMPTY_MAIL:
	  nextFocus="RainbruRPG/CreateAccount/EMail";
	  mess="Cannot create an account with empty mail address.";
	  break;
	case CAA_MAIL_INUSE:
	  nextFocus="RainbruRPG/CreateAccount/EMail";
	  mess="This mail is already used for another account. You can "
	    "only create one account for each different mail address.";
	  break;
	case CAA_MAIL_SIGN_AT:
	  nextFocus="RainbruRPG/CreateAccount/EMail";
	  mess="The mail address should contain a '@' sign.";
	  break;
	case CAA_MAIL_SIGN_DOT:
	  nextFocus="RainbruRPG/CreateAccount/EMail";
	  mess="The mail address should contain a '.' sign.";
	  break;
	}

	win->getChild(nextFocus)->activate();
	GuiManager::getSingleton().showMessageBox(err01, mess, parent);

      }

    }
  }
  catch(const CEGUI::Exception& e){
    LOGE("Cannot get some widgets");
  }

  return true;
}

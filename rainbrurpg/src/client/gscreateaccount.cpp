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

/** \file gscreateaccount.cpp
  * Implements a gamestate that lets the user create an account
  *
  */

#include "gscreateaccount.h"

//#include <curlaccountadd.h>
#include <logger.h>

#include "keyboardnavigation.h"

/*#include "ogreGui/bgwindow.h"
#include "ogreGui/bgbutton.h"
#include "ogreGui/pushbutton.h"
#include "ogreGui/label.h"
#include "ogreGui/bgtextinput.h"
*/
/** The default constructor
  *
  */
RainbruRPG::Core::gsCreateAccount::gsCreateAccount():
  gsMenuBase("gsCreateAccount", false),
  window(NULL),
  winBack(NULL),
  btnBack(NULL),
  btnSubmit(NULL),
  labName(NULL),
  labPwd1(NULL),
  labPwd2(NULL),
  labMail(NULL),
  labHelp(NULL),
  tiName(NULL),
  tiPwd1(NULL),
  tiPwd2(NULL),
  tiMail(NULL)
{

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

  //  delete window;
  window=NULL;

  //  delete winBack;
  winBack=NULL;

  //  delete btnBack;
  btnBack=NULL;

  //  delete btnSubmit;
  btnSubmit=NULL;

  // Label widget
    /*  delete labName;  labName=NULL;
  delete labPwd1;  labPwd1=NULL;
  delete labPwd2;  labPwd2=NULL;
  delete labMail;  labMail=NULL;
  delete labHelp;  labHelp=NULL;
    */
  // Text input widgets
    /*  delete tiName;   tiName=NULL;
  delete tiPwd1;   tiPwd1=NULL;
  delete tiPwd2;   tiPwd2=NULL;
  delete tiMail;   tiMail=NULL;
    */
}

/** Initialize the game state
  *
  */
void RainbruRPG::Core::gsCreateAccount::init(){
  gsMenuBase::init();
  yBorder=0.5f;

  setupCreateAccountMenu();
  setupTabOrder();
}

/** Resume the state after a pause() call or a state change
  *
  */
void RainbruRPG::Core::gsCreateAccount::resume(){
  setupCreateAccountMenu();
  setupTabOrder();
  yBorder=0.5f;

}


/** The 'back' button callback
  *
  */
void RainbruRPG::Core::gsCreateAccount::onBackClicked(void){

  GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GameEngine::getSingleton().changeState("gsConnection");
  GuiManager::getSingleton().beginGuiFadeIn();
}

/** Setup the screen
  *
  */
void RainbruRPG::Core::gsCreateAccount::setupCreateAccountMenu(){
  /*  
  BetaGUI::GUI* mGUI = &GUI::getSingleton();

  // Center the window in the right background
  RenderWindow* mRenderWindow=GameEngine::getSingleton().getRenderWindow();
  unsigned int w=mRenderWindow->getWidth();
  unsigned int h=mRenderWindow->getHeight();

  // The width of the window in pixels
  unsigned int winWidth=300;
  // The height of the window in pixels
  unsigned int winHeight=210;

  // The position of the window
  unsigned int winY=(h/2)-(winHeight/2);
  unsigned int winX=((w/2)-40)+(w/4-(winWidth/2));
  winX+=(int)(double)w*0.025;     // The border

  // The create account  window
  window = new BetaGUI::Window(Vector4(winX,winY,winWidth,winHeight),
		      BetaGUI::OWT_RESIZE_AND_MOVE, "Create account", mGUI);

  String mess="Please enter these required informations. The account\n"
    "will not be activated since you receive a mail.";

  // The incremented position of widget
  unsigned int posY=20;
  // Y position of right widget
  unsigned int rightX=100;

  
  Vector4 labHelpDim(10,posY,winWidth-20,24);
  labHelp=new Label(labHelpDim, mess, window);
  window->addWidget(labHelp);

  posY+=35;
  Vector4 labNameDim(10,posY,rightX-10,24);
  labName=new Label(labNameDim, "Account name", window);
  window->addWidget(labName);
  Vector4 tiNameDim(rightX,posY,winWidth-rightX-20,24);
  tiName=new TextInput(tiNameDim, "", 20, window);
  window->addWidget(tiName);

  posY+=30;
  Vector4 labPwd1Dim(10,posY,rightX-10,24);
  labPwd1=new Label(labPwd1Dim, "Password", window);
  window->addWidget(labPwd1);
  Vector4 tiPwd1Dim(rightX,posY,winWidth-rightX-20,24);
  tiPwd1=new TextInput(tiPwd1Dim, "", 20, window);
  tiPwd1->setMasked(true);
  window->addWidget(tiPwd1);

  posY+=30;
  Vector4 labPwd2Dim(10,posY,rightX-10,24);
  labPwd2=new Label(labPwd2Dim, "Repeat password", window);
  window->addWidget(labPwd2);
  Vector4 tiPwd2Dim(rightX,posY,winWidth-rightX-20,24);
  tiPwd2=new TextInput(tiPwd2Dim, "", 20, window);
  tiPwd2->setMasked(true);
  window->addWidget(tiPwd2);

  posY+=30;
  Vector4 labMailDim(10,posY,rightX-10,24);
  labMail=new Label(labMailDim, "Email", window);
  window->addWidget(labMail);
  Vector4 tiMailDim(rightX,posY,winWidth-rightX-20,24);
  tiMail=new TextInput(tiMailDim, "", 40, window);
  window->addWidget(tiMail);
  */
  /*
  posY+=30;
  unsigned int btnSubmitWidth=100;
  Vector4 btnSubmitDim((winWidth/2)-(btnSubmitWidth/2),posY,btnSubmitWidth,24);
  btnSubmit= new PushButton(btnSubmitDim, "Submit", 
			    BetaGUI::Callback::Callback(this), window);
  window->addWidget(btnSubmit);
  mGUI->addWindow(window);
  */

  // The Back button window (false= no border)
  /*  winBack = new BetaGUI::Window(Vector4(20,h-50 ,120,53),
		       BetaGUI::OWT_NONE, "Connection", mGUI, OSI_NAVIGATION);
  winBack->setAlwaysTransparent(true);

  btnBack = new PushButton(Vector4(10,10,100,33),
			   "Back", BetaGUI::Callback::Callback(this), winBack);
  winBack->addWidget(btnBack);
  mGUI->addWindow(winBack);
  */
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
  /*  tabNav->clear();
  tabNav->setParent("RainbruRPG/CreateAccount");
  tabNav->addWidget("RainbruRPG/CreateAccount/Name");
  tabNav->addWidget("RainbruRPG/CreateAccount/Pwd");
  tabNav->addWidget("RainbruRPG/CreateAccount/RepPwd");
  tabNav->addWidget("RainbruRPG/CreateAccount/EMail");
  tabNav->addWidget("RainbruRPG/CreateAccount/Submit");
  tabNav->addWidget("RainbruRPG/CreateAccountWin/Back");
  */
}

/** The Suibmit button callback
  *
  * Clicked by the user when he entered all required informations, it
  * submit the account creation to the admin site.
  *
  * \return Always \c true
  *
  */
void RainbruRPG::Core::gsCreateAccount::onSubmitClicked(void){
  /*
  LOGI("Submit button clicked");
  String name, pwd, repPwd, mail;

  String mess;
  String err01="Account creation error";


  name   =tiName->getValue();
  pwd    =tiPwd1->getValue();
  repPwd =tiPwd2->getValue();
  mail   =tiMail->getValue();

  if (name.empty() || pwd.empty()){
    GuiManager::getSingleton()
      .setErrorMessage("Please enter a name and a password.");
  }
  else if (pwd!=repPwd){
    GuiManager::getSingleton()
      .setErrorMessage("Please correctly repeat the password");
  }
  else{
    CurlAccountAdd caa;
    caa.setName(name.c_str());
    caa.setPassword(pwd.c_str());
    caa.setMail(mail.c_str());
    
    bool success=caa.perform();
    
    if (success){
      GuiManager::getSingleton()
	.showMessageBox("Account successfully "
	       "created", 
	       "The account was correctly added. Before you are able to use "
	       "it, you must activate it.\n\nPlease wait the activation mail.");
    }
    else{
      tCurlAccountAddReturn ret=caa.getResponse();
      
      switch (ret){
      case CAA_EXISTS :
	mess="This account name is already used. Please choose another "
	  "identifier.";
	break;
      case CAA_EMPTY_NAME:
	mess="Cannot create an account with empty name.";
	break;
      case CAA_EMPTY_PWD:
	mess="Cannot create an account with empty password.";
	  break;
      case CAA_EMPTY_MAIL:
	mess="Cannot create an account with empty mail address.";
	break;
      case CAA_MAIL_INUSE:
	mess="This mail is already used for another account. You can\n"
	     "only create one account for each different mail address.";
	break;
      case CAA_MAIL_SIGN_AT:
	mess="The mail address should contain a '@' sign.";
	break;
      case CAA_MAIL_SIGN_DOT:
	mess="The mail address should contain a '.' sign.";
	break;
      }
      GuiManager::getSingleton().showMessageBox(err01, mess);
      
    }
    
  }
  */
}

/** The OgreGUI buttons callback
  *
  * \param btn The button that fire the event
  *
  */
void RainbruRPG::Core::gsCreateAccount::onButtonPress(BetaGUI::Button* btn){
  /*  if (btn==btnSubmit){
    onSubmitClicked();
  }
  else if (btn==btnBack){
    onBackClicked();
  }
  */
}

/** Pause the execution of this GameState
  *
  */
void RainbruRPG::Core::gsCreateAccount::pause(){
  LOGI("RainbruRPG::Core::gsCreateAccount::pause called");
  if (window){
    //    window->hide();
    //    delete window;
    window=NULL;
  }
  else{
    LOGW("Cannot get window pointer");
  }

  if (winBack){
    //    winBack->hide();
    //    delete winBack;
    winBack=NULL;
  }
  else{
    LOGW("Cannot get winBack pointer");
  }
}

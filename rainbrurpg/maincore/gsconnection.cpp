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

/** \file gsconnection.cpp
  * Implements a gamestate that lets the user enter its username and password
  *
  */

#include "keyboardnavigation.h"
#include "gsconnection.h"
#include "vcconstant.h"
#include "guimanager.h"

#include <bgwindow.h>
#include <bgtextinput.h>
#include <pushbutton.h>
#include <label.h>


#include <OgrePrerequisites.h> // for Ogre::String


/** The default constructor
  *
  * Constructs a new velocity and begin a translation to 0.0f.
  *
  */
RainbruRPG::Core::gsConnection::gsConnection():
  gsMenuBase(false),
  btnBack(NULL),
  btnConnect(NULL),
  btnCreateAccount(NULL),
  btnLostPwd(NULL),
  window(NULL),
  winBack(NULL),
  tiUserName(NULL),
  tiPassword(NULL)
{

  LOGI("Constructing a gsConnection");
  velocity=new vcConstant();
}

/** The default destructor
  *
  */
RainbruRPG::Core::gsConnection::~gsConnection(){
  if (velocity){
    delete velocity;
    velocity=NULL;
  }

  delete btnBack;
  btnBack=NULL;

  delete btnConnect;
  btnConnect=NULL;

  delete btnCreateAccount;
  btnCreateAccount=NULL;

  delete btnLostPwd;
  btnLostPwd=NULL;

  delete tiUserName;
  tiUserName=NULL;

  delete tiPassword;
  tiPassword=NULL;

  delete window;
  window=NULL;

  delete winBack;
  winBack=NULL;
}

/** Initialize the game state
  *
  * This function may not call GuiManager::beginGuiFadeIn as it is called
  * at the end of the menu border transition.
  *
  */
void RainbruRPG::Core::gsConnection::init(){
  LOGI("Initialising gsConnection");
  gsMenuBase::init();
  yBorder=0.5f;
  translateTo(0.4f);
  setupConnectionMenu();
  setupTabOrder();
  LOGI("gsConnection initialization complete");
}

/** The Quit CEGUI button callback
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onQuitClicked(){

  LOGI("Quit button clicked");
  GameEngine::getSingleton().quit();
  // Event handled
  return true;
}

/** Setup the connection menu buttons
  *
  */
void RainbruRPG::Core::gsConnection::setupConnectionMenu(){
  BetaGUI::GUI* mGUI =GameEngine::getSingleton().getOgreGui();

  // Center the window in the right background
  RenderWindow* mRenderWindow=GameEngine::getSingleton().getRenderWindow();
  unsigned int w=mRenderWindow->getWidth();
  unsigned int h=mRenderWindow->getHeight();

  // The width of the window in pixels
  unsigned int winWidth=300;
  // The height of the window in pixels
  unsigned int winHeight=180;

  // The position of the window
  unsigned int winY=(h/2)-(winHeight/2);
  unsigned int winX=((w/2)-40)+(w/4-(winWidth/2));
  winX+=(int)(double)w*0.025;     // The border

  // The connection window
  window = new BetaGUI::Window(Vector4(winX,winY,winWidth,winHeight),
		      BetaGUI::OWT_RESIZE_AND_MOVE, "Connection", mGUI);

  Vector4 laDim(10,40,80,24);
  Label* labUserName=new Label(laDim, "User name", window);
  window->addWidget(labUserName);

  Vector4 tiDim(100,40,180,24);
  tiUserName=new TextInput(tiDim, "", 20, window);
  window->addWidget(tiUserName);

  Vector4 laDim2(10,70,80,24);
  Label* labPassword=new Label(laDim2, "Password", window);
  window->addWidget(labPassword);

  Vector4 tiDim2(100,70,180,24);
  tiPassword=new TextInput(tiDim2, "", 20, window);
  tiPassword->setMasked(true);
  window->addWidget(tiPassword);
  
  // Buttons
  btnConnect = new PushButton(Vector4(70,100,160,24),
      "Network game", BetaGUI::Callback::Callback(this), window);
  window->addWidget(btnConnect);
  
  btnCreateAccount = new PushButton(Vector4(10,130,135,24),
       "Create account", BetaGUI::Callback::Callback(this), window);
  window->addWidget(btnCreateAccount);

  btnLostPwd = new PushButton(Vector4(winWidth-145,130,135,24),
       "Lost password", BetaGUI::Callback::Callback(this), window);
  window->addWidget(btnLostPwd);
  mGUI->addWindow(window);

  // The Back button window (false= no border)
  winBack = new BetaGUI::Window(Vector4(20,h-50 ,120,53),
		       BetaGUI::OWT_NONE, "Connection", mGUI, OSI_NAVIGATION);
  winBack->setAlwaysTransparent(true);

  btnBack = new PushButton(Vector4(10,10,100,33),
			   "Back", BetaGUI::Callback::Callback(this), winBack);
  winBack->addWidget(btnBack);
  mGUI->addWindow(winBack);
}

/** The callback of the Connect button
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onConnectClicked(){
  LOGI("Connect button clicked");

  // Get the strings
  Ogre::String name=tiUserName->getValue();

  if (name.empty()){
    GuiManager::getSingleton()
      .showMessageBox("Empty account name", 
		      "Please enter a user name.");
  }
  else{
    const char* cName=name.c_str();
    const char* cPwd=tiPassword->getValue().c_str();
    
    // connection successfull
    if (GameEngine::getSingleton().connectUser(cName, cPwd)){
      GuiManager::getSingleton().beginGuiFadeOut();

      // We must wait for the CEGUI fade end to prevent
      // SEGFAULT in access to CEGUI windows (getAlpha())
      while (GuiManager::getSingleton().isInGuiFadeOut()){
	Ogre::Root::getSingleton().renderOneFrame();
      }
      
      GameEngine::getSingleton().changeState(ST_SERVER_LIST);
      GuiManager::getSingleton().beginGuiFadeIn();
    }

  }
  return true;
}

/** Resume the state after a call or changestate call
  *
  */
void RainbruRPG::Core::gsConnection::resume(){
  setupConnectionMenu();
  setupTabOrder();
  //yBorder=0.5f;
  translateTo(0.4f);
}

/** The callback of the 'create account' button
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onCreateAccountClicked(){
  LOGI("onCreateAccountClicked called");

  GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GameEngine::getSingleton().changeState(ST_CREATE_ACCOUNT);
  GuiManager::getSingleton().beginGuiFadeIn();

  return true;
}

/** The callback of the 'lost password' button
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::onLostPasswordClicked(){

  LOGI("onLostPasswordClicked called");

  GuiManager::getSingleton()
    .showMessageBox("Lost Password", 
    "This function isn't yet implemented. Please contact me\n"
    "directly (rainbru@free.fr)");
  return true;
}

/** Setup the tab order for this game state
  *
  */
void RainbruRPG::Core::gsConnection::setupTabOrder(){
  // Registering TabNavigation
  /*  tabNav->clear();
  tabNav->setParent("RainbruRPG/Connection");
  tabNav->addWidget("RainbruRPG/Connection/Name");
  tabNav->addWidget("RainbruRPG/Connection/Pwd");
  tabNav->addWidget("Connect");
  tabNav->addWidget("CreateAccount");
  tabNav->addWidget("LostPassword");
  tabNav->addWidget("Back");
  */
}

/** The general OgreGUI buttons callback
  * 
  * \param btn The button that send the event
  *
  */
void RainbruRPG::Core::gsConnection::onButtonPress(BetaGUI::Button* btn){
 
  if (btn==btnBack){
    onBackClicked();
  }
  else if (btn==btnConnect){
    onConnectClicked();
  }
  else if (btn==btnCreateAccount){
    onCreateAccountClicked();
  }
  else if (btn==btnLostPwd){
    onLostPasswordClicked();
  }

}

/** Pause the execution of this GameState
  *
  */
void RainbruRPG::Core::gsConnection::pause(){
  LOGI("gsConnection::pause() called");

  if (window){
    window->hide();
    delete window;
    window=NULL;
  }

  if (winBack){
    winBack->hide();
    delete winBack;
    winBack=NULL;
  }

  if (window==NULL || winBack==NULL){
    LOGW("Cannot get main or back windows");
  }
}

/** The back button implementation
  *
  * Makes the GameEngine changes to ST_MAIN_MENU, the gsMainMenu game state.
  *
  */
void RainbruRPG::Core::gsConnection::onBackClicked(void){
    LOGI("Back button clicked");
    translateTo(0.5f);

 
    GuiManager::getSingleton().beginGuiFadeOut();

    // We must wait for the CEGUI fade end to prevent
    // SEGFAULT in access to CEGUI windows (getAlpha())
    while (GuiManager::getSingleton().isInGuiFadeOut()){
      Ogre::Root::getSingleton().renderOneFrame();
    }

    GameEngine::getSingleton().changeState(ST_MAIN_MENU);
    GuiManager::getSingleton().beginGuiFadeIn();

}

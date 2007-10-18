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

#include "keyboardnavigation.h"
#include "gsconnection.h"
#include "vcconstant.h"
#include "guimanager.h"

#include <bgwindow.h>
#include <bgtextinput.h>
#include <pushbutton.h>

/** The default constructor
  *
  * Constructs a new velocity and begin a translation to 0.0f.
  *
  */
RainbruRPG::Core::gsConnection::gsConnection()
  :gsMenuBase(false){

  LOGI("Constructing a gsConnection");
  velocity=new vcConstant();
  //  translateTo(0.0f);
}

/** The default destructor
  *
  */
RainbruRPG::Core::gsConnection::~gsConnection(){
  if (velocity){
    delete velocity;
    velocity=NULL;
  }
}

/** Initialize the game state
  *
  * This function may not call GuiManager::beginGuiFadeIn as it is called
  * at the end of the menu border transition.
  */
void RainbruRPG::Core::gsConnection::init(){
  LOGI("Initialising gsConnection");
  gsMenuBase::init();
  yBorder=0.5f;
  translateTo(0.0f);
  setupConnectionMenu();
  setupTabOrder();
  LOGI("gsConnection initialization complete");
}

/** The Quit CEGUI button callback
  *
  * \param evt The CEGUI event
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onQuitClicked(const CEGUI::EventArgs& evt){

  LOGI("Quit button clicked");
  GameEngine::getSingleton().quit();
  // Event handled
  return true;
}

/** Returns to the main menu layout
  *
  * \param evt The CEGUI event
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onBackToMainClicked(const CEGUI::EventArgs& evt){

  GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GuiManager::getSingleton().removeCurrentCEGUILayout();

  GameEngine::getSingleton().changeState(ST_MAIN_MENU);
  GuiManager::getSingleton().beginGuiFadeIn();

  return true;
}

/** Setup the connection menu buttons
  *
  * Subscribe events for the connection layout.
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
  unsigned int winHeight=150;

  // Te position of the window
  unsigned int winY=(h/2)-(winHeight/2);
  unsigned int winX=(w/2)+(w/4-(winWidth/2));
  winX+=(int)(double)w*0.025;     // The border

  Window* window = new Window(Vector4(winX,winY,winWidth,winHeight),
		      BetaGUI::OWT_RESIZE_AND_MOVE, "Connection", mGUI);

  Vector4 tiDim(10,55,180,24);
  TextInput* ti=new TextInput(tiDim, "", 20, window);


  btnConnect = new PushButton(Vector4(20,40,160,24),
				 "Network game", BetaGUI::Callback::Callback(this), window);
  window->addWidget(btnConnect);

  mGUI->addWindow(window);
}

/** The callback of the Connect button
  *
  * \param evt The CEGUI event
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onConnectClicked(const CEGUI::EventArgs& evt){
  LOGI("Connect button clicked");

  // Get the strings
  CEGUI::Window* root=CEGUI::System::getSingleton().getGUISheet();
  CEGUI::Window* connect=root->getChild("RainbruRPG/Connection");
  CEGUI::Window* connectWin=connect->getChild("RainbruRPG/ConnectionWindow");
  nameWidget=connectWin->getChild("RainbruRPG/Connection/Name");

  if (nameWidget->getText().empty()){
    GuiManager::getSingleton()
      .showMessageBox("Empty account name", 
		      "Please enter a user name.", "RainbruRPG/Connection");
  }
  else{
    pwdWidget=connectWin->getChild("RainbruRPG/Connection/Pwd");
    const char* cName=nameWidget->getText().c_str();
    const char* cPwd=pwdWidget->getText().c_str();
    
    // connection successfull
    if (GameEngine::getSingleton().connectUser(cName, cPwd)){
      GuiManager::getSingleton().beginGuiFadeOut();

      // We must wait for the CEGUI fade end to prevent
      // SEGFAULT in access to CEGUI windows (getAlpha())
      while (GuiManager::getSingleton().isInGuiFadeOut()){
	Ogre::Root::getSingleton().renderOneFrame();
      }
      
      GuiManager::getSingleton().removeCurrentCEGUILayout();
      
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
  Ogre::RenderWindow* rw=GameEngine::getSingleton().getRenderWindow();
  // GuiManager::getSingleton().createTitleOverlay(rw);
  GuiManager::getSingleton().loadCEGUILayout("connection.layout");
  setupConnectionMenu();

  // Initialise the dialog parent
  this->rootWindowName="RainbruRPG/Connection";

  setupTabOrder();
}

/** The callback of the 'create account' button
  *
  * \param evt The CEGUI event
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onCreateAccountClicked(const CEGUI::EventArgs& evt){
  LOGI("onCreateAccountClicked called");

  GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GuiManager::getSingleton().removeCurrentCEGUILayout();

  GameEngine::getSingleton().changeState(ST_CREATE_ACCOUNT);
  GuiManager::getSingleton().beginGuiFadeIn();

  return true;
}

/** The callback of the 'lost password' button
  *
  * \param evt The CEGUI event
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onLostPasswordClicked(const CEGUI::EventArgs& evt){
  LOGI("onLostPasswordClicked called");

  GuiManager::getSingleton()
    .showMessageBox("Lost Password", 
    "This function isn't yet implemented. Please contact me directly"
    " (rainbru@free.fr)", "RainbruRPG/Connection");
  return true;
}

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

void RainbruRPG::Core::gsConnection::onButtonPress(BetaGUI::Button* btn){

}

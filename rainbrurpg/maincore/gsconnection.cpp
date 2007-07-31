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

#include "gsconnection.h"
#include "vcconstant.h"
#include "guimanager.h"

/** The default constructor
  *
  * Constructs a new velocity and begin a translation to 0.0f.
  *
  */
RainbruRPG::Core::gsConnection::gsConnection()
  :gsMenuBase(false){

  LOGI("Constructing a gsConnection");
  velocity=new vcConstant();
  translateTo(0.0f);
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
  GuiManager::getSingleton().loadCEGUILayout("connection.layout");

  // Initialise the dialog parent
  this->rootWindowName="RainbruRPG/Connection";

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
  LOGI("setupConnectionMenu called");

  // Subscribe event
  CEGUI::Window* root=CEGUI::System::getSingleton().getGUISheet();

  // Root window
  CEGUI::Window* rainbruConnection=root->getChild("RainbruRPG/Connection");
  // Back button
  CEGUI::Window* btnBack=rainbruConnection->getChild("Back");
  if (btnBack){
    btnBack->setFont("Iconified-20");
    btnBack->subscribeEvent(CEGUI::Window::EventMouseClick, 
      CEGUI::Event::Subscriber(&gsConnection::onBackToMainClicked,this));

  }
  else{
    LOGW("Cannot get the 'Back' button");
  }

  // Get the Connection window
  CEGUI::Window* connectWin=rainbruConnection
    ->getChild("RainbruRPG/ConnectionWindow");
  nameWidget=connectWin->getChild("RainbruRPG/Connection/Name");
  pwdWidget=connectWin->getChild("RainbruRPG/Connection/Pwd");

  CEGUI::Editbox* eb=static_cast<CEGUI::Editbox*>(pwdWidget);
  eb->setTextMasked(true);

 // Connect button
  CEGUI::Window* btnConnect=connectWin->getChild("Connect");
  if (btnConnect){
    btnConnect->subscribeEvent(CEGUI::Window::EventMouseClick, 
      CEGUI::Event::Subscriber(&gsConnection::onConnectClicked,this));

  }
  else{
    LOGW("Cannot get the 'Connect' button");
  }

  // CreateAccount
  CEGUI::Window* btnCreateAccount=connectWin->getChild("CreateAccount");
  if (btnConnect){
    btnCreateAccount->subscribeEvent(CEGUI::Window::EventMouseClick, 
      CEGUI::Event::Subscriber(&gsConnection::onCreateAccountClicked,this));

  }
  else{
    LOGW("Cannot get the 'CreateAccount' button");
  }

  // LostPassword
  CEGUI::Window* btnLostPassword=connectWin->getChild("LostPassword");
  if (btnConnect){
    btnLostPassword->subscribeEvent(CEGUI::Window::EventMouseClick, 
      CEGUI::Event::Subscriber(&gsConnection::onLostPasswordClicked,this));

  }
  else{
    LOGW("Cannot get the 'LostPassword' button");
  }

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
    const char* cPwd=(const char*)pwdWidget->getText().c_str();
    CEGUI::String strPwd=pwdWidget->getText();
    
    HashPassword hp;
    std::string hashPwd=hp.encryptString(cPwd);
    LOGCATS("Name :");
    LOGCATS(cName);
    LOGCATS(" Pwd :");
    LOGCATS(cPwd);
    LOGCATS(" HS :");
    LOGCATS(hashPwd.c_str());
    LOGCAT();

    // connection successfull
    if (GameEngine::getSingleton().connectUser(cName, hashPwd.c_str())){
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
  tabNav.clear();
  tabNav.setParent("RainbruRPG/Connection");
  tabNav.addWidget("RainbruRPG/Connection/Name");
  tabNav.addWidget("RainbruRPG/Connection/Pwd");
  tabNav.addWidget("Connect");
  tabNav.addWidget("CreateAccount");
  tabNav.addWidget("LostPassword");
  tabNav.addWidget("Back");
}

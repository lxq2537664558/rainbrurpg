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

#include "gsconnection.h"
#include "vcconstant.h"
#include "guimanager.h"
#include "tabnavigation.h"

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
  // Do notGuiManager::beginGuiFadeIn
  //  GuiManager::getSingleton().beginGuiFadeIn();


  setupConnectionMenu();
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

/** The Local Test CEGUI button callback
  *
  * \param evt The CEGUI event
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onLocalTestClicked(const CEGUI::EventArgs& evt){

  LOGI("LocalTest button clicked");
  //  GameEngine::getSingleton().enterLocalTest();
  GameEngine::getSingleton().changeState(ST_LOCAL_TEST);

  // Event handled
  return true;
}

/** The Network Game CEGUI button callback
  *
  * \param evt The CEGUI event
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onNetworkGameClicked(const CEGUI::EventArgs& evt){
  LOGI("NetworkGame button clicked");

  GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GuiManager::getSingleton().removeCurrentCEGUILayout();
  GuiManager::getSingleton().loadCEGUILayout("connection.layout");
  GuiManager::getSingleton().debugChild("RainbruRPG/Connection");

  GuiManager::getSingleton().beginGuiFadeIn();

  // Subscribe event
  CEGUI::Window* root=CEGUI::System::getSingleton().getGUISheet();

  // Root window
  CEGUI::Window* rainbruConnection=root->getChild("RainbruRPG/Connection");
  // Back button
  CEGUI::Window* btnBack=rainbruConnection->getChild("Back");
  if (btnBack){
    btnBack->setFont("Iconified-20");
    btnBack->subscribeEvent("Clicked", 
      CEGUI::Event::Subscriber(&gsConnection::onBackToMainClicked,this));

  }
  else{
    LOGW("Cannot get the 'Back' button");
  }

  // Get the Connection window
  CEGUI::Window* connectWin=rainbruConnection
    ->getChild("RainbruRPG/ConnectionWindow");

 // Connect button
  CEGUI::Window* btnConnect=connectWin->getChild("Connect");
  if (btnConnect){
    btnConnect->subscribeEvent("Clicked", 
      CEGUI::Event::Subscriber(&gsConnection::onConnectClicked,this));

  }
  else{
    LOGW("Cannot get the 'Connect' button");
  }


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

  GuiManager::getSingleton().loadCEGUILayout("mainmenu.layout");
  GuiManager::getSingleton().beginGuiFadeIn();

  setupConnectionMenu();

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
    btnBack->subscribeEvent("Clicked", 
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
    btnConnect->subscribeEvent("Clicked", 
      CEGUI::Event::Subscriber(&gsConnection::onConnectClicked,this));

  }
  else{
    LOGW("Cannot get the 'Connect' button");
  }

  // Registering TabNavigation
  TabNavigation* tabNav=new TabNavigation();
  tabNav->setParent("RainbruRPG/ConnectionWindow");
  tabNav->addWidget("RainbruRPG/Connection/Name");
  tabNav->addWidget("RainbruRPG/Connection/Pwd");
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
  pwdWidget=connectWin->getChild("RainbruRPG/Connection/Pwd");
  const char* cName=nameWidget->getText().c_str();
  const char* cPwd=(const char*)pwdWidget->getText().c_str();
  CEGUI::String strPwd=pwdWidget->getText();

  // Get a valid const char*
  CEGUI::String::const_iterator iter;
  for (iter=strPwd.begin(); iter!=strPwd.end(); iter++){
    cout << hex << (*iter) << endl;
  }

  HashPassword hp;
  std::string hashPwd=hp.encryptString(cPwd);
  LOGCATS("Name :");
  LOGCATS(cName);
  LOGCATS(" Pwd :");
  LOGCATS(cPwd);
  LOGCAT();
  GameEngine::getSingleton().connectUser(cName, hashPwd.c_str());

  return true;
}

bool RainbruRPG::Core::gsConnection::keyPressed(const OIS::KeyEvent & evt){
  OIS::KeyCode kc=evt.key;
  unsigned int text=evt.text;
  bool masked=false;

  // Special cases
  CEGUI::Key::Scan scanCode;

  if (kc==OIS::KC_DELETE){
    CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::Delete);
  }
  else if (kc==OIS::KC_BACK){
    CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::Backspace);
  }
  else if (kc==OIS::KC_LEFT){
    CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::ArrowLeft);
  }
  else if (kc==OIS::KC_RIGHT){
    CEGUI::System::getSingleton().injectKeyDown(CEGUI::Key::ArrowRight);
  }
  else if (kc==OIS::KC_TAB){
    // Do nothing
  }
  else if (kc==OIS::KC_LSHIFT || kc==OIS::KC_RSHIFT){
    // Do nothing
  } 
  else{
    CEGUI::System::getSingleton().injectChar((CEGUI::utf32)text);
  }

  return true;
}

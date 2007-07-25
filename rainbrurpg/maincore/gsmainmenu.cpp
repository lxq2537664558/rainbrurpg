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

#include "gsmainmenu.h"

#include "vcconstant.h"
#include "guimanager.h"

/** The default constructor
  *
  * Constructs a new velocity and begin a translation to 0.0f.
  *
  */
RainbruRPG::Core::gsMainMenu::gsMainMenu()
  :gsMenuBase(true){

  LOGI("Constructing a gsMainMenu");
  velocity=new vcConstant();
  translateTo(0.0f);
}

/** The default destructor
  *
  */
RainbruRPG::Core::gsMainMenu::~gsMainMenu(){
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
void RainbruRPG::Core::gsMainMenu::init(){
  LOGI("Initialising gsMainMenu");
  gsMenuBase::init();
  GuiManager::getSingleton().loadCEGUILayout("mainmenu.layout");
  // Do notGuiManager::beginGuiFadeIn
  //  GuiManager::getSingleton().beginGuiFadeIn();


  setupMainMenu();
  LOGI("gsMainMenu initialization complete");

}

/** The Quit CEGUI button callback
  *
  * \param evt The CEGUI event
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsMainMenu::
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
bool RainbruRPG::Core::gsMainMenu::
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
bool RainbruRPG::Core::gsMainMenu::
onNetworkGameClicked(const CEGUI::EventArgs& evt){
  LOGI("NetworkGame button clicked");


  GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GuiManager::getSingleton().detroyTitleOverlay();
  GuiManager::getSingleton().removeCurrentCEGUILayout();
  GameEngine::getSingleton().changeState(ST_MENU_CONNECT);

  GuiManager::getSingleton().beginGuiFadeIn();


  return true;
}

/** Setup the main menu buttons
  *
  * This method does not call GuiManager::beginGuiFadeIn because in the
  * init function, it must not be called. The fade in is started when the
  * menu border transition is ended. however, onBackToMainClicked must
  * manually call GuiManager::beginGuiFadeIn. So, the mainmenu CEGUI layout
  * is loaded in the init() and onBackToMainClicked() functions.
  *
  */
void RainbruRPG::Core::gsMainMenu::setupMainMenu(){
  LOGI("setupMainMenu called");
  // Subscribe event
  CEGUI::Window* root=CEGUI::System::getSingleton().getGUISheet()
    ->getChild("RainbruRPG/MainMenu");;

  // Quit button
  CEGUI::Window* btnQuit=root->getChild("Quit");
  if (btnQuit){
    //    btnQuit->setFont("Iconified-20");
    btnQuit->subscribeEvent("Clicked", 
	     CEGUI::Event::Subscriber(&gsMainMenu::onQuitClicked,this));

  }
  else{
    LOGW("Cannot get the 'Quit' button");
  }


  // Local test
  CEGUI::Window* btnLocalTest=root->getChild("LocalTest");
  if (btnLocalTest){
    //    btnLocalTest->setFont("Iconified-20");
    btnLocalTest->subscribeEvent("Clicked", 
	     CEGUI::Event::Subscriber(&gsMainMenu::onLocalTestClicked,
				      this));
  }
  else{
    LOGW("Cannot get the 'Quit' button");
  }

  // Network game
  CEGUI::Window* btnNetGame=root->getChild("NetGame");
  if (btnNetGame){
    //    btnNetGame->setFont("Iconified-20");
    btnNetGame->subscribeEvent("Clicked", 
	     CEGUI::Event::Subscriber(&gsMainMenu::onNetworkGameClicked,
				      this));
  }
  else{
    LOGW("Cannot get the 'Network game' button");
  }

  // Registering TabNavigation
  tabNav.setParent("RainbruRPG/MainMenu");
  tabNav.addWidget("NetGame");
  tabNav.addWidget("LocalTest");
  tabNav.addWidget("Quit");
}

void RainbruRPG::Core::gsMainMenu::resume(){
  Ogre::RenderWindow* rw=GameEngine::getSingleton().getRenderWindow();
  // GuiManager::getSingleton().createTitleOverlay(rw);
  GuiManager::getSingleton().loadCEGUILayout("mainmenu.layout");
  setupMainMenu();
  // Initialise the dialog parent
  this->rootWindowName="RainbruRPG/Connection";
}


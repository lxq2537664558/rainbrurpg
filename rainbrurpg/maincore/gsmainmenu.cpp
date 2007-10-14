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

#include "gsmainmenu.h"

#include "keyboardnavigation.h"
#include "vcconstant.h"
#include "guimanager.h"

#include "bgcallback.h"
#include "pushbutton.h"

#include <OgreViewport.h>

using namespace RainbruRPG::OgreGui;

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

  window=NULL;
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
  //  GuiManager::getSingleton().loadCEGUILayout("mainmenu.layout");
  // Do notGuiManager::beginGuiFadeIn
  //  GuiManager::getSingleton().beginGuiFadeIn();


  setupMainMenu();
  setupTabOrder();

  LOGI("gsMainMenu initialization complete");

}

/** The Network Game function
  *
  * Is is called when the `network game` button is clicked.
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsMainMenu::
onNetworkGameClicked(){
  LOGI("NetworkGame button clicked");


  GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GuiManager::getSingleton().destroyTitleOverlay();
  GuiManager::getSingleton().removeCurrentCEGUILayout();
  GameEngine::getSingleton().changeState(ST_MENU_CONNECT);

  GuiManager::getSingleton().beginGuiFadeIn();


  return true;
}

void RainbruRPG::Core::gsMainMenu::resume(){
  Ogre::RenderWindow* rw=GameEngine::getSingleton().getRenderWindow();
  // GuiManager::getSingleton().createTitleOverlay(rw);
  GuiManager::getSingleton().loadCEGUILayout("mainmenu.layout");
  setupMainMenu();
  // Initialise the dialog parent
  this->rootWindowName="RainbruRPG/Connection";

  if (window)
    window->show();

  setupTabOrder();
}

void RainbruRPG::Core::gsMainMenu::setupTabOrder(){
  // Registering TabNavigation
  /*  tabNav->clear();
  tabNav->setParent("RainbruRPG/MainMenu");
  tabNav->addWidget("NetGame");
  tabNav->addWidget("LocalTest");
  tabNav->addWidget("Quit");
  */
}

/** Setup the screen
  *
  * It uses OgreGUI to creates the main menu screen.
  *
  */
void RainbruRPG::Core::gsMainMenu::setupMainMenu(){
  BetaGUI::GUI* mGUI =GameEngine::getSingleton().getOgreGui();

  mGUI->createMousePointer(Vector2(32, 32), "bgui.pointer");


  // Center the window
  RenderWindow* mRenderWindow=GameEngine::getSingleton().getRenderWindow();
  unsigned int w=mRenderWindow->getWidth();
  unsigned int h=mRenderWindow->getHeight();

  window = mGUI->
    createWindow(Vector4((w/2)-100,(h/2)-75,200,150),"bgui.window", 
		 BetaGUI::OWT_RESIZE_AND_MOVE, "Main menu");


  // Creates a test button
  Callback testC(this);
  Vector4 pb1Dim(10,25,100,24);
  PushButton* pb1=new PushButton(pb1Dim, "Test", testC, mGUI, window);
  window->addWidget(pb1);

  Vector4 tiDim(10,55,180,24);
  TextInput* ti=new TextInput(tiDim, "Test input :)", 20, window);
  window->addWidget(ti);

  /*
  btnNetworkGame= window->createButton(Vector4(20,40,160,24), "bgui.button", 
                      "Network game", BetaGUI::Callback::Callback(this));

  btnLocalTest = window->createButton(Vector4(20,70,160,24), "bgui.button", 
			 "Local test", BetaGUI::Callback::Callback(this));

  btnExit = window->createButton(Vector4(20,100,160,24), "bgui.button", 
         "Exit", BetaGUI::Callback::Callback(this));
  */
}

/** The BetaGui button callback implementation
  *
  * \param b The button that was pressed
  *
  */
void RainbruRPG::Core::gsMainMenu::onButtonPress(BetaGUI::Button* b){
  if (b==btnLocalTest){
    //  GameEngine::getSingleton().enterLocalTest();
    GameEngine::getSingleton().changeState(ST_LOCAL_TEST);
  }
  else if (b==btnExit){
    LOGI("Quit button clicked");
    GameEngine::getSingleton().quit();
  }
  else if (b==btnNetworkGame){
    onNetworkGameClicked();
  }
  else{
    LOGW("gsMainMenu::onButtonPress called");
  }
}

void RainbruRPG::Core::gsMainMenu::pause(){
  if (window)
    window->hide();
}

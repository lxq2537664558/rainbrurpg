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
#include "scrollbar.h"
#include "scrollpane.h"

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
  //  translateTo(0.0f);

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

  GameEngine::getSingleton().changeState(ST_MENU_CONNECT);
  GuiManager::getSingleton().beginGuiFadeIn();


  return true;
}

void RainbruRPG::Core::gsMainMenu::resume(){

  setupMainMenu();
  // Initialise the dialog parent
  this->rootWindowName="RainbruRPG/Connection";

  if (window)
    window->show();

  setupTabOrder();

  //isMouseButtonPressed=false;
  LOGI("gsMainMenu::resume() called");
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


  // Center the window in the right background
  RenderWindow* mRenderWindow=GameEngine::getSingleton().getRenderWindow();
  unsigned int w=mRenderWindow->getWidth();
  unsigned int h=mRenderWindow->getHeight();

  // The width of the window in pixels
  unsigned int winWidth=200;
  // The height of the window in pixels
  unsigned int winHeight=150;

  // The position of the window
  unsigned int winY=(h/2)-(winHeight/2);
  unsigned int winX=(w/2)+(w/4-(winWidth/2));
  winX+=(int)(double)w*0.025;     // The border

  window = new Window(Vector4(winX,winY,winWidth,winHeight),
		      BetaGUI::OWT_RESIZE_AND_MOVE, "Main menu", mGUI);
  mGUI->addWindow(window);


  btnNetworkGame= new PushButton(Vector4(20,40,160,24),
				 "Network game", BetaGUI::Callback::Callback(this), window);
  window->addWidget(btnNetworkGame);

  btnLocalTest = new PushButton(Vector4(20,70,160,24), 
			 "Local test", BetaGUI::Callback::Callback(this), window);

  // ***************************************************
  // ***************************************************
  // Only for tests
  Window* testWin=new Window(Vector4(10, 10, 300, 300),
		      BetaGUI::OWT_RESIZE_AND_MOVE, "Test window", mGUI);
  mGUI->addWindow(testWin);

  /*
  // First overlay of the scrollPane
  OverlayContainer* oc1=static_cast<OverlayContainer*>
    (OverlayManager::getSingleton().createOverlayElement("Panel", "test01"));
  testWin->getOverLayContainer()->addChild(oc1);
  oc1->setMetricsMode(GMM_PIXELS);
  oc1->setDimensions(200, 200);
  oc1->setPosition(10, 10);

  Matrix4 m4;
  m4.makeTrans(0.2, 0, 0);

  // Child overlay of the scrollPane
  OverlayContainer* oc2=static_cast<OverlayContainer*>
    (OverlayManager::getSingleton().createOverlayElement("Panel", "test02"));
  oc2->setMetricsMode(GMM_PIXELS);
  oc2->setDimensions(512, 512);
  oc2->setPosition(0, 0);
  oc2->setMaterialName("bgui.test");
  oc1->addChild(oc2);
  oc2->getMaterial()->getTechnique(0)->getPass(0)->getTextureUnitState(0)
    ->setTextureScroll(0.2, 0.2);
  */

  Vector4 sbDim(300-16,30,14,300-60);
  ScrollBar* sb=new ScrollBar(sbDim, testWin, OST_VERTICAL);
  testWin->addWidget(sb);
  sb->setMax(500);
  sb->setSteps(20,50);
  ScrollPane* sp=new ScrollPane(sbDim, testWin);
  testWin->addWidget(sp);

  // End of tests
  // ***************************************************
  // ***************************************************

  window->addWidget(btnLocalTest);

  btnExit = new PushButton(Vector4(20,100,160,24), 
         "Exit", BetaGUI::Callback::Callback(this), window);
  window->addWidget(btnExit);

}

/** The BetaGui button callback implementation
  *
  * \param b The button that was pressed
  *
  */
void RainbruRPG::Core::gsMainMenu::onButtonPress(BetaGUI::Button* b){

  if (b==btnLocalTest){
    translateTo(3.0);
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
  if (window){
    window->hide();
    delete window;
    window=NULL;
  }
}

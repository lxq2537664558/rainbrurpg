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

#include "gsmainmenu.h"

#include "keyboardnavigation.h"
#include "vcconstant.h"
#include "guimanager.h"

#include "bgcallback.h"
#include "pushbutton.h"
#include "vscrollbar.h"
#include "hscrollbar.h"
#include "scrollpane.h"
#include "multicolumnlist.h"
#include "label.h"

#include <OgreViewport.h>

using namespace RainbruRPG::OgreGui;

/** The default constructor
  *
  * Constructs a new velocity and begin a translation to 0.0f.
  *
  */
RainbruRPG::Core::gsMainMenu::gsMainMenu():
  gsMenuBase(true),
  window(NULL)
#ifdef RB_SCROLLPANE_TEST
  ,ScrollPaneTestWin(NULL)
  ,ctrlWin(NULL)
#endif // RB_SCROLLPANE_TEST
#ifdef RB_MULTICOLUMNLIST_TEST
  ,MultiColumnListWin(NULL)
#endif // RB_MULTICOLUMNLIST_TEST
{

  LOGI("Constructing a gsMainMenu");
  velocity=new vcConstant();
  //  translateTo(0.0f);

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
				 "Network game", 
				 BetaGUI::Callback::Callback(this), window);
  window->addWidget(btnNetworkGame);

  btnLocalTest = new PushButton(Vector4(20,70,160,24), 
				"Local test", BetaGUI::Callback::Callback(this),
				window);

  window->addWidget(btnLocalTest);

  btnExit = new PushButton(Vector4(20,100,160,24), 
         "Exit", BetaGUI::Callback::Callback(this), window);
  window->addWidget(btnExit);

 // ***************************************************
  // ***************************************************
#ifdef RB_SCROLLPANE_TEST
  createScrollPaneTestWindow();
#endif // RB_SCROLLPANE_TEST

#ifdef RB_MULTICOLUMNLIST_TEST
  createMultiColumnListTestWindow();
#endif // RB_MULTICOLUMNLIST_TEST

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
#ifdef RB_SCROLLPANE_TEST
  else if (b==btnAddLabel){
    onAddLabel();
  }
#endif // RB_SCROLLPANE_TEST
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

#ifdef RB_SCROLLPANE_TEST
  if (ScrollPaneTestWin) ScrollPaneTestWin->hide();
  if (ctrlWin) ctrlWin->hide();
#endif // RB_SCROLLPANE_TEST

}

#ifdef RB_SCROLLPANE_TEST
/** Create a window to test scrollpane
  *
  * \note This function is built only if the \c RB_SCROLLPANE_TEST is
  *       define using the \c configure script. Please see 
  *       \ref RainbruRPG::Core::gsMainMenu "gsMainMenu"
  *       for more information.
  *
  */
void RainbruRPG::Core::gsMainMenu::createScrollPaneTestWindow(void){
  // Only built if the RB_SCROLLPANE_TEST macro is defined


  // ScrollPane test window
  LOGI("Creating ScrollPaneTestWindow");
  BetaGUI::GUI* mGUI =GameEngine::getSingleton().getOgreGui();
  if (!ScrollPaneTestWin){
    ScrollPaneTestWin =new Window(Vector4(10, 10, 300, 300),
				  BetaGUI::OWT_RESIZE_AND_MOVE, 
				  "Scrollpane test", mGUI);
    mGUI->addWindow(ScrollPaneTestWin);
  }
  else{
    ScrollPaneTestWin->show();
  }

  if (!ctrlWin){
    // Control window
    ctrlWin=new Window(Vector4(10, 310, 300, 90),
		       BetaGUI::OWT_RESIZE_AND_MOVE, 
		       "Control window", mGUI);
    mGUI->addWindow(ctrlWin);

    Vector4 labPosDim(10,30,50,20);
    Label* labPos=new Label(labPosDim, "Label position", ctrlWin);
    ctrlWin->addWidget(labPos);
    
    Vector4 tiXPosDim(120,30,50,20);
    tiXPos=new TextInput(tiXPosDim, "", 5, ctrlWin);
    ctrlWin->addWidget(tiXPos);
    
    Vector4 tiYPosDim(180,30,50,20);
    tiYPos=new TextInput(tiYPosDim, "", 5, ctrlWin);
    ctrlWin->addWidget(tiYPos);
    
    btnAddLabel = new PushButton(Vector4(80,60,160,24),
				 "Add label", 
				 BetaGUI::Callback::Callback(this), ctrlWin);
    ctrlWin->addWidget(btnAddLabel);
  }
  else{
    ctrlWin->show();
  }
}

/** Adds a label to the ScrollPane test window
  *
  * \note This function is built only if the \c RB_SCROLLPANE_TEST macro is
  *       define using the \c configure script. Please see 
  *       \ref RainbruRPG::Core::gsMainMenu "gsMainMenu"
  *       for more information.
  *
  */
void RainbruRPG::Core::gsMainMenu::onAddLabel(void){
  // Only built if the RB_SCROLLPANE_TEST macro is defined
  int x=tiXPos->getIntValue();
  int y=tiYPos->getIntValue();

  Vector4 labPosDim(x,y,100,30);
  PushButton* newLab=new PushButton(labPosDim, "New label", 
				    BetaGUI::Callback::Callback(this),
				    ScrollPaneTestWin);
  ScrollPaneTestWin->addWidget(newLab);
  ScrollPaneTestWin->debugScrollPane();
}

#endif // RB_SCROLLPANE_TEST

#ifdef RB_MULTICOLUMNLIST_TEST
/** Adds a label to the ScrollPane test window
  *
  * \note This function is built only if the \c  RB_MULTICOLUMNLIST_TEST
  *       macro is define using the \c configure script. Please see 
  *       \ref RainbruRPG::Core::gsMainMenu "gsMainMenu"
  *       for more information.
  *
  */
void RainbruRPG::Core::gsMainMenu::createMultiColumnListTestWindow(void){
  // Only built if the RB_MULTICOLUMNLIST_TEST macro is defined
  // ScrollPane test window
  LOGI("Creating MultiColumnListTestWindow");
  BetaGUI::GUI* mGUI =GameEngine::getSingleton().getOgreGui();
  if (!MultiColumnListWin){
    MultiColumnListWin =new Window(Vector4(10, 10, 340, 370),
				  BetaGUI::OWT_RESIZE_AND_MOVE, 
				  "MultiColumnList test", mGUI);
    mGUI->addWindow(MultiColumnListWin);

    Vector4 labPosDim(10,30,50,20);
    MultiColumnList* mcl=new MultiColumnList(labPosDim, MultiColumnListWin);
    MultiColumnListWin->addWidget(mcl);

  }
  else{
    MultiColumnListWin->show();
  }

}
#endif // RB_MULTICOLUMNLIST_TEST

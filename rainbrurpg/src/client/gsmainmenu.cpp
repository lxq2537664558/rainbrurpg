/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file gsmainmenu.cpp
  * Implements the main menu game state
  *
  */

#include "gsmainmenu.h"

#include <Window.hpp>
#include <Label.hpp>

#include "keyboardnavigation.h"
#include "vcconstant.h"

//#include "guimanager.h" // redefinition of class Widget
/*
#include "bgcallback.h"
#include "pushbutton.h"
#include "vscrollbar.h"
#include "hscrollbar.h"
#include "scrollpane.h"
#include "multicolumnlist.h"
#include "multicolumnlistitem.h"
#include "multicolumnlistcolumn.h"
#include "label.h"
*/
#include <OgreViewport.h>
#include <gameengine.h>


using namespace RainbruRPG::OgreGui;

/** The default constructor
  *
  * Constructs a new velocity and begin a translation to 0.0f.
  *
  */
RainbruRPG::Core::gsMainMenu::gsMainMenu():
  gsMenuBase("gsMainMenu", true),
  window(NULL)
#ifdef RB_SCROLLPANE_TEST
  ,ScrollPaneTestWin(NULL)
  ,ctrlWin(NULL)
#endif // RB_SCROLLPANE_TEST
#ifdef RB_MULTICOLUMNLIST_TEST
  ,mcl(NULL)
  ,MultiColumnListWin(NULL)
  ,MultiColumnListCtrlWin(NULL)
  ,btnAddMclItem(NULL)
  ,tiMclCol1(NULL)
  ,tiMclCol2(NULL)
  ,tiMclCol3(NULL)
#endif // RB_MULTICOLUMNLIST_TEST
{

  LOGI("Constructing a gsMainMenu");
  velocity=new vcConstant();
  //  translateTo(0.0f);

}

/** The default destructor
  *
  * Deletes the \ref velocity member.
  *
  */
RainbruRPG::Core::gsMainMenu::~gsMainMenu(){
  if (velocity){
    delete velocity;
    velocity=NULL;
  }
#ifdef RB_SCROLLPANE_TEST
  delete ScrollPaneTestWin;
  delete ctrlWin;
#endif // RB_SCROLLPANE_TEST
#ifdef RB_MULTICOLUMNLIST_TEST
  delete mcl;
  delete MultiColumnListWin;
  delete MultiColumnListCtrlWin;
  delete btnAddMclItem;
  delete tiMclCol1;
  delete tiMclCol2;
  delete tiMclCol3;
#endif // RB_MULTICOLUMNLIST_TEST
}


/** Initialize the game state
  *
  * This function may not call GuiManager::beginGuiFadeIn as it is called
  * at the end of the menu border transition.
  *
  * The function used here are \ref gsMenuBase::init(), \ref setupMainMenu()
  * and \ref setupTabOrder().
  *
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
  * Is is called when the `network game` button is clicked. It 
  * begin a GUI fade out and switch to \ref gsConnection game state.
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsMainMenu::
onNetworkGameClicked(){
  LOGI("NetworkGame button clicked");

  /*
    GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GameEngine::getSingleton().changeState("gsConnection");
  GuiManager::getSingleton().beginGuiFadeIn();
  */

  return true;
}

/** Resume the main menu after a pause() call
  *
  * It calls \ref setupMainMenu() and show the window.
  *
  */
void RainbruRPG::Core::gsMainMenu::resume(){

  setupMainMenu();

  //  if (window)
  //    window->show();

  setupTabOrder();

  //isMouseButtonPressed=false;
  LOGI("gsMainMenu::resume() called");
}

/** Set up the keyboard navigation tab order
  *
  */
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
  * The members \ref window, \ref btnNetworkGame, \ref btnLocalTest and 
  * \ref btnExit are initialized here.
  *
  * If the associated option is enable in the \c ./configure script, 
  * it also call the createScrollPaneTestWindow() and 
  * createMultiColumnListTestWindow() functions.
  *
  */
void RainbruRPG::Core::gsMainMenu::setupMainMenu(){

  OgreGui::Window* w = new OgreGui::Window(mContainer, "aze", 10, 20, 600, 300);
  Label* l = new Label(w , 15, 25, 55, 95, "A");
  w->push_back(l);
  mContainer->push_back(w);
  mContainer->setDirty(true);

  /*
  BetaGUI::GUI* mGUI = &GUI::getSingleton();


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
  */
}

/** The BetaGui button callback implementation
  *
  * The button recieved in parameter is here compared with \ref btnLocalTest,
  * \ref btnNetworkGame and \ref btnExit.
  *
  * The buttons associated with the enable \c ./configure script options
  * are also tested in this function.
  *
  * \param b The button that was pressed
  *
  */
void RainbruRPG::Core::gsMainMenu::onButtonPress(BetaGUI::Button* b){

  if (b==btnLocalTest){
    translateTo(3.0);
    GameEngine::getSingleton().changeState("gsLocalTest");
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
#ifdef RB_MULTICOLUMNLIST_TEST
  else if ( b==btnAddMclItem ){
    onAddItem();
  }
#endif // RB_MULTICOLUMNLIST_TEST
  else{
    LOGW("gsMainMenu::onButtonPress called");
  }

}

/** Temporally stop this game state
  *
  * This function hides the \ref window. After a call to this function, you
  * could call \ref resume() to show again the game state.
  *
  */
void RainbruRPG::Core::gsMainMenu::pause(){
  if (window){
    //    window->hide();
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
  BetaGUI::GUI* mGUI =&GUI::getSingleton();
  if (!MultiColumnListWin){
    MultiColumnListWin =new Window(Vector4(10, 10, 340, 345),
				  BetaGUI::OWT_RESIZE_AND_MOVE, 
				  "MultiColumnList test", mGUI);
    mGUI->addWindow(MultiColumnListWin);

    Vector4 mclPosDim(10,30,320,305);
    mcl=new MultiColumnList(mclPosDim, MultiColumnListWin);
    mcl->setDebugName("MCL.MCLTestWindow");
    MultiColumnListWin->addWidget(mcl);

    mcl->addColumn( "Col1", 60 )->setMinimumWidth(20);
    mcl->addColumn( "Column2", 100 )->setMinimumWidth(40);
    mcl->addColumn( "Column3", 140 )->setMinimumWidth(40);

    // Adding item 1
    addItem("IT1ST1", "IT1ST2", "IT1ST3");
    addItem("Khean", "Carine", "Jerome");
    addItem("AAA", "Carine", "Jerome");
    addItem("BBB", "Carine", "Jerome");
    addItem("ert", "rty", "tyu");
    addItem("qsd", "sdf", "dfg");
    addItem("BBB", "Carine", "Jerome");
    addItem("ert", "rty", "tyu");
    addItem("qsd", "sdf", "dfg");
    addItem("AAA", "Carine", "Jerome");
    addItem("BBB", "Carine", "Jerome");
    addItem("ert", "rty", "tyu");
    addItem("qsd", "sdf", "dfg");
    addItem("BBB", "Carine", "Jerome");
    addItem("ert", "rty", "tyu");
    addItem("qsd", "sdf", "dfg");
    addItem("BBB", "Carine", "Jerome");
    addItem("ert", "rty", "tyu");
    addItem("qsd", "sdf", "dfg");
    addItem("BBB", "Carine", "Jerome");
    addItem("ert", "rty", "tyu");

    // Control window
    MultiColumnListCtrlWin=new Window(Vector4(200, 365, 420, 90),
		       BetaGUI::OWT_RESIZE_AND_MOVE, 
		       "MCLTest control window", mGUI);
    mGUI->addWindow(MultiColumnListCtrlWin);

    Vector4 labPosDim(12,30,50,20);
    Label* labPos=new Label(labPosDim,"Item content", MultiColumnListCtrlWin);
    MultiColumnListCtrlWin->addWidget(labPos);
    
    Vector4 tiXPosDim(120,30,90,20);
    tiMclCol1 = new TextInput(tiXPosDim, "", 5, MultiColumnListCtrlWin);
    MultiColumnListCtrlWin->addWidget(tiMclCol1);
    
    Vector4 tiYPosDim(220,30,90,20);
    tiMclCol2 = new TextInput(tiYPosDim, "", 5, MultiColumnListCtrlWin);
    MultiColumnListCtrlWin->addWidget(tiMclCol2);
 
    Vector4 tiCol3PosDim(320,30,90,20);
    tiMclCol3 = new TextInput(tiCol3PosDim, "", 5, MultiColumnListCtrlWin);
    MultiColumnListCtrlWin->addWidget(tiMclCol3);
   
    btnAddMclItem = new PushButton(Vector4(130, 55, 160, 24),
				 "Add Item", 
				 BetaGUI::Callback::Callback(this), 
				 MultiColumnListCtrlWin);
    MultiColumnListCtrlWin->addWidget(btnAddMclItem);
  }
  else{
    MultiColumnListWin->show();
  }
}

/** Add an item in the MultiColumnList used for test
  *
  * \note This function is build only if RB_MULTICOLUMNLIST_TEST is defined.
  *
  * \param s1, s2, s3 The columns captions
  *
  */
void RainbruRPG::Core::gsMainMenu::
addItem(const string& s1, const string& s2, const string& s3){
  MultiColumnListItem* item=new MultiColumnListItem();
  item->setText(0, s1);
  item->setText(1, s2);
  item->setText(2, s3);
  mcl->addItem(item);
}

/** The Add item button caption
  *
  * \note This function is build only if RB_MULTICOLUMNLIST_TEST is defined.
  *
  */
void RainbruRPG::Core::gsMainMenu::onAddItem(void){
  String col1, col2, col3;
  col1 = tiMclCol1->getValue();
  col2 = tiMclCol2->getValue();
  col3 = tiMclCol3->getValue();

  bool e1, e2, e3;
  e1 = col1.empty();
  e2 = col2.empty();
  e3 = col3.empty();

  if (!e1 && !e2 && !e3){
    addItem( col1, col2, col3 );
    tiMclCol1->setValue("");
    tiMclCol2->setValue("");
    tiMclCol3->setValue("");
  }
  else{
    LOGW("At least one column is empty. Item is not added");
  }


}


#endif // RB_MULTICOLUMNLIST_TEST

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

#include "gschangepassword.h"

#include <logger.h>
#include "gameengine.h"

/** The constructor of the game state
  *
  */
void RainbruRPG::Core::gsChangePassword::init(){
  isInit=true;

  this->irrDevice  = GameEngine::getSingleton().getIrrlichtDevice();
  this->driverType = GameEngine::getSingleton().getDriverType();
  this->irrDriver  = GameEngine::getSingleton().getIrrlichtDriver();
  this->irrSmgr    = GameEngine::getSingleton().getIrrlichtSmgr();
  this->irrGui     = GameEngine::getSingleton().getIrrlichtGui();

  createGui();
}

/** The destructor of the game state
  *
  */
void RainbruRPG::Core::gsChangePassword::cleanup(){
  LOGI("    Cleaning up gsConnection game state...");
  //  delete irrCamera;
   this->irrDevice=NULL;
  // delete q3node;
  // delete q3levelmesh;

  this->irrDevice  = NULL;
  //  this->driverType = NULL;
  this->irrDriver  = NULL;
  this->irrSmgr    = NULL;
  this->irrGui     = NULL;
}

/** The drawing method
  * 
  * This method is called by the GameEngine for each frame. It just
  * calls the Irrlicht draw function. It also calls the drawDebug()
  * method if \c debug is set to \c true.
  *
  */
void RainbruRPG::Core::gsChangePassword::run(){
  irrDriver->beginScene(true, true, 0);
  
  irrSmgr->drawAll();
  
  // draw gui
  irrGui->drawAll();
  
  // On a fini d'écrire	    
  irrDriver->endScene();
}

/** Creates the gui of the game GameState
  *
  * Do nothing.
  */
void RainbruRPG::Core::gsChangePassword::createGui(){
 LOGI("Creating AccountAcreation GUI...");

 // Window size
 s32 winW=400;
 s32 winH=155;

 // viewport size
 rect<s32> r=irrGui->getVideoDriver()->getViewPort( );
 s32 h=r.getHeight();
 s32 w=r.getWidth();

 // Win rect
 s32 x1=(w/2)-(winW/2);
 s32 y1=20;
 s32 x2=x1+winW;
 s32 y2=y1+winH;

 //rect<s32>(150,200,250,340)
 // Tab
  irrTab=irrGui->addTab(rect<s32>(0,0,w,h), 0, 1001);

 // Window
 IGUIWindow*win= irrGui->addWindow( rect<s32>( x1, y1, x2, y2), false, 
				    L"Change password", irrTab, 1002);

 // Widgets de 180 px centres
 s32 xBtn=(winW/2)-90;

 // Username
 irrGui->addStaticText(L"Username", rect<s32>(10,20,190,40), 
 		       false, true, win);

 irrGui->addEditBox (L"", rect<s32>(200,20,390,40), true, win, 10);


 // Password
 irrGui->addStaticText(L"Old password", rect<s32>(10,45,190,65), 
 		       false, true, win);

 IGUIEditBox* pwdEditBox=irrGui
   ->addEditBox (L"", rect<s32>(200,45,390,65), true, win, 11);

 // Repeat password
 irrGui->addStaticText(L"New password", rect<s32>(10,70,190,90), 
 		       false, true, win);

 irrGui->addEditBox (L"", rect<s32>(200,70,390,90), true, win, 11);


 // EMail adress
 irrGui->addStaticText(L"Repeat password", rect<s32>(10,95,190,115), 
 		       false, true, win);

 irrGui->addEditBox (L"", rect<s32>(200,95,390,115), true, win, 11);



 // Connect&create button
 irrGui->addButton(rect<s32>(xBtn+25,125,xBtn+140,145), win, 101, L"Change" );
 irrGui->addButton(rect<s32>(10,125,100,145), win, 102, 
		   L"Back" );
 
  irrTab->setVisible(true);
}

/** Pause the game GameState
  *
  * It will stop the Irrlicht Device timer and disable the player's
  * camera input. You may call resume() to continue playing. 
  *
  *
  */
void RainbruRPG::Core::gsChangePassword::pause(){
  LOGI("state CreateAccount in pause...");

  // stop the Irrlicht Engine
  irrDevice->getTimer()->stop();

  // Disabled camera input
  //  irrCamera->setInputReceiverEnabled(false);
  irrTab->setVisible(false);

}

/** Resume the game after a pause() call
  *
  * It reinitialize the erGame event receiver, send it to the Irrlicht device
  * and set the mouse cursor invisible.
  *
  */
void RainbruRPG::Core::gsChangePassword::resume(){
  LOGI("state CreateAccount in Resume...");

  erGame receiver;
  // GameEngine::getSingleton().getIrrlichtDevice()->setEventReceiver(&receiver);

  if (irrDevice==0)
    LOGE("Try to setting an EventReceiver on a NULL Irrlicht Device");

  // stop the Irrlicht Engine
  irrDevice->getTimer()->start();

  // Disabled camera input
  //  irrCamera->setInputReceiverEnabled(true);

  irrDevice->getCursorControl()->setVisible(true);
  irrTab->setVisible(true);

}

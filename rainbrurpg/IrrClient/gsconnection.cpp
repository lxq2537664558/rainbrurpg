/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

#include <logger.h>
#include "gameengine.h"

/** The constructor of the game state
  *
  */
void RainbruRPG::Core::gsConnection::init(){
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
void RainbruRPG::Core::gsConnection::cleanup(){
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
void RainbruRPG::Core::gsConnection::run(){
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
void RainbruRPG::Core::gsConnection::createGui(){
 LOGI("Creating GameConnection GUI...");

 // Window size
 s32 winW=400;
 s32 winH=170;

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

 // Background
  ITexture* tex=irrDriver->getTexture("../data/3d/wall.jpg");

  irrDriver->draw2DImage(tex,rect<s32>(0,0,512,512),
			    rect<s32>(0,0,w,h));

  //  IGUIImage* bgImage=irrGui->addImage(rect<s32>(0,0,w,h), irrTab);
  //  bgImage->setImage(tex);
  //  tex->regenerateMipMapLevels  	(   	  	 );
 // Window
 IGUIWindow*win= irrGui->addWindow( rect<s32>( x1, y1, x2, y2), false, 
				    L"Connection", irrTab, 1002);

 // Widgets de 180 px centres
 s32 xBtn=(winW/2)-90;

 // Username
 irrGui->addStaticText(L"Username", rect<s32>(10,20,190,40), 
 		       false, true, win);

 irrGui->addEditBox (L"", rect<s32>(10,40,180,60), true, win, 10);


 // Password
 irrGui->addStaticText(L"Password", rect<s32>(200,20,390,40), 
 		       false, true, win);

 IGUIEditBox* pwdEditBox=irrGui
   ->addEditBox (L"", rect<s32>(200,40,390,60), true, win, 11);

 // Connect&create button
 irrGui->addButton(rect<s32>(xBtn+25,75,xBtn+140,105), win, 101, L"Connect" );
 irrGui->addButton(rect<s32>(xBtn,125,xBtn+180,140), win, 102, 
		   L"Create account" );

 // Others button
 irrGui->addButton(rect<s32>(10,145,190,160), win, 103, 
		   L"Change password" );
 irrGui->addButton(rect<s32>(200,145,390,160), win, 104, 
		   L"Lost password" );

 irrTab->setVisible(true);

}

/** Pause the game GameState
  *
  * It will stop the Irrlicht Device timer and disable the player's
  * camera input. You may call resume() to continue playing. 
  *
  *
  */
void RainbruRPG::Core::gsConnection::pause(){
  LOGI("state Connection in pause...");

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
void RainbruRPG::Core::gsConnection::resume(){
  LOGI("state Connection in Resume...");

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

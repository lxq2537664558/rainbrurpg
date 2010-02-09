/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

#include "gsgameesc.h"

#include "logger.h"
#include "gameengine.h"
#include "irrfontmanager.h"

#include <IGUIButton.h>

/** The constructor of the gsGame game state
  *
  */
void RainbruRPG::Core::gsGameEsc::init(){
  isInit=true;
  triangleSelector=true;

  this->irrDevice  = GameEngine::getSingleton().getIrrlichtDevice();
  this->driverType = GameEngine::getSingleton().getDriverType();
  this->irrDriver  = GameEngine::getSingleton().getIrrlichtDriver();
  this->irrSmgr    = GameEngine::getSingleton().getIrrlichtSmgr();
  this->irrGui     = GameEngine::getSingleton().getIrrlichtGui();

  createGui();
}

/** The method called by GameEngine for each frame
  *
  * It simply call the draw methods for the Irrlicht scene manager and
  * Irrlicht gui environment.
  */
void RainbruRPG::Core::gsGameEsc::run(){
  irrDriver->beginScene(true, true, 0);
  irrSmgr->drawAll();
  // draw gui
  irrGui->drawAll();
 
  // On a fini d'écrire	    
  irrDriver->endScene();
}

/** The destructor of the game state
  *
  */
void RainbruRPG::Core::gsGameEsc::cleanup(){
  LOGI("Cleaning up state GameEsc ...");
  this->irrDevice  = NULL;
  //  this->driverType = NULL;
  this->irrDriver  = NULL;
  this->irrSmgr    = NULL;
  this->irrGui     = NULL;
}

/** The pause method
  *
  * It simply hides the tab containing the menu.
  *
  */
void RainbruRPG::Core::gsGameEsc::pause(){
  LOGI("Pausing state GameEsc ...");
   irrTab->setVisible(false);
}

/** The resum method
  *
  * We can call this method after a call to pause(). It makes the tab
  * containing the menu and the mouse cursor visible.
  *
  */
void RainbruRPG::Core::gsGameEsc::resume(){
  LOGI("Resuming state GameEsc ...");
   irrTab->setVisible(true);
  // enable mouse cursor
  irrDevice->getCursorControl()->setVisible(true);
}

/** Create the menu
  *
  * It uses a Irrlicht gui tab (not a tab control) sized as the
  * entireIrrlicht viewport, draw a centered window and add some buttons.
  */

void RainbruRPG::Core::gsGameEsc::createGui(){
 LOGI("Creating GameEsc GUI...");

 // Window size
 s32 winH=300;
 s32 winW=200;

 // viewport size
 rect<s32> r=irrGui->getVideoDriver()->getViewPort( );
 s32 h=r.getHeight();
 s32 w=r.getWidth();

 // Win rect
 s32 x1=(w/2)-(winW/2);
 s32 y1=(h/2)-(winH/2);
 s32 x2=x1+winW;
 s32 y2=y1+winH;

 //rect<s32>(150,200,250,340)
 // Tab
  irrTab=irrGui->addTab(rect<s32>(0,0,w,h), 0, 1001);

 // Window
 IGUIWindow*win= irrGui->addWindow( rect<s32>( x1, y1, x2, y2), false, 
				    L"In game menu", irrTab, 1002);

 // Boutons de 180 px centrés
 s32 xBtn=(winW/2)-90;

 // Boutons
 irr::gui::IGUIButton* b1= irrGui->addButton(rect<s32>(xBtn,50,xBtn+180,90), 
					     win, 01, L"Return to game");
 irr::gui::IGUIButton* b2= irrGui->addButton(rect<s32>(xBtn,100,xBtn+180,140), 
					     win, 102, L"Main menu");
 irr::gui::IGUIButton* b3= irrGui->addButton(rect<s32>(xBtn,150,xBtn+180,190), 
					     win, 103, L"Quit");

 IrrFontManager::getSingleton().setWidgetFont( b1, IFM_INC_BLACK, 26);
 IrrFontManager::getSingleton().setWidgetFont( b2, IFM_PLA_BLACK, 20);
 IrrFontManager::getSingleton().setWidgetFont( b3, IFM_SHA_BLACK, 20);

 irrTab->setVisible(false);
}


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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "guimanager.h"

#include "logger.h"
#include "iostream"

/** The constructor of the singleton
  *
  * This method must be called before using GuiManager
  */
void RainbruRPG::Gui::GuiManager::init(){
  LOGI("Initializing GuiManager...");
  this->irrDevice  = GameEngine::getSingleton().getIrrlichtDevice();
  this->irrDriver  = GameEngine::getSingleton().getIrrlichtDriver();
  this->irrSmgr    = GameEngine::getSingleton().getIrrlichtSmgr();
  this->irrGui     = GameEngine::getSingleton().getIrrlichtGui();

  lastFPS=-1;
  i_minFPS=25000;
  i_maxFPS=1;

  lastPri=-1;
  i_minPri=200000;
  i_maxPri=1;

}

/** The destructor of the singleton
  *
  *This method must be called after using GuiManager
  *
  */
void RainbruRPG::Gui::GuiManager::cleanup(){
  LOGI("Cleaning up GuiManager...");
  irrDevice=NULL;
  irrDriver=NULL;
  irrSmgr=NULL;
  irrGui=NULL;

  minFps=NULL;
  curFps=NULL;
  maxFps=NULL;

  minPri=NULL;
  curPri=NULL;
  maxPri=NULL;
}

/** Create a Irrlicht GUI window wich shows fps and primitives count
  *
  * The window shows the minimum, maximum ans actual number of fps
  * (frame per second) and drawn primitives
  *
  */
void RainbruRPG::Gui::GuiManager::createNumDebugWindow(){
  LOGI("Creating Numeric Debug Window...");

  int marge=2;

 rect<s32> r=irrGui->getVideoDriver()->getViewPort( );
 s32 h=r.getHeight();
 s32 w=r.getWidth();



  IGUIWindow* window = irrGui->addWindow( 
		      core::rect<s32>(marge, h-65-marge, 200+marge , h-marge), 
				       false, // modal?
				       L"Stats");
  
  irrGui->addStaticText(L"Min.",  
		     core::rect<s32>(50,20,100,35),
		     false, // border?
		     false, // wordwrap?
		     window);

  irrGui->addStaticText(L"Cur.",  
		     core::rect<s32>(100,20,150,35),
		     false, // border?
		     false, // wordwrap?
		     window);

  irrGui->addStaticText(L"Max.",  
		     core::rect<s32>(150,20,200,35),
		     false, // border?
		     false, // wordwrap?
		     window);

   irrGui->addStaticText(L"FPS :",  
		     core::rect<s32>(5,35,50,50),
		     false, // border?
		     false, // wordwrap?
		     window);

   irrGui->addStaticText(L"prim :",  
		     core::rect<s32>(5,50,50,65),
		     false, // border?
		     false, // wordwrap?
		     window);

   /// Variable FPS contents
   minFps=  irrGui->addStaticText(L"",  
		     core::rect<s32>(50,35,100,50),
		     false, // border?
		     false, // wordwrap?
		     window);

   curFps=  irrGui->addStaticText(L"",  
		     core::rect<s32>(100,35,150,50),
		     false, // border?
		     false, // wordwrap?
		     window);

   maxFps=  irrGui->addStaticText(L"",  
		     core::rect<s32>(150,35,200,50),
		     false, // border?
		     false, // wordwrap?
		     window);
 
   /// Variable FPS contents
   minPri=  irrGui->addStaticText(L"",  
		     core::rect<s32>(50,50,100,65),
		     false, // border?
		     false, // wordwrap?
		     window);

   curPri=  irrGui->addStaticText(L"",  
		     core::rect<s32>(100,50,150,65),
		     false, // border?
		     false, // wordwrap?
		     window);

   maxPri=  irrGui->addStaticText(L"",  
		     core::rect<s32>(150,50,200,65),
		     false, // border?
		     false, // wordwrap?
		     window);
}

/** Actualize the window created with createNumDebugWindow()
  *
  * The values are taken from the Irrlicht Driver getFPS() and
  * getPrimitiveCountDrawn() functions. We also manage the minimum and
  * maximum values of fps and primitives.
  *
  */
void RainbruRPG::Gui::GuiManager::showFPS(){
  int fps = irrDriver->getFPS();
  
  if (lastFPS != fps){
    core::stringw str = L"";
    str += fps;
    
    curFps->setText(str.c_str());
    lastFPS = fps;

    // Min FPS
    if (fps!=0&&fps<i_minFPS){
      i_minFPS=fps;
      minFps->setText(str.c_str());
    }

    // Max FPS
    if (fps>i_maxFPS){
      i_maxFPS=fps;
      maxFps->setText(str.c_str());
    }
  }

  // The number of primitives drawn
  int pri=irrDriver->getPrimitiveCountDrawn();

  if (lastPri!=pri){
    core::stringw str2 = L"";
    str2 += pri;
  
    curPri->setText( str2.c_str() );

    lastPri=pri;

    // Min pri
    if (pri!=0&&pri<i_minPri){
      i_minPri=pri;
      minPri->setText(str2.c_str());
    }

    // Max pri
    if (pri>i_maxPri){
      i_maxPri=pri;
      maxPri->setText(str2.c_str());
    }
  }
}



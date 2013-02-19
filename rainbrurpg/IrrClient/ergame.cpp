/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

#include "ergame.h"

#include "iostream"
#include "console.h"

/** The event Receiver main loop
  *
  * \param event The event
  */
bool  RainbruRPG::Events::erGame::OnEvent(SEvent event){

  if (event.EventType == EET_GUI_EVENT)	    {
    s32 id = event.GUIEvent.Caller->getID();
    IGUIEnvironment* env=GameEngine::getSingleton().getIrrlichtGui();
    irr::IrrlichtDevice * device  = GameEngine::getSingleton().
                                    getIrrlichtDevice();

    // Mouse events
    switch(event.GUIEvent.EventType){
		  
      /*
	If a button was clicked, it could be one of 'our'
	three buttons. If it is the first, we shut down the engine.
	If it is the second, we create a little window with some 
	text on it. We also add a string to the list box to log
	what happened. And if it is the third button, we create
	a file open dialog, and add also this as string to the list box.
	That's all for the event receiver.
      */
    case EGET_BUTTON_CLICKED:
    
      break;

    }
  }
  
  // Keyboard Events
   switch(event.KeyInput.Key){
   case KEY_ESCAPE :
     if (!event.KeyInput.PressedDown){
       //       LOGI(" TOUCHE ESC RELACHEE!!!!!!!");
       GameEngine::getSingleton().changeState(ST_GAME_ESC);
     }
     else {
       //       LOGI(" TOUCHE ESC APPUYEE!!!!!!!");
     }
     break;

   case KEY_F1  :
     if (!event.KeyInput.PressedDown){
       LOGI("Show Console");
       GameEngine::getSingleton().showConsole();
     }
     break;
     
   case KEY_F12  :
     if (!event.KeyInput.PressedDown){
       //       LOGI(" SNAP SHOT");
       Core::ScreenshotManager::getSingleton().take();
     }   
     break;

   }

  return false;
  
}

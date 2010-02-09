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

#include "erconsole.h"


#include "console.h"


/** The event Receiver main loop
  *
  * \param event The event
  */
bool  RainbruRPG::Events::erConsole::OnEvent(SEvent event){

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
   
    case EGET_EDITBOX_ENTER: //ENTER in the edit box
      Exception::Console::getSingleton().enter();
      break;
    }
  }
  
  // Keyboard Events
   switch(event.KeyInput.Key){

   case KEY_F1  :
     if (!event.KeyInput.PressedDown){
       LOGI("Hidding Console");
       GameEngine::getSingleton().hideConsole();
     }
     break;
     
   case KEY_F12  :
     if (!event.KeyInput.PressedDown){
       //       LOGI(" SNAP SHOT");
       Core::ScreenshotManager::getSingleton().take();
     }   
     break;

     // Console
   case KEY_UP :
     if (!event.KeyInput.PressedDown){
       Exception::Console::getSingleton().setUp();
     }   
     break;
   case KEY_DOWN :
     if (!event.KeyInput.PressedDown){
       Exception::Console::getSingleton().setDown();
     }  
     break;
   case KEY_PRIOR :
     if (!event.KeyInput.PressedDown){
       Exception::Console::getSingleton().setPageUp();
     }  
     break;
   case KEY_NEXT :
     if (!event.KeyInput.PressedDown){
       Exception::Console::getSingleton().setPageDown();
     }  
     break;
   case KEY_HOME :
     if (!event.KeyInput.PressedDown){
       Exception::Console::getSingleton().setHome();
     }  
     break;
   case KEY_END :
     if (!event.KeyInput.PressedDown){
       Exception::Console::getSingleton().setEnd();
     }  
     break;

   }

  return false;
  
}

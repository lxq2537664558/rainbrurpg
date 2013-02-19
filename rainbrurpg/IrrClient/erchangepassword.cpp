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

#include "erchangepassword.h"
#include "screenshotmanager.h"

/** The event Receiver main loop
  *
  * \param event The event
  */
bool RainbruRPG::Events::erChangePassword::OnEvent(SEvent event){

  if (event.EventType == EET_GUI_EVENT)	    {
    s32 id = event.GUIEvent.Caller->getID();
    IGUIEnvironment* env=GameEngine::getSingleton().getIrrlichtGui();
    irr::IrrlichtDevice * device  = GameEngine::getSingleton().
                                    getIrrlichtDevice();


    IGUIElement *root= env->getRootGUIElement();
    if (!root)
      LOGW("Failed to get IGUIEnvironment root element");

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
      if (id == 101){ //Create account bouton
	LOGI("CHANGE PWD button has been clicked");

	// Get the user edit box content
	if (root){
	  controlBefore(root);
	}

	return true;
      }
      if (id == 102){ //back account bouton
	LOGI("BACK button was clicked");
	GameEngine::getSingleton().changeState(ST_CONNECT);
	return true;
      }

      break;
    }
  }
  
  // Keyboard Events
  /*   switch(event.KeyInput.Key){
   case KEY_ESCAPE :
     if (!event.KeyInput.PressedDown)
       GameEngine::getSingleton().changeState(ST_GAME);
     
     break;

   case KEY_F12  :
   if (!event.KeyInput.PressedDown){
       Core::ScreenshotManager::getSingleton().take();
     }
   }
  */
  return false;
  
}

/** Makes some control before asking connection
  *
  * \param root the root IGUIElement as return by 
  *        IGUIEnvironment::getRootGUIElement()
  *
  * \return true if the controls are passed, false it they fail.
  */
bool RainbruRPG::Events::erChangePassword::controlBefore(IGUIElement* root){
  bool ret=true;
  IGUIEnvironment* env=GameEngine::getSingleton().getIrrlichtGui();

  // username test
  IGUIElement* userContent=root->getElementFromId(10, true);
  if (!userContent){
    LOGW("Failed to get username editbox element");
    ret=false;
  }
  else{ // The text was found
    const wchar_t* userText=userContent->getText();
    if (wcslen(userText)==0){
      LOGW("The username is empty");
      ret=false;
      env->addMessageBox (L"Connection failed", 
			  L"The username is empty");
      
    }
    else{ // username is not empty


      IGUIElement* pwdContent=root->getElementFromId(11, true);
      if (!pwdContent){
	LOGW("Failed to get password editbox element");
	ret=false;
      }
      else{ // The text was found
	const wchar_t* pwdText=pwdContent->getText();
	if (wcslen(pwdText)==0){
	  LOGW("The username is empty");
	  ret=false;
	  env->addMessageBox (L"Connection failed", 
			      L"The password is empty");
	  
	}  
      }
    }
  }
  // password test

  return ret;
}

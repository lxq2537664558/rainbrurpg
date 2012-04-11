/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file GsConnection.cpp
  * Implements a gamestate that lets the user enter its username and password
  *
  */

#include "GsConnection.hpp"
#include "guimanager.h"

#include <KeyboardNavigation.hpp>

#include <OgrePrerequisites.h> // for Ogre::String


/** The default constructor
  *
  * Constructs a new velocity and begin a translation to 0.0f.
  *
  */
RainbruRPG::Core::gsConnection::gsConnection():
  gsMenuBase("gsConnection", false)
{

  LOGI("Constructing a gsConnection");
  velocity=new vcConstant();
}

/** The default destructor
  *
  */
RainbruRPG::Core::gsConnection::~gsConnection(){
  if (velocity){
    delete velocity;
    velocity=NULL;
  }

  /* Must wait for OgreGui widgets implementation
  delete btnBack;
  delete btnConnect;
  delete btnCreateAccount;
  delete btnLostPwd;
  delete tiUserName;
  delete tiPassword;
  */
  /* delete window;
  delete winBack;
  */
}

/** Initialize the game state
  *
  * This function may not call GuiManager::beginGuiFadeIn as it is called
  * at the end of the menu border transition.
  *
  */
void RainbruRPG::Core::gsConnection::init(){
  LOGI("Initialising gsConnection");
  gsMenuBase::init();
  yBorder=0.5f;
  translateTo(0.4f);
  setupConnectionMenu();
  setupTabOrder();
  LOGI("gsConnection initialization complete");
}

/** The Quit CEGUI button callback
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onQuitClicked(){

  LOGI("Quit button clicked");
  GameEngine::getSingleton().quit();
  // Event handled
  return true;
}

/** Setup the connection menu buttons
  *
  */
void RainbruRPG::Core::gsConnection::setupConnectionMenu()
{
  // Should now use OgreGui
}

/** The callback of the Connect button
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onConnectClicked(){
  LOGI("Connect button clicked");
  return true;
}

/** Resume the state after a call or changestate call
  *
  */
void RainbruRPG::Core::gsConnection::resume(){
  setupConnectionMenu();
  setupTabOrder();
  //yBorder=0.5f;
  translateTo(0.4f);
}

/** The callback of the 'create account' button
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::
onCreateAccountClicked(){
  LOGI("onCreateAccountClicked called");

  GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GameEngine::getSingleton().changeState("gsCreateAccount");
  GuiManager::getSingleton().beginGuiFadeIn();

  return true;
}

/** The callback of the 'lost password' button
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Core::gsConnection::onLostPasswordClicked(){

  LOGI("onLostPasswordClicked called");

  GuiManager::getSingleton()
    .showMessageBox("Lost Password", 
    "This function isn't yet implemented. Please contact me\n"
    "directly (rainbru@free.fr)");
  return true;
}

/** Setup the tab order for this game state
  *
  */
void RainbruRPG::Core::gsConnection::
setupTabOrder()
{
}

/** The general OgreGUI buttons callback
  * 
  * \param btn The button that send the event
  *
  */
void RainbruRPG::Core::gsConnection::onButtonPress(BetaGUI::Button* btn)
{

}

/** Pause the execution of this GameState
  *
  */
void RainbruRPG::Core::gsConnection::pause()
{
  LOGI("gsConnection::pause() called");
}

/** The back button implementation
  *
  * Makes the GameEngine changes to ST_MAIN_MENU, the gsMainMenu game state.
  *
  */
void RainbruRPG::Core::gsConnection::onBackClicked(void)
{
    LOGI("Back button clicked");
    translateTo(0.5f);

 
    GuiManager::getSingleton().beginGuiFadeOut();

    // We must wait for the CEGUI fade end to prevent
    // SEGFAULT in access to CEGUI windows (getAlpha())
    while (GuiManager::getSingleton().isInGuiFadeOut()){
      Ogre::Root::getSingleton().renderOneFrame();
    }

    GameEngine::getSingleton().changeState("gsMainMenu");
    GuiManager::getSingleton().beginGuiFadeIn();

}

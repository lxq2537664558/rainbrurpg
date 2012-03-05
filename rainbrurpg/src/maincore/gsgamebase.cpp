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

/** \file gsgamebase.cpp
  * Implements a base class for all state supplying game capabilities
  *
  */

#include "gsgamebase.h"
#include <iostream>

#include <Logger.hpp>
#include "GameEngine.hpp"

/** The default constructor
  *
  */
RainbruRPG::Core::gsGameBase::gsGameBase(const std::string& vName):
  GameState(vName, GST_GAME)
{
  LOGI(_("Constructing a gsGameBase"));
  mapName="";
  mMoveScale=2.0f;
  inputWrapper=new InputWrapper();
  mTranslateVector=Vector3(0.0, 0.0, 0.0);
}

/** The initialization of the GameState
  *
  */
void RainbruRPG::Core::gsGameBase::init(){
  LOGI(_("Initialising gsGameBase"));

  mRoot=GameEngine::getSingleton().getOgreRoot();
  mSceneMgr=GameEngine::getSingleton().getOgreSceneMgr();

  isInit=true;
}

/** Cleans up the GameState
  *
  */
void RainbruRPG::Core::gsGameBase::cleanup(){
  delete inputWrapper;
}

/** Pauses the gamestate
  *
  */
void RainbruRPG::Core::gsGameBase::pause(){

}

/** Resumes the gamestate
  *
  * It restarts after a pause call.
  */
void RainbruRPG::Core::gsGameBase::resume(){
  LOGI(_("gsGameBase::resume called"));
}

/** Runs the gamestate
  *
  */
void RainbruRPG::Core::gsGameBase::run(){

}

/** Overrides the GameState::frameStarted() function
  *
  * It is call by the GameEngine for each frame.
  *
  * \param evt The Ogre FrameEvent
  *
  */
void RainbruRPG::Core::gsGameBase::frameStarted(const FrameEvent& evt){
  moveCamera();
}

/** Overrides the GameState::frameEnded() function
  *
  * It is call by the GameEngine for each frame.
  *
  * \param evt The Ogre FrameEvent
  *
  */
void RainbruRPG::Core::gsGameBase::frameEnded(const FrameEvent& evt){

}

/** Gets the name of the map
  *
  *
  *
  */
const char* RainbruRPG::Core::gsGameBase::getMapName(){
  return this->mapName;
}

/** The keypressed OIS callback implementation
  *
  * \param evt The OIS event
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsGameBase::keyPressed(const OIS::KeyEvent& evt){
  OIS::KeyCode kc=evt.key;

  if (kc==inputWrapper->getForward()){
    mTranslateVector.z = -mMoveScale;
  }

  if (kc==inputWrapper->getBackward()){
    mTranslateVector.z = mMoveScale;
  }

  if (kc==inputWrapper->getLeft()){
    mTranslateVector.x = -mMoveScale;

  }

  if (kc==inputWrapper->getRight()){
    mTranslateVector.x = mMoveScale;

  }
}

/** The keyReleased OIS callback implementation
  *
  * \param evt The OIS event
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsGameBase::keyReleased(const OIS::KeyEvent& evt){
  mTranslateVector=Vector3(0.0, 0.0, 0.0);

}

/** The mouseMoved OIS callback implementation
  *
  * \param evt The OIS event
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsGameBase::mouseMoved(const OIS::MouseEvent& evt){
  // Move the camera
  int x=evt.state.X.rel;
  int y=evt.state.Y.rel;
  mRotX = Degree(x * 0.13);
  mRotY = Degree(y * 0.13);
}

/** The mousePressed OIS callback implementation
  *
  * \param evt The OIS event
  * \param id The OIS mouse button
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsGameBase::
mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){

}

/** The mouseReleased OIS callback implementation
  *
  * \param evt The OIS event
  * \param id The OIS mouse button
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsGameBase::
mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){

}

/** Make all the changes to the camera
  *
  * Note that YAW direction is around a fixed axis (freelook style) 
  * rather than a natural YAW (e.g. airplane)
  *
  */
void RainbruRPG::Core::gsGameBase::moveCamera(){
  Camera* mCamera=GameEngine::getSingleton().getCamera();
  mCamera->yaw(-mRotX);
  mCamera->pitch(-mRotY);
  mCamera->moveRelative(mTranslateVector);

  mRotX=0;
  mRotY=0;
}

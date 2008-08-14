/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

/** \file exampleframelistener.cpp
  * Implements an Ogre frame listener
  *
  */

#include "exampleframelistener.h"

#include <iostream>

/** The constructor
  *
  * \param win The Ogre window used for rendering the scene
  * \param cam The camera in use
  * \param useBufferedInputKeys Using buffered input keys?
  * \param useBufferedInputMouse  Using buffered input mouse?
  *
  */
RainbruRPG::Core::ExampleFrameListener::
ExampleFrameListener( RenderWindow* win, Camera* cam, 
		      bool useBufferedInputKeys, 
		      bool useBufferedInputMouse){


       mUseBufferedInputKeys = useBufferedInputKeys;
      mUseBufferedInputMouse = useBufferedInputMouse;
      mInputTypeSwitchingOn = mUseBufferedInputKeys || mUseBufferedInputMouse;

      if (mInputTypeSwitchingOn){
	/*		mEventProcessor = new EventProcessor();
	mEventProcessor = EventProcessor::getSingletonPtr();
	mEventProcessor->initialise(win);
	mEventProcessor->startProcessingEvents();
	mEventProcessor->addKeyListener(this);
	mInputDevice = mEventProcessor->getInputReader();
	*/
      }
      else{
  
	//	mInputDevice = PlatformManager::getSingleton().createInputReader();
	//	mInputDevice->initialise(win,true, true);
	  }

      mCamera = cam;
      mWindow = win;
      mStatsOn = true;
      mNumScreenShots = 0;
      mTimeUntilNextToggle = 0;
      mMoveScale = 0.0f;
      mRotScale = 0.0f;
      mTranslateVector = Vector3::ZERO;
      mAniso = 1;
      mFiltering = TFO_BILINEAR;
}

/** The default destructor
  *
  */
RainbruRPG::Core::ExampleFrameListener::~ExampleFrameListener(){
  if (mInputTypeSwitchingOn){
    //    delete mEventProcessor;
  }
  else{
    //   PlatformManager::getSingleton().destroyInputReader( mInputDevice );
  }
}

/** Process to the key unbuffered input
  *
  * \param evt The FrameEvet got from Ogre
  *
  * \return Always return \c true (continue rendering)
  */
bool RainbruRPG::Core::ExampleFrameListener::
processUnbufferedKeyInput(const FrameEvent& evt){
  /*  if (mInputDevice->isKeyDown(KC_A)){
    // Move camera left
    mTranslateVector.x = -mMoveScale;
  }
  
  if (mInputDevice->isKeyDown(KC_D)){
    // Move camera RIGHT
    mTranslateVector.x = mMoveScale;
  }
  
  // Move camera forward by keypress. 
  if (mInputDevice->isKeyDown(KC_UP) || mInputDevice->isKeyDown(KC_W) ){
    mTranslateVector.z = -mMoveScale;
  }
  
  // Move camera backward by keypress.
  if (mInputDevice->isKeyDown(KC_DOWN) || mInputDevice->isKeyDown(KC_S)){
    mTranslateVector.z = mMoveScale;
  }
  
  if (mInputDevice->isKeyDown(KC_PGUP)){
    // Move camera up
    mTranslateVector.y = mMoveScale;
  }
  
  if (mInputDevice->isKeyDown(KC_PGDOWN)){
    // Move camera down
    mTranslateVector.y = -mMoveScale;
  }
  
  if (mInputDevice->isKeyDown(KC_RIGHT)){
    mCamera->yaw(-mRotScale);
  }
  
  if (mInputDevice->isKeyDown(KC_LEFT)){
    mCamera->yaw(mRotScale);
  }
  
  if( mInputDevice->isKeyDown( KC_ESCAPE) ){            
    return false;
  }
  
  // see if switching is on, and you want to toggle 
  if (mInputTypeSwitchingOn && mInputDevice->
      isKeyDown(KC_M) && mTimeUntilNextToggle <= 0){
    switchMouseMode();
    mTimeUntilNextToggle = 1;
  }
  
  if (mInputTypeSwitchingOn && mInputDevice->
      isKeyDown(KC_K) && mTimeUntilNextToggle <= 0){
    // must be going from immediate keyboard to buffered keyboard
    switchKeyMode();
    mTimeUntilNextToggle = 1;
  }
  if (mInputDevice->isKeyDown(KC_F) && mTimeUntilNextToggle <= 0){
    mStatsOn = !mStatsOn;
    mTimeUntilNextToggle = 1;
  }
  
  
  if (mInputDevice->isKeyDown(KC_T) && mTimeUntilNextToggle <= 0){
    switch(mFiltering){
    case TFO_BILINEAR:
      mFiltering = TFO_TRILINEAR;
      mAniso = 1;
      break;
    case TFO_TRILINEAR:
      mFiltering = TFO_ANISOTROPIC;
      mAniso = 8;
      break;
    case TFO_ANISOTROPIC:
      mFiltering = TFO_BILINEAR;
      mAniso = 1;
      break;
    default:
      break;
    }
    MaterialManager::getSingleton().
      setDefaultTextureFiltering(mFiltering);
    MaterialManager::getSingleton().setDefaultAnisotropy(mAniso);
    
    mTimeUntilNextToggle = 1;
  }
   
  if (mInputDevice->isKeyDown(KC_SYSRQ) && mTimeUntilNextToggle <= 0){
    char tmp[20];
    sprintf(tmp, "screenshot_%d.png", ++mNumScreenShots);
    mWindow->writeContentsToFile(tmp);
    mTimeUntilNextToggle = 0.5;
    //    mWindow->setDebugText(String("Wrote ") + tmp);
  }
  if (mInputDevice->isKeyDown(KC_R) && mTimeUntilNextToggle <=0){
    mSceneDetailIndex = (mSceneDetailIndex+1)%3 ;
    switch(mSceneDetailIndex) {
    case 0 : mCamera->setPolygonMode(PM_SOLID) ; break ;
    case 1 : mCamera->setPolygonMode(PM_WIREFRAME) ; break ;
    case 2 : mCamera->setPolygonMode(PM_POINTS) ; break ;
    }
    mTimeUntilNextToggle = 0.5;
  }
  static bool displayCameraDetails = false;
  if (mInputDevice->isKeyDown(KC_P) && mTimeUntilNextToggle <= 0){
    displayCameraDetails = !displayCameraDetails;
    mTimeUntilNextToggle = 0.5;

  }
  
  if (displayCameraDetails){
    // Print camera details
 
  }
  
*/
  // Return true to continue rendering
  return true;
}


/** Process to the mouse unbuffered input
  *
  * \param evt The FrameEvet got from Ogre
  *
  * \return Always return \c true (continue rendering)
  */
bool RainbruRPG::Core::ExampleFrameListener::
processUnbufferedMouseInput(const FrameEvent& evt){
  /* Rotation factors, may not be used if the second mouse 
     button is pressed. */
  
  /* If the second mouse button is pressed, then the mouse 
     movement results in 
     sliding the camera, otherwise we rotate. */
  /*  if( mInputDevice->getMouseButton( 1 ) ){
    mTranslateVector.x += mInputDevice->getMouseRelativeX() * 0.13;
    mTranslateVector.y -= mInputDevice->getMouseRelativeY() * 0.13;
  }
  else{
    mRotX = Degree(-mInputDevice->getMouseRelativeX() * 0.13);
    mRotY = Degree(-mInputDevice->getMouseRelativeY() * 0.13);
  }
  */
  return true;
}

/** Make all the changes to the camera
  *
  * Note that YAW direction is around a fixed axis (freelook style) 
  *rather than a natural YAW (e.g. airplane)
  *
  */
void RainbruRPG::Core::ExampleFrameListener::moveCamera(){
  mCamera->yaw(mRotX);
  mCamera->pitch(mRotY);
  mCamera->moveRelative(mTranslateVector);
}

/** The FrameStarted implementation
  *
  * \param evt The FrameEvet got from Ogre
  *
  * \return \c true to continue rendering, \c false to stop Ogre main loop
  */
bool RainbruRPG::Core::ExampleFrameListener::
frameStarted(const FrameEvent& evt){
  if(mWindow->isClosed())
    return false;
      
  //  if (!mInputTypeSwitchingOn){
  //  mInputDevice->capture();
    //  }

  if ( !mUseBufferedInputMouse || !mUseBufferedInputKeys){
    // one of the input modes is immediate, so setup what is 
    // needed for immediate mouse/key movement
    if (mTimeUntilNextToggle >= 0) 
      mTimeUntilNextToggle -= evt.timeSinceLastFrame;
    
    // If this is the first frame, pick a speed
    if (evt.timeSinceLastFrame == 0){
      mMoveScale = 1;
      mRotScale = 0.1;
    }
    
    // Otherwise scale movement units by time passed since last frame
    else{
      // Move about 100 units per second,
      mMoveScale = mMoveSpeed * evt.timeSinceLastFrame;
      // Take about 10 seconds for full rotation
      mRotScale = mRotateSpeed * evt.timeSinceLastFrame;
    }
    mRotX = 0;
    mRotY = 0;
    mTranslateVector = Vector3::ZERO;
  }
  

    if (processUnbufferedKeyInput(evt) == false){
      return false;
    }
  
  
   if (processUnbufferedMouseInput(evt) == false){
      return false;
    }
  
    moveCamera();
    
  return true;
}

/** Switch the buffered/unbeffered mouse input mode
  *
  */
void RainbruRPG::Core::ExampleFrameListener::switchMouseMode(){
  mUseBufferedInputMouse = !mUseBufferedInputMouse;
  /*  mInputDevice->setBufferedInput(mUseBufferedInputKeys, 
				 mUseBufferedInputMouse);
  */
}

/** Switch the buffered/unbeffered key input mode
  *
  */
void RainbruRPG::Core::ExampleFrameListener::switchKeyMode(){
  mUseBufferedInputKeys = !mUseBufferedInputKeys;
  /*  mInputDevice->setBufferedInput(mUseBufferedInputKeys, 
				 mUseBufferedInputMouse);
  */
}

/** Treat the key clicked event
  *
  * \param e The Ogre key event
  *
  */
void RainbruRPG::Core::ExampleFrameListener::keyClicked(KeyEvent* e){
  if (e->text == 'm'){
    switchMouseMode();
  }
  else if (e->text == 'k'){
    switchKeyMode();
  }
}

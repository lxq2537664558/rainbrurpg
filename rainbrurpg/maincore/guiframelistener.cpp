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

#include "guiframelistener.h"


/** The constructor
  *
  * \param win The Ogre render window
  * \param cam The Ogre camera
  *
  */
RainbruRPG::Events::GuiFrameListener::
GuiFrameListener(RenderWindow* win, Camera* cam):
  ExampleFrameListener(win, cam, true, true),
  mShutdownRequested(false),
  mMoveScale(1.1f)
{
  LOGI("Constructing GuiFrameListener");
  /*  mEventProcessor->addMouseMotionListener(this);
  mEventProcessor->addMouseListener(this);
  mEventProcessor->addKeyListener(this);
  */
}

/** Set the renderer to be shutdown
  *
  */
void RainbruRPG::Events::GuiFrameListener::requestShutdown(void){
  LOGI("requestShutdown called");
  mShutdownRequested = true;
}

/** The Ogre frame listener frameStarted implementation
  *
  * \param evt The Ogre FrameEvent parameter
  *
  * \return always \c true
  *
  */
bool RainbruRPG::Events::GuiFrameListener::frameStarted(const FrameEvent& evt){
  moveCamera();

  GameEngine::getSingleton().frameStarted(evt);

  GuiManager::getSingleton().guiFade();

  if (!GameEngine::getSingleton().running())
    mShutdownRequested=true;

  //  ExampleFrameListener::frameStarted( evt);

  return true;
}

/** The Ogre frame listener frameEnded implementation
  *
  * \param evt The Ogre FrameEvent parameter
  *
  * \return \c false if the shutdown was requested, otherwise, returns
  *         the value of ExampleFrameListener::frameEnded(evt)
  *
  */
bool RainbruRPG::Events::GuiFrameListener::frameEnded(const FrameEvent& evt){
  GameEngine::getSingleton().frameEnded(evt);
  GuiManager::getSingleton().showFPS();
  
  if (mShutdownRequested)
    return false;
  else
    return ExampleFrameListener::frameEnded(evt);
}

/** The mouseMoved listener implementation
  *
  * \param e The Ogre mouse event
  *
  */
bool RainbruRPG::Events::GuiFrameListener::mouseMoved(const MouseEvent& e){
  //  e.consume();
}

/** The mouseDragged listener implementation
  *
  * \param e The Ogre mouse event
  *
  */
bool RainbruRPG::Events::GuiFrameListener::mouseDragged(const MouseEvent& e){ 
  mouseMoved(e);
}

/** The mousePressed listener implementation
  *
  * \param e The Ogre mouse event
  *
  */
bool RainbruRPG::Events::GuiFrameListener::mousePressed(const MouseEvent& e){
  //  e.consume();
}

/** The mouseReleased listener implementation
  *
  * \param e The Ogre mouse event
  *
  */
bool RainbruRPG::Events::GuiFrameListener::mouseReleased(const MouseEvent& e){
  //  e.consume();
}

/** The keyPressed listener implementation
  *
  * \param e The Ogre key event
  *
  */
bool RainbruRPG::Events::GuiFrameListener::keyPressed(const KeyEvent& e){
  if(e.key == KC_ESCAPE){
    mShutdownRequested = true;
    //   e.consume();
    return true;
  }
  /* Move camera forward by keypress. */
  if (e.key == KC_UP ||e.key == KC_Z ){
    mTranslateVector.z = -mMoveScale;
  }
  /* Move camera backward by keypress. */
  /*  if (mInputDevice->isKeyDown(KC_DOWN) || mInputDevice->isKeyDown(KC_S)){
    mTranslateVector.z = mMoveScale;
  }
  */
  //  e.consume();
}

/** The keyReleased listener implementation
  *
  * \param e The Ogre key event
  *
  */
bool RainbruRPG::Events::GuiFrameListener::keyReleased(const KeyEvent& e){
  mTranslateVector.z = 0.0f;

   //  e.consume();
}

/** The keyClicked listener implementation
  *
  * \param e The Ogre key event
  *
  */
bool RainbruRPG::Events::GuiFrameListener::keyClicked(const KeyEvent& e){
  // Do nothing
  //  e.consume();
}

/** Change the current camera
  *
  * \param cam The new camera to set
  *
  */
void RainbruRPG::Events::GuiFrameListener::setCamera(Camera*cam){
  mCamera=cam;
}

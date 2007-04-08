/*
 *  Copyright 2006 Jerome PASQUIER
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
  * \param renderer The CEGUI renderer
  *
  */
RainbruRPG::Events::GuiFrameListener::
GuiFrameListener(RenderWindow* win, Camera* cam, CEGUI::Renderer* renderer)
                               :ExampleFrameListener(win, cam, true, true){
  mGUIRenderer=renderer;
  mShutdownRequested=false;

  LOGI("Constructing GuiFrameListener");
  mEventProcessor->addMouseMotionListener(this);
  mEventProcessor->addMouseListener(this);
  mEventProcessor->addKeyListener(this);

  mMoveScale = 1.1f;
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
void RainbruRPG::Events::GuiFrameListener::mouseMoved (MouseEvent *e){
  CEGUI::System::getSingleton().injectMouseMove(
	         e->getRelX() * mGUIRenderer->getWidth(), 
		 e->getRelY() * mGUIRenderer->getHeight());
  e->consume();
}

/** The mouseDragged listener implementation
  *
  * \param e The Ogre mouse event
  *
  */
void RainbruRPG::Events::GuiFrameListener::mouseDragged(MouseEvent *e){ 
  mouseMoved(e);
}

/** The mousePressed listener implementation
  *
  * \param e The Ogre mouse event
  *
  */
void RainbruRPG::Events::GuiFrameListener::mousePressed(MouseEvent *e){
  CEGUI::System::getSingleton().injectMouseButtonDown(
		 GameEngine::getSingleton().
		 convertOgreButtonToCegui(e->getButtonID()));

  e->consume();
}

/** The mouseReleased listener implementation
  *
  * \param e The Ogre mouse event
  *
  */
void RainbruRPG::Events::GuiFrameListener::mouseReleased(MouseEvent *e){
  CEGUI::System::getSingleton().injectMouseButtonUp(
		 GameEngine::getSingleton().
		 convertOgreButtonToCegui(e->getButtonID()));
  e->consume();
}

/** The keyPressed listener implementation
  *
  * \param e The Ogre key event
  *
  */
void RainbruRPG::Events::GuiFrameListener::keyPressed(KeyEvent* e){
  if(e->getKey() == KC_ESCAPE){
    mShutdownRequested = true;
    e->consume();
    return;
  }
  /* Move camera forward by keypress. */
  if (e->getKey() == KC_UP ||e->getKey() == KC_Z ){
    mTranslateVector.z = -mMoveScale;
  }
  /* Move camera backward by keypress. */
  if (mInputDevice->isKeyDown(KC_DOWN) || mInputDevice->isKeyDown(KC_S)){
    mTranslateVector.z = mMoveScale;
  }

 
  CEGUI::System::getSingleton().injectKeyDown(e->getKey());
  CEGUI::System::getSingleton().injectChar(e->getKeyChar());
  e->consume();
}

/** The keyReleased listener implementation
  *
  * \param e The Ogre key event
  *
  */
void RainbruRPG::Events::GuiFrameListener::keyReleased(KeyEvent* e){
    mTranslateVector.z = 0.0f;


  CEGUI::System::getSingleton().injectKeyUp(e->getKey());
  e->consume();
}

/** The keyClicked listener implementation
  *
  * \param e The Ogre key event
  *
  */
void RainbruRPG::Events::GuiFrameListener::keyClicked(KeyEvent* e){
  // Do nothing
  e->consume();
}

/** Change the current camera
  *
  * \param cam The new camera to set
  *
  */
void RainbruRPG::Events::GuiFrameListener::setCamera(Camera*cam){
  mCamera=cam;
}

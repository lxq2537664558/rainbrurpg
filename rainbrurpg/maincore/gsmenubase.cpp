/*
 *  Copyright 2006-2007 Jerome PASQUIER
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


#include "gsmenubase.h"

#include <iostream>
#include <OgreSceneNode.h>
#include <logger.h>

#include <OIS/OISPrereqs.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include "velocitycalculator.h"
#include "keyboardnavigation.h"
#include "inputmanager.h"
#include "inputwrapper.h"
#include "gameengine.h"
#include "guimanager.h"


/** The constructor
  *
  * The createMenu parameter should be \c true only one time as some
  * Ogre objects name would be duplicated.
  *
  * \param cm Should we ceate the dynamic menu ?
  *
  * \sa gsMenuBase::createMenu (variable)
  *
  */
RainbruRPG::Core::gsMenuBase::gsMenuBase(bool cm):
  bordRect(NULL),
  menuRect(NULL),
  dynaRect(NULL),
  velocity(NULL),
  createMenu(cm)
{

  LOGI("Constructing a  gsMenuBase");
  inputWrapper=new InputWrapper();
  tabNav=new KeyboardNavigation();
}

/** The initialization of the GameState
  *
  */
void RainbruRPG::Core::gsMenuBase::init(){
  LOGI("Initialising gsMenuBase");
  yBorder=1.1f;
  yBorderFrom=0.0f;
  yBorderTo=0.0f;

  initFrameNumber=3;
  initFrameCount=0;

  inTransition=false;

  // if yBorder=0.0f, u=1.0, v=0.7
  uMappingScreenSize=0.5f;
  vMappingScreenSize=0.7f;

  mRoot=GameEngine::getSingleton().getOgreRoot();
  mSceneMgr=GameEngine::getSingleton().getOgreSceneMgr();

  if (this->createMenu){
    menuNode = mSceneMgr->getRootSceneNode()
      ->createChildSceneNode("Menu");
    
    // The overlay that contains dynamic menu elements
    Overlay* rootOverlay=OverlayManager::getSingleton().create("MenuOverlay");
    rootOverlay->setZOrder(10);
    rootOverlay->show();

    drawMenuBackground();
    drawDynamicBackground();
    drawBorder();
    translateTo(0.5);
    setCorners();
  }

  isInit=true;
}

/** Cleans up the GameState
  *
  */
void RainbruRPG::Core::gsMenuBase::cleanup(){
  if (velocity){
    delete velocity;
    velocity=NULL;
  }

  delete inputWrapper;
  delete tabNav;

  inputWrapper=NULL;
  tabNav=NULL;
}

/** Pauses the gamestate
  *
  */
void RainbruRPG::Core::gsMenuBase::pause(){

}

/** Rerun after a pause() call or a state change
  *
  * It is used to reload a removed layout when recovering a
  * previous changed state and re-register the events.
  *
  */
void RainbruRPG::Core::gsMenuBase::resume(){
}

/** Runs the gamestate
  *
  */
void RainbruRPG::Core::gsMenuBase::run(){

}

/** Draws the border
  *
  */
void RainbruRPG::Core::gsMenuBase::drawBorder(){
  LOGI("Draw border");

  bordRect=static_cast<OverlayContainer*>
    (OverlayManager::getSingleton().createOverlayElement("Panel", "Dynamic_Border"));
  
  bordRect->setMetricsMode(GMM_RELATIVE);
  bordRect->setDimensions(0.05,1.0);
  bordRect->setPosition(yBorder-0.025, 0.0);
  bordRect->setMaterialName("RainbruRPG.menu.border");

  OverlayManager::getSingleton().getByName("MenuOverlay")->add2D(bordRect);
  bordRect->show();
}

/** Draw the right panel background
  *
  */
void RainbruRPG::Core::gsMenuBase::drawMenuBackground(){
  LOGI("Draw MenuBackground");

   menuRect=static_cast<OverlayContainer*>
    (OverlayManager::getSingleton().createOverlayElement("Panel", 
							 "Static_Menu"));
  
  menuRect->setMetricsMode(GMM_RELATIVE);
  menuRect->setDimensions(1.0,1.0);
  menuRect->setPosition(yBorder, 0.0);
  menuRect->setMaterialName("RainbruRPG.menu.static");

  OverlayManager::getSingleton().getByName("MenuOverlay")->add2D(menuRect);
  menuRect->show();
}

/** Draw the left panel background
  *
  */
void RainbruRPG::Core::gsMenuBase::drawDynamicBackground(){
  LOGI("Draw DynamicBackground");

  dynaRect=static_cast<OverlayContainer*>
    (OverlayManager::getSingleton().createOverlayElement("Panel", 
							 "Dynamic_Menu"));
  
  dynaRect->setMetricsMode(GMM_RELATIVE);
  dynaRect->setDimensions(1.2,1.0);
  dynaRect->setPosition(yBorder-0.2, 0.0);
  dynaRect->setMaterialName("RainbruRPG.menu.dynamic");

  OverlayManager::getSingleton().getByName("MenuOverlay")->add2D(dynaRect);
  dynaRect->show();
}

/** Makes the menu transition
  *
  */
void RainbruRPG::Core::gsMenuBase::transition(){
  if (inTransition){
    if (velocity){
      // Engine initialization
      if (initFrameCount<initFrameNumber){
	initFrameCount++;
	velocity->reset();
      }
      else{
	yBorder-=  velocity->getNextFrame(inTransition);
      }

      // If the transition is ended
      if (!inTransition){
	LOGI("Transition ended");
	yBorder=yBorderTo;
	GuiManager::getSingleton().beginGuiFadeIn();
      }
    }
    else{
      LOGW("Cannot get translation value, VelocityCalculator pointer is NULL");
    }
    setCorners();
  }
}

/** Moves the border and the menus by moving their corners
  *
  */
void RainbruRPG::Core::gsMenuBase::setCorners(){
  bordRect->setPosition(yBorder-0.025f, 0.0);
  menuRect->setPosition(yBorder+0.025f, 0.0);
  // Adding 0.2f to x to avoid a left black border
  dynaRect->setPosition(yBorder-1.225f, 0.0);

}

/** Sets the the menu to translate to the given position
  *
  * \param f The position in the screen the translation go to.
  *
  */
void RainbruRPG::Core::gsMenuBase::translateTo(float f){
  LOGI("Setting gsMenuBase translation");
  inTransition=true;
  yBorderFrom=yBorder;
  yBorderTo=f;

  if (velocity){
    velocity->setTranslationLenght(getTranslationLenght(yBorderFrom, 
							yBorderTo));
    velocity->start();
  }
  else{
    LOGW("Cannot start VelocityCalculator, pointer is NULL");
  }

  if (bordRect&&menuRect&&dynaRect){
    LOGI("translation pointers OK");
  }
  else{
    try{
      bordRect=static_cast<OverlayContainer*>
	(OverlayManager::getSingleton().getOverlayElement("Dynamic_Border"));
      menuRect=static_cast<OverlayContainer*>
	(OverlayManager::getSingleton().getOverlayElement("Static_Menu"));
      dynaRect=static_cast<OverlayContainer*>
	(OverlayManager::getSingleton().getOverlayElement("Dynamic_Menu"));

    }
    catch(...){
      LOGE("One or more translation pointers is NULL");
    }
  }

}

/** Is this menu in transition?
  *
  * It simply returns the value of the inTransition variable.
  *
  * \return \c true if we are in transition, \c false otherwise
  *
  */
bool RainbruRPG::Core::gsMenuBase::isInTransition(){
  return this->inTransition;
}

/** Get the lenght between two points
  *
  * The \c to and \c from values are in OpenGL format (-1.0 to 1.0).
  * So we need to calculate it.
  *
  * The return value is positive is we move from right to left and 
  * negative from left to right.
  *
  * \param from From where the transition begin
  * \param to Where the transition is going to
  *
  * \return A lenght in the OpenGL format wich can be positive or negative.
  */
float RainbruRPG::Core::gsMenuBase::getTranslationLenght(float from, 
							     float to){

  float ret=0.0f;

  if (from>=0.0f && to>=0.0f){
    ret=from-to;
  }
  else if (from>=0.0f && to<0.0f){
    ret=from;
    ret-=to;
  }
  else{
    LOGW("getTranslationLenght's case not implemented");
  }
  LOGI("getTranslationLenght debug :");
  LOGCATS("From :");
  LOGCATF(from);
  LOGCATS(" To :");
  LOGCATF(to);
  LOGCATS(" ret= ");
  LOGCATF(ret);
  LOGCAT();

  return ret;
}

/** Overrides the GameState::frameStarted() function
  *
  * It is call by the GameEngine for each frame.
  *
  * \param evt The Ogre FrameEvent
  *
  */
void RainbruRPG::Core::gsMenuBase::frameStarted(const FrameEvent& evt){


  if (isInTransition())
    transition();

}

/** Overrides the GameState::frameEnded() function
  *
  * It is call by the GameEngine for each frame.
  *
  * \param evt The Ogre FrameEvent
  *
  */
void RainbruRPG::Core::gsMenuBase::frameEnded(const FrameEvent& evt){

}

/** The keyReleased OIS callback implementation
  *
  * \param evt The OIS event
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsMenuBase::keyReleased(const OIS::KeyEvent& evt){
  OIS::KeyCode kc=evt.key;
  unsigned int text=evt.text;
  bool masked=false;

  // Special cases
  CEGUI::Key::Scan scanCode;

  if (kc==OIS::KC_DELETE){
    CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::Delete);
  }
  else if (kc==OIS::KC_BACK){
    CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::Backspace);
  }
  else if (kc==OIS::KC_LEFT){
    CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::ArrowLeft);
  }
  else if (kc==OIS::KC_RIGHT){
    CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::ArrowRight);
  }
  else if (kc==OIS::KC_TAB){
    CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::Tab);
  }
  else if (kc==OIS::KC_LSHIFT){
    CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::LeftShift);
  } 
  else if (kc==OIS::KC_RSHIFT){
    CEGUI::System::getSingleton().injectKeyUp(CEGUI::Key::RightShift);
  }

  return true;
}

/** The mouseMoved OIS callback implementation
  *
  * \param evt The OIS event
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsMenuBase::mouseMoved(const OIS::MouseEvent& evt){
  // CEGUI
  int x=evt.state.X.rel;
  int y=evt.state.Y.rel;
  float deltaX=x*inputWrapper->getMouseMenuSensibility();
  float deltaY=y*inputWrapper->getMouseMenuSensibility();

  CEGUI::System::getSingleton().injectMouseMove(deltaX, deltaY);


  // OgreGUI
  mouseX=evt.state.X.abs;
  mouseY=evt.state.Y.abs;

  GameEngine::getSingleton().getOgreGui()
    ->injectMouse(mouseX, mouseY);

  return true;
}

/** The mousePressed OIS callback implementation
  *
  * \param evt The OIS event
  * \param id The OIS mouse button
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsMenuBase::
mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){

  CEGUI::System::getSingleton().injectMouseButtonDown(
    inputWrapper->OISButtontoCEGUI(id));

  GameEngine::getSingleton().getOgreGui()
    ->injectMouseButtonPressed("gsMenuBase::mousePressed");

  // OgreGUI
  mouseX=evt.state.X.abs;
  mouseY=evt.state.Y.abs;

  GameEngine::getSingleton().getOgreGui()
    ->injectMouse(mouseX, mouseY);


  return true;
}

/** The mouseReleased OIS callback implementation
  *
  * \param evt The OIS event
  * \param id The OIS mouse button
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsMenuBase::
mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
  // CEGUI
  CEGUI::System::getSingleton().injectMouseButtonUp(
    inputWrapper->OISButtontoCEGUI(id));

  // OgreGUI
  GameEngine::getSingleton().getOgreGui()
    ->injectMouseButtonReleased();

  return true;
}

/** The keyPressed OIS callback implementation
  *
  * It injects the pressed key to the OgreGUI::GUI object.
  *
  * \param evt The OIS event
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsMenuBase::keyPressed(const OIS::KeyEvent& evt){
  // Injecting BackSpace as a special char
  if (evt.key == OIS::KC_BACK){
    GameEngine::getSingleton().getOgreGui()->injectBackspace(mouseX, mouseY);
  }
  /* The next specials cases (Left shift and Right Shift) are
   * mandatory. Injecting this in OgreGUI::GUI seems to break
   * the next injected characters. No more entries can be 
   * injected if a SHIFT modifier is sent.
   *
   */
  else if (evt.key == OIS::KC_LSHIFT){
    LOGI("Left shift clicked");
  }
  else if (evt.key == OIS::KC_RSHIFT){
    LOGI("Right shift clicked");
  }
  else{
    char c=(char)evt.text;
    Ogre::String s="";
    s+=c;

    if (s.size()!=0){
      GameEngine::getSingleton().getOgreGui()->injectKey(s, mouseX, mouseY);
    }
  }

  return true;
}


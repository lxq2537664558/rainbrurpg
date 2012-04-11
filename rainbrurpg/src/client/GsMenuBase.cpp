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

/** \file GsMenuBase.cpp
  * Implements the base class for all menu game state
  *
  */

#include "GsMenuBase.hpp"

#include <iostream>
#include <OgreSceneNode.h>
#include <Logger.hpp>

#include <OIS/OISPrereqs.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>
#include <OgreVector4.h>

#include <Container.hpp>
//#include <bgwindow.h>
#include <staticimage.h>
#include <TextureNotFoundException.hpp>
#include <InputManager.hpp>

#include "GameEngine.hpp"
#include "guimanager.h"
#include "bggui.h"

#include <InputWrapper.hpp>
#include <KeyboardNavigation.hpp>
#include <VelocityCalculator.hpp>


using namespace RainbruRPG::Exception;

/** The constructor
  *
  * The createMenu parameter should be \c true only one time as some
  * Ogre objects name would be duplicated.
  *
  * \param vName The game state name
  * \param cm    Should we ceate the dynamic menu ?
  *
  * \sa gsMenuBase::createMenu (variable)
  *
  */
RainbruRPG::Core::gsMenuBase::gsMenuBase(const string& vName, bool cm):
  GameState(vName, GST_MENU),
  velocity(NULL),
  createMenu(cm),
  menuWindow(NULL)
{

  LOGI("Constructing a  gsMenuBase");
  inputWrapper=new InputWrapper();
  tabNav=new KeyboardNavigation();

  string textureName = "staticmenu.png";

  try{
    mBackgroundTexture = Ogre::TextureManager::getSingleton()
      .load(textureName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  }
  catch(const Ogre::FileNotFoundException& e){
    throw TextureNotFoundException(textureName);
  }


  mContainer->setTexturePtr(mBackgroundTexture);
  
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
    createStaticMenu();

    translateTo(0.5);
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

/** Creates the OgreGui window used to draw dynamic menu widget
  *
  * This must be called before calling createBorder(), createMenuBackground()
  * or createDynamicBackground().
  *
  */
void RainbruRPG::Core::gsMenuBase::createMenuWindow(void){
  /*
  BetaGUI::GUI* mGUI =&GUI::getSingleton();

  RenderWindow* mRenderWindow=GameEngine::getSingleton().getRenderWindow();
  unsigned int w=mRenderWindow->getWidth();
  unsigned int h=mRenderWindow->getHeight();

  Ogre::Vector4 v(0, 0, w,h);

  menuWindow = new BetaGUI::Window(v, BetaGUI::OWT_NONE, 
				   "Dynamic menu", mGUI, OSI_NAVIGATION);

  mGUI->addWindowBeforeOverlays(menuWindow);
  */
}

/** Makes the menu transition
  *
  */
void RainbruRPG::Core::gsMenuBase::transition(){
  RenderWindow* mRenderWindow=GameEngine::getSingleton().getRenderWindow();
  unsigned int w=mRenderWindow->getWidth();
  unsigned int h=mRenderWindow->getHeight();

  if (inTransition){
    if (velocity){
      // Engine initialization
      if (initFrameCount<initFrameNumber){
	initFrameCount++;
	velocity->reset();
      }
      else{
	yBorder-=velocity->getNextFrame(inTransition);

	float newYBorder=yBorder+1.0f;
	int xPos=(int)newYBorder*(w/2);

      }

      // If the transition is ended
      if (!inTransition){
	yBorder=yBorderTo;
	GuiManager::getSingleton().beginGuiFadeIn();
      }
    }
    else{
      LOGW("Cannot get translation value, VelocityCalculator pointer is NULL");
    }
  }
}

/** Sets the menu to translate to the given position
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
  /*
  // CEGUI
  int x=evt.state.X.rel;
  int y=evt.state.Y.rel;
  float deltaX=x*inputWrapper->getMouseMenuSensibility();
  float deltaY=y*inputWrapper->getMouseMenuSensibility();

  // OgreGUI
  mouseX=evt.state.X.abs;
  mouseY=evt.state.Y.abs;

  GUI::getSingleton().injectMouse(mouseX, mouseY);
  */
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
  /*
  if (evt.state.buttonDown(OIS::MB_Left)){
    GUI::getSingleton().injectMouseButtonPressed("gsMenuBase::mousePressed");
  }
  else if (evt.state.buttonDown(OIS::MB_Right)){
    GUI::getSingleton()
      .injectRightMouseButtonPressed("gsMenuBase::mousePressed");
  }

  // OgreGUI
  mouseX=evt.state.X.abs;
  mouseY=evt.state.Y.abs;
  */
  /* v0.0.5-189 : 
   * I removed this call because a segfault occurs here.
   * The segfault occured in MousePointer::setState().
   */
  //  GUI::getSingleton().injectMouse(mouseX, mouseY);


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
  // OgreGUI
  //  GUI::getSingleton().injectMouseButtonReleased();

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
    //    GUI::getSingleton().injectBackspace(mouseX, mouseY);
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
  else if (evt.key == OIS::KC_LMENU){
    LOGI("Left Alt clicked");
  }
  else if (evt.key == OIS::KC_RMENU){
    LOGI("Right Alt clicked");
  }
  else if ((evt.key == 0) && (evt.text==0)){
    LOGI("evt.key == 0 && evt.text=0");
  }
  else{
  char c=(char)evt.text;

    if (c==0x40){
      LOGI("<At> sign clicked");

      Ogre::String s="@";
      //      GUI::getSingleton().injectKey(s, mouseX, mouseY);
    }
    else {
      LOGCATS("Another key pressed : text=");
      LOGCATI(c);
      LOGCATS(" key=");
      LOGCATI(evt.key);
      LOGCAT();
      Ogre::String s="";
      s+=c;
      
      if (s.size()!=0){
	//	GUI::getSingleton().injectKey(s, mouseX, mouseY);
      }
    }
  }

  return true;
}

/** Creates the static menu
  * 
  * Create a static background image.
  *
  */
void RainbruRPG::Core::gsMenuBase::createStaticMenu(void){
  /*
  BetaGUI::GUI* mGUI = &GUI::getSingleton();

  RenderWindow* mRenderWindow=GameEngine::getSingleton().getRenderWindow();
  unsigned int w=mRenderWindow->getWidth();
  unsigned int h=mRenderWindow->getHeight();

  Ogre::Vector4 v(0, 0, w,h);

  menuWindow = new BetaGUI::Window(v, BetaGUI::OWT_NONE, 
				   "Static menu", mGUI, OSI_NAVIGATION);

  mGUI->addWindowBeforeOverlays(menuWindow);

  Ogre::Vector4 d(0, 0, w,h);
  StaticImage* staticMenu =new StaticImage(d, menuWindow);
  staticMenu->setAlphaMode(QBM_ALPHA);
  staticMenu->setTextureName("staticmenu.png");
  menuWindow->addWidget(staticMenu);

  GuiManager::getSingleton().createErrorLabel();
  */
}

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

#include <OgreSceneNode.h>

#include "gsmenubase.h"
#include <iostream>

#include <logger.h>
#include "gameengine.h"

/** The default constructor
  *
  */
RainbruRPG::Core::gsMenuBase::gsMenuBase(){
  LOGI("Constructing a  gsMenuBase");
  velocity=NULL;
  stateType=GST_MENU;
  inputWrapper=new InputWrapper();
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

  menuNode = mSceneMgr->getRootSceneNode()
    ->createChildSceneNode("Menu");

  translateTo(0.0);

  drawMenuBackground();
  drawDynamicBackground();
  drawBorder();
  setCorners();
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
}

/** Pauses the gamestate
  *
  */
void RainbruRPG::Core::gsMenuBase::pause(){

}

/** Resumes the gamestate
  *
  * It restarts after a pause call.
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

  // Create background material
  MaterialPtr material = MaterialManager::getSingleton().create("Border", "General");

  material->getTechnique(0)->getPass(0)->createTextureUnitState("border.jpg");
  material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
  material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
  material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
  material->getTechnique(0)->getPass(0)->getTextureUnitState(0)
    ->setTextureScale(1.0f, 0.25f);
  
  // Create background rectangle covering the whole screen
  bordRect = new Rectangle2D(true);
  //rect->setCorners(-1.0, 1.0, 1.0, -1.0);
  bordRect->setCorners(yBorder-0.05f, 1.0, yBorder+0.05f, -1.0);
  bordRect->setMaterial("Border");
  
  bordRect->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 
				      100000.0*Vector3::UNIT_SCALE));
  
  // Attach background to the scene
  SceneNode* node = menuNode->createChildSceneNode("Border");
  node->attachObject(bordRect);
}

/** Draw the right panel background
  *
  */
void RainbruRPG::Core::gsMenuBase::drawMenuBackground(){
  LOGI("Draw MenuBackground");

  // Create background material
  MaterialPtr material = MaterialManager::getSingleton()
    .create("StaticBackground", "General");

  material->getTechnique(0)->getPass(0)
    ->createTextureUnitState("staticmenu.jpg");

  material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
  material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
  material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
  material->getTechnique(0)->getPass(0)->getTextureUnitState(0)
    ->setTextureScale(uMappingScreenSize, vMappingScreenSize);
  
  menuRect = new Rectangle2D(true);
  menuRect->setMaterial("StaticBackground");

  menuRect->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 
				      100000.0*Vector3::UNIT_SCALE));
 
  // Attach background to the scene
  SceneNode* node = menuNode->createChildSceneNode("StaticBackground");
  node->attachObject(menuRect);
}

/** Draw the left panel background
  *
  */
void RainbruRPG::Core::gsMenuBase::drawDynamicBackground(){
  LOGI("Draw DynamicBackground");

  // Create background material
  MaterialPtr material = MaterialManager::getSingleton().create("DynamicBackground", "General");
  material->getTechnique(0)->getPass(0)->createTextureUnitState("dynamicmenu.jpg");
  material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
  material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
  material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
  material->getTechnique(0)->getPass(0)->getTextureUnitState(0)
    ->setTextureScale(uMappingScreenSize, vMappingScreenSize);
  
  // Create background rectangle covering the whole screen
  dynaRect = new Rectangle2D(true);
  dynaRect->setMaterial("DynamicBackground");
  
  dynaRect->setBoundingBox(AxisAlignedBox(-100000.0*Vector3::UNIT_SCALE, 
				      100000.0*Vector3::UNIT_SCALE));
  
  // Attach background to the scene
  SceneNode* node = menuNode->createChildSceneNode("DynamicBackground");
  node->attachObject(dynaRect);
}

/** Draws a static image
  *
  * \todo To remove
  *
  */
void RainbruRPG::Core::gsMenuBase::drawStaticImage(){
      
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
  bordRect->setCorners(yBorder-0.05f, 1.0, yBorder+0.05f, -1.0);
  dynaRect->setCorners(yBorder-2.10f, 1.0, yBorder-0.05f, -1.0);
  menuRect->setCorners(yBorder+0.05f, 1.0, yBorder+2.05f, -1.0);

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

/** The keyPressed OIS callback implementation
  *
  * \param evt The OIS event
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsMenuBase::keyPressed(const OIS::KeyEvent& evt){
  return true;
}

/** The keyReleased OIS callback implementation
  *
  * \param evt The OIS event
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::gsMenuBase::keyReleased(const OIS::KeyEvent& evt){
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
  int x=evt.state.X.rel;
  int y=evt.state.Y.rel;
  float deltaX=x*inputWrapper->getMouseMenuSensibility();
  float deltaY=y*inputWrapper->getMouseMenuSensibility();

  CEGUI::System::getSingleton().injectMouseMove(deltaX, deltaY);
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

  CEGUI::System::getSingleton().injectMouseButtonUp(
    inputWrapper->OISButtontoCEGUI(id));

  return true;
}

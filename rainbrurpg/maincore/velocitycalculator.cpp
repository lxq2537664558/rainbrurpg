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

/** \file velocitycalculator.cpp
  * Implements a superlass for computation of moving velocity
  *
  */

#include "velocitycalculator.h"

#include <logger.h>
#include "guimanager.h"

/** The default constructor
  *
  * It creates a new Ogre timer and set the transitionTime equal to the
  * GuiManager default transition time.
  *
  */
RainbruRPG::Core::VelocityCalculator::VelocityCalculator(){
  mRunning=false;
  //  timer= Ogre::PlatformManager::getSingleton().createTimer();
  timer= new Timer();

  this->setTransitionTime(GuiManager::getSingleton().getTransitionTime());
  translationLenght=0;
}

/** The default destructor
  *
  * It asks the Ogre platform manager to destroy the used Ogre timer.
  *
  */
RainbruRPG::Core::VelocityCalculator::~VelocityCalculator(){
  //  Ogre::PlatformManager::getSingleton().destroyTimer(timer);

  delete timer;
  timer=NULL;
}

/** Start the calculation of the ranslation
  *
  */
void RainbruRPG::Core::VelocityCalculator::start(){
  mRunning=true;
  lastFrameTimeLine=0;
  timer->reset();
}

/** Is this velocity calculator running ?
  * 
  * It simply returns the value of VelocityCalculator::mRunning
  *
  * \return \c true if this instance is running, otherwise \c false
  *
  */
bool RainbruRPG::Core::VelocityCalculator::running(){
  return this->mRunning;
}

/** Sets the total lenght of translation
  *
  * OpenGL uses often a translation factor in screen size (1.0 is the 
  * half screen).
  *
  * It sends a warning log if the given parameter is equal to 0.
  *
  * \param f The new translation lenght
  *
  */
void RainbruRPG::Core::VelocityCalculator::setTranslationLenght(float f){
  translationLenght=f;
}

/** Sets the transition time
  *
  * See the subclass documentation you are using to know if it uses
  * milliseconds or microseconds as the Ogre timer handles both times.
  *
  * It sends a warning log if the given parameter is equal to 0.
  *
  * \param i The new transition time
  *
  */
void RainbruRPG::Core::VelocityCalculator::setTransitionTime(unsigned int i){
  if (i==0)
    LOGW("setting a null transition time");

  transitionTime=i;
}

/** Reset this instance
  *
  * It simply calls reset in the used Ogre timer.
  *
  */
void RainbruRPG::Core::VelocityCalculator::reset(){
  timer->reset();

}

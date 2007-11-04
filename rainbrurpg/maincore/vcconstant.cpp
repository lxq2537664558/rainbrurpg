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

#include "vcconstant.h"

#include "logger.h"
#include "iostream"

/** The default constructor
  *
  */
RainbruRPG::Core::vcConstant::vcConstant()
                             :VelocityCalculator(){

  LOGI("Creation vcConstant");

}

/** Get the next frame
  *
  * It returns the translation lenght since the last call. You must pass
  * a boolean by reference as parameter for \c b because it may be modified.
  * It will be set to \c false if the translation is ended.
  *
  * First, we get \c curentTime and \c timeEllapsed 
  * (by the formula \f$curentTime-lastFrameTimeLine\f$).
  * Then, we calcultate the returned translation value :
  * \f$getLenghtByTime(curentTime)-getLenghtByTime(lastFrameTimeLine)\f$.
  *
  * \sa getLenghtByTime(), lastFrameTimeLine.
  *
  * \param b The boolean that will be set to \c false if the 
  *          transation is ended
  *
  * \returns The translation value since the last call of this function
  *
  */
float RainbruRPG::Core::vcConstant::getNextFrame(bool& b){
  if (!mRunning){
    LOGW("VelocityCalculator not started");
    return 0.0f;
  }
  else{
    unsigned long curentTime, timeEllapsed;
    float trans;

    curentTime=timer->getMilliseconds();
    timeEllapsed=curentTime-lastFrameTimeLine;
    trans=getLenghtByTime(curentTime)-getLenghtByTime(lastFrameTimeLine);
    lastFrameTimeLine=curentTime;

    // Set the transition to be ended if transitiontime exeeced
    if (curentTime>=transitionTime){
      b=false;
      LOGI("Transition ended");
    }
    return trans;
  }
}

/** Get the lenght made at this TimeLine
  *
  * This function is called by getNextFrame(bool&). It returns the lenght
  * the translation may made for the given time elapsed. 
  *
  * The returned value is : 
  * \f$\frac{(translationLenght*d)}{transitionTime}\f$.
  *
  * \sa transitionTime, translationLenght.
  *
  * \param d the time of a frame
  *
  * \return The transition theorically made for the given time
  *
  */
float RainbruRPG::Core::vcConstant::getLenghtByTime(double d){
  if (transitionTime==0){
    LOGW("transitionTime=0");
  }
  else if (translationLenght==0){
    LOGW("transitionLenght=0");
  }

  float dev=(translationLenght*d)/(transitionTime);
  return dev;
}

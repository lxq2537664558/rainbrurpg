/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file optionfloatrangeattribute.cpp
  * Implements a range of floats for the launcher's options editor
  *
  */

#include "optionfloatrangeattribute.h"

/** The constructor
  *
  * \param name The name of this option attribute
  * \param min The minimal range
  * \param max The maximal range
  *
  */
RainbruRPG::Options::OptionFloatRangeAttribute::
OptionFloatRangeAttribute(const char* name, float min, float max)
                                  :OptionFloatAttribute(name){

  this->setType(OAT_FLOAT_RANGE);
  this->setMinRange(min);
  this->setMaxRange(max);
  this->setStep(1);
  this->value=0;
}


/** The constructor
  *
  * \param name The name of this option attribute
  * \param min The minimal range
  * \param max The maximal range
  * \param step The incremental step
  *
  */
RainbruRPG::Options::OptionFloatRangeAttribute::
OptionFloatRangeAttribute(const char* name, float min, float max, float step)
                                           :OptionFloatAttribute(name){

  this->setMinRange(min);
  this->setMaxRange(max);
  this->setStep(step);
  this->value=0;
}

/** Sets the minimal range
  *
  * \param i The new minimal range
  *
  */
void RainbruRPG::Options::OptionFloatRangeAttribute::setMinRange(float i){
  this->minRange=i;
  this->value=i;
}

/** Sets the maximal range
  *
  * \param i The new maximal range
  *
  */
void RainbruRPG::Options::OptionFloatRangeAttribute::setMaxRange(float i){
  this->maxRange=i;

}

/** Gets the minimal range
  *
  * \return The minimal range
  *
  */
float RainbruRPG::Options::OptionFloatRangeAttribute::getMinRange(){
  return this->minRange;
}

/** Gets the maximal range
  *
  * \return The maximal range
  *
  */
float RainbruRPG::Options::OptionFloatRangeAttribute::getMaxRange(){
  return this->maxRange;
}

/** Set the value of this attribute 
  *
  * If the value is out of range, the value is not changed and a warning log
  * is sent
  *
  * \param c The new value
  *
  * \return Always \c true
  */
bool RainbruRPG::Options::OptionFloatRangeAttribute::
setValueStr(const char* c){


  float i=StringConv::getSingleton().ctof(c);

  if (i>=minRange && i<=maxRange){
    this->value=i;
  }
  else{
    LOGW("The value is out of range :");
    LOGCATS("Attribute name : "); 
    LOGCATS(this->getName());
    LOGCATS("  Value : "); 
    LOGCATF(i);
    LOGCATS("  Accepted range : "); 
    LOGCATF(minRange);
    LOGCATS(" to "); 
    LOGCATF(maxRange);
    LOGCAT();
  }

  return true;
}

/** Increase the value
  *
  * Adds the step to the value
  * 
  */
void RainbruRPG::Options::OptionFloatRangeAttribute::increase(){
  controlStep();
  float i=value+step;

  if (i>maxRange){
    this->value=maxRange;
  }
  else
    value=i;
}

/** Decrease the value
  *
  * Removes the step to the value
  * 
  */
void RainbruRPG::Options::OptionFloatRangeAttribute::decrease(){
  controlStep();
  float i=value-step;

  if (i<minRange){
    this->value=minRange;
  }
  else
    value=i;
}

/** Updates the associated FOX widget
  *
  * \todo Implement this
  *
  */
void RainbruRPG::Options::OptionFloatRangeAttribute::update(){
  if (widget){
    LOGW("Update not yet implemented");
  }
  else{
    LOGW("Cannot update optionattribute : widget=NULL");
  }
}

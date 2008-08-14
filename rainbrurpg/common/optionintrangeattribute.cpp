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

/** \file optionintrangeattribute.cpp
  * Implements a range of integers for the launcher's options editor
  *
  */

#include "optionintrangeattribute.h"

/** The base constructor
  *
  * It constructs an option beetween the min and the max range with a
  * step of 1. The initial value is set to 0.
  *
  * \param name The name of the option attribute
  * \param min The min range
  * \param max the max range
  *
  */
RainbruRPG::Options::OptionIntRangeAttribute::
OptionIntRangeAttribute(const char* name, int min, int max)
                                  :OptionIntAttribute(name){

  this->setType(OAT_INT_RANGE);
  this->setMinRange(min);
  this->setMaxRange(max);
  this->setStep(1);
  this->value=0;
}

/** The step-defined constructor
  *
  * It constructs an option beetween the min and the max range with a
  * defined step.The initial value is set to 0.
  *
  * \param name The name of the option attribute
  * \param min The min range
  * \param max the max range
  * \param step The step of the attribute
  */
RainbruRPG::Options::OptionIntRangeAttribute::
OptionIntRangeAttribute(const char* name, int min, int max, unsigned int step)
                                                    :OptionIntAttribute(name){
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
void RainbruRPG::Options::OptionIntRangeAttribute::setMinRange(int i){
  this->minRange=i;
  this->value=i;
}

/** Sets the maximal range 
  *
  * \param i The new maximal range
  *
  */
void RainbruRPG::Options::OptionIntRangeAttribute::setMaxRange(int i){
  this->maxRange=i;

}

/** Get the minimal range 
  *
  * \return The minimal range
  *
  */
int RainbruRPG::Options::OptionIntRangeAttribute::getMinRange(){
  return this->minRange;
}

/** Get the maximal range 
  *
  * \return The maximal range
  *
  */
int RainbruRPG::Options::OptionIntRangeAttribute::getMaxRange(){
  return this->maxRange;
}

/** Set the value of the attribute
  *
  * If the value is out of range, the value is not changed and a warning log
  * is sent
  *
  * \param c The new value
  *
  * \return always \c true
  */
bool RainbruRPG::Options::OptionIntRangeAttribute::setValueStr(const char* c){
  int i=StringConv::getSingleton().stoi(c);

  if (i>=minRange && i<=maxRange){
    this->value=i;
  }
  else{
    LOGW("The value is out of range :");
    LOGCATS("Attribute name : "); 
    LOGCATS(this->getName());
    LOGCATS("  Value : "); 
    LOGCATI(i);
    LOGCATS("  Accepted range : "); 
    LOGCATI(minRange);
    LOGCATS(" to "); 
    LOGCATI(maxRange);
    LOGCAT();
  }

  return true;
}

/** Increase the value
  *
  * It adds the step value
  *
  */
void RainbruRPG::Options::OptionIntRangeAttribute::increase(){
  controlStep();
  int i=value+step;

  if (i>maxRange){
    this->value=maxRange;
  }
  else
    value=i;
}

/** Decrease the value
  *
  * 
  *
  */
void RainbruRPG::Options::OptionIntRangeAttribute::decrease(){
  controlStep();
  int i=value-step;

  if (i<minRange){
    this->value=minRange;
  }
  else
    value=i;
}

/** Update the widget associated with this attribute
  *
  * \todo Implement this
  *
  */
void RainbruRPG::Options::OptionIntRangeAttribute::update(){
  if (widget){
    LOGW("Update not yet implemented");
  }
  else{
    LOGW("Cannot update optionattribute : widget=NULL");
  }
}

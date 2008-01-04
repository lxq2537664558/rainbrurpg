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

#include "optionintattribute.h"

/** A named integer attribute constructor
  *
  * \param n The name of the attribute
  */
RainbruRPG::Options::OptionIntAttribute::OptionIntAttribute(const char* n)
                                :OptionAttribute(OAT_INTEGER){

  LOGI("Constructing an integer OptionAttribute");
  this->setName(n);
  this->value=0;
  this->setStep(1);

}

/** Sets the value of the attribute
  *
  * \param c The new value
  *
  * \return always return \c true
  */
bool RainbruRPG::Options::OptionIntAttribute::setValueStr(const char* c){
  this->value =StringConv::getSingleton().stoi(c);
  return true;
}

/** Get the value of this attribute
  *
  * \return the value of this attribute in a string format
  *
  */
const char* RainbruRPG::Options::OptionIntAttribute::getValueStr() const{
  return StringConv::getSingleton().itoc(this->value);
}

/** Set a new step
  *
  * No controls here
  *
  * \param i The new step of this integer attribute
  *
  */
void RainbruRPG::Options::OptionIntAttribute::setStep(unsigned int i){
  this->step=i;
}

/** Get the step
  *
  * \return The step of this integer attribute
  *
  */
unsigned int RainbruRPG::Options::OptionIntAttribute::getStep(){
  return this->step;
}

/** Increase the value
  *
  *
  */
void RainbruRPG::Options::OptionIntAttribute::increase(){
  controlStep();
  value+=step;
}

/** Decrease the value
  *
  *
  */
void RainbruRPG::Options::OptionIntAttribute::decrease(){
  controlStep();
  value-=step;
}

/** Controls the step
  *
  * It logs a warning message if the step is equal to 0.
  *
  */
void RainbruRPG::Options::OptionIntAttribute::controlStep(){
  if (step==0)
    LOGW("Calling increase or decrease with a step set to 0");
}

/** Updates the widget associated with this spinner
  *
  *
  *
  */
void RainbruRPG::Options::OptionIntAttribute::update(){
  if (widget){
    FXSpinner* spin=(FXSpinner*)widget;
    if (spin){
      LOGI("Updating an OptionIntAttribute");
      spin->setValue(this->value);
    }
    else{
      LOGW("Cannot get a valid FXSpinner");
    }
  }
  else{
    LOGW("Cannot update optionattribute : widget=NULL");
  }
}

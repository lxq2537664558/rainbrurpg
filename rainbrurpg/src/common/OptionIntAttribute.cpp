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

/** \file OptionIntAttribute.cpp
  * Implements an integer option for the launcher's options editor
  *
  */

#include "OptionIntAttribute.hpp"

/** A named integer attribute constructor
  *
  * The name of the attribute should always be used to work with
  * an attribute in a program, it is always in english language.
  * The caption can be translated and may change with the user's
  * environment setup.
  *
  * \param vName     The name of the option attribute
  * \param vCaption The caption of the attribute
  *
  */
RainbruRPG::Options::OptionIntAttribute::
OptionIntAttribute(const char* vName, const char* vCaption):
  OptionAttribute(OAT_INTEGER)
{
  LOGI(_("Constructing an integer OptionAttribute"));
  this->setName(vName);
  this->setCaption(vCaption);
  this->value=0;
  this->setStep(1);

}

/** Sets the value of the attribute
  *
  * \param c The new value
  *
  * \return always return \c true
  *
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
    LOGW(_("Calling increase or decrease with a step set to 0"));
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
      LOGI(_("Updating an OptionIntAttribute"));
      spin->setValue(this->value);
    }
    else{
      LOGW(_("Cannot get a valid FXSpinner"));
    }
  }
  else{
    LOGW(_("Cannot update OptionIntAttribute : widget=NULL"));
  }
}

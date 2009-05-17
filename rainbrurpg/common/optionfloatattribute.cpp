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

/** \file optionfloatattribute.cpp
  * Implements a float attribute for the launcher's options editor
  *
  */

#include "optionfloatattribute.h"

/** A named constructor
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
RainbruRPG::Options::OptionFloatAttribute::
OptionFloatAttribute(const char* vName, const char* vCaption):
  OptionAttribute(OAT_FLOAT)
{
  setName(vName);
  setCaption(vCaption);

  setStep(0.0f);
  value=0.0f;
}

/** Set the value of the attribute
  *
  * \param c The new value
  *
  * \return Always \c true
  */
bool RainbruRPG::Options::OptionFloatAttribute::setValueStr(const char* c){
  value=StringConv::getSingleton().ctof(c);


  return true;
}

/** Get the value of the attribute
  *
  * \return The value of this attribute
  *
  */
const char* RainbruRPG::Options::OptionFloatAttribute::getValueStr() const{
  return StringConv::getSingleton().ftoc(value);
}

/** Use f as step
  * 
  * The parameter can  not be negative I use std::abs to get only positive
  * value.
  *
  * \param f The new step
  *
  */
void RainbruRPG::Options::OptionFloatAttribute::setStep(float f){
  this->step=std::abs(f);
}

/** Get the step of this attribute
  *
  * \return the step value
  *
  */
float RainbruRPG::Options::OptionFloatAttribute::getStep(){
  return this->step;
}

/** Increase the value
  *
  * It adds the step to this attribute's value.
  *
  */
void RainbruRPG::Options::OptionFloatAttribute::increase(){
  controlStep();
  value+=step;
}

/** Decrease the value
  *
  * It removes the step to this attribute's value.
  *
  */
void RainbruRPG::Options::OptionFloatAttribute::decrease(){
   controlStep();
   value-=step;
}

/** Control if the step is a positive non-null value
  *
  * It sends a warning log message if the step is NULL (equal to 0)
  *
  */

void RainbruRPG::Options::OptionFloatAttribute::controlStep(){
  if (step==0.0f)
    LOGW(_("Calling increase or decrease with a step set to 0"));
}

/** Update the associated widget
  *
  * \todo Implement this
  *
  */
void RainbruRPG::Options::OptionFloatAttribute::update(){
  if (widget){
    LOGW(_("Update not yet implemented"));
  }
  else{
    LOGW(_("Cannot update optionattribute : widget=NULL"));
  }
}

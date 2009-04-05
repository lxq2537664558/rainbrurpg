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

/** \file optionboolattribute.cpp
  * Implements an option attribute storing a boolean value
  *
  *
  */
#include "optionboolattribute.h"

/** The named constructor
  *
  * It sets the type of the attribuet at OAT_BOOLEAN, call setName() and
  * sets value to \c true.
  *
  * \sa OptionAttribute, setName(), value
  *
  * \param n The setName() param.
  *
  */
RainbruRPG::Options::OptionBoolAttribute::OptionBoolAttribute(const char* n)
                                :OptionAttribute(OAT_BOOLEAN){

  LOGI(_("Constructing a bool OptionAttribute"));
  this->setName(n);
  this->value=false;

}

/** Set the value of the attribute
  *
  * It internally use StringConv::ctob() to convert a string to a boolean.
  * It waits a string like 'true' or 'false', not a number (ie. 0/1).
  *
  * \sa StringConv, getValueStr(), value
  *
  * \returns Always true
  */
bool RainbruRPG::Options::OptionBoolAttribute::setValueStr(const char* c){
  this->value =StringConv::getSingleton().ctob(c);
  return true;
}


/** Get the value of the attribute
  *
  * It internally use StringConv::btoc() to convert a boolean to a string.
  * It returns a string like 'true' or 'false', not a number (ie. 0/1).
  *
  * \sa StringConv, setValueStr(), value
  *
  * \returns Always true
  */
const char* RainbruRPG::Options::OptionBoolAttribute::getValueStr() const{
  return StringConv::getSingleton().btoc(this->value);
}


/** Updates the associated widget
  *
  *
  */
void RainbruRPG::Options::OptionBoolAttribute::update(){
  if (widget){
    FXCheckButton* spin=(FXCheckButton*)widget;
    if (spin){
      LOGI(_("Updating an OptionIntAttribute"));
      spin->setCheck(this->value);
    }
    else{
      LOGW(_("Cannot get a valid FXCheckButton"));
    }
  }
  else{
    LOGW(_("Cannot update optionattribute : widget=NULL"));
  }
}

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

/** \file optionlistattribute.cpp
  * Implements a list of string for the launcher's options editor
  *
  */

#include "optionlistattribute.h"

/** A named constructor
  *
  * \param n The name of the option attribute
  *
  */
RainbruRPG::Options::OptionListAttribute::OptionListAttribute(const char* n)
                                     :OptionAttribute( OAT_LIST )
{
  hasDefaultValue=false;
  setName(n);
  value="";
}

/** Set a new value to this attribute
  *
  * \param c The new value
  *
  * \return always \c true
  *
  */
bool RainbruRPG::Options::OptionListAttribute::setValueStr(const char* c){

  LOGCATS("Attribute value :");
  LOGCATS(c);
  LOGCAT();

  if (exists(c))
    value=c;
  else
    LOGW ("The selected value does not exist");

  return true;
}

/** Get the value of this attribute
  *
  * \return The string value of this option attribute
  *
  */
const char* RainbruRPG::Options::OptionListAttribute::getValueStr() const{
  return value.c_str();
}

/** Add a value to the list
  *
  * The value can not be empty and will be tested for already existing.
  *
  * \param it The new value to append to the values list
  *
  */
void RainbruRPG::Options::OptionListAttribute::add(const char* it){
  if (strlen(it)!=0){
    if (!exists(it)){
      valueList.push_back(it);

      if (!hasDefaultValue){
	setValueStr(it);
	hasDefaultValue=true;
      }

    }
    else{
      LOGW("Inserting an existing value to an OptionListAttribute");

    }
  }
  else
    LOGW("Inserting an empty string to an OptionListAttribute");


}

/** Tests if a value already exist
  *
  * \param c The value to test
  *
  * returns \c true if the c exists, otherwise returns \c false
  *
  */
bool RainbruRPG::Options::OptionListAttribute::exists(const char* c){

  bool ret=false;
  list<const char*>::const_iterator iter;

  for (iter=valueList.begin(); iter!=valueList.end(); iter++){
    if (strcmp(c, (*iter))==0)
      ret=true;
  }

  return ret;
}

/** Return the number of possibly values
  *
  * \return The number of choices
  *
  */
unsigned int RainbruRPG::Options::OptionListAttribute::valueCount(){
  return valueList.size();
}

/** Get the list of values
  *
  * \return A valueList pointer
  *
  */
RainbruRPG::Options::tValueList* 
RainbruRPG::Options::OptionListAttribute::getValueList(){

  return &valueList;
}

/** Update the Combobox of this list attribute
  *
  *
  */
void RainbruRPG::Options::OptionListAttribute::update(){
  if (widget){

    FXComboBox* cb=(FXComboBox*)widget;
    if (cb){
      LOGI("Updating an OptionListAttribute");
      int i=cb->findItem(this->value.c_str());
      cb->setCurrentItem(i);
    }
    else{
      LOGW("Cannot get a valid FXCheckButton");
    }

  }
  else{
    LOGW("Cannot update optionattribute : widget=NULL");
  }
}

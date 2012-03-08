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

/** \file OptionListAttribute.cpp
  * Implements a list of string for the launcher's options editor
  *
  */

#include "OptionListAttribute.hpp"

/** A named constructor
  *
  * The name of the attribute should always be used to work with
  * an attribute in a program, it is always in english language.
  * The caption can be translated and may change with the user's
  * environment setup.
  *
  * \param vName    The name of the attribute
  * \param vCaption The caption of the attribute
  *
  */
RainbruRPG::Options::OptionListAttribute::
OptionListAttribute(const char* vName, const char* vCaption)
                                     :OptionAttribute( OAT_LIST )
{
  hasDefaultValue=false;
  setName(vName);
  setCaption(vCaption);
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

  if (exists(c)){
    value=c;
  }
  else{
    GTS_LIT(str);
    // TRANSLATORS: This message is used when trying to select a
    // value that does not exist in the list. The parameter is the
    // value we are trying to set.
    sprintf(str, _("The requested value (%s) does not exist in the list"),
	    c);
    LOGW(str);
  }
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
      LOGW(_("Inserting an existing value to an OptionListAttribute"));
    }
  }
  else
    LOGW(_("Inserting an empty string to an OptionListAttribute"));


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
      LOGI(_("Updating an OptionListAttribute"));
      int i=cb->findItem(this->value.c_str());
      cb->setCurrentItem(i);
    }
    else{
      LOGW(_("Cannot get a valid FXCheckButton to update an "
	     "OptionListAttribute"));
    }

  }
  else{
    LOGW("Cannot update optionattribute : widget=NULL");
  }
}
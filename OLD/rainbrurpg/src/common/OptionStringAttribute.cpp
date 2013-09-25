/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file OptionStringAttribute.cpp
  * Implements a string for the launcher's options editor
  *
  */

#include "OptionStringAttribute.hpp"

/** The named constructor
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
RainbruRPG::Options::OptionStringAttribute::
OptionStringAttribute(const char* vName, const char* vCaption):
  OptionAttribute(OAT_STRING)
{

  LOGI(_("Constructing an OptionStringAttribute"));
  this->setName(vName);
  this->setCaption(vCaption);
  this->value="";

}

/** Sets the value of the attribute
  *
  * \param c The new value of the option
  * \return always \c true
  */
bool RainbruRPG::Options::OptionStringAttribute::
setValueStr(const char* c){


  this->value =c;
  return true;
}

/** Gets the value of the option
  *
  * \return The value of this option
  *
  */
const char* RainbruRPG::Options::OptionStringAttribute::getValueStr() const{
  return this->value.c_str();
}

/** Updates the FOX widget associated with this option attribute
  *
  * The widget is a FXTextField.
  *
  */
void RainbruRPG::Options::OptionStringAttribute::update(){
  if (widget){
    FXTextField* tf=(FXTextField*)widget;
    if (tf){
      LOGI(_("Updating an OptionStringAttribute"));
      tf->setText(this->value.c_str());
    }
    else{
      LOGW(_("Cannot get a valid FXTextField to update an "
	     "OptionStringAttribute"));
    }
  }
  else{
    LOGW("Cannot update optionattribute : widget=NULL");
  }
}

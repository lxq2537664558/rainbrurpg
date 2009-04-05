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

/** \file optionattribute.cpp
  * Implements an attribute that will be shown in the launcher's option editor
  *
  */

#include "optionattribute.h"

// Added here cause it doesn't work if added in optionattribute.h
#include "rainbrudef.h" // For the gettext stuff

/** A typed default constructor
  *
  * This calls setType() with \c t as parameter.
  *
  * \param t The type of the newly created attribute (or your custom type).
  *
  */
RainbruRPG::Options::OptionAttribute::OptionAttribute(tOptionAttributeType t){
  this->setType(t);
  tooltip="";
  widget=NULL;
}

/** Set the type of the attribute
  *
  * Set OptionAttribute::type to t. If the type is OAT_UNKNOWN, a warning
  * log message is sent to the Logger.
  *
  * \sa getType(), type.
  *
  * \param t The new type of the attribute
  */
void RainbruRPG::Options::OptionAttribute::setType(tOptionAttributeType t){
  if (t==OAT_UNKNOWN)
    LOGW(_("Setting a unknown type to an OptionAttribute"));

  this->type=t;
}

/** Get the type of the attribute
  *
  * No controls here.
  *
  * \sa setType(), type
  *
  * \return The type of the attribute
  */
RainbruRPG::Options::tOptionAttributeType 
RainbruRPG::Options::OptionAttribute::getType(){

  return this->type;
}

/** Set the name of the attribute
  *
  * Logs a warning message if the name is empty. The control of the
  * lenght of the string is done by std::strlen.
  *
  * \sa getName(), name
  *
  * \param n The new name of the attribute
  *
  */
void RainbruRPG::Options::OptionAttribute::setName(const char*n){
  if (strlen(n)==0)
    LOGW(_("Setting an empty name to an OptionAttribute"));
  this->name=n;
}

/** Set the tooltip of the attribute
  *
  * \sa getToolTip(), tooltip
  *
  */
void RainbruRPG::Options::OptionAttribute::setToolTip(const char*t){
  this->tooltip=t;
}

/** Get the name of the attribute
  *
  * \sa setName(), name
  *
  */
const char* RainbruRPG::Options::OptionAttribute::getName(){
  return this->name;
}

/** Get the tooltip text of the attribute
  *
  * The name can contains space and other specials character but keep in 
  * mind this is used as the label of the option (in LauncherOptions
  * dialog).
  *
  * \sa setToolTip(), tooltip
  *
  */
const char* RainbruRPG::Options::OptionAttribute::getToolTip(){
  return this->tooltip;
}

/** Set the widget used for the updates
  *
  * If none widget is set, a warning log is sent.
  *
  * \param o The object used for the update
  *
  * \sa getWidget(), widget
  *
  */
void RainbruRPG::Options::OptionAttribute::setWidget(FXObject* o){
  this->widget=o;
}

/** Get the widget used for the updates
  *
  * \return The object used for the update or NULL if not set
  *
  * \sa setWidget(), widget
  *
  */
FXObject* RainbruRPG::Options::OptionAttribute::getWidget(){
  return this->widget;
}


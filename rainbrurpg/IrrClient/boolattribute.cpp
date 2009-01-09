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

#include "boolattribute.h"
#include <logger.h>

#include <string.h>

/** The named constructor of a boolean attribute
  *
  * The name is passed to the ObjectAttribute constructor.
  *
  * \param name The name of the attribute to create.
  */
RainbruRPG::Exception::BoolAttribute::BoolAttribute(const char * name)
                                     :ObjectAttribute(name){

}

const char* RainbruRPG::Exception::BoolAttribute::getTypeText(){
  return "[boolean]";
}

const char* RainbruRPG::Exception::BoolAttribute::getValueText(){
  if (value)
    return "on";
  else
    return "off";
}

bool RainbruRPG::Exception::BoolAttribute::setValueText(const char *c){
  if (strcmp(c,"on")==0){
    value=true;
    setValue(true);
    return true;
  }
  else if (strcmp(c,"off")==0){
    value=false;
    setValue(false);
    return true;
  }
  else
    return false;

}


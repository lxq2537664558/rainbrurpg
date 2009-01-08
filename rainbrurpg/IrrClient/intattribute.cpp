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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "intattribute.h"
#include "logger.h"

#include <string.h>

/** The named integer attribute constructor
  *
  * \param name The value of the name property like we can show it in
  *        the console. 
  */
RainbruRPG::Exception::IntAttribute::IntAttribute(const char * name)
                                     :ObjectAttribute(name){

}

const char* RainbruRPG::Exception::IntAttribute::getTypeText(){
  return "[integer]";
}

const char* RainbruRPG::Exception::IntAttribute::getValueText(){

  return "000";
}

bool RainbruRPG::Exception::IntAttribute::setValueText(const char *c){
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


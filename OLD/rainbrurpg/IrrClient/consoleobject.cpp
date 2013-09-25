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

#include "consoleobject.h"

#include "logger.h"

/** A Constuctor withn the ConsoleObject name
  *
  * The name of object is used in the console as an identifier. This
  * constructor use the setName( char* name) method.The description
  * property is set to an empty string. Use setDesc( char* desc) to
  * define a new description string.
  *
  * \param name The name string
  */

RainbruRPG::Exception::ConsoleObject::ConsoleObject( char* name ){
  setName(name);
  this->desc="";
}

/** Change the name 
  *
  * If the name passed as parameter is NULL (empty), the Logger
  * received a error log message.
  *
  * \param name The new name of the object
  */
void RainbruRPG::Exception::ConsoleObject::setName( char* name){
  if (name==""){
    LOGE("Creating a ConsoleObject with empty name");
  }
  else{
    this->name=name;
  }
}

/** Return the value of the name property
  *
  * \return the name string
  *
  */
char* RainbruRPG::Exception::ConsoleObject::getName(){
  return this->name;
}

/** Change the description string of the object
  *
  * The method does not control the value of the parameter.
  *
  * \param desc The new description string
  *
  */
void RainbruRPG::Exception::ConsoleObject::setDesc( char* desc){
    this->desc=desc;
}

/** Return the value of the description string
  *
  *
  * \return The description string
  */
char* RainbruRPG::Exception::ConsoleObject::getDesc(){
  return this->desc;
}

/** Return the list of attributes of this object
  *
  * It is a vector of ObjectAttribute subclass instance.
  *
  * \return A stl vector containing all the atributes of this object
  */
RainbruRPG::Exception::tAttrbList* RainbruRPG::Exception::ConsoleObject::
                                                          getAttrbList(){
  return &this->attrbList;
}

/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

#include "objectattribute.h"

#include "logger.h"

/** The constructor of a named object attribute
  *
  * the setName( char* name) method is used internally.
  *
  * \param name The name of the attribute
  */
RainbruRPG::Exception::ObjectAttribute::ObjectAttribute( const char* name ){
  this->setName(name);
}

/** Change the name of this attribute
  *
  * The char* is set to the name attribute. If it is \c NULL (an empty
  * string) an Error message is send to the Logger.
  * 
  * \param name The new name of the attribute
  */
void RainbruRPG::Exception::ObjectAttribute::setName( const char* name){
  if (name==""){
    LOGE("Creating an ObjectAttribute with empty name");
  }
  else{
    this->name=name;
  }
}

/** Get the name of the attribute
  *
  * \return The value of the name property
  */
const char* RainbruRPG::Exception::ObjectAttribute::getName(){
  return this->name;
}

/** Change the Description of the attribute
  *
  * Send a warning message to the Logger if the parameter is an empty string.
  *
  * \param desc The new description string
  */
void RainbruRPG::Exception::ObjectAttribute::setDesc( const char* desc){
  if (desc==""){
    LOGW("Creating an ObjectAttribute with empty description");
  }
  this->desc=desc;
}

/** Get the description of the attribute
  *
  * If the desc string is empty, a warning message will be send to the Logger.
  *
  * \return A \c char* to the description of the attribute
  *
  */
const char* RainbruRPG::Exception::ObjectAttribute::getDesc(){
  if (this->desc==""){
    LOGW("Returning an empty 'desc' ObjectAttribute");
  }
  return this->desc;
}

/** Get the access mode in text format
  *
  * 
  * \return \c [ro] if the attribute is in read-only mode, otherwise
  * return \c [rw] (read and write mode).
  */
const char* RainbruRPG::Exception::ObjectAttribute::getAccessText(){
  if (this->readOnly)
    return "[ro]";
  else
    return "[rw]";
}

/** Count the available commands for this attribute
  *
  * \return 1 if the attribute is in read-only mode, otherwise returns 2.
  *
  *
  */
int RainbruRPG::Exception::ObjectAttribute::count(){
  if (this->readOnly)
    return 1;
  else
    return 2;
}

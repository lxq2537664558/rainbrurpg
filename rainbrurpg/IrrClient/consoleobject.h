/*
 *  Copyright 2006 Jerome PASQUIER
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

#ifndef CONSOLE_OBJECT_H
#define CONSOLE_OBJECT_H

#include <irrlicht.h>
#include <vector>

#include "objectattribute.h"


using namespace std;
using namespace irr;
using namespace core;

namespace RainbruRPG {
  namespace Exception{

    /** The List of Attribute typedef
      *
      */
    typedef vector<ObjectAttribute*> tAttrbList;

    /** The Console to Object wrapper
      *
      * To provides the console access to Instance of classes, we use
      * a ConsoleObject for each class. All the ConsoleObject must be a
      * subclass of this. To provides a ConsoleObject access in the
      * console the \c name property is used. A property called \c
      * desc (for description) is used in the console to provides a
      * brief help on each object.
      *
      * The most important use of the console objects is their
      * typed attributes. Each ConsoleObject has a vector of
      * ObjectAttribute. 
      */
    class ConsoleObject{
    public:
      ConsoleObject ( char* name );

      void setName( char* name);
      char* getName();
     
      void setDesc( char* desc);
      char* getDesc();
 
      tAttrbList* getAttrbList();

    private:
      /** The name of the object
        *
	* This name can't be null. It's the name we use in the console to
	* access its attributes.
	*/
      char* name;
      /** A description of the object
        *
	* The description will be shown with the name with the show
	* command
	*
	*/
      char* desc;


    protected:
      /** The list of the Object's attributes
        *
	* A console object can have some typed attributes. They are
	* stored in a stl vector of ObjectAttribute.
	*
	*/
      tAttrbList attrbList;
    };
  }
}

#endif// CONSOLE_OBJECT_H

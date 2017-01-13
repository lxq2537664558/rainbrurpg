/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011-2017 Jérôme Pasquier
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/** \file Object.hpp
  * The header file for of a logger-ready base object
  *
  */

#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <string>
#include <list>
#include <sstream>

namespace Rpg
{
  // Forward declaration...
  class ObjectInspector;

  /** Defines an object to be logged
    *
    * To be able to log the instance of an object, an object
    * \b must inherit this class and implement the Object::inspect pure
    * virtual function.
    *
    */
  class Object
  {
  public:
    /**  The default constructor
     *
     */
    Object(){}; 
    
    /** The inspect function to be implemented
     *
     * \return An inspector containing object's attributes
     *
     */
    virtual ObjectInspector inspect()const = 0;
  };
} // !namespace Rpg

// ... because ObjectInspector must know about Object
#include "ObjectInspector.hpp"

#endif // _OBJECT_HPP_

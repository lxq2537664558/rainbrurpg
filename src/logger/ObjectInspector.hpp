/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011-2015 Jérôme Pasquier
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

/** \file ObjectInspector.hpp
  * The header file of the ObjectInspector object
  *
  */

#ifndef _OBJECT_INSECTOR_HPP_
#define _OBJECT_INSECTOR_HPP_

#include "Object.hpp"
#include "ObjectAttribute.hpp"

#include <string>
#include <list>

namespace Rpg
{
  /** An object used to describe a C++ class internals
    *
    * This object is used when you need to log a complete object to
    * the logger stream.
    *
    */
  class ObjectInspector
  {
  public:
    ObjectInspector(std::string class_name, const void* address);
    
    ObjectInspector& add(std::string name, int value);
    ObjectInspector& add(std::string name, Object&o);

    const std::string& getName(void);
    const std::string& getAddress(void);
    std::list<ObjectAttribute> getAttributes(void);

  private:    
    std::string name;                //!< The class name of the inspected object
    std::string address;             //!< Its memory address
    std::list<ObjectAttribute> attributes;//!< The object attributes
  };
} // !namespace Rpg

#endif // !_OBJECT_INSECTOR_HPP_

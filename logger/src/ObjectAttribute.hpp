/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011-2012 Jérôme Pasquier
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

/** \file ObjectAttribute.hpp
  * The header of the ObjectAttribute object
  *
  */

#ifndef _OBJECT_ATTRIBUTE_HPP_
#define _OBJECT_ATTRIBUTE_HPP_

#include <string>

using namespace std;

namespace Rpg
{
  /** Defines the attribute on an object
    *
    */
  class ObjectAttribute
  {
  public:
    ObjectAttribute(string t, string n, string v);
    
    string type;  //!< The internal type of the attribute (ie. int for integer)
    string name;  //!< The attribute's name
    string value; //!< The value to be logged
  };
} // !namespace Rpg


#endif // !_OBJECT_ATTRIBUTE_HPP_

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

/** \file ObjectInspector.cpp
  * The implementation of ObjectInspector object
  *
  */

#include "ObjectInspector.hpp"

using namespace std;

/** The innscpector constructor
  *
  * The <em>memory address</em> comes from a pointer to the object you
  * inspect.
  *
  * \param class_name The object's class name
  * \param address     The memory address of the object
  *
  */
Rpg::ObjectInspector::ObjectInspector(string class_name, const void* address):
  name(class_name)
{
  ostringstream oss;
  oss << address;
  this->address = oss.str();
  
};

/** Add an integer attribute to the inspector
  *
  * \param name  The name of the attribute
  * \param value The integer value of the attribute
  *
  * \return a reference to this inspector
  *
  */
Rpg::ObjectInspector& 
Rpg::ObjectInspector::add(std::string name, int value)
{
  ostringstream oss;
  oss << value;
  attributes.push_back(ObjectAttribute("int", name, oss.str()));
  return *this;
};

/** Add an object attribute to the inspector
  *
  * \param name The name of the attribute
  * \param o    The object
  *
  * \return a reference to this inspector
  *
  */
Rpg::ObjectInspector& 
Rpg::ObjectInspector::add(std::string name, Object& o)
{
  attributes.push_back(ObjectAttribute("int", name, "Nested object"));
  return *this;
};


/** Get the name
  *
  * \return the name of this inspector
  *
  */
const std::string& 
Rpg::ObjectInspector::getName(void)
{
  return this->name;
}

/** Return the inpsector address
  *
  * \return the address as a string
  *
  */
const std::string& 
Rpg::ObjectInspector::getAddress(void)
{
  return this->address;
}

/** The attributes getter
  *
  * \return The list of ObjectAttribute
  *
  */
std::list<Rpg::ObjectAttribute> 
Rpg::ObjectInspector::getAttributes(void)
{
  return this->attributes;
}

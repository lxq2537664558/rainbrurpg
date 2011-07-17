/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011 Jérôme Pasquier
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

ObjectInspector::ObjectInspector(string class_name, const void* address):
  name(class_name)
{
  ostringstream oss;
  oss << address;
  this->address = oss.str();
  
};

ObjectInspector& 
ObjectInspector::add(string name, int value)
{
  ostringstream oss;
  oss << value;
  attributes.push_back(ObjectAttribute("int", name, oss.str()));
  return *this;
};

ObjectInspector& 
ObjectInspector::add(string name, Object&o)
{
  /*
    ostringstream oss;
    oss << value;
  */
  attributes.push_back(ObjectAttribute("int", name, "Nested object"));
  return *this;
};

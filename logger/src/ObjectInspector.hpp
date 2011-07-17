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

/** \file ObjectInspector.hpp
  * The header file of ObjectInspector object
  *
  */

#ifndef _OBJECT_INSECTOR_HPP_
#define _OBJECT_INSECTOR_HPP_

#include "Object.hpp"
#include "ObjectAttribute.hpp"

#include <string>
#include <list>

using namespace std;

class ObjectInspector
{
public:
  ObjectInspector(string class_name, const void* address);

  ObjectInspector& add(string name, int value);

  ObjectInspector& add(string name, Object&o);

  string name;
  string address;
  list<ObjectAttribute> attributes;
};

#endif // !_OBJECT_INSECTOR_HPP_

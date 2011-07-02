/* 
 * logger - The RainbruRPG's logging library.
 *
 * Copyright (C) 2011 Jérôme Pasquier
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.  
 *
 */

#ifndef _OBJECT_HPP_
#define _OBJECT_HPP_

#include <string>
#include <list>
#include <sstream>

using namespace std;

class Object;

class ObjectAttribute
{
public:
  ObjectAttribute(string t, string n, string v):
    type(t), name(n), value(v)
  {    
  };

  string type;
  string name;
  string value;
};

class ObjectInspector
{
public:
  ObjectInspector(string class_name, const void* address):
    name(class_name)
  {
    ostringstream oss;
    oss << address;
    this->address = oss.str();

  };

  ObjectInspector& add(string name, int value)
  {
    ostringstream oss;
    oss << value;
    attributes.push_back(ObjectAttribute("int", name, oss.str()));
    return *this;
  };

  ObjectInspector& add(string name, Object&o)
  {
    /*
    ostringstream oss;
    oss << value;
    */
    attributes.push_back(ObjectAttribute("int", name, "Nested object"));
    return *this;
  };

  string name;
  string address;
  list<ObjectAttribute> attributes;
};

class Object
{
public:
  Object(){};

  virtual ObjectInspector inspect()const =0;
};

#endif // _OBJECT_HPP_

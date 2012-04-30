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

/** \file ObjectAttribute.cpp
  * The implementation of ObjectAttribute object
  *
  */

#include "ObjectAttribute.hpp"

using namespace std;

/** The attribute constructor
  *
  * \param vType  The attribute type (ie. \em int for an integer)
  * \param vName  The attribute's name
  * \param vValue The attribute value, stored as a string
  *
  */
Rpg::ObjectAttribute::ObjectAttribute(string vType, string vName, 
				      string vValue):
  type(vType), name(vName), value(vValue)
{    
};

const std::string&
Rpg::ObjectAttribute::getType(void)
{
  return this->type;
}

const std::string& 
Rpg::ObjectAttribute::getName(void)
{
  return this->name;
}

const std::string& 
Rpg::ObjectAttribute::getValue(void)
{
  return this->value;
}

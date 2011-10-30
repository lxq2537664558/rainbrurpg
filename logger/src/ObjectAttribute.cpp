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

/** \file ObjectAttribute.cpp
  * The implementation of ObjectAttribute object
  *
  */

#include "ObjectAttribute.hpp"

/** The attribute constructor
  *
  * \param vType  The attribute type (ie. \em int for an integer)
  * \param vName  The attribute's name
  * \param vValue The attribute value, stored as a string
  *
  */
ObjectAttribute::ObjectAttribute(string vType, string vName, string vValue):
  type(vType), name(vName), value(vValue)
{    
};

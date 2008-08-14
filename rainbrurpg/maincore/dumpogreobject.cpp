/*
 *  Copyright 2006-2008 Jerome PASQUIER
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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file dumpogreobject.cpp
  * Implements some functions used to dump Ogre objects
  *
  */

#include "dumpogreobject.h"

/** Shows debug informations on an Ogre rectangle
  * 
  * You should better use the \ref DUMP_RECT macro defined in the file
  * dumpogreobject.h as the file and line parameters ars autofilled.
  *
  * \param file The filename
  * \param line The line
  * \param obj  The rectangle to dump
  *
  */
void dumpOgreRectangle(const string& file, const string& line, 
		       const Rectangle& obj){

  ostringstream oss;
  oss << "Debugging ogre rectangle : top=" << obj.top
      << "; left=" << obj.left
      << "; bottom=" << obj.bottom
      << "; right=" << obj.right << ";";
  
  Logger::getSingleton().log(file.c_str(), line.c_str(), LL_INFO,
			     oss.str().c_str());

}

/** Shows debug informations on an Ogre Vector4
  * 
  * You should better use the \ref DUMP_VEC4 macro defined in the file
  * dumpogreobject.h as the file and line parameters ars autofilled.
  *
  * \param file The filename
  * \param line The line
  * \param obj  The Vector4 object to dump
  *
  */
void dumpOgreVector4(const string& file, const string& line, 
		     const Vector4& obj){

  ostringstream oss;
  oss << "Debugging ogre Vector4 : "
      << "x=" << obj.x
      << "; y=" << obj.y
      << "; z=" << obj.z
      << "; w=" << obj.w << ";";
  
  Logger::getSingleton().log(file.c_str(), line.c_str(), LL_INFO,
			     oss.str().c_str());

}

/** Shows debug informations on an Ogre Vector2
  * 
  * You should better use the \ref DUMP_VEC2 macro defined in the file
  * dumpogreobject.h as the file and line parameters ars autofilled.
  *
  * \param file The filename
  * \param line The line
  * \param obj  The Vector2 object to dump
  *
  */
void dumpOgreVector2(const string& file,const string& line,const Vector2& obj){

  ostringstream oss;
  oss << "Debugging ogre Vector2 : "
      << "x=" << obj.x
      << "; y=" << obj.y << ";";
  
  Logger::getSingleton().log(file.c_str(), line.c_str(), LL_INFO,
			     oss.str().c_str());
}

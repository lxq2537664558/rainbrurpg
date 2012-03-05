/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file dumpogreobject.h
  * Declares preprocessor macros used to dump Ogre objects
  *
  * The preprocessor macros in this header may be use to dump Ogre object.
  * It provide The \c __FILE__ and \c __LINE__ autofill that let the caller
  * filename and line number be printed with the dumped ogre object. Please
  * note that the Logger is used to log objects informations.
  *
  * \warning Preprocessor macros do not provide clear type checking and a
  *          bad parameter could lead to an undefined behaviour.
  *
  * \warning Please use the Ogre namespace to scope Rectangle objects
  *          to avoid ambiguous use on Win32 platform when included from
  *          the OgreGui library.
  *
  *
  * Modifications :
  * - 28 aug 2009 : Translated messages with gettext
  * - 13 aug 2008 : Single file documentation
  * - 06 jan 2008 : Starting implementations
  *
  */

#ifndef _DUMP_OGRE_OBJECT_H_
#define _DUMP_OGRE_OBJECT_H_

#include <Logger.hpp> // To define STRINGIFY

#include <string>
#include <sstream>

#include <OgreVector2.h>
#include <OgreVector4.h>
#include <OgreRectangle.h>

#include <rainbrudef.h> // For the GNU gettext stuff

using namespace std;
using namespace Ogre;
using namespace RainbruRPG::Exception;


/** \def DUMP_RECT(RECTANGLE)
  * Dump an Ogre rectangle
  * 
  * \param RECTANGLE The rectangle to be logger
  *
  *
  */
#define DUMP_RECT(RECTANGLE) dumpOgreRectangle(__FILE__,		\
					       TOSTRING(__LINE__),	\
					       RECTANGLE );


/** \def DUMP_VEC4(VECTOR4)
  * Dump an Ogre Vector4 object
  * 
  * \param VECTOR4 The Vector4 object to be logger
  *
  *
  */
#define DUMP_VEC4(VECTOR4) dumpOgreVector4(__FILE__,		\
					   TOSTRING(__LINE__),	\
					   VECTOR4 );

/** \def DUMP_VEC2(VECTOR2)
  * Dump an Ogre Vector2 object
  * 
  * \param VECTOR2 The Vector2 object to be logger
  *
  *
  */
#define DUMP_VEC2(VECTOR2) dumpOgreVector2(__FILE__,		\
					   TOSTRING(__LINE__),	\
					   VECTOR2 );


void dumpOgreRectangle(const string&, const string&, const Ogre::Rectangle&);
void dumpOgreVector4(const string&, const string&, const Vector4&);
void dumpOgreVector2(const string&, const string&, const Vector2&);

#endif //_DUMP_OGRE_OBJECT_H_


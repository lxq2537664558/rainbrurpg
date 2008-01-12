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

/* Modifications :
 * - 06 jan 2008 : Starting implementations
 *
 */

#ifndef _DUMP_OGRE_OBJECT_H_
#define _DUMP_OGRE_OBJECT_H_

#include <logger.h> // To define STRINGIFY

#include <string>
#include <sstream>

#include <OgreVector2.h>
#include <OgreVector4.h>
#include <OgreRectangle.h>

using namespace std;
using namespace Ogre;
using namespace RainbruRPG::Exception;

/* The preprocessor macros in this header may be use to dump Ogre object.
 *
 */

#define DUMP_RECT(RECTANGLE) dumpOgreRectangle(__FILE__,		\
					       TOSTRING(__LINE__),	\
					       RECTANGLE );

#define DUMP_VEC4(VECTOR4) dumpOgreVector4(__FILE__,		\
					   TOSTRING(__LINE__),	\
					   VECTOR4 );

#define DUMP_VEC2(VECTOR2) dumpOgreVector2(__FILE__,		\
					   TOSTRING(__LINE__),	\
					   VECTOR2 );


void dumpOgreRectangle(const string&, const string&, const Rectangle&);
void dumpOgreVector4(const string&, const string&, const Vector4&);
void dumpOgreVector2(const string&, const string&, const Vector2&);

#endif //_DUMP_OGRE_OBJECT_H_


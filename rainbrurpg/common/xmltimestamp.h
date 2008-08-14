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

/** \file xmltimestamp.h
  * Declares a class that manage XML timestamps
  *
  * Modifications :
  * - 11 aug 2008 : Single file documentation
  * - 03 mar 2007 : fix a SEGFAULT during unit test of ClientConnect
  */

#ifndef XML_TIME_STAMP_H
#define XML_TIME_STAMP_H

#include <time.h>
#include <iostream>
#include <string>
#include <sstream> // for stringstream

#include "tinyxml.h"


using namespace std;

namespace RainbruRPG{
  namespace Network {
    namespace Ident {

      /** A xml timestamp class
        *
	* A timestamp defines a date and a time with a custom
	* tag. Usually, the tag is \c creation or \c modification, but
	* it can be another string.
	*
	* This example shows a creation timestamp. The text is of type
	* of time_t, a value define in the standard c++ \c time.h header.
	*
	*/
      class xmlTimestamp{
      public:
	xmlTimestamp();
	~xmlTimestamp();

	void addTimestamp( const char *, TiXmlNode* );
	void delTimestamp( const char *, TiXmlNode* );

	const char* getCTime(  const char *, TiXmlElement* );
	std::string getCTimeS(  const char *, TiXmlElement* );

      };
    }
  }
}
#endif // XML_TIME_STAMP_H

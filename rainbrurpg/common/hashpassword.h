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

/** \file hashpassword.h
  * Declares a class used to compute password's hashsum 
  *
  * Modifications :
  * - 31 jul 2007 : Remove decryptString() (function)
  * - 02 mar 2007 : Disable a cout that make a line break in stdout
  *
  */

#ifndef HASH_PASSWORD_H
#define HASH_PASSWORD_H

// For hash sum
#include <unistd.h>
#include <string>
#include <sstream>

#include "logger.h"
#include "sha1.h"

using namespace RainbruRPG::Core;
using namespace std;

namespace RainbruRPG {
  namespace Network {
    namespace Ident {


      /** Class used to compute password's hashsum 
        *
	* This class is used to compute hashsum of a password using
	* the SHA-1 algorythm implemented in the Sha1 class.
	*
	* \sa \ref RainbruRPG::Core::HashFile "HashFile" to compute the
	*     hashsum of a file.
	*
	*/
        class HashPassword {
        public:
	  HashPassword();
	  ~HashPassword();
	  
	  std::string encryptString(const char *instr);
	  
	  bool compare(const char*, const char*);
	  
	};
    }
  }
}


#endif //HASH_PASSWORD_H

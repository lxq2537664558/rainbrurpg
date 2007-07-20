/*
 *  Copyright 2006-2007 Jerome PASQUIER
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
 * - 20 jul 2007 : Starting implementation
 *
 */

#ifndef _HASH_FILE_H_
#define _HASH_FILE_H_

// For hash sum
#include <unistd.h>
#include <string>
#include <fstream>
#include <sstream>

#include "logger.h"
#include "sha1.h"

using namespace std;

namespace RainbruRPG{
  namespace Core{


    class HashFile{
    public:
      HashFile();

      std::string getHashSum(const std::string&);

    private:
      std::string getMessageDigest(unsigned *message_digest);

    };

  }
}

#endif // _HASH_FILE_H_

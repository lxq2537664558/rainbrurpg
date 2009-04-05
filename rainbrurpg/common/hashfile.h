/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file hashfile.h
  * Declares a class that compute hash sum of a file
  *
  * Modifications :
  * - 01 apr 2009 : Now using gettext compliant string
  * - 07 aug 2008 : Single file documentation
  * - 20 jul 2007 : Starting implementation
  *
  */

#ifndef _HASH_FILE_H_
#define _HASH_FILE_H_

#include <unistd.h> // For hash sum

#include <string>
#include <fstream>
#include <sstream>
#include <sigc++/sigc++.h>

#include "logger.h"
#include "sha1.h"

#include "rainbrudef.h" // For the gettext stuff

using namespace std;

namespace RainbruRPG{
  namespace Core{

    /** Computes the SHA-1 hashsum of a file
      *
      * This class is used to compute the hashsum of a file. It is mainly
      * used during the datafiles update process. The SHA-1 algorythm
      * is provided by the Sha1 class.
      *
      * \sa \ref RainbruRPG::Network::Ident::HashPassword "HashPassword" to
      *     compute the hashsum of a password.
      *
      */
    class HashFile{
    public:
      HashFile();
      virtual ~HashFile();

      std::string getHashSum(const std::string&);
      /** The progression signal
        *
	* The returned value is void. The parameters are :
	* - The filesize
	* - The read bytes
	* - The percentage completed
	*
	*/
      sigc::signal<void, int, int, double> progress;

    private:
      int getFileSize(const char*);
      void computePercent();

      /** The file size in bytes */
      int fsize;
      /** The number of already read bytes */
      int readBytes;
      /** The percent of completed work */
      double completePercent;
    };

  }
}

#endif // _HASH_FILE_H_

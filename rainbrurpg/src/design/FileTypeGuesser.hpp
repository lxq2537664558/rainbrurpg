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

/** \file FileTypeGuesser.hpp
  * Declares a class that try to guess the type of a file
  *
  * Modifications :
  * - 13 aug 2008 : Single file documentation
  * - 14 jul 2007 : Starting implementation
  *
  */

#ifndef FILE_TYPE_GUESSER_H
#define FILE_TYPE_GUESSER_H

#include <string>

#include <itemlistfile.h>
#include <magic.h>
#include <globaluri.h>

using namespace RainbruRPG::Network;
using namespace RainbruRPG::Options;

namespace RainbruRPG{
  namespace Core{

    /** Defines the status of a file in quarantine
      *
      */
    typedef enum{
      QFS_ACCEPTED,   //!< The file is accepted (good extension and in 
	              //!< accepted extension list)

      QFS_REFUSED,    //!< The file is refused (good extension but in 
	              //!< refused extension list)

      QFS_WRONGEXT,   //!< The file is refused (bad extension)

      QFS_TESTEDEXT,  //!< The extension is good but the file is neither
	              //!< in accepted nor in refused list

      QFS_UNKNOWN,    //!< This type of file
    }tQuarantineFileStatus;

    /** A class that try to guess the type of a file
      *
      * \section magic_extension_sec "Magic numbers and file extension"
      *
      * This class used 
      * <a href="http://en.wikipedia.org/wiki/Magic_number_%28programming%29">
      * magic numbers</a> (provided by the libmagic library) to determine the 
      * file type. To avoid security issues
      * we also get the file extension and check if file type is logical
      * with file extension.
      *
      * \section file_status_sec "File status"
      *
      * To tell the file status (ACCEPTED, REFUSED or UNSET), we work with 
      * two files : \c file_extensions.accepted and \c file_extensions.refused.
      * You can modify these files with a text editor to provides your
      * own types.
      *
      */
    class FileTypeGuesser{
    public:
      FileTypeGuesser();
      ~FileTypeGuesser();

      std::string getMimeType(const std::string&); 
      tQuarantineFileStatus getFileStatus(const std::string&);

    private:
      std::string getExtension(const std::string&); 
      int testExtension(const std::string&);

      /** The magic number database from libmagic */
      magic_t magic;

      /** The item list file for accepted extensions */
      ItemListFile* ilfAccepted;
      /** The item list file for refused extensions */
      ItemListFile* ilfRefused;
    };

  }
}


#endif //FILE_TYPE_GUESSER_H

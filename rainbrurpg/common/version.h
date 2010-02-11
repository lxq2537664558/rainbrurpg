/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file version.h
  * Declares a class for libraries versions logging
  *
  * Modifications :
  * - 11 feb 2010 : Need a conversion for VERSION and BUILD_RELEASE
  * - 17 sep 2009 : Now logs build date and time
  * - 25 apr 2009 : Added gettext stuff header
  * - 11 aug 2008 : Single file documentation
  * - 05 jul 2007 : Removing using namespace Ogre due to conflicts Ogre/Qt4
  * - 04 jul 2007 : OIS version added
  *
  */ 

#ifndef VERSION_H
#define VERSION_H

#include <iostream>
#include <string>
#include <sstream>
#include <curl/curlver.h>
#include <fox-1.6/fxver.h>
#include <OIS/OISPrereqs.h>

/* The following macro is used by server and tools that do not link Ogre3D
 * to prevent compilation error
 */
#ifndef INCLUDE_VERSION_WITHOUT_OGRE
#  include <maincore/ogreimport.h> // For Ogre version
#endif //INCLUDE_VERSION_WITHOUT_OGRE

#include "logger.h"
#include "rainbrudef.h" // For the gettext stuff

using namespace std;
using namespace OIS;

/* We cannot use the Ogre namespace this way
 *
 * If we declare globally the Ogre namespace, its uint typedef conflicts
 * with the Qt4 uint one when building Editor and Server.
 *
 */
//using namespace Ogre;
using namespace RainbruRPG::Exception;

namespace RainbruRPG{
  namespace Core{

    /** Draw a little message telling the version of the program 
      * and the libraries it uses at runtime
      *
      * It also prints a GNU message.
      *
      * Since the build 107, The package name, version and build number
      * are taken from the config.h file.
      *
      */
    class Version{
    public:
      Version();
      ~Version();
      void logVersion();

      void setApplicationName(const char*);

    private:
      /** The name of the application
        *
	* This class is used by several applications (client, server...)
	* so it is possible to change the application name. Use 
	* setApplicationName(const char*) to override it. The default is
	* taken from the config.h header.
	*
	*/
      const char* appName;

      /** The version comming from config.h 
        *
	* If we consider w.x.y-z, the version is w.x.y.
	*
	*/
      const char* version;
      /** The build version of the application comming from config.h
        *
	* If we consider w.x.y-z, the build version number is z.
	*
	*/
      const char* build;

      /** The compilation date
        *
	* The value of this string will be set to \c __DATE__
	* in the constructor.
	*
	*/
      const char* buildDate;

      /** The compilation time
        *
	* The value of this string will be set to \c __TIME__
	* in the constructor.
	*
	*/
      const char* buildTime;
    };
  }
}

#endif // VERSION_H

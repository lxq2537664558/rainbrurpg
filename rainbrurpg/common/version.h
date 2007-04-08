/*
 *  Copyright 2006 Jerome PASQUIER
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

#include <iostream>
#include <string>
#include <sstream>
#include <curl/curlver.h>
#include <OGRE/OgrePrerequisites.h>
#include <CEGUI/CEGUIVersion.h>
#include <fox-1.6/fxver.h>
#include "logger.h"

#ifndef VERSION_H
#define VERSION_H

using namespace std;
using namespace Ogre;
using namespace RainbruRPG::Exception;

namespace RainbruRPG{
  namespace Core{

    /** Draw a little message telling the version of the program 
      * and the libraries it is linked with or it uses at runtime
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

    };
  }
}

#endif // VERSION_H

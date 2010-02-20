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

/** \file version.cpp
  * Implements a class for libraries versions logging
  *
  */

#include "version.h"
#include "../config.h"

#include <sstream>

using namespace std;

/** The default constructor
  *
  * It set appName to its default value (RainbruRPG) and calls 
  * initVersion(). The value returned by this call is set to initOk.
  *
  */
RainbruRPG::Core::Version::Version(){

  stringstream ss, ss2;
  ss << VERSION;
  ss2 << BUILD_RELEASE;

  this->appName =PACKAGE;
  this->version =ss.str().c_str();
  this->build   =ss2.str().c_str();
  this->buildDate = __DATE__;
  this->buildTime = __TIME__;
}

/** The default destructor
  *
  */
RainbruRPG::Core::Version::~Version(){

}

/** The log method
  *
  * By a call to this method, you ask this class to compute the version 
  * text and send it to the logger.
  *
  * it uses std::ostringstream to perform the computation of version 
  * numbers and strings, then it calls Logger::logMessage().
  */
void RainbruRPG::Core::Version::logVersion(){
  GTS_BIG(str);
  // TRANSLATORS: The parameters are (in the same order and line layout) :
  // L1 : The application name, version, revision
  // L2 : Fox-Toolkit major, minor and level version
  // L3 : Ogre major, minor version, version patch and version name
  // L4 : Same as Ogre for OIS
  // L5 : libCurl version, timestamp
  sprintf(str, _("Starting %s v%s-%s using :\n"
		 " - FOX-Toolkit v%d.%d.%d\n"
		 " - Ogre3D v%d.%d.%d (%s)\n"
		 " - OIS v%d.%d.%d (%s)\n"
		 " - libCurl v%s (%s)"),
	  appName, version, build,                // First line : own version
	  FOX_MAJOR, FOX_MINOR, FOX_LEVEL,        // Fox versions
	  OGRE_VERSION_MAJOR, OGRE_VERSION_MINOR, // Ogre 1st part
	  OGRE_VERSION_PATCH, OGRE_VERSION_NAME,  // Ogre 2nd part
	  OIS_VERSION_MAJOR, OIS_VERSION_MINOR,   // OIS 1st part
	  OIS_VERSION_PATCH, OIS_VERSION_NAME,    // OIS 2nd part
	  LIBCURL_VERSION, LIBCURL_TIMESTAMP      // libCurl
	  );
   
  Logger::getSingleton().logMessage( str );

  GTS_MID(str2);
  // TRANSLATORS: The parameters are the build (compilation) date and time.
  sprintf(str2, _("Built '%s' at '%s' \n"), buildDate, buildTime);
  Logger::getSingleton().logMessage( str2 );

  string m;
  m=_("Copyright (C) 2006-2010 Jerome PASQUIER\n"
      "RainbruRPG comes with ABSOLUTELY NO WARRANTY. This is free software,\n"
      "and you are welcome to redistribute it under certain conditions.\n"
      "See the GNU General Public License for more details.\n");
  Logger::getSingleton().logMessage(m.c_str());

}

/** Change the application's name
  *
  * It simply change the appName value.
  *
  * \param name The new name of the application.
  */
void RainbruRPG::Core::Version::setApplicationName(const char* name){
  appName=name;
}

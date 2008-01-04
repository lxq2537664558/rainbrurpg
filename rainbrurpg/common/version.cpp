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

#include "version.h"
#include "config.h"

/** The default constructor
  *
  * It set appName to its default value (RainbruRPG) and calls 
  * initVersion(). The value returned by this call is set to initOk.
  *
  */
RainbruRPG::Core::Version::Version(){
  this->appName =PACKAGE;
  this->version =VERSION;
  this->build   =BUILD_RELEASE;
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
  string m;

  std::ostringstream ostr;
    
  ostr <<endl <<endl << appName << " v" <<version << "-"
       << build << " using :" << endl 
       << " - FOX-Toolkit v"
       << FOX_MAJOR << "."
       << FOX_MINOR << "."
       << FOX_LEVEL << endl 
       << " - Ogre3D v"
       << OGRE_VERSION_MAJOR << "." << OGRE_VERSION_MINOR 
       << "." << OGRE_VERSION_PATCH << " (" 
       << OGRE_VERSION_NAME<< ")"<< endl 
       << " - OIS v" 
       << OIS_VERSION_MAJOR << "." << OIS_VERSION_MINOR
       << "." << OIS_VERSION_PATCH << " (" 
       << OIS_VERSION_NAME << ")" << endl
       << " - CURL v"
       << LIBCURL_VERSION << " (" <<  LIBCURL_TIMESTAMP
       << ")" << endl;

  Logger::getSingleton().logMessage( ostr.str() );



  m="Copyright (C) 2006 Jerome PASQUIER";
  Logger::getSingleton().logMessage(m.c_str());
  
  m="RainbruRPG comes with ABSOLUTELY NO WARRANTY. This is free software,";
  Logger::getSingleton().logMessage(m.c_str());
  
  m="and you are welcome to redistribute it under certain conditions.";
  Logger::getSingleton().logMessage(m.c_str());
  
  m="See the GNU General Public License for more details.";
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

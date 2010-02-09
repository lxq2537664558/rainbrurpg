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

/** \file loglistener.cpp
  * Implements a class used to show Ogre messages in a Qt widget
  *
  */

#include "loglistener.h"

/** The default constructor
  *
  * \param parent The parent widget
  *
  */
myLogListener::myLogListener(QWidget* parent) 
  : LogListener(), QWidget(parent){

}

/** The default destructor
  *
  */
myLogListener::~myLogListener(){
}

/** Write a new log message
  *
  * \param name An unused parameter
  * \param msg The log message
  * \param lvl An unused parameter
  * \param maskDebug An unused parameter
  *
  */
void myLogListener::write(const Ogre::String& name, const Ogre::String& msg, Ogre::LogMessageLevel lvl, bool maskDebug)
{
	Q_UNUSED(name);
	Q_UNUSED(lvl);
	Q_UNUSED(maskDebug);
	logMsg = msg.c_str();
}

/** Gets the logged message
  *
  * \return The logged message
  *
  */
QString myLogListener::getMsg(){
	return logMsg;
}

/** A message is about to be logged
  *
  *
  * \param message   The message to be logged
  * \param lvl       The message level the log is using
  * \param maskDebug If we are printing to the console or not
  * \param logName   the name of this log (so you can have several listeners 
  *                  for different logs, and identify them)
  */
void myLogListener::
messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lvl, 
	      bool maskDebug, const Ogre::String& logName){

  Q_UNUSED(logName);
  Q_UNUSED(lvl);
  Q_UNUSED(maskDebug);
  logMsg = message.c_str();
}

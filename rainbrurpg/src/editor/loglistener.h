/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file loglistener.h
  * Declares a class used to show Ogre messages in a Qt widget
  *
  * Modifications :
  * - 13 aug 2008 : Single file documentation
  * - 04 jan 2008 : GNU header added
  */

#ifndef MY_LOG_LISTENER
#define MY_LOG_LISTENER

#include <ogreimport.h>
#include <QWidget>


/** A subclass of Ogre::LogListener showing messages in a QWidget
  *
  */
class myLogListener : public Ogre::LogListener, QWidget{
 public:
  myLogListener(QWidget* parent = 0);
  ~myLogListener();
  
  void write(const Ogre::String &name, const Ogre::String &message,
	     Ogre::LogMessageLevel lml=Ogre::LML_CRITICAL, 
	     bool maskDebug=true);
  
  virtual void messageLogged(const Ogre::String&, Ogre::LogMessageLevel, 
			     bool, const Ogre::String&);
    
    QString getMsg();
  
 private:
  /** The log message */
  QString logMsg;
};

#endif // MY_LOG_LISTENER

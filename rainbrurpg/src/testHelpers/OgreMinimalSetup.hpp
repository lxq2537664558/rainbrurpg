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

#ifndef _OGRE_MINIMAL_SETUP_HPP_
#define _OGRE_MINIMAL_SETUP_HPP_

#include <OgreLogManager.h>
#include <OgreRenderWindow.h>

#include <OgreRoot.h>

// Define a configuration directory according to the platform
#ifdef WIN32
#  define CONFIG_DIR "./"
#else
#  define CONFIG_DIR "../../"
#endif

/** A quiet log listener for Ogre */
class SilentLogListener:public Ogre::LogListener{
  /** Does nothing with the log */
  void messageLogged(const Ogre::String& message, Ogre::LogMessageLevel lml, 
		     bool maskDebug, const Ogre::String& logName){
    switch (lml){
    case Ogre::LML_NORMAL:
      break;
    case Ogre::LML_CRITICAL:
      break;
    case Ogre::LML_TRIVIAL:
      break;
    }
  }
};

/// Warning: using this class need X11 to run tests
class OgreMinimalSetup{
public:
  OgreMinimalSetup();
  ~OgreMinimalSetup();

  void setupOgre(bool custom_log=true, const Ogre::String& base_dir=CONFIG_DIR);
  void teardownOgre();

  Ogre::RenderWindow* getRenderWindow();

protected:
  bool dirExists(const std::string&);
  void debugRenderList(Ogre::RenderSystemList*);
  
  SilentLogListener* mListener;      //!< The custom log listener
  Ogre::RenderWindow* mRenderWindow; //!< The render window
};

#endif // !_OGRE_MINIMAL_SETUP_HPP_

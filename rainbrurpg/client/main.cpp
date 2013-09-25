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

//#include <irrlicht.h>
#include <iostream>

#include "gameengine.h"
#include <logger.h>
//#include "guimanager.h"
#include <version.h>
//#include <cstdlib> 
#include <ctime> 
#include <iostream>

#include "options.h"
#include "vcconstant.h"
#include "globaluri.h"

/** To avoid a double definition og PI
  *
  * Fox and Ogre both defines PI (fxdefs.h and OgreMath.h)
  *
  */
#define PI
#include <fox-1.6/fx.h>
#include "launcher.h"
#include <optionmanager.h>
#undef PI

using namespace RainbruRPG::Core;
using namespace RainbruRPG::Gui;
using namespace RainbruRPG::Options;
using namespace RainbruRPG::Network;
using namespace FX;


/** Comment it if you compile under WIN32 in a
  * console application project
  */
#define WIN_GUI_APPLICATION


/** return true if we must launch the game, 
  * false if the Cancel button is clicked
  */
bool showLauncher(int argc, char **argv){

  // Options initialization
  OptionManager::getSingleton().init();
  OptionManager::getSingleton().createAttributes();
  OptionManager::getSingleton().setAttributesDefaultValues();

  // The main return value
  bool execRet;
  
  FX::FXApp application("RainbruRPG","rainbruFreeFr");
  
  // The true should cause a segfault if omitted
  application.init(argc,argv, true);
  
  new Launcher(&application);
  
  application.create();

  // Return 999 if the game may run
  int ret =application.run();

  if (ret==999){
    // The game must be launched
    execRet=true;
    RainbruRPG::Core::GameEngine::getSingleton().play();

  }
  else{
    // The 'Quit' button was clicked : stopping execution
    execRet=false;
  }

  return execRet;
}


#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#  define WIN32_LEAN_AND_MEAN

#  define NOMINMAX
#  include "windows.h"

#  ifdef WIN_GUI_APPLICATION
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )

  // We must fake the argc and argv variables
  // to prevent FXApp::init() call, but
  // the following causes a segfault
  int argc=1;
  char* fakeArgv="";
  char** argv=&fakeArgv;

#  endif
#else
int main(int argc, char **argv)
#endif

{
  // Initialize the pseudo-random number generator
  srand((unsigned)time(0)); 

  // Setting up Ogre::Root
  GlobalURI gu;
  std::string plugFN=gu.getShareFile("config/plugins.cfg");
  std::string ogreFN=gu.getUserDirFile("ogre.cfg");
  new Ogre::Root(plugFN.c_str(), ogreFN.c_str(), "ogre.log");

  // Log out the versions
  Version v;
  v.setApplicationName("RainbruRPG Client");
  v.logVersion();
  


  if (showLauncher(argc, argv)){

    GuiManager::getSingleton().init();
    GameEngine::getSingleton().init();
    GameEngine::getSingleton().changeState(ST_MAIN_MENU);

    //    GuiManager::getSingleton().loadCEGUILayout("gui.xml");
    
    
    // main loop
    GameEngine::getSingleton().run();
    
    GameEngine::getSingleton().cleanup();

  }
  return 0;
}



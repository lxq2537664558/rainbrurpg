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

/* Modifications :
 * - 24 jan 2008 : Handles help and version command-line options
 *
 */

#include <iostream>

#include "gameengine.h"
#include <logger.h>
#include "guimanager.h"

#include <version.h>
//#include <cstdlib> 
#include <ctime> 
#include <iostream>

#include "options.h"
#include "vcconstant.h"
#include "globaluri.h"

/** To avoid a double definition of PI
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


// Forward declarations
void handleCommandLineOptions(int argc, char **argv);
void showHelp(void);
bool showLauncher(int argc, char **argv);
void showVersion(void);
// End of forward declarations



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#  define WIN32_LEAN_AND_MEAN

#  define NOMINMAX
#  include "windows.h"

#  ifdef WIN_GUI_APPLICATION
INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT ){

  // We must fake the argc and argv variables
  // to prevent FXApp::init() call, but
  // the following causes a segfault
  int argc=1;
  char* fakeArgv="";
  char** argv=&fakeArgv;

#  endif
#else
int main(int argc, char **argv){
#endif

  handleCommandLineOptions(argc, argv);
  showVersion();

  // Initialize the pseudo-random number generator
  srand((unsigned)time(0)); 

  // Setting up Ogre::Root
  GlobalURI gu;
  std::string plugFN=gu.getShareFile("config/plugins.cfg");
  std::string ogreFN=gu.getUserDirFile("ogre.cfg");
  Ogre::Root* root=new Ogre::Root(plugFN.c_str(), ogreFN.c_str(), "ogre.log");

  // Shows the launcher 
  if (showLauncher(argc, argv)){

    GuiManager::getSingleton().init();
    GameEngine::getSingleton().init();
    GameEngine::getSingleton().changeState(ST_MAIN_MENU);

    // main loop
    GameEngine::getSingleton().run();
    
    GameEngine::getSingleton().cleanup();

  }

  delete root;
  root=NULL;

  return 0;
}


/** Execute the FOX-toolkit launcher
  *
  * The launcher allows the user the exit the game before playing  or
  * edit the options. The argument come from the C++ standard main() 
  * function and are mandatory to create a FX::FXApp object.
  *
  * \param argc The number of command line arguments
  * \param argv The command line arguments array
  *
  * \return \c true if we must launch the game, \c false if the Cancel 
  *          button was clicked
  *
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
  
  Launcher* launcher=new Launcher(&application);
  
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

  delete launcher;
  launcher=NULL;

  return execRet;
}

/** Print the usage message in stdout
  *
  * The common GNU usage is to use -h and --help command-line
  * options to show the usage message (a list of available command-line
  * options) and quit the program. This function print the usage
  * message to the standard output (using std::cout).
  *
  */
void showHelp(void){
  cout << "usage: rainbrurpg [-h] [-V]" << endl
       << "-h, --help\t\t" <<  "show this usage message." << endl
       << "-V, --Version\t\t"<<"show version." << endl;
}
 
/** Handles the command line options
  *
  * \param argc The number of command line arguments
  * \param argv The command line arguments array
  *
  */
void handleCommandLineOptions(int argc, char **argv){
   // Handles command-line options
   for (unsigned int i=0; i<argc; i++){
     if (strcmp(argv[i], "-h")==0 || strcmp(argv[i], "--help")==0){
       showHelp();
       exit(0);
     }
     if (strcmp(argv[i], "-V")==0 || strcmp(argv[i], "--version")==0){
       showVersion();
       exit(0);
     }
   }
   
 }

 /** Shows the version numbers 
   *
   * This function uses a \ref RainbruRPG::Core::Version "Version"
   * object to log out the version numbers. It is called from 
   * both handleCommandLineOptions() and main() functions.
   *
   */
 void showVersion(void){
   Version v;
   v.setApplicationName("RainbruRPG Client");
   v.logVersion();
 }
 

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

/** \file src/client/main.cpp
  *
  * The file declaring the client's main() function
  *
  * Modifications :
  * - 17 jun 2008 : Adding a quiet option
  *                 Now using std::string
  * - 09 jun 2008 : Fix a SEGFAULT due to deleting Ogre Root object
  * - 24 jan 2008 : Handles help and version command-line options
  *
  */

#include <iostream>

#include "GameEngine.hpp"
#include <Logger.hpp>
#include "GuiManager.hpp"
#include "skinmanager.h"
#include "bggui.h"
#include "GuiFrameListener.hpp"
#include <renderqueuelistener.h>

#include <Version.hpp>
//#include <cstdlib> 
#include <ctime> 
#include <iostream>
#include <string>

#include <VcConstant.hpp>
#include <Options.hpp>
#include <GlobalUri.hpp>

// includes game states
#include "GsMainMenu.hpp"
#include "GsConnection.hpp"
#include "GsCreateAccount.hpp"
#include "GsServerList.hpp"
#include "GsUpdateDatafiles.hpp"

#include "GsOgreguiTest.hpp"

#include <GsLocalTest.hpp>

/** To avoid a double definition of PI, launcher.h, that include Ogre3D
  * headers must be included before fox headers. Fox and Ogre both defines 
  * PI (fxdefs.h and OgreMath.h).
  *
  */
#include "launcher.h"
#include <fox-1.6/fx.h>
#include <OptionManager.hpp>

#include "../config.h"
#include <OgrePlatform.h>

using namespace RainbruRPG::Core;
using namespace RainbruRPG::Events;
using namespace RainbruRPG::Gui;
using namespace RainbruRPG::Options;
using namespace RainbruRPG::Network;
using namespace FX;
using namespace std;

// Forward declarations
void handleCommandLineOptions(int argc, char **argv, GameEngineOptions*);
void showHelp(void);
bool showLauncher(int argc, char **argv);
void showVersion(void);
void initGameStates();
// End of forward declarations


// Handling win32 graphical main fonction
#if (OGRE_PLATFORM == OGRE_PLATFORM_WIN32)
/** Tells that we are running on a Win32 platform */
#  define WIN32_LEAN_AND_MEAN
/** Avoid declaration of min and max macro from Win32 */
#  define NOMINMAX
#  include "windows.h"

/** Win32 specific main entry for non-console application
  *
  * Actually, none of the parameters are used, however I put their
  * documentation.
  *
  * \param hInstance     Handle to the current instance of the application.
  * \param hPrevInstance Handle to the previous instance of the application. 
  *                      This parameter is always NULL.
  * \param lpCmdLine     Pointer to a null-terminated string specifying the 
  *                      command line for the application, excluding the 
  *                      program name.
  * \param nCmdShow      Specifies how the window is to be shown.
  *
  */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, 
		    LPSTR lpCmdLine, INT nCmdShow){

  // We must fake the argc and argv variables
  // to prevent FXApp::init() call, but
  // the following causes a segfault
  int argc=1;
  char* fakeArgv="";
  char** argv=&fakeArgv;

#else /* OGRE_PLATFORM == OGRE_PLATFORM_WIN32 */
  /** The main function for other platforms than Win32 and for Win32 in
    * console
    *
    * \param argc The number of arguments
    * \param argv The arguments C-strings array
    *
    */
int main(int argc, char **argv){
#endif /* OGRE_PLATFORM == OGRE_PLATFORM_WIN32 */

  GameEngineOptions geo;
  geo.ogreGuiTest = false;
  geo.fullscreen = false;

  handleCommandLineOptions(argc, argv, &geo);
  showVersion();

  // Initialize the pseudo-random number generator
  srand((unsigned)time(0)); 

  // Setting up Ogre::Root
  GlobalURI gu;
#ifdef WIN32
  std::string plugFN=gu.getShareFile("config/plugins-win32.cfg");
#else
  std::string plugFN=gu.getShareFile("config/plugins.cfg");
#endif
  std::string ogreFN=gu.getUserDirFile("ogre.cfg");
  Ogre::Root* root=new Ogre::Root(plugFN.c_str(), ogreFN.c_str(), "ogre.log");

  // Shows the launcher 
  if (showLauncher(argc, argv)){

    GuiManager::getSingleton().init();
    GameEngine::getSingleton().init(geo);

    // Must be called after GameEngine::init() for ressources to be loaded
    //    SkinManager::getSingleton().init();


    initGameStates();
    GameEngine::getSingleton().changeState("gsMainMenu");

    // Moved from GameEngine::init()
    GuiFrameListener* mFrameListener = 
      new GuiFrameListener(GameEngine::getSingleton().getRenderWindow(), 
			   GameEngine::getSingleton().getCamera());
    Ogre::Root::getSingleton().addFrameListener(mFrameListener);
    mFrameListener->setCamera(GameEngine::getSingleton().getCamera());

    if (!GameEngine::getSingleton().getOgreRoot()){
      LOGE("OgreRoot is not initialized");
    }

    // Moved from GameEngine::init()
    mFrameListener->setCamera(GameEngine::getSingleton().getCamera());


    // GuiManager settings
#ifdef RAINBRU_RPG_DEBUG
    GuiManager::getSingleton()
      .createNumDebugWindow(GameEngine::getSingleton().getRenderWindow());
#endif
    GuiManager::getSingleton()
      .createTitleOverlay(GameEngine::getSingleton().getRenderWindow());

 
   // main loop
    GameEngine::getSingleton().run();
    
    GameEngine::getSingleton().cleanup();

  }

  root->shutdown();

  // Removed due to a SEGFAULT in Ogre::SharedPtr :(
   //delete root;
  //  root=NULL;

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
       << "-?, -h, --help\t\t"   << "show this usage message." << endl
       << "-f, --fullscreen\t\t" << "Launch the game in fullscreen mode." << endl
       << "-V, --version\t\t"    << "show version." << endl
       << "-q, --quiet\t\t"      << "disabled std-out messages logging." << endl
       << "    --ogregui-test\t" << "used to test the GUI feature." << endl;
}
 
/** Handles the command line options
  *
  * It is a basic ang ugly command line options handling. Mostly
  * using \c std::string conversion and \c operator==.
  *
  * \param argc The number of command line arguments
  * \param argv The command line arguments array
  * \param geo  The game engine related options
  *
  */
void handleCommandLineOptions(int argc, char **argv, GameEngineOptions* geo){

  string opt;
  // Start at 1 to prevent a 'Unknown option rainbrurpg' bug
  for (unsigned int i=1; i<argc; i++){
     opt=argv[i];
     if (opt == "-?" || opt == "-h" ||opt == "--help"){

       showHelp();
       exit(EXIT_SUCCESS);
     }
     else if (opt == "-f" || opt == "--fullscreen"){
       geo->fullscreen=true;
     }
     else if (opt == "-V" || opt == "--version"){
       showVersion();
       exit(EXIT_SUCCESS);
     }
     // Quiet option, no log in std::out
     else if (opt == "-q" || opt == "--quiet"){
       RainbruRPG::Exception::Logger::getSingleton().setLogType(LOG_FILE);
       // Do not quit the game
     }
     // Quiet option, no log in std::out
     else if (opt == "--ogregui-test"){
       geo->ogreGuiTest = true;
       GameEngine::getSingleton().changeState("gsOgreGuiTest");
     }
     // Unknown options
     else{
       cout << "Unknown option " << opt << endl
	    << "Please run with --help option for usage." << endl;
       exit(EXIT_FAILURE);
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
 
 /** Initializes the game states
   *
   */
 void initGameStates(){
   GameEngine::getSingleton().registerGameState(new gsMainMenu());
   GameEngine::getSingleton().registerGameState(new gsConnection());
   GameEngine::getSingleton().registerGameState(new gsServerList());
   //   GameEngine::getSingleton().registerGameState(new gsUpdateDatafiles());

   GameEngine::getSingleton().registerGameState(new gsLocalTest());
   GameEngine::getSingleton().registerGameState(new gsOgreguiTest());
  
 }

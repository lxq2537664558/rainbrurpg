/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file server/main.cpp
  * The file that implements the server's main function 
  *
  * Modifications :
  * - 05 sep 2008 : Single file documentation
  * - 24 jan 2008 : Handles help and version command-line options
  * - 05 jul 2007 : Log out the versions
  *
  */

#include <QApplication>
#include <QWidget>

#include <Logger.hpp>

#define INCLUDE_VERSION_WITHOUT_OGRE
#include <Version.hpp>


#include <string>

#include "mainwindow.h"
#include "uniquename.h"

using namespace std;
using namespace RainbruRPG::Server;


// Forward declarations
void handleCommandLineOptions(int argc, char **argv);
void showHelp(void);
void showVersion(void);
// End of forward declarations

/** The Server main function
  *
  * \param argc The command line arguments number
  * \param argv The command line arguments array
  *
  */
int main(int argc, char *argv[]){
  showVersion();

  QApplication app(argc, argv);

  // Set the UniqueName in main window title bar
  std::string s;
  s="RainbruRPG server (";
  s+=UniqueName::getUniqueName();
  s+=")";

  QString s2(s.c_str());

  MainServerWindow* mainWin = new MainServerWindow(s2);
  mainWin->setWindowState( Qt::WindowMaximized );

  mainWin->show();
  LOGI("Mainwin::show() ended");

  LOGI("Entering Qt main loop");

  QObject::connect( &app, SIGNAL( aboutToQuit() ), mainWin, 
		    SLOT( exitRequested() ) );

  QObject::connect (&app, SIGNAL( focusChanged(QWidget* ,QWidget* )),
	            mainWin, SLOT(focusChanged(QWidget* ,QWidget* )));

  return app.exec();
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
  cout << "usage: rainbrurpg-server [-h] [-V]" << endl
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
  v.setApplicationName("RainbruRPG Server");
  v.logVersion();
}
 

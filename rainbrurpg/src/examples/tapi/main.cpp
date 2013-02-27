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

/** \file examples/tapi/main.cpp
  * A simple example showing how to use TerminalApi
  *
  * Modifications :
  * - 13 aug 2008 : Single file documentation
  *
  */

#include <infodialog.h>
#include <terminalapp.h>
#include <menubar.h>
#include <menu.h>
#include <menuitem.h>
#include <window.h>

#include <logger.h>

using namespace RainbruRPG::Terminal;
using namespace RainbruRPG::Exception;

// Forward declarations
MenuBar* createMenubar(void);

int slotFileExit(void);
int slotExampleDialog(void);
int slotExampleWindow(void);
// End of forward declarations

/** The main fonction of the example
  *
  * Here, we initialize the TerminalApp singleton and set the menubar
  * created by the \ref createMenubar() function.
  *
  * \param argc The number of command-line arguments
  * \param argv The array of command-line arguments
  *
  */
int main(int argc, char** argv){
  Logger::getSingleton().setFilename("RainbruRPG-examples-tapi.log");

  TerminalApp::getSingleton().init();
  TerminalApp::getSingleton().setMenubar(createMenubar());
  TerminalApp::getSingleton().draw();
  TerminalApp::getSingleton().run();

};


/** Create the menu bar
  *
  * \return The newly created menubar
  *
  */
MenuBar* createMenubar(void){
  MenuBar* mBar=new MenuBar();

    Menu* mFile = new Menu("&File");
      MenuItem* mFileExit=new MenuItem("&Exit");
      mFileExit->setAction(&slotFileExit);
    mFile->addItem(mFileExit);


    Menu* mExamples = new Menu("E&xamples");
      MenuItem* mExampleDialog=new MenuItem("&Dialog");
      mExampleDialog->setAction(&slotExampleDialog);
      MenuItem* mExampleWindow=new MenuItem("&Window");
      mExampleWindow->setAction(&slotExampleWindow);
    mExamples->addItem(mExampleDialog);
    mExamples->addItem(mExampleWindow);

  mBar->addMenu(mFile);
  mBar->addMenu(mExamples);
  return mBar;
}

/** The function associated to the File/Exit menu
  *
  * \return A value different to -1.
  *
  */
int slotFileExit(void){
  TerminalApp::getSingleton().cleanup();
  exit(0);
  return 0;
};

/** The function associated to the Examples/Dialog menu
  *
  * \return A value different to -1.
  *
  */
int slotExampleDialog(void){
  Dialog* mDialog=new InfoDialog("", 40,16);
  mDialog->setTitle("InfoDialog sample");
  mDialog->setMessage("This is a centered dialog. This example shows how it \
is simple to create a dialog with a title, a message and a OK button.\n\n \
This dialog is always modal.");

  TerminalApp::getSingleton().showDialog(mDialog);
  return 0;
   
}

/** Creates an example window
  *
  * \return Always 0
  *
  */
int slotExampleWindow(void){
  Window* mWin=new Window("Window example");
  mWin->move(4,5);
  mWin->resize(25, 12);

  TerminalApp::getSingleton().addWindow(mWin);

  return 0;
}

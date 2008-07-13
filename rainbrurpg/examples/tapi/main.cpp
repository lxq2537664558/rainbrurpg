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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include <infodialog.h>
#include <terminalapp.h>
#include <menubar.h>
#include <menu.h>
#include <menuitem.h>

#include <logger.h>

using namespace RainbruRPG::Terminal;
using namespace RainbruRPG::Exception;

// Forward declarations
MenuBar* createMenubar(void);

int slotFileExit(void);
int slotExampleDialog(void);
// End of forward declarations

int main(int argc, char** argv){
  Logger::getSingleton().setFilename("RainbruRPG-examples-tapi.log");

  TerminalApp::getSingleton().init();
  TerminalApp::getSingleton().setMenubar(createMenubar());
  TerminalApp::getSingleton().draw();
  TerminalApp::getSingleton().run();

};



MenuBar* createMenubar(void){
  MenuBar* mBar=new MenuBar();

    Menu* mFile = new Menu("&File");
      MenuItem* mFileExit=new MenuItem("&Exit");
      mFileExit->setAction(&slotFileExit);
    mFile->addItem(mFileExit);


    Menu* mExamples = new Menu("E&xamples");
      MenuItem* mExampleDialog=new MenuItem("&Dialog");
      mExampleDialog->setAction(&slotExampleDialog);
    mExamples->addItem(mExampleDialog);

  mBar->addMenu(mFile);
  mBar->addMenu(mExamples);
  return mBar;
}

int slotFileExit(void){
  TerminalApp::getSingleton().cleanup();
  exit(0);
};

int slotExampleDialog(void){
  Dialog* mDialog=new InfoDialog("", 40,16);
  mDialog->setTitle("InfoDialog sample");
  mDialog->setMessage("This is a centered dialog. This example shows how it \
is simple to create a dialog with a title, a message and a OK button.\n\n \
This dialog is always modal.");

  TerminalApp::getSingleton().showDialog(mDialog);
    
}

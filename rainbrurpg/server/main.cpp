/*
 *  Copyright 2006-2007 Jerome PASQUIER
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
 * - 05 jul 2007 : Log out the versions
 *
 */

#include <QApplication>

#include <logger.h>
#include <version.h>
#include <QWidget>

#include "mainwindow.h"
#include "uniquename.h"

using namespace RainbruRPG::Server;

/** The Server main function
  *
  * \param argc The command line arguments number
  * \param argv The command line arguments vector
  *
  */
int main(int argc, char *argv[]){
  LOGI("Starting RainbruRPG editor");
  QApplication app(argc, argv);

  // Log out the versions
  Version v;
  v.setApplicationName("RainbruRPG Client");
  v.logVersion();

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

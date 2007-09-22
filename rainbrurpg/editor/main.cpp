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

#include <QApplication>
#include <OGRE/Ogre.h>
#include <version.h>

#include "mainwindow.h"

using namespace RainbruRPG::Editor;

/** The Editor main function
  *
  * \param argc The command line arguments number
  * \param argv The command line arguments vector
  *
  */
int main(int argc, char *argv[]){
  // Log out the versions
  Version v;
  v.setApplicationName("RainbruRPG Editor");
  v.logVersion();

  LOGI("Starting RainbruRPG editor");
  QApplication app(argc, argv);

  QPixmap pixmap(":/images/splash.png");
  QSplashScreen* splashScreen = new QSplashScreen(pixmap);
  splashScreen->show();
  splashScreen->showMessage("Initialising Engine", 
       Qt::AlignCenter |Qt::AlignBottom | Qt::AlignAbsolute, Qt::black);

  EditorMainWindow* mainWin = new EditorMainWindow("Show Mesh");
  
  mainWin->show();
  LOGI("Mainwin::show() ended");


  splashScreen->finish(mainWin);
  delete splashScreen;

  LOGI("Entering Qt main loop");
  return app.exec();
}

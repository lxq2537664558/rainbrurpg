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

// Essai avec libfox
#include <fx.h>
#include <iostream>
#include "launcher.h"


using namespace FX;
using namespace RainbruRPG::Gui;

#ifdef WIN32
int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, 
		    LPSTR lpCmdLine, int nShowCmd){

  // We must fake the argc and argv variables
  // to prevent FXApp::init() call.
  int argc=1;
  char* fakeArgv="";
  char** argv=&fakeArgv;

#  else
int main(int argc,char ** argv) {
#endif

  // The main erturn value
  int execRet=0;
  
  FXApp application("RainbruRPG","rainbruFreeFr");
  
  // The true should cause a segfault if omitted
  application.init(argc,argv, true);
  
  new Launcher(&application);
  
  application.create();

  // Return 999 if the game may run
  int ret =application.run();

  if (ret==999){
    // The game must be launched
    std::cout << "To be continued..." <<  std::endl;
  }
  else{
    // The 'Quit' button was clicked : stopping execution
    std::cout << "Stopping execution of RainbruRPG" <<  std::endl;
    execRet=ret;
  }

  return execRet;
 } 


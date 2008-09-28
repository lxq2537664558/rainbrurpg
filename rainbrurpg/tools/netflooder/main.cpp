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

/** \file tools/netflooder/main.cpp
  * Implements the main entry of the NetFlooder tool
  *
  * Modifications :
  * - 22 sep 2008 : Single file documentation
  *
  */

#include <iostream>
#include <logger.h>

#define INCLUDE_VERSION_WITHOUT_OGRE
#include <version.h>

#include <fox-1.6/fx.h>

#include "netflooderwindow.h"

using namespace FX;
using namespace RainbruRPG::Gui;

/** xIdent main entry
  *
  * \param argc The number of command-line argument
  * \param argv The array of command-line argument
  *
  */
int main(int argc, char **argv){

  FX::FXApp application("RainbruRPG","rainbruFreeFr");
  
  // The true should cause a segfault if omitted
  application.init(argc,argv, true);
  
  new NetFlooderWindow(&application);
  
  application.create();

  // Return 999 if the game may run
  int ret =application.run();

  return 0;
}



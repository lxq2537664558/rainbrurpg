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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */
#include <iostream>

// For test purpose
#include <xmltimestamp.h>
#include <tinyxml.h>
#include <logger.h>
// End of test

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Select_Browser.H>
 
#include <FL/Fl_Input.H>
#include <FL/Fl_Secret_Input.H>
#include <FL/Fl_Group.H>

#include "xidentwindow.h"


using namespace std;
using namespace RainbruRPG::Gui;

int main( int argc, char ** argv ){

  RainbruRPG::Exception::Logger::getSingleton().setFilename("xident.log");
  
  XIdentWindow *window = new XIdentWindow();
  window->show(argc, argv);
  return Fl::run();

}

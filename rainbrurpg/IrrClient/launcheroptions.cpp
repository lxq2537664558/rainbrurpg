/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

#include "launcheroptions.h"

#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Output.H>
#include <FL/Fl_Tabs.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Choice.H>

#include "logger.h"

RainbruRPG::Options::LauncherOptions::LauncherOptions()
           :Fl_Window(100, 100, 500,400,"Options editor"){
  begin();
    Fl_Button *btnCancel=new Fl_Button( 390, 360, 100, 30, "Cancel" );
    Fl_Button *btnOK=new Fl_Button( 10, 360, 100, 30, "OK" );
    Fl_Tabs *tabs=new Fl_Tabs(10, 10, 480, 340,"");

  end();

  //Create pages
  Fl_Group *optGraph=new Fl_Group(10,10,200,200, "Graphics");
  optGraph->begin();
    Fl_Check_Button *cbFullscreen=new Fl_Check_Button(
                         20, 20, 120,20, "Fullscreen");
    Fl_Choice *sbRes=new Fl_Choice( 55, 40, 120, 20,"Res." );
    sbRes->add("640 X 480");
    sbRes->add("800 X 600");
    sbRes->add("1024 X 768");
    sbRes->add("1280 X 1024");

    // tooltips
    cbFullscreen->tooltip("Set the game to be played in fullscreen mode");
    sbRes->tooltip("Set the screen resolution for both fullscreen and"
		   " windowed mode");
  optGraph->end();

  Fl_Group *optSound=new Fl_Group(50,50,270,250, "Sounds");

  // Add pages
  tabs->add(optGraph);
  tabs->add(optSound);

  // callbacks
  btnCancel->callback( cbQuit, this );

  this->set_modal();

  this->show();
}

RainbruRPG::Options::LauncherOptions::~LauncherOptions(){
  LOGI("Deleting launcherOption fltk window");

}

/** Static callback for the \c Quit button */
void RainbruRPG::Options::LauncherOptions::cbQuit (Fl_Widget*, void*v){
   ( (LauncherOptions*)v )->i_cbQuit();
}

/** Inline callback for the \c Quit button */
void RainbruRPG::Options::LauncherOptions::i_cbQuit (){
  this->hide();
}

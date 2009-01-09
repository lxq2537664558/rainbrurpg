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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "launcher.h"

#include <irrlicht.h>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Multiline_Output.H>
#include <FL/fl_ask.H>
#include <FL/Fl.H>

#include "gameengine.h"
#include "logger.h"

/** Default constructor */
RainbruRPG::Gui::Launcher::Launcher()
          :Fl_Window(300, 400, "RainbruRPG Launcher"){
  // Center the launcher in the screen
  int x=(Fl::w()/2)-(this->w()/2);
  int y=(Fl::h()/2)-(this->w()/2);
  this->position(x, y);

  lo=0;

  begin();
  Fl_Multiline_Output moHelp( 10, 10, 280, 150 );


    Fl_Choice chQuality( 60 , 185, 230, 20, "Quality" ); 

    sbRenderer =new Fl_Hold_Browser( 90, 250, 200, 115, "Renderer" );

    Fl_Button btnPlay( 10, 250, 70, 30, "Play" );
    Fl_Button btnOpts( 10, 300, 70, 30, "Options" );
    Fl_Button btnQuit( 10, 350, 70, 30, "Quit" );
  end();

  // Help text
  moHelp.color( FL_BACKGROUND_COLOR, FL_RED );
  moHelp.value("Here you can choose the renderer\n"
	       "according to your OS. You can only\n"
	       "select a graphic quality snapshot\n"
	       "or create a new one by clicking the\n"
	       "Options button.");
  
  // Renderers list
  sbRenderer->add("Software 1");
  sbRenderer->add("Software 2");

  sbRenderer->add("OpenGL 1.5");
  sbRenderer->add("Direct3D 9.0c");
  sbRenderer->add("Direct3D 8.1");


  // applies callbacks
  btnPlay.callback( cbPlay, this );
  btnOpts.callback( cbOpts, this );
  btnQuit.callback( cbQuit, this );
  sbRenderer->callback( cbDriverList, this );


  this->show();
  Fl::run();  

}

/** Default destructor */
RainbruRPG::Gui::Launcher::~Launcher(){
  LOGI("Deleting launcher fltk window");
  this->hide();
  //  lo=NULL;
  //  sbRenderer=NULL;

  if (lo){
    LOGI("  Deleting launcherOption if open");

    lo->~LauncherOptions();
  }
  //  lo=NULL;
  LOGI("  Destructor complete");

}

/** Static callback for the \c Play button */
void RainbruRPG::Gui::Launcher::cbPlay (Fl_Widget*, void*v){
   ( (Launcher*)v )->i_cbPlay();
}

/** Inline callback for the \c Play button */
void RainbruRPG::Gui::Launcher::i_cbPlay (){
  RainbruRPG::Core::GameEngine::getSingleton().play();
  this->setRenderer();
}

/** Static callback for the \c Quit button */
void RainbruRPG::Gui::Launcher::cbOpts (Fl_Widget*, void*v){
   ( (Launcher*)v )->i_cbOpts();
}

/** Inline callback for the \c Quit button */
void RainbruRPG::Gui::Launcher::i_cbOpts (){
  lo=new Options::LauncherOptions();

}

/** Static callback for the \c Quit button */
void RainbruRPG::Gui::Launcher::cbQuit (Fl_Widget*, void*v){
   ( (Launcher*)v )->i_cbQuit();
}

/** Inline callback for the \c Quit button */
void RainbruRPG::Gui::Launcher::i_cbQuit (){
  this->hide();
  RainbruRPG::Core::GameEngine::getSingleton().quit();
}

/** Set the selected renderer in GameEngine */
void RainbruRPG::Gui::Launcher::setRenderer(){
  int bValue=sbRenderer->value();
  irr::video::E_DRIVER_TYPE d;

  // no item selected
  if (bValue!=0) {
    LOGI("Setting GameEngine driver type...");
    switch(bValue){
    case 1:
      d=irr::video::EDT_SOFTWARE;
      break;
    case 2:
      d=irr::video::EDT_SOFTWARE2;
      break;
    case 3:
      d=irr::video::EDT_OPENGL;
      break;
    case 4:
      d=irr::video::EDT_DIRECT3D9;
      break;
    case 5:
      d=irr::video::EDT_DIRECT3D8;
      break;
    default:
        d=irr::video::EDT_NULL;
    }
    Core::GameEngine::getSingleton().setDriverType(d);
    this->hide();
  }
  else
    fl_message("Select a renderer before click the play button!");
  
}

/** Static callback for the \c DriverList double click */
void RainbruRPG::Gui::Launcher::cbDriverList (Fl_Widget*, void*v){
   ( (Launcher*)v )->i_cbDriverList();
}

/** Inline callback for the \c DriverList double click */
void RainbruRPG::Gui::Launcher::i_cbDriverList (){
  LOGI("Click sur DriverList");
  int i=Fl::event_clicks(); 

  if (i!=0)
    this->i_cbPlay();
}

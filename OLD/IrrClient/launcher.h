/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <iostream>

#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Hold_Browser.H>
#include <FL/Fl_Box.H>

#include "launcheroptions.h"

using namespace std;


//using namespace RainbruRPG::Events;

namespace RainbruRPG{
  namespace Gui{

    /** The launcher class of RainbruRPG
      *
      * The launcher is a fltk little window centered in the screen. It
      * lets you choose if you want
      * - play
      * - change options
      * - quit
      *
      * \todo The launcher must keep the options snapshot in a xml
      *       files. So the user can user several config and selecting
      *       one in a combo box.
      *
      */
    class Launcher : public Fl_Window{
    public:
      Launcher();
      ~Launcher();


    private:
      static void cbPlay (Fl_Widget*, void*);
      inline void i_cbPlay ();

      static void cbOpts (Fl_Widget*, void*);
      inline void i_cbOpts ();

      static void cbQuit (Fl_Widget*, void*);
      inline void i_cbQuit ();

      static void cbDriverList (Fl_Widget*, void*);
      inline void i_cbDriverList ();

      void setRenderer();

      /** The dialog opened when we click the options button */
      Options::LauncherOptions *lo;

      /** A fltk Hold Crowser (a list box)
        *
	* It is used to select the graphic rendere (OpenGL, Direct3D...)
	*/
      Fl_Hold_Browser *sbRenderer;
    };
  }
}

#endif // LAUNCHER_H

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

#ifndef LAUNCHER_OPTIONS_H
#define LAUNCHER_OPTIONS_H

#include <FL/Fl.H>
#include <FL/Fl_Window.H>

namespace RainbruRPG {
  namespace Options {

    /** The Launcher's option editor
     *
     * This fltk window is shown when the Options button is clicked.
     * All the game options can be changed in this window.
     */
    class LauncherOptions : public Fl_Window{
    public:
      LauncherOptions( );
      ~LauncherOptions( );

    private:
      static void cbQuit(Fl_Widget*, void*);
      inline void i_cbQuit();

    };
  }
}


#endif // LAUNCHER_OPTIONS_H

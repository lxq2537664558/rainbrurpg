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

/** \file testwindow.h
  * Declares a sample window for test purpose
  *
  * \todo This window seems to be unused in example programs. 
  *
  * Modifications :
  * - 19 sep 2008 : Single file documentation
  *
  */

#ifndef TEST_WINDOW_H
#define TEST_WINDOW_H

#include "window.h"

namespace RainbruRPG{
  namespace Terminal{

    /** A test window for TerminalApp
      *
      * This creates a sample terminalAPI window for
      * in-development test purpose.
      */
    class TestWindow : public Window{

    public:
      TestWindow();
      ~TestWindow();
    };

  }
}


#endif // TEST_WINDOW_H


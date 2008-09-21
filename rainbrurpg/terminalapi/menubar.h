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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file menubar.h
  * Declares a menubar widget
  *
  * Modifications :
  * - 19 sep 2008 : Single file documentation
  *
  */

#ifndef TERMINAL_MENU_BAR
#define TERMINAL_MENU_BAR

#include <list>		
#include <logger.h>

#include "menu.h"

namespace RainbruRPG{
  namespace Terminal{

    /** A STL list of Menu
      *
      * It is used internally by a MenuBar to stores its Menu.
      *
      */
    typedef std::list<Menu*> tMenuList;

    /** The menubar used with the TerminalApp
      *
      * this is a horizontal MenuBar. We can add some Menu classes with
      * the addMenu() method.
      *
      *
      */
    class MenuBar{
    public:
      MenuBar();
      ~MenuBar();

      void addMenu(Menu*);

      tMenuList* getMenuList();
      int getSize();

    private:
      /** The list of Menu
        *
	*/
      tMenuList menuList;
    };
  }
}

#endif // TERMINAL_MENU_BAR

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

/** \file menu.h
  * Declares a menu used in menubars
  *
  * Modifications :
  * - 19 sep 2008 : Single file documentation
  *
  */

#ifndef TERMINAL_MENU
#define TERMINAL_MENU

#include <string>
#include <list>
#include <logger.h>
#include <cstring> // For strlen()

#include "menuitem.h"

using namespace std;

namespace RainbruRPG{
  namespace Terminal{

    /** A STL list of MenuItem
      *
      * It is used internally by a Menu to stores its MenuItem.
      */
    typedef list<MenuItem*> tMenuItemList;


    /** The menu used with the MenuBar class
      *
      * This is a vertical list of MenuItem. We can add some MenuItem
      * classes with the addItem() method.
      *
      * We must know the largestItem of the menu to set the width of
      * the menu window.
      */
    class Menu{
    public:
      Menu();
      Menu(const char*);
      ~Menu();

      void addItem(MenuItem*);

      void setName(const char*);
      const char* getName();
      unsigned int getWidth();
      unsigned int getHeight();
      unsigned int itemCount();

      tMenuItemList* getItemList();

    private:
      /** The caption of the manu */
      const char* name;
      /** The size of the largest menu item */
      int width;
      /** The number of Items */
      int height;

      /** The list of MenuItem
        *
	*/
      tMenuItemList itemList;
    };
  }
}

#endif // TERMINAL_MENU

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
#ifndef TERMINAL_MENU_ITEM
#define TERMINAL_MENU_ITEM

#include <logger.h>

namespace RainbruRPG{
  namespace Terminal{


    /** Defines the type of action you can set to a pushbutton
      *
      * \todo MenuItem should use this system
      *
      */
    typedef enum{
      TAT_NONE, //!< No action was set
      TAT_FUNC, //!< The action is a function pointer
      TAT_OBJT  //!< The action is a function wrapper
    }tActionType;

    /** A function pointer returning an integer value 
      *
      */
    typedef int (*FuncPtr)();

    /** A function pointer returning an integer value 
      *
      */
    typedef int (*ObjFuncPtr)(void*);

    /** The menu item used with the Menu class
      *
      * A menuItem must have a name which ca be passed in the constructor.
      *
      * We must know the largestItem of the menu to set the width of
      * the menu window.
      *
      * The action is set by a call to setAction(FuncPtr) with a
      * function pointer as parameter. The call to fireAction()
      * return -1 if none action has been set.
      *
      * See the setAction(FuncPtr) function for more information.
      */
    class MenuItem{
    public:
      MenuItem();
      MenuItem( const char* );
      ~MenuItem();

      int fireAction();

      void setName(const char*);
      const char* getName();

      void setAction(FuncPtr);

    private:
      /** The text show by the menu item
        *
	* This value can be passed as a parameter in the constructor
	*
	*/
      const char* name;
      /** The function pointer to the action
        *
	*/
      FuncPtr fptr;
      /** true if an action was set, otherwise false */
      bool actionSet;
    };
  }
}

#endif // TERMINAL_MENU_ITEM

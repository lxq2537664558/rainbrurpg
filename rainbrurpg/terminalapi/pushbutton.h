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

/** \file terminalapi/pushbutton.h
  * Declares a push button widget
  *
  * Modifications :
  * - 19 sep 2008 : Single file documentation
  *
  */

#ifndef PUSH_BUTTON_H
#define PUSH_BUTTON_H

#include <slang.h>
#include <logger.h>

#include "widget.h"
#include "caption.h"
#include "menuitem.h" // for the function pointer

namespace RainbruRPG{
  namespace Terminal{

    /** The push button Widget
      *
      * A push button can fire an action when we hit the Return key
      * when focused.
      *
      * There is two ways for setting an action:
      * - A function pointer : see \ref setAction().
      * - A member functionwrapper : see \ref setObjectAction().
      *
      */
    class PushButton : public Widget{
    public:
      PushButton();
      PushButton( const string& );
      PushButton( const string&, int, int );

      virtual ~PushButton();

      void setText( const string& );
      const string& getText()const;

      virtual void draw( int x, int y );
      virtual void receiveKeyEvent(int);

      void setAction(FuncPtr);
      void setObjectAction(void*, ObjFuncPtr);

      int fireAction();


    private:
      /** The caption used to center the text
        *
	*/
      Caption* caption;

      /** The function pointer to the action when using a flobal function
        *
	*/
      FuncPtr fptr;

      /** The function pointer when using a static member wrapper */
      ObjFuncPtr ofptr;

      /** The object pointer when using a static member wrapper */
      void* mObjectAction;

      /** The type of action */
      tActionType actionSet;

    };
  }
}

#endif // PUSH_BUTTON_H

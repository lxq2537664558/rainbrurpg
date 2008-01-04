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
      */
    class PushButton : public Widget{
    public:
      PushButton();
      PushButton( const char* );
      PushButton( const char*, int, int );

      virtual ~PushButton();

      void setText( const char* );
      const char* getText();

      virtual void draw( int x, int y );
      virtual void receiveKeyEvent(int);

      void setAction(FuncPtr);
      int fireAction();


    private:
      /** The caption used to center the text
        *
	*/
      Caption* caption;

      /** The function pointer to the action
        *
	*/
      FuncPtr fptr;

      /** true if an action was set, otherwise false */
      bool actionSet;

    };
  }
}

#endif // PUSH_BUTTON_H

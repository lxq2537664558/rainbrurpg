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
#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include <slang.h>
#include <string>

#include "widget.h"

using namespace std;

namespace RainbruRPG{
  namespace Terminal{

    /** The simpliest input widget
      *
      * The lineedit provide a input in a single line.
      *
      * The width of the widget do not affect the maximum number of
      * character that can be entered.
      */
    class LineEdit : public Widget{
    public:
      LineEdit();
      LineEdit( const char* );
      LineEdit( const char*, int, int );

      virtual ~LineEdit();

      void setText( const char* );
      const char* getText();

      virtual void draw( int x, int y );
      virtual void receiveKeyEvent(int);

    private:

      void addChar(int);
      void moveLeft();
      void moveRight();
      void moveUp();
      void moveDown();
      void hitSuppr();
      void hitBackspace();

      /** The text of the lineedit */
      string text;
      /** Represents the position of the cursor in the text
        *
	*
	*/
      int cursorPosition;

    };
  }
}

#endif // LINE_EDIT_H

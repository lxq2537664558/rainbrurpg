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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file terminalapi/dialog.h
  * Declares a base class of all dialogs
  *
  * Modifications :
  * - 06 sep 2008 : Single file documentation
  *
  */

#ifndef DIALOG_H
#define DIALOG_H

#include <slang.h>
#include <string>

#include "caption.h"
#include "pushbutton.h"

namespace RainbruRPG{
  namespace Terminal{

    /** The base class of all dialogs
      *
      * This class can not be instancied. You must use InfoDialog and
      * others subclass or make your own subclass.
      *
      * A dialog can have up to 3 buttons. It can show a title and a
      * message. 
      */
    class Dialog{
    public:
      Dialog( int, int );
      virtual ~Dialog();
      /** The pure virtual draw method
        *
	* This method must be subclassed. To draw a standard dialog,
	*it must call the drawDialog() protected method.
	*/
      virtual void draw()=0;

      void setTitle( std::string );
      void setMessage( std::string );

      const char* getTitle();
      const char* getMessage();

      void addButton( PushButton* );

      void receiveKeyEvent(int);

      void show(void);
      void hide(void);

      static int hide_wrapper(void*);

    protected:
      void drawDialog();

    private:

      void drawEmpty();
      void drawBorder();
      void drawShadow();
      void drawTitle();
      void drawCaption();
      void drawButtons();

      void center( int, int );

      /** The x coordonate of the Dialog
        *
	*/
      int xPos;
      /** The y coordonate of the Dialog
        *
	*/
      int yPos;

      /** The width of the Dialog
        *
	*/
      int width;
      /** The height of the Dialog
        *
	*/
      int height;

      /** The number of buttons that have been added to this Dialog
        *
	*/
      int nbButton;

      /** The title of the Dialog
        *
	*/
      string title;
      /** The caption (message of the Dialog
        *
	*/
      Caption* caption;

      /** The first button of the Dialog
        *
	*/
      PushButton* btn1;
      /** The second button of the Dialog
        *
	*/
      PushButton* btn2;
      /** The third button of the Dialog
        *
	*/
      PushButton* btn3;

      /** Is the dialog drawn ? */
      bool visible;
    };

  }
}
#endif // DIALOG_H

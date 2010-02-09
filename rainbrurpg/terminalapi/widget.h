/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file terminalapi/widget.h
  * Declares the base class of all widgets
  *
  * Modifications :
  * - 19 sep 2008 : Single file documentation
  *
  */

#ifndef WIDGET_H
#define WIDGET_H

namespace RainbruRPG{
  namespace Terminal{

    /** The base class of all widgets
      *
      */
    class Widget{
    public:
      Widget();
      virtual ~Widget();

      void setPosition( int, int );
      void setSize( int, int );

      void setX( int );
      void setY( int );
      void setWidth( int );
      void setHeight( int );
      void setFocus( bool );

      int getX();
      int getY();
      int getWidth();
      int getHeight();
      bool getFocus();

      bool canHaveFocus();
       /** The pure virtual draw method
        *
	* Every widget must subclass this method to be able to draw
	* itself. The Layout call it for every widget.
	*
	* The parameters tells the widget the position of the Window
	* wich contains the widget. They are set by the Layout::Draw()
	* with the Layout::setOrigin( int, int ) method parameters.
	*
	* \param x The position of the window 
	* \param y The position of the window 
	*/      
      virtual void draw( int x, int y )=0;
      /** Receive the key event from the TerminalApp singleton
        *
	*/
      virtual void receiveKeyEvent(int)=0;
    protected:
      /** This boolean is used to know if the widget can have the
        * focus
	*
	* We can access this value with the canHaveFocus() function.
	*
	* All the subclass of Widget must set this property to \c true
	* or \c false. Typically, a Label can not have the focus,
	* otherwise, a ListBox or a LineEdit must be able to have the focus.
	*
	*/
      bool canTakeFocus;

      /** Set to \c true if this widget has the focus
        *
	*/
      bool hasFocus;

      /** The x coordonate of the widget
        *
	* This value is relative to the window top-left corner and
	* cannot be inferior to 0.
	*/
      int x;

      /** The y coordonate of the widget
        *
	* This value is relative to the window top-left corner and
	* cannot be inferior to 0.
	*/
      int y;

      /** The width of the widget
        *
	* This value cannot be inferior to 1.
	*/
      int width;

      /** The height of the widget
        *
	* This value cannot be inferior to 1.
	*/
      int height;
    };

  }
}

#endif // WIDGET_H

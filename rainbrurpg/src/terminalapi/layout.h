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

/** \file layout.h
  * Declares the base class of all layouts
  *
  * Modifications :
  * - 18 sep 2008 : Single file documentation
  *
  */

#ifndef LAYOUT_H
#define LAYOUT_H

#include <list>

#include "widget.h"

namespace RainbruRPG{
  namespace Terminal{

    /** The STL list of widget 
      *
      * It is used internally by the Layout to store its added Widget.
      */
    typedef std::list<Widget*> tWidgetList;

    /** The base class of all the layout
      *
      * Un layout contains a widget list AND another list wich can be
      * use like it want. it is a numeric values list. This second
      * list can not be defined here. It must be defined in the
      * Layout's subclass. 
      *
      * In order to draw properly the widgets, we must know the window
      * position. xOrigin and yOrigin are set with the setOrigin( int,
      * int ) method and are passed as paramater of the Widget::draw(
      * int, int ).
      *
      * The addWidget(Widget*, ...) function can have some parameter,
      * according to the layout type.
      */
    class Layout{
    public:
      Layout();
      virtual ~Layout();

      void addWidget( Widget* );

      virtual void addWidget( Widget* , int, int );
      virtual void addWidget( Widget* , int, int , int, int);

      void draw();
      void setOrigin( int, int );
      void setXOrigin( int );
      void setYOrigin( int );

      int getXOrigin();
      int getYOrigin();

      void getFirstFocus();
      void getNextFocus();

      Widget* getFocusedWidget();

    private:
      void currentWidgetLostFocus();

      /** The STL list of Widget
        *
	*/
      tWidgetList widgetList;

      /** The currently focused Widget
        *
	* This pointer stores the Widget currently focused to be able
	* to turn off its focus status.
	*/
      Widget* focusedWidget;

      /** The X coordonate of the window */
      int xOrigin;
      /** The Y coordonate of the window */
      int yOrigin;

      /** The focused widget index in the widgetList
        *
	* This value is used to know where to start the iteration of
	* the widgetList.
	*
	*/
      int focusedWidgetIndex;
    };

  }
}

#endif // LAYOUT_H

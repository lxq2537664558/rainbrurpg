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

/** \file layout.cpp
  * Implements the base class of all layouts
  *
  */

#include "layout.h"

/** The default constructor
  *
  */
RainbruRPG::Terminal::Layout::Layout():
  xOrigin(0),
  yOrigin(0),
  focusedWidget(NULL)
{

}

/** The default destructor
  *
  */
RainbruRPG::Terminal::Layout::~Layout(){
  focusedWidget==NULL;
}

/** The simplest method to add a widget
  *
  * It simply pushback the widget in the widgetList.
  *
  * \param w the widget to be added.
  */
void RainbruRPG::Terminal::Layout::addWidget( Widget* w ){
  widgetList.push_back( w );
}

/** Call the draw method of all the previously added widget
  *
  */
void RainbruRPG::Terminal::Layout::draw(){
  // Get the right menuItem instance
  tWidgetList::const_iterator iter;

  // Iterate through list and draw all widgets
  for (iter=widgetList.begin(); iter != widgetList.end(); iter++)  {
    (*iter)->draw( xOrigin, yOrigin );
  }

  // Draw the focused widget to provides cursor positionning
  if (focusedWidget)
    focusedWidget->draw( xOrigin, yOrigin );
}

/** Add the widget and set its x and y properties
  *
  * It simply calls the Layout::addWidget(Widget*), the
  * Widget::setX(int) and the Widget::setY(int) functions.
  *
  * \param w the widget to add
  * \param x the x coordonate to set to the widget
  * \param y the y coordonate to set to the widget
  */
void RainbruRPG::Terminal::Layout::addWidget( Widget* w, int x, int y ){
  w->setX( x );
  w->setY( y );
  this->addWidget( w );
}

/** Add the widget and set its x and y properties
  *
  * It simply calls the Layout::addWidget(Widget*), the
  * Widget::setX(int) ,the Widget::setY(int) the
  * Widget::setWidth(int) and the Widget::setHeight(int) functions.
  *
  * \param w the widget to add
  * \param x the x coordonate to set to the widget
  * \param y the y coordonate to set to the widget
  * \param width the width to set to the widget
  * \param height the height coordonate to set to the widget
  */
void RainbruRPG::Terminal::Layout::addWidget( Widget* w, int x, int y, 
					      int width, int height){
  w->setX( x );
  w->setY( y );
  w->setWidth( width );
  w->setHeight( height );
  this->addWidget( w );
}

/** Set the origin of the window
  *
  * \param x the origin of the window
  * \param y the origin of the window
  */
void RainbruRPG::Terminal::Layout::setOrigin( int x, int y){
  setXOrigin( x );
  setYOrigin( y );
}

/** Set the origin of the window
  *
  * \param x the origin of the window
  */
void RainbruRPG::Terminal::Layout::setXOrigin( int x ){
   this->xOrigin=x;
}

/** Set the origin of the window
  *
  * \param y the origin of the window
  */
void RainbruRPG::Terminal::Layout::setYOrigin( int y ){
   this->yOrigin=y;
}

/** Set the focus to the first Widget that can have it
  *
  * It tuns through the widgetList and set the first Widget that can
  * be focused (according to the Widget::canTakeFocus property).
  *
  */
void RainbruRPG::Terminal::Layout::getFirstFocus(){
  tWidgetList::const_iterator iter;

  int ind=1;
  bool found=false;

  // If a widget is already focused, set it to false
  //  currentWidgetLostFocus();

  // Iterate through list and set the focus to the first focusable Widget
  for (iter=widgetList.begin(); iter != widgetList.end(); iter++)  {
    if ( (*iter)->canHaveFocus() ){
      focusedWidgetIndex=ind;
      focusedWidget=(*iter);
      focusedWidget->setFocus(true);
      found = true;
      break;
    }
    ind++;
  }

  if (!found){
    focusedWidget=NULL;
  }
}

/** The next widget to have the focus
  *
  * It iterates through the widgetList and set the focus to the next
  * focusable widget.
  */
void RainbruRPG::Terminal::Layout::getNextFocus(){
  tWidgetList::const_iterator iter;

  int ind=1;
  bool found=false;

  // If a widget is already focused, set it to false
  currentWidgetLostFocus();

  // Iterate through list and set the focus to the first focusable Widget
  for (iter=widgetList.begin(); iter != widgetList.end(); iter++)  {
    if ( (*iter)->canHaveFocus() & ind>focusedWidgetIndex & found==false){
      focusedWidgetIndex=ind;
      focusedWidget=(*iter);
      focusedWidget->setFocus(true);
      found=true;
      break;
    }
    ind++;
  }

  // We have not found any other focusable Widget
  if (!found){
    currentWidgetLostFocus();
    getFirstFocus();
  }
}

/** Set the current focused widget to has not the focus
  * 
  * It calls the current focused widget's setFocus method with \c
  * false as parameter
  */
void RainbruRPG::Terminal::Layout::currentWidgetLostFocus(){
  if (focusedWidget!=NULL){
    focusedWidget->setFocus(false);
  }
}

/** Returns the current focused widget
  *
  * \return A pointer to the current focused widget
  */
RainbruRPG::Terminal::Widget* 
RainbruRPG::Terminal::Layout::getFocusedWidget(){
  return focusedWidget;
}

/** Returns the origin of the layout
  *
  * \return The x origin of the Layout
  */
int RainbruRPG::Terminal::Layout::getXOrigin(){
  return  xOrigin;
}

/** Returns the origin of the layout
  *
  * \return The y origin of the Layout
  */
int RainbruRPG::Terminal::Layout::getYOrigin(){
  return  yOrigin;
}

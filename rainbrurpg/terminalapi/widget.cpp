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

/** \file terminalapi/widget.cpp
  * Implements the base class of all widgets
  *
  */

#include "widget.h"

/** Default constructor
  *
  */
RainbruRPG::Terminal::Widget::Widget(){
  canTakeFocus=false;
}

/** The default destructor
  *
  */
RainbruRPG::Terminal::Widget::~Widget(){

}

/** Move the window to new coordonates
  *
  * \param x the new x value
  * \param y the new y value
  */
void RainbruRPG::Terminal::Widget::setPosition( int x, int y ){
  this->setX( x );
  this->setY( y );
}

/** Resize the window
  *
  * \param w the new width value
  * \param h the new height value
  */
void RainbruRPG::Terminal::Widget::setSize( int w, int h ){
  this->setWidth( w );
  this->setHeight( h );
}

/** Set the X coordonate
  *
  * \param i the new value
  */
void RainbruRPG::Terminal::Widget::setX( int i ){
  this->x=i;

  if (this->x<0)
    this->x=0;
}

/** Set the Y coordonate
  *
  * \param i the new value
  */
void RainbruRPG::Terminal::Widget::setY( int i ){
  this->y=i;

  if (this->y<0)
    this->y=0;
}

/** Set the width of the window
  *
  * \param w the new value
  */
void RainbruRPG::Terminal::Widget::setWidth( int w ){
  this->width=w;

  if (this->width<1)
    this->width=1;
}

/** Set the height of the window
  *
  * \param h the new value
  */
void RainbruRPG::Terminal::Widget::setHeight( int h ){
  this->height=h;

  if (this->height<1)
    this->height=1;
}

/** Get the x coordonate of the widget
  *
  * \return the x coordonate
  */
int RainbruRPG::Terminal::Widget::getX(){
  return this->x;
}

/** Get the y coordonate of the widget
  *
  * \return the y coordonate
  */
int RainbruRPG::Terminal::Widget::getY(){
  return this->y;
}

/** Get the width of the widget
  *
  * \return the width of the widget
  */
int RainbruRPG::Terminal::Widget::getWidth(){
  return this->width;
}

/** Get the height of the widget
  *
  * \return the height of the widget
  */
int RainbruRPG::Terminal::Widget::getHeight(){
  return this->height;
}

/** Get the canTakeFocus value
  *
  * 
  */
bool RainbruRPG::Terminal::Widget::canHaveFocus(){
  return this->canTakeFocus;
}

/** Set the focus to the Widget
  *
  * If set the parameter's value to hasFocus.
  *
  * \param b the new focus status
  */
void RainbruRPG::Terminal::Widget::setFocus( bool b ){
  this->hasFocus=b;
}

/** Get the focus status of the Widget
  *
  * \return the value of hasFocus.
  *
  */
bool RainbruRPG::Terminal::Widget::getFocus(){
  return this->hasFocus;
}

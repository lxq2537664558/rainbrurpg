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

/** \file terminalapi/window.cpp
  * Implements a window for terminalapi
  *
  */

#include "window.h"

/** The default constructor
  *
  */
RainbruRPG::Terminal::Window::Window(){
  this->caption="";
  this->selected=false;
  focusWindow=false;
  this->state=NORMAL;

  layout=new FreeLayout();
  layout->setOrigin( x, y );

  this->setX( 3 );
  this->setY( 3 );
  this->setHeight( 10 );
  this->setWidth( 30 );

  panel=new ScrollingPanel();
}

/** The named constructor
  *
  * The window is created with a noarmel state, it is unselected.
  * It initialize the ScrollingPanel and create a default FreeLayout.
  *
  */
RainbruRPG::Terminal::Window::Window( const char* c){
  this->caption=c;
  this->selected=false;
  focusWindow=false;
  this->state=NORMAL;

  layout=new FreeLayout();
  layout->setOrigin( x, y );

  this->setX( 3 );
  this->setY( 3 );
  this->setHeight( 10 );
  this->setWidth( 30 );

  panel=new ScrollingPanel();
}

/** The default destructor
  *
  */
RainbruRPG::Terminal::Window::~Window(){
  delete panel;
  panel=NULL;

  delete layout;
  layout=NULL;
}

/** Set the caption (the title) of the window
  *
  * \param c the new caption
  */
void RainbruRPG::Terminal::Window::setCaption( const char* c ){
  this->caption=c;
}

/** Set the X coordonate
  *
  * \param i the new value
  */
void RainbruRPG::Terminal::Window::setX( int i ){
  this->x=i;
  layout->setXOrigin( i );

}

/** Set the Y coordonate
  *
  * \param i the new value
  */
void RainbruRPG::Terminal::Window::setY( int i ){
  this->y=i;
  layout->setYOrigin( i );

}

/** Set the width of the window
  *
  * \param i the new value
  */
void RainbruRPG::Terminal::Window::setWidth( int i ){
  this->width=i;
}

/** Set the height of the window
  *
  * \param i the new value
  */
void RainbruRPG::Terminal::Window::setHeight( int i ){
  this->height=i;
}

/** Move the window to new coordonates
  *
  * \param x the new x value
  * \param y the new y value
  */
void RainbruRPG::Terminal::Window::move( int x , int y ){
  this->setX( x );
  this->setY( y );
}

/** Resize the window
  *
  * \param w the new width value
  * \param h the new height value
  */
void RainbruRPG::Terminal::Window::resize( int w , int h ){
  this->setWidth( w );
  this->setHeight( h );
}

/** Get the title of the window
  *
  * \return the current window's caption. 
  *
  */
const char* RainbruRPG::Terminal::Window::getCaption( ){
  return this->caption;
}

/** Get the X coordonate of the window
  *
  * \return the current window's x coordonate. 
  *
  */
int RainbruRPG::Terminal::Window::getX( ){
  return this->x;
}

/** Get the Y coordonate of the window
  *
  * \return the current window's y coordonate. 
  *
  */
int RainbruRPG::Terminal::Window::getY( ){
  return this->y;
}

/** Get the width of the window
  *
  * \return the current window's width. 
  *
  */
int RainbruRPG::Terminal::Window::getWidth( ){
  return this->width;
}

/** Get the height of the window
  *
  * \return the current window's height. 
  *
  */
int RainbruRPG::Terminal::Window::getHeight( ){
  return this->height;
}

/** Create graphically the window
  *
  * It draws the box according to the window stateand call the
  * layout's draw() method.
  *
  * It finally the Layout::draw() method.
  */
void RainbruRPG::Terminal::Window::draw( ){
  int x, y, h, w;

  if (state==NORMAL){
    x=this->x;
    y=this->y;
    h=this->height;
    w=this->width;
  }
  else if(state==MAXIMIZED){
    x=0;
    y=1;
    h=SLtt_Screen_Rows-2;
    w=SLtt_Screen_Cols;
  }

  if (focusWindow&&selected){
    SLsmg_set_color (6);
  }

  // Border
  SLsmg_draw_box ( y, x, h, w );

  // Title
  SLsmg_gotorc ( y, x+2);
  SLsmg_set_char_set (1);
  SLsmg_write_char( SLSMG_RTEE_CHAR );
  SLsmg_set_char_set (0);

  // cast to char* to avoid deprecated converion warning
  SLsmg_printf( (char*)" %s ", caption );
  SLsmg_set_char_set (1);
  SLsmg_write_char( SLSMG_LTEE_CHAR );
  SLsmg_set_char_set (0);

  SLsmg_set_color (0);

  layout->draw();
};

/** return the visible field of the window
  *
  * \return true if the window is visible, otherwise false.
  */
bool RainbruRPG::Terminal::Window::isVisible(){
  if (state!=HIDDEN)
    return true;
  else
    return false;
}

/** Call the show method if true 
  *
  * \param b true to make the window visible, otherwise, hide it.
  */
void RainbruRPG::Terminal::Window::setVisible( bool b ){
  if (b)
    this->show();
  else
    this->hide();
}

/** Set the visible field to true
  *
  * If the window was hidden, it restores the laste state.
  */
void RainbruRPG::Terminal::Window::show(){
  if (state==HIDDEN)
    this->state=lastState;
}

/** Set the window state to HIDDEN
  *
  */
void RainbruRPG::Terminal::Window::hide(){
  this->setState(HIDDEN);
}

/** Set the window state to a given state
  *
  * If s=HIDDEN, it stores the last state.
  *
  * \param s the new window state
  */
void RainbruRPG::Terminal::Window::setState(tWindowState s){
  if (s==HIDDEN){
    lastState=state;
  }
  state=s;
}

/** Set the selected value
  *
  * If b is \c true, it calls Layout::getFirstFocus()
  *
  * \param b the new selected value
  */
void RainbruRPG::Terminal::Window::setSelected( bool b ){
  this->selected= b;
  if (b){
    this->layout->getFirstFocus();
  }
}

/** Get the current Window's layout
  *
  * \return The terminal Layout
  */
RainbruRPG::Terminal::Layout* 
RainbruRPG::Terminal::Window::getLayout(){
  return this->layout;
}

/** Is the Window selected
  *
  * \return the selected value
  */
bool RainbruRPG::Terminal::Window::isSelected(){
  return this->selected;
}

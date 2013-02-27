/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file lineedit.cpp
  * Implements a simple line input widget
  *
  */

#include "lineedit.h"

#include "logger.h"
#include "terminalapp.h"

/** The default constructor
  *
  * It initialize the caption to an empty string. x and y are set to 0.
  *
  */
RainbruRPG::Terminal::LineEdit::LineEdit(){
  this->text="";
  this->setX( 0 );
  this->setY( 0 );
  this->canTakeFocus=true;
  cursorPosition=0;
}

/** The named constructor
  *
  * It initialize the caption to c. x and y are set to 0.
  *
  * \param c the caption of the label
  */
RainbruRPG::Terminal::LineEdit::LineEdit( const string& c ){
  this->text=c;
  this->setX( 0 );
  this->setY( 0 );
  this->canTakeFocus=true;
  cursorPosition=0;
}

/** The named and positionned constructor
  *
  * It initialize the caption to c and x and y to the correspondng
  * parameters.
  *
  * \param c the caption of the label
  * \param x the x coordonate of the label
  * \param y the y coordonate of the label
  */
RainbruRPG::Terminal::LineEdit::LineEdit( const string& c, int x, int y ){
  this->text=c;
  this->setX( x );
  this->setY( y );
  this->canTakeFocus=true;
  cursorPosition=0;
}

/** The default destructor
  *
  */
RainbruRPG::Terminal::LineEdit::~LineEdit(){

}

/** Change the caption to c
  *
  * \param c the new caption of the label
  */
void RainbruRPG::Terminal::LineEdit::setText( const string& c ){
  this->text=c;
}

/** Get the caption of the label
  *
  * \return the caption of the label
  *
  */
const string& RainbruRPG::Terminal::LineEdit::getText()const{
  return this->text;
}

void RainbruRPG::Terminal::LineEdit::draw( int x, int y ){
  int tempX=0;

  int xw=(x+this->x)-2;
  int yw=(y+this->y)-1;

  SLsmg_gotorc (yw, xw);

  if (this->hasFocus)
    SLsmg_set_color (6);
  else
    SLsmg_set_color (0);


  for (int i=1; i<width; i++){
    SLsmg_gotorc (yw, xw+tempX);
    // cast to char* to avoid deprecating conversion warning
    SLsmg_printf( (char*)"_" );

    tempX++;
  }

  SLsmg_gotorc (yw, xw);
  // cast to char* to avoid deprecating conversion warning
  SLsmg_printf( (char*)"%s", this->text.c_str() );

  SLsmg_set_color (0);
  //  SLsmg_gotorc ((y+this->y)-1, ((x+this->x)-2)+cursorPosition);
  SLsmg_gotorc (yw, xw+cursorPosition);

}

/** The keycode receiver
  *
  * \param ch the keycode received
  */
void RainbruRPG::Terminal::LineEdit::receiveKeyEvent(int ch){
  // a letter
  if (ch>64 && ch<123)
    addChar(ch);
  // a number
  if (ch>47 && ch<58)
    addChar(ch);
  // the space bar
  if (ch==32)
    addChar(ch);

  if (ch==1)
    moveUp();

  if (ch==2)
    moveDown();

  if (ch==3)
    moveLeft();

  if (ch==4)
    moveRight();

  if (ch==19)
    hitSuppr();

  if (ch==16)
    hitBackspace();

}

/** Adds a char to the caption
  *
  *
  */
void RainbruRPG::Terminal::LineEdit::addChar(int ch){
  char c=ch;
  string tmp;
  tmp=c;
  this->text.insert( cursorPosition, tmp );
  cursorPosition++;
}

/** The left arrow key action
  *
  */
void RainbruRPG::Terminal::LineEdit::moveLeft(){
  cursorPosition--;
  if (cursorPosition<0)
    cursorPosition=0;
}

/** The right arrow key action
  *
  */
void RainbruRPG::Terminal::LineEdit::moveRight(){
  cursorPosition++;
  if (cursorPosition > (text.length()))
    cursorPosition=(text.length());
}

/** The up arrow key action
  *
  */
void RainbruRPG::Terminal::LineEdit::moveUp(){
    cursorPosition=0;
}

/** The down arrow key action
  *
  */
void RainbruRPG::Terminal::LineEdit::moveDown(){
    cursorPosition=(text.length());
}

/** The suppr key action
  *
  */
void RainbruRPG::Terminal::LineEdit::hitSuppr(){
  string tmp1, tmp2;

  tmp1= text.substr( 0, cursorPosition );
  tmp2= text.substr(cursorPosition+1, text.length()-cursorPosition-1);
  tmp1+= tmp2;
  this->text= tmp1;
}

/** The backspace key action
  *
  */
void RainbruRPG::Terminal::LineEdit::hitBackspace(){
  string tmp1, tmp2;

  tmp1= text.substr( 0, cursorPosition-1 );
  tmp2= text.substr(cursorPosition, text.length()-cursorPosition);
  tmp1+= tmp2;
  this->text= tmp1;

  moveLeft();
}

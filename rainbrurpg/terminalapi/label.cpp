/*
 *  Copyright 2006 Jerome PASQUIER
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
#include "label.h"

#include <logger.h>

/** The default constructor
  *
  * It initialize the caption to an empty string. x and y are set to 0.
  *
  */
RainbruRPG::Terminal::Label::Label(){
  this->caption="";
  this->setX( 0 );
  this->setY( 0 );
  this->canTakeFocus=false;
}

/** The named constructor
  *
  * It initialize the caption to c. x and y are set to 0.
  *
  * \param c the caption of the label
  */
RainbruRPG::Terminal::Label::Label( char* c ){
  this->caption=c;
  this->setX( 0 );
  this->setY( 0 );
  this->canTakeFocus=false;
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
RainbruRPG::Terminal::Label::Label( char* c, int x, int y ){
  this->caption=c;
  this->setX( x );
  this->setY( y );
  this->canTakeFocus=false;
}

/** The default destructor
  *
  */
RainbruRPG::Terminal::Label::~Label(){

}

/** Change the caption to c
  *
  * \param c the new caption of the label
  */
void RainbruRPG::Terminal::Label::setText( char* c ){
  this->caption=c;
}

/** Get the caption of the label
  *
  * \return the caption of the label
  *
  */
char* RainbruRPG::Terminal::Label::getText(){
  return this->caption;
}

void RainbruRPG::Terminal::Label::draw( int x, int y ){
  SLsmg_gotorc ((y+this->y)-1, (x+this->x)-2);
  SLsmg_printf( "%s", this->caption );
}

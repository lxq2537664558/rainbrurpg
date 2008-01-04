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
#include "pushbutton.h"

#include "terminalapp.h"

/** The default constructor
  *
  * It initialize the caption to an empty string. x and y are set to 0.
  *
  */
RainbruRPG::Terminal::PushButton::PushButton(){
  actionSet=false;
  this->setX( 0 );
  this->setY( 0 );
  this->canTakeFocus=true;
  caption=new Caption( H_CENTERED, "", 0, 0, this->width, this->height );

}

/** The named constructor
  *
  * It initialize the caption to c. x and y are set to 0.
  *
  * \param c the caption of the PushButton
  */
RainbruRPG::Terminal::PushButton::PushButton( const char* c ){
  actionSet=false;
  this->setX( 0 );
  this->setY( 0 );
  this->canTakeFocus=true;

  caption=new Caption( H_CENTERED, c, 0, 0, this->width, this->height );
}

/** The named and positionned constructor
  *
  * It initialize the caption to c and x and y to the correspondng
  * parameters.
  *
  * \param c the caption of the label
  * \param x the x coordonate of the PushButton
  * \param y the y coordonate of the PushButton
  */
RainbruRPG::Terminal::PushButton::PushButton( const char* c, int x, int y ){
  actionSet=false;
  this->setX( x );
  this->setY( y );
  this->setY( y );
  this->canTakeFocus=true;
  caption=new Caption( H_CENTERED, c, x, y, this->width, this->height );
}

/** The default destructor
  *
  */
RainbruRPG::Terminal::PushButton::~PushButton(){

}

/** Change the caption to c
  *
  * \param c the new caption of the PushButton
  */
void RainbruRPG::Terminal::PushButton::setText( const char* c ){
  this->caption->setText( c );
}

/** Get the caption of the PushButton
  *
  * \return the caption of the label
  *
  */
const char* RainbruRPG::Terminal::PushButton::getText(){
  return this->caption->getText().c_str();
}

void RainbruRPG::Terminal::PushButton::draw( int x, int y ){
  int xw=(x+this->x)-2;
  int yw=(y+this->y)-1;


  if (hasFocus){
    SLsmg_set_color (1);
    SLsmg_gotorc (yw, xw);
    for (int i=0; i< this->width; i++)
      SLsmg_printf( " " );
  }

  caption->setXPos( xw );
  caption->setYPos( yw );
  caption->setWidth( this->width );
  caption->setHeight( this->height );

  SLsmg_gotorc (yw, xw);
  SLsmg_printf( "<" );
  SLsmg_gotorc (yw, xw+this->width);
  SLsmg_printf( ">" );

  caption->draw();

  SLsmg_set_color (0);
}

void RainbruRPG::Terminal::PushButton::receiveKeyEvent(int ch){

  if (ch==13){ //Enter
    int a=fireAction();
    if (a==-1)
      TerminalApp::getSingleton().showMessage( "This PushButton has no action set."); 
  }
}

/** Fire the action
  *
  * Return -1 if none action has been set, otherwise return the value
  * of the pointed function.
  */ 
int RainbruRPG::Terminal::PushButton::fireAction(){
  if (actionSet){
    int ret=(*(fptr))();
    return ret;
  }
  else{
    return -1;
  }
}

/** Set the action of the menu
  *
  * A typical use of this method :
  *
  * First step is to declare and implement a C fuction that return a
  * result different of -1. The -1 is reserved for menu that has not
  * an action defined
  *
  * <pre>
  * int item1Action(){
  *   // Your code here
  *   return 1; 
  * }
  * </pre>
  *
  * The last step is to set a pointer to this function as parameter of
  * thr setAction method. When this menuItem will be selected, it will
  * call this function.
  *
  * <pre>
  * MenuItem* it1=new MenuItem("&Identification");
  * it1->setAction(&item1Action);
  * </pre>
  *
  * \param a the function pointer
  */
void RainbruRPG::Terminal::PushButton::setAction(FuncPtr a){
  actionSet=true;
  this->fptr=a;
}

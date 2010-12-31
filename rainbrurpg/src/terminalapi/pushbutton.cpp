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

/** \file terminalapi/pushbutton.cpp
  * Implements a push button widget
  *
  */

#include "pushbutton.h"

#include "terminalapp.h"

/** The default constructor
  *
  * It initialize the caption to an empty string. x and y are set to 0.
  *
  */
RainbruRPG::Terminal::PushButton::PushButton():
  mObjectAction(NULL)
{
  actionSet=TAT_NONE;
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
RainbruRPG::Terminal::PushButton::PushButton( const string& c ):
  mObjectAction(NULL)
{
  actionSet=TAT_NONE;
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
RainbruRPG::Terminal::PushButton::PushButton( const string& c, int x, int y ):
  mObjectAction(NULL)
{
  actionSet=TAT_NONE;
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
void RainbruRPG::Terminal::PushButton::setText( const string& c ){
  this->caption->setText( c );
}

/** Get the caption of the PushButton
  *
  * \return the caption of the label
  *
  */
const string& RainbruRPG::Terminal::PushButton::getText()const{
  return this->caption->getText();
}

void RainbruRPG::Terminal::PushButton::draw( int x, int y ){
  int xw=(x+this->x)-2;
  int yw=(y+this->y)-1;


  if (hasFocus){
    SLsmg_set_color (1);
    SLsmg_gotorc (yw, xw);
    for (int i=0; i< this->width; i++)
      // cast to char* to avoid deprecating conversion warning
      SLsmg_printf( (char*)" " );
  }

  caption->setXPos( xw );
  caption->setYPos( yw );
  caption->setWidth( this->width );
  caption->setHeight( this->height );

  SLsmg_gotorc (yw, xw);
  // cast to char* to avoid deprecating conversion warning
  SLsmg_printf( (char*)"<" );
  SLsmg_gotorc (yw, xw+this->width);
  // cast to char* to avoid deprecating conversion warning
  SLsmg_printf( (char*)">" );

  caption->draw();

  SLsmg_set_color (0);
}

void RainbruRPG::Terminal::PushButton::receiveKeyEvent(int ch){

  if (ch==13){ //Enter
    int a=fireAction();
    if (a==-1)
      TerminalApp::getSingleton()
	.showMessage( "This PushButton has no action set."); 
  }
}

/** Fire the action
  *
  * Return -1 if none action has been set, otherwise return the value
  * of the pointed function.
  *
  */ 
int RainbruRPG::Terminal::PushButton::fireAction(){
  if (actionSet==TAT_FUNC){
    int ret=(*(fptr))();
    return ret;
  }
  else if (actionSet==TAT_OBJT){
    int ret=(*(ofptr))(mObjectAction);
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
  actionSet=TAT_FUNC;
  this->fptr=a;
}

/** Sets a wrapper as action
  *
  * A wrapper is a static member that take an object as parameter. Here
  * is an example of implementation :
  *
  * If you have a member function called hide(void) in a class called Foo, 
  * a possible wrapper 
  * could be :
  *
  * Declaration :
  * <pre>
  * class Foo{
  * public:
  *   void hide(void);
  *   static int hide_wrapper(void*);
  * ];
  * </pre>
  *
  * Implementation :
  * <pre>
  * int Foo::hide_wrapper(void* vObject){
  *   Dialog* dial = static_cast<Dialog*>(vObject);
  *   if (dial){
  *     dial->hide();
  *     return 0;
  *   }
  *   else{
  *     LOGW("Cannot call hide() from its wrapper. Object's pointer is NULL");
  *     return 1;
  *   }
  * }
  * </pre>
  *
  * Usage (to be placed in Foo):
  * <pre>
  * PushButton* btnOk=new PushButton("Ok");
  * btnOk->setObjectAction(this, &Foo::hide_wrapper);
  * </pre>
  *
  * \param vObj The Object to pass to the function wrapper
  * \param vPtr The function wrapper
  *
  */
void RainbruRPG::Terminal::PushButton::
setObjectAction(void* vObj, ObjFuncPtr vPtr){
  actionSet=TAT_OBJT;
  mObjectAction = vObj;
  this->ofptr=vPtr;
}

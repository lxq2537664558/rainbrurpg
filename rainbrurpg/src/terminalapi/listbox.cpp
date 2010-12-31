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

/** \file listbox.cpp
  * Implements a list box widget
  *
  */

#include "listbox.h"

/** The default constructor
  *
  * It initialize the caption to an empty string. x and y are set to 0.
  *
  */
RainbruRPG::Terminal::ListBox::ListBox(){
  this->caption="";
  this->setX( 0 );
  this->setY( 0 );
  drawCaption=true;
  this->canTakeFocus=true;
  selectedItem=1;
}

/** The named constructor
  *
  * It initialize the caption to c. x and y are set to 0.
  *
  * \param c the caption of the label
  */
RainbruRPG::Terminal::ListBox::ListBox( const std::string& c ){
  this->caption=c;
  this->setX( 0 );
  this->setY( 0 );
  drawCaption=true;
  this->canTakeFocus=true;
  selectedItem=1;
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
RainbruRPG::Terminal::ListBox::ListBox( const std::string& c, int x, int y ){
  this->caption=c;
  this->setX( x );
  this->setY( y );
  drawCaption=true;
  this->canTakeFocus=true;
  selectedItem=1;
}

/** The default destructor
  *
  */
RainbruRPG::Terminal::ListBox::~ListBox(){

}

/** Change the caption to c
  *
  * \param c the new caption of the label
  */
void RainbruRPG::Terminal::ListBox::setText( const std::string& c ){
  this->caption=c;
}

/** Get the caption of the label
  *
  * \return the caption of the label
  *
  */
const std::string& RainbruRPG::Terminal::ListBox::getText()const{
  return this->caption;
}

void RainbruRPG::Terminal::ListBox::draw( int x, int y ){
  int xp= (x+this->x)-2;
  int yp= (y+this->y)-1;

  // Sets the draw color according to the focus state of the widget
  if (this->hasFocus)
    SLsmg_set_color (6);
  else
    SLsmg_set_color (0);

  // Draw the frame of the widget
  SLsmg_draw_box ( yp, xp, height, width );

  // Draws the caption if enabled
  if (drawCaption)
    this->drawTheCaption(xp, yp);

  // Draw the item list
  SLsmg_set_color (0);
  this->drawItems(xp+1, yp+1);
}

/** Add an item to the ListBox
  *
  * it creates a tListBoxItem containing the parameter and push_back()
  * it to itemList.
  *
  * \param c the caption of the item to add.
  */
void RainbruRPG::Terminal::ListBox::addItem(const std::string& c){
  ListBoxItem *item=new ListBoxItem(c);

  itemList.push_back( item );
}

/** x and y are the position where the first item caption must be
  * draw. It is not the same as ListBox::draw( int x, int y ).
  *
  * \param x the x coordonate of the item
  * \param y the y coordonate of the item
  */
void RainbruRPG::Terminal::ListBox::drawItems(int x, int y){

  tListBoxItemList::const_iterator iter;
  int ind=1;

  // Iterate through list and fire the action
  for (iter=itemList.begin(); iter != itemList.end(); iter++)  {
    SLsmg_gotorc ( y, x );


    if ( hasFocus && ind==selectedItem ){
      SLsmg_set_color (1);
      // All the line in reverse video
      for (int j=1; j<width-1; j++)
	// cast to char* to avoid deprecating conversion warning
	SLsmg_printf( (char*)" " );

      SLsmg_gotorc ( y, x );
    }
    else
      SLsmg_set_color (0);

    // cast to char* to avoid deprecating conversion warning
    if ( (*iter)->isChecked() )
      SLsmg_printf( (char*)"[X] %s", (*iter)->getCaption().c_str() );
    else
      SLsmg_printf( (char*)"[ ] %s", (*iter)->getCaption().c_str() );

    y++;
    ind++;
  }
}

/** Turn on or off the ability to draw the ListBox caption
  *
  * This modify the drawCaption boolean directly and without any control.
  *
  * \param b if \c true, the ListBox will draw its caption, otherwise,
  *          it will not draw it.
  */
void RainbruRPG::Terminal::ListBox::setDrawCaption( bool b ){
  drawCaption=b;
}

/** Return the status of the caption's drawing ability
  *
  * \return the drawCaption value.
  */
bool RainbruRPG::Terminal::ListBox::getDrawCaption(){
  return drawCaption;
}

/** Draws the caption of the box
  *
  * \param x the x coordonate of the box
  * \param y the y coordonate of the box
  */
void RainbruRPG::Terminal::ListBox::drawTheCaption( int x, int y){
  SLsmg_gotorc ( y, x+2);
  SLsmg_set_char_set (1);
  SLsmg_write_char( SLSMG_RTEE_CHAR );
  SLsmg_set_char_set (0);

  // cast to char* to avoid deprecating conversion warning
  SLsmg_printf( (char*)" %s ", caption.c_str() );
  SLsmg_set_char_set (1);
  SLsmg_write_char( SLSMG_LTEE_CHAR );
  SLsmg_set_char_set (0);
}

/** Receives and treat the keycode  send by TerminalApp
  *
  * \param ch the keycode to treat
  */
void RainbruRPG::Terminal::ListBox::receiveKeyEvent(int ch){
  if (ch==2) // bas
    keyDownHit();
    
  if (ch==1) // haut
    keyUpHit();

  if (ch==32) // space
    keySpaceHit();
}

/** The up key action
  *
  * Goes to the next item.
  */
void RainbruRPG::Terminal::ListBox::keyDownHit(){
  selectedItem++;
  if (selectedItem>itemList.size())
    selectedItem=itemList.size();
}

/** The up key action
  *
  * Goes to the previous item.
  */
void RainbruRPG::Terminal::ListBox::keyUpHit(){
  selectedItem--;
  if (selectedItem<1)
    selectedItem=1;
}

/** The space key action
  *
  * it calls the toggleItem method.
  */
void RainbruRPG::Terminal::ListBox::keySpaceHit(){
  toggleItem( );
}

/** Toggles the current selected item
  *
  */
void RainbruRPG::Terminal::ListBox::toggleItem( ){
  tListBoxItemList::const_iterator iter;

  int ind=1;

  // Iterate through list and fire the action
  for (iter=itemList.begin(); iter != itemList.end(); iter++){
    if (ind==selectedItem){
      (*iter)->toggle();
    }
    ind++;
  }
}

/** Get the number of items
  *
  * \return The size of the item list.
  *
  */
unsigned int RainbruRPG::Terminal::ListBox::itemCount(){
  return itemList.size();
}

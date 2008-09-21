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

/** \file listview.cpp
  * Implements a list view widget
  *
  */

#include "listview.h"

/** The default constructor
  *
  *
  *
  */
RainbruRPG::Terminal::ListView::ListView(){
  this->caption="";
  this->setX( 0 );
  this->setY( 0 );
  init();
}

/** The named constructor
  *
  * \param caption The caption of the list view
  *
  */
RainbruRPG::Terminal::ListView::ListView( const char* caption ){
  this->caption=caption;
  this->setX( 0 );
  this->setY( 0 );
  init();
}

/** The named and positionned constructor
  *
  * \param caption The caption of the list view
  * \param x The The x position of the widget
  * \param y The The x position of the widget
  *
  */
RainbruRPG::Terminal::ListView::ListView( const char* caption, int x, int y){
  this->caption=caption;
  this->setX( x );
  this->setY( y );
  init();
}

/** The initialization common to multiple constructors
  *
  */
void RainbruRPG::Terminal::ListView::init(){
  drawCaption=true;
  this->canTakeFocus=true;
  selectedItem=0;
  selectedColumn=0;
  selType=LVS_CELL;
  selType=LVS_LINE;
}


/** The default destructor
  *
  */
RainbruRPG::Terminal::ListView::~ListView(){

}

/** The drawing method of ListView
  *
  * 
  *
  * \param x The x position of the ListView
  * \param y The y position of the ListView
  *
  */
void RainbruRPG::Terminal::ListView::draw( int x, int y ){
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

  drawColumns(xp, yp);


  unsigned int itemNum=0;
  // Draws the items
  tListViewItemList::const_iterator iter;
  // Iterate through list and output each column
  for (iter=itemList.begin(); iter != itemList.end(); iter++){
    if (hasFocus && selType==LVS_LINE && itemNum==selectedItem)
      drawItem( (*iter), xp+1, yp+2+itemNum, true );
    else if (hasFocus && selType==LVS_CELL && itemNum==selectedItem)
      drawItem( (*iter), xp+1, yp+2+itemNum, true );
    else
      drawItem( (*iter), xp+1, yp+2+itemNum, false );

    itemNum++;
  }
}

/** Treats the keycode send to this widget
  *
  *
  * \param ch The keycode received from TerminalApp
  *
  */
void RainbruRPG::Terminal::ListView::receiveKeyEvent(int ch){
  if (ch==1) // haut
    keyUpHit();

  if (ch==2) // down
    keyDownHit();

  if (ch==3){ // Left
    keyLeftHit();
  }
  else if (ch==4){ //Right
    keyRightHit();
  }
}

/** Adds a column to this ListView
  *
  * \param col The column to add
  *
  */
void RainbruRPG::Terminal::ListView::addColumn(ListViewColumn* col){
  columnList.push_back(col);
}

/** Draws the caption of this listView
  *
  * \param x The x coordonate
  * \param y The y coordonate
  *
  */
void RainbruRPG::Terminal::ListView::drawTheCaption( int x, int y){
  SLsmg_gotorc ( y, x+2);
  SLsmg_set_char_set (1);
  SLsmg_write_char( SLSMG_RTEE_CHAR );
  SLsmg_set_char_set (0);

  // cast to char* to avoid deprecated converion warning
  SLsmg_printf( (char*)" %s ", caption );
  SLsmg_set_char_set (1);
  SLsmg_write_char( SLSMG_LTEE_CHAR );
  SLsmg_set_char_set (0);
}

/** Draws all the columns
  *
  * \param x The x coordonate
  * \param y The y coordonate
  *
  */
void RainbruRPG::Terminal::ListView::drawColumns( int x, int y){
  unsigned int columnNum=0;
  unsigned int fillY=0;

  // Makes the header background
  SLsmg_set_color(2);
  SLsmg_gotorc( y+1, x+1);
  // cast to char* to avoid deprecated converion warning
  SLsmg_write_nchars((char*)"                                     ", width-2);


  tListViewColumnList::const_iterator iter;

  // Iterate through list and output each column
  for (iter=columnList.begin(); iter != columnList.end(); iter++){
    // Draw the background of a preselected column
    if (hasFocus && selType==LVS_COLUMN && selectedColumn==columnNum){
      SLsmg_set_color(1);
      for (fillY=0; fillY!=this->height-3; fillY++){
	SLsmg_gotorc( y+fillY+2, x+1);
	// cast to char* to avoid deprecated converion warning
	SLsmg_write_nchars((char*)"                       ", (*iter)->getWidth());

      }

    }

    // Draws the column's caption
    SLsmg_set_color(2);
    SLsmg_gotorc( y+1, x+1);
    // cast to char* to avoid deprecated converion warning
    SLsmg_printf( (char*)"%s", (*iter)->getCaption() );
    
    SLsmg_set_color(10);
    SLsmg_gotorc( y+1, x+1+(*iter)->getWidth());
    SLsmg_write_char( SLSMG_VLINE_CHAR );
    
    // Draws the vertical line
    SLsmg_set_color(0);
    SLsmg_gotorc ( y+2, x+1+(*iter)->getWidth());
    SLsmg_draw_vline(height-3);
    SLsmg_set_color(0);
    
    x+=(*iter)->getWidth()+1;
    columnNum++;
  }
}

/** Draws an item
  *
  * \param it The item to draw
  * \param x The x coordonate
  * \param y The y coordonate
  * \param selected Draw it selected 
  *
  */
void RainbruRPG::Terminal::ListView::drawItem(ListViewItem* it, int x, int y,
					      bool selected){
  unsigned int columnNum=0;

  // Draw the first column
  tListViewColumnList::const_iterator iter;

  // Iterate through list and output each column
  for (iter=columnList.begin(); iter != columnList.end(); iter++){
    // The column selection handle
    if (hasFocus && selType==LVS_COLUMN && selectedColumn==columnNum){
      SLsmg_set_color(1);
    }
    else if (hasFocus && selType==LVS_CELL 
	     && selectedColumn==columnNum && selected){
      SLsmg_set_color(1);
    }
    else if (hasFocus && selType==LVS_LINE && selected){
      SLsmg_set_color(1);
    }
    else{
      SLsmg_set_color(0);
    }


    SLsmg_gotorc( y, x);
    // cast to char* to avoid deprecated converion warning
    SLsmg_printf( (char*)"%s", it->getColumn(columnNum) );

    columnNum++;
    x+=(*iter)->getWidth()+1;
  }

}

/** Adds an item to the listview
  *
  * \param it The item to add
  *
  */
void RainbruRPG::Terminal::ListView::addItem(ListViewItem* it){
  itemList.push_back(it);
}

/** The left arrow key was pressed
  *
  */
void RainbruRPG::Terminal::ListView::keyLeftHit(){
  unsigned int max=columnList.size();

  selectedColumn--;
  if (selectedColumn<0 || selectedColumn>max)
    selectedColumn=0;
}

/** The right arrow key was pressed
  *
  */
void RainbruRPG::Terminal::ListView::keyRightHit(){
  unsigned int max=columnList.size()-1;

  selectedColumn++;
  if (selectedColumn>max)
    selectedColumn=max;

}

/** The up arrow key was pressed
  *
  */
void RainbruRPG::Terminal::ListView::keyUpHit(){
  unsigned int max=itemList.size();

  selectedItem--;
  if (selectedItem<0 || selectedItem>max)
    selectedItem=0;
}

/** The down arrow key was pressed
  *
  */
void RainbruRPG::Terminal::ListView::keyDownHit(){
  unsigned int max=itemList.size()-1;

  selectedItem++;
  if (selectedItem<0 || selectedItem>max)
    selectedItem=max;
}

/** Gets the number of item
  *
  * \return The size of the item list
  *
  */
unsigned int RainbruRPG::Terminal::ListView::itemCount(){
  return itemList.size();
}

/** Gets the number of column
  *
  * \return The size of the column list
  *
  */
unsigned int RainbruRPG::Terminal::ListView::columnCount(){
  return columnList.size();
}

/** Change the caption of this ListView
  *
  * \param c The new caption
  *
  */
void RainbruRPG::Terminal::ListView::setCaption( const char*c ){
  this->caption=c;
}

/** Get the current caption
  *
  * \return This ListView caption
  *
  */
const char* RainbruRPG::Terminal::ListView::getCaption( ){
  return this->caption;
}

/** Returns the drawCaption value
  *
  * \return \c true if we draw the ListView's caption
  *
  */
bool RainbruRPG::Terminal::ListView::getDrawCaption(){
  return this->drawCaption;
}

/** Sets the drawCaption value
  *
  * \param b \c true if we draw the ListView's caption
  *
  */
void RainbruRPG::Terminal::ListView::setDrawCaption( bool b ){
  this->drawCaption=b;
}

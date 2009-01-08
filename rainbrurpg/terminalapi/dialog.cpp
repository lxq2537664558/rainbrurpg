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

/** \file terminalapi/dialog.cpp
  * Implements a base class of all dialogs
  *
  */

#include "dialog.h"

/** The constructor of a centered Dialog
  *
  * \param w the width of the Dialog
  * \param h the height of the Dialog
  */
RainbruRPG::Terminal::Dialog::Dialog( int w, int h ):
  visible(true)
{
  this->width=w;
  this->height=h;
  center( w, h );
  caption=new Caption( WORD_WRAPPED, "", xPos+1, yPos+1, width-1, height-4 );
  nbButton=0;
}

/** An empty virtual destructor
  *
  */
RainbruRPG::Terminal::Dialog::~Dialog(){

}

/** Calculates the xPos and yPos values
  *
  * \param w the width of the Dialog
  * \param h the height of the Dialog
  */
void RainbruRPG::Terminal::Dialog::center( int w, int h ){
  this->xPos= (SLtt_Screen_Cols/2)-(width/2); 
  this->yPos= (SLtt_Screen_Rows/2)-(height/2);
}

/** Calls all the methods to draw a complete Dialog
  *
  * This method must be called by the subclasses.
  */
void RainbruRPG::Terminal::Dialog::drawDialog(){
  if (visible){
    drawEmpty();
    drawBorder();
    drawShadow();
    if (title.length()>0)
      drawTitle();
    
    drawCaption();
    drawButtons();
  }
}

/** Draws the white panel
  *
  */
void RainbruRPG::Terminal::Dialog::drawEmpty(){
  SLsmg_set_color (1);

  for (int y=yPos; y<yPos+height; y++){
    SLsmg_gotorc (y, xPos);
    for (int x=xPos; x<xPos+width; x++){

     // cast to char* to avoid deprecating conversion warning
      SLsmg_printf( (char*)" " );
    }
  }
  SLsmg_set_color (0);
}

/** Draws the borders of the Dialog
  *
  */
void RainbruRPG::Terminal::Dialog::drawBorder(){
  //The lightgray border
  SLsmg_set_color (8);

  SLsmg_gotorc (yPos, xPos);
  SLsmg_set_char_set (1); //Use the alt charset

  // The top line
  SLsmg_write_char(SLSMG_ULCORN_CHAR);
  SLsmg_draw_hline(width-1);

  // The left border
  for (int y=1; y<height; y++){
    SLsmg_gotorc (yPos+y, xPos);

    if (y==height-3)
      SLsmg_write_char(SLSMG_LTEE_CHAR);
    else if (y==height-1)
      SLsmg_write_char(SLSMG_LLCORN_CHAR);
    else
      SLsmg_write_char(SLSMG_VLINE_CHAR);
  }

  // The buttonbar line
  SLsmg_gotorc (yPos+height-3, xPos+1);
  SLsmg_draw_hline(width-1);

  // The gray border
  SLsmg_set_color (9);

  for (int y=0; y<height; y++){
    SLsmg_gotorc (yPos+y, xPos+width);

    if (y==0)
      SLsmg_write_char(SLSMG_URCORN_CHAR);
    else if (y==height-3)
      SLsmg_write_char(SLSMG_RTEE_CHAR);
    else if (y==height-1)
      SLsmg_write_char(SLSMG_LRCORN_CHAR);
    else
      SLsmg_write_char(SLSMG_VLINE_CHAR);
  }

  // The bottom line
  SLsmg_gotorc (yPos+height-1, xPos+1);
  SLsmg_draw_hline(width-1);

  SLsmg_set_char_set(0); //Use the normal charset
  SLsmg_set_color(0);
}

/** Draws the shadow of the Dialog
  *
  */
void RainbruRPG::Terminal::Dialog::drawShadow(){
  SLsmg_set_color(5);


  for (int y=yPos+1; y<yPos+height+1; y++){
    SLsmg_gotorc (y, xPos+width+1);
    // cast to char* to avoid deprecating conversion warning
    SLsmg_printf( (char*)"  " );
  }

  for (int x=xPos+1; x<xPos+width+3; x++){
    SLsmg_gotorc (yPos+height, x);
    // cast to char* to avoid deprecating conversion warning
    SLsmg_printf( (char*)" " );
  }

  SLsmg_set_color(0);
}

/** Changes the title of the Dialog
  *
  */
void RainbruRPG::Terminal::Dialog::setTitle( std::string s ){
  title=s;
}

/** Changes the message of the Dialog
  *
  */
void RainbruRPG::Terminal::Dialog::setMessage( std::string s ){
  caption->setText( s );
}

/** Get the title of the Dialog
  *
  */
const char* RainbruRPG::Terminal::Dialog::getTitle(){
  return title.c_str();
}

/** Get the message of the Dialog
  *
  */
const char* RainbruRPG::Terminal::Dialog::getMessage(){
  return caption->getText().c_str();
}

/** Draws the title of the Dialog
  *
  */
void RainbruRPG::Terminal::Dialog::drawTitle(){
  int l=title.length();
  int x=(SLtt_Screen_Cols/2)-(l/2);

  SLsmg_set_color (8);


  SLsmg_set_char_set (1); //Use the alt charset
  SLsmg_gotorc (yPos, x-2);
  SLsmg_write_char(SLSMG_RTEE_CHAR);
  SLsmg_gotorc (yPos, x+l+1);
  SLsmg_write_char(SLSMG_LTEE_CHAR);

  //title
  SLsmg_set_color (9);
  SLsmg_gotorc (yPos, x-1);
  SLsmg_set_char_set (0); //Use the alt charset

  // cast to char* to avoid deprecating conversion warning
  SLsmg_printf( (char*)" %s ", title.c_str() );

}

/** Draws the message of the Dialog
  *
  */
void RainbruRPG::Terminal::Dialog::drawCaption(){
  SLsmg_set_color (9);
  caption->draw();
}

/** Adds a PushButton the Dialog
  *
  * \param pb The button to add
  */
void RainbruRPG::Terminal::Dialog::addButton(PushButton* pb){
  if (nbButton<3){
    switch(nbButton){
    case 0:
      btn1=pb;
      break;

    case 1:
      btn2=pb;
      break;

    case 2:
      btn3=pb;
      break;
    }
    nbButton++;
  }
}

/** Draws the PushButtons of the Dialog
  *
  * The width of the buttons is set to 8 by default.
  */
void RainbruRPG::Terminal::Dialog::drawButtons(){
  if (nbButton==1){
    btn1->setSize( 8, 1 );
    btn1->setY( height-1 );
    btn1->setX( (width/2)-4 );
    btn1->draw( xPos, yPos );
  }
}

/** The keycode receiver
  *
  * \param ch the keycode to treat
  */
void RainbruRPG::Terminal::Dialog::receiveKeyEvent(int ch){
  if (nbButton>0){
    if (ch==13){ //ENTER
      btn1->fireAction();
    }
  }
}

/** Shows this dialog
  *
  */
void RainbruRPG::Terminal::Dialog::show(void){
  visible=true;
}

/** Hides this dialog
  *
  */
void RainbruRPG::Terminal::Dialog::hide(void){
  visible=false;
}

/** A static wrapper to call the hide function
  *
  * Please see the InfoDialog implementationfor more informations.
  *
  */
int RainbruRPG::Terminal::Dialog::hide_wrapper(void* vObject){
  Dialog* dial = static_cast<Dialog*>(vObject);
  if (dial){
    dial->hide();
    return 0;
  }
  else{
    LOGW("Cannot call hide() from its wrapper. Object's pointer is NULL");
    return 1;
  }
}

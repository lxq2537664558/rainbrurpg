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

/** \file terminalapi/caption.cpp
  * Implements a caption widget
  *
  */

#include "caption.h"

#include <vector>

/** The default constructor
  *
  * It creates a basic word-wrapped Caption widget.
  */
RainbruRPG::Terminal::Caption::Caption(){
  type=WORD_WRAPPED;
  text="";
  xPos=0;
  yPos=0;
  width=10;
  height=1;
  this->xOffset=0;
  this->yOffset=0;
}

/** The default destructor
  *
  */
RainbruRPG::Terminal::Caption::~Caption(){

}


/** The typical Caption constructor
  *
  * It constructs a Caption with offsets set to 0.
  *
  * \param t The type of Caption
  * \param s The stl string to draw
  * \param x The x position of the Caption
  * \param y The y position of the Caption
  * \param w The width of the caption
  * \param h The height of the caption
  */
RainbruRPG::Terminal::Caption::Caption( tCaptionType t, string s, int x, 
					int y, int w, int h ){
  type=t;
  text=s;
  xPos=x;
  yPos=y;
  width=w;
  height=h;
  this->xOffset=0;
  this->yOffset=0;
}

/** Sets the type of the Caption
  *
  * \param t The type to change to
  */
void RainbruRPG::Terminal::Caption::setType( tCaptionType t ){
  this->type=t;
}

/** Changes the text of the Caption
  *
  * \param s The text of the caption
  */
void RainbruRPG::Terminal::Caption::setText( std::string s ){
  this->text=s;
}

/** Set the x position of the Caption
  *
  * \param x The x position of the Caption
  */
void RainbruRPG::Terminal::Caption::setXPos( int x ){
  this->xPos=x;
}

/** Changes the y position of the Caption
  *
  * \param y The y position of the Caption
  */
void RainbruRPG::Terminal::Caption::setYPos( int y ){
  this->yPos=y;
}

/** Changes the width of the Caption
  *
  * \param w The new width
  */
void RainbruRPG::Terminal::Caption::setWidth( int w ){
  this->width=w;
}

/** Changes the height of the Caption
  *
  * \param h The new height
  */
void RainbruRPG::Terminal::Caption::setHeight( int h ){
  this->height=h;
}

/** Return the type of this caption
  *
  * \return The caption's type
  */
RainbruRPG::Terminal::tCaptionType RainbruRPG::Terminal::Caption::getType(){
  return this->type;
}

/** Get the current text of the caption
  *
  * \return the text of the caption
  */
const std::string& RainbruRPG::Terminal::Caption::getText()const{
  return this->text;
}

/** Get the x position of the caption
  *
  * \return the x position
  */
int RainbruRPG::Terminal::Caption::getXPos(){
  return this->xPos;
}

/** Get the y position of the caption
  *
  *\return the y position
  */
int RainbruRPG::Terminal::Caption::getYPos(){
  return this->yPos;
}

/** Return the width of the Caption
  *
  * \return the width of the Caption
  */
int RainbruRPG::Terminal::Caption::getWidth(){
  return this->width;
}

/** Return the height of the Caption
  *
  * \return the height of the Caption
  */
int RainbruRPG::Terminal::Caption::getHeight(){
  return this->height;
}

/** Set the xOffset of the Caption
  *
  * See the xOffset property for more information.
  *
  * \param x The new xOffset value
  */
void RainbruRPG::Terminal::Caption::setXOffset(int x){
  this->xOffset=x;
}

/** Set the yOffset of the Caption
  *
  * See the yOffset property for more information.
  *
  * \param y The new yOffset value
  */
void RainbruRPG::Terminal::Caption::setYOffset(int y){
  this->yOffset=y;
}

/** Set both the xOffset and yOffset values
  *
  * \param x The new xOffset value
  * \param y The new yOffset value
  *
  */
void RainbruRPG::Terminal::Caption::setOffset(int x, int y){
  this->xOffset=x;
  this->yOffset=y;
}

/** Returns the xOffset value
  *
  * \return the value of the xOffset property
  */
int RainbruRPG::Terminal::Caption::getXOffset(){
  return this->xOffset;
}

/** Returns the yOffset value
  *
  * \return the value of the yOffset property
  */
int RainbruRPG::Terminal::Caption::getYOffset(){
  return this->yOffset;
}

/** The drawing method
  *
  * It simply call the right drawing method according to the type of
  * the caption.
  */
void RainbruRPG::Terminal::Caption::draw(){
  switch(type){
  case H_CENTERED:
    drawHCentered();
    break;

  case WORD_WRAPPED:
    drawWordWrapped();
    break;

  }
}

/** Draw the caption if its style is horizontally centered 
  *
  * It calculate the xPos value and draw the text
  */
void RainbruRPG::Terminal::Caption::drawHCentered(){
  // Calculate the x placement
  int x=(xPos+(width/2))- (text.length()/2);
  SLsmg_gotorc ( yPos, x );

  // cast to char* to avoid deprecating conversion warning
  SLsmg_printf( (char*)"%s",  text.c_str());
}

/** Get the first word of the text property and erase it
  *
  * This function is used to draw the word wrapped text. 
  *
  *
  * \return the next word to word-wrap
  */
string RainbruRPG::Terminal::Caption::getWord(){
  string ret;

  // Erase the first space if one
  if (temp.find(" ", 0)==0)
    temp.erase(0, 1);

  string::size_type p=temp.find(" ", 0);
  ret=temp.substr(0, p);
  temp.erase(0, p);
  return ret;
}

/** Draw a word wrapped caption 
  *
  * It draws each word of the text property individually (by using the
  * getWord() function) only if it do not override the caption's
  * width. If the word can stand this limit, it is writtent in a
  * newline. 
  *
  * The number of lines used is not tested.
  *
  */
void RainbruRPG::Terminal::Caption::drawWordWrapped(){
  int toWidth=0;
  int y=yPos;
  string w;

  SLsmg_gotorc (yPos, xPos);
  temp=text;

  while (temp.length()>0){

    //  for (int i=0; i<10; i++){
    w=getWord();

    if (toWidth+w.length()>width-1){
      toWidth=0;
      y++;
      SLsmg_gotorc (y, xPos);
    }

    // cast to char* to avoid deprecating conversion warning
    SLsmg_printf( (char*)"%s ", w.c_str() );
    toWidth+=w.length();
    toWidth++;
  }
}

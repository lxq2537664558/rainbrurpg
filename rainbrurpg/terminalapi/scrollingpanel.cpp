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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file scrollingpanel.cpp
  * Implements a class that provides the window's scrolling facility
  *
  */

#include "scrollingpanel.h"

/** The default constructor
  *
  * Sets the logical and physical screen's size to 1,1.
  * The offstes are both set to 0.
  */
RainbruRPG::Terminal::ScrollingPanel::ScrollingPanel(){
  setPhysicalSize( 1, 1 );
  setLogicalSize( 1, 1 );

  xOffset=0;
  yOffset=0;
}

/** The default destructor 
  *
  */
RainbruRPG::Terminal::ScrollingPanel::~ScrollingPanel(){

}

/** Set the size od the physical screen
  *
  * \param w the width of the physical screen
  * \param h the height of the physical screen
  */
void RainbruRPG::Terminal::ScrollingPanel::setPhysicalSize(int w, int h){
  physicalWidth=w;
  physicalHeight=h;

}

/** Set the size od the logical screen
  *
  * The logical can't be smaller than the physical screen.
  *
  * \param w the width of the logical screen
  * \param h the height of the logical screen
  */
void RainbruRPG::Terminal::ScrollingPanel::setLogicalSize(int w, int h){
  logicalWidth=w;
  if (w<physicalWidth)
    w=physicalWidth;

  logicalHeight=h;
  if (h<physicalHeight)
    h=physicalHeight;

}

/** Set the yOffset as if we move the physical screen down
  *
  * The limit is tested as \c yOffset<=(logicalHeight-physicalHeight)
  *
  */
void RainbruRPG::Terminal::ScrollingPanel::goDown(){
  int maxYOffset=logicalHeight-physicalHeight;

  yOffset++;
  if (yOffset>maxYOffset)
    yOffset=maxYOffset;
}

/** Set the yOffset as if we move the physical screen up
  *
  * The limit is tested as \c yOffset>=0
  *
  */
void RainbruRPG::Terminal::ScrollingPanel::goUp(){
  yOffset--;
  if (yOffset<0)
    yOffset=0;
}

/** Set the xOffset as if we move the physical screen right
  *
  * The limit is tested as \c xOffset<=(logicalWidth-physicalWidth)
  *
  */
void RainbruRPG::Terminal::ScrollingPanel::goRight(){
  int maxXOffset=logicalWidth-physicalWidth;

  xOffset++;
  if (xOffset>maxXOffset)
    xOffset=maxXOffset;
}

/** Set the xOffset as if we move the physical screen up
  *
  * The limit is tested as \c xOffset>=0
  *
  */
void RainbruRPG::Terminal::ScrollingPanel::goLeft(){
  xOffset--;
  if (xOffset<0)
    xOffset=0;
}

/** Gets the physical width value
  *
  * \return the physical width
  *
  */
int RainbruRPG::Terminal::ScrollingPanel::getPhysicalWidth(){
  return this->physicalWidth;
}

/** Gets the physical height value
  *
  * \return the physical height
  *
  */
int RainbruRPG::Terminal::ScrollingPanel::getPhysicalHeight(){
  return this->physicalHeight;
}

/** Gets the logical width value
  *
  * \return the logical width
  *
  */
int RainbruRPG::Terminal::ScrollingPanel::getLogicalWidth(){
  return this->logicalWidth;
}

/** Gets the logical height value
  *
  * \return the logical height
  *
  */
int RainbruRPG::Terminal::ScrollingPanel::getLogicalHeight(){
  return this->logicalHeight;
}

/** Gets the X offset value
  *
  * \return the X offset
  *
  */
int RainbruRPG::Terminal::ScrollingPanel::getXOffset(){
  return this->xOffset;
}

/** Gets the Y offset value
  *
  * \return the Y offset
  *
  */
int RainbruRPG::Terminal::ScrollingPanel::getYOffset(){
  return this->yOffset;
}

/** Sets the X offset value
  *
  * \param x The X offset value
  *
  */
void RainbruRPG::Terminal::ScrollingPanel::setXOffset(int x){
  this->xOffset=x;
}

/** Sets the Y offset value
  *
  * \param y The Y offset value
  *
  */
void RainbruRPG::Terminal::ScrollingPanel::setYOffset(int y){
  this->yOffset=y;
}

/** Sets the physical width value
  *
  * \param i The phyical width
  *
  */
void RainbruRPG::Terminal::ScrollingPanel::setPhysicalWidth(int i){
  physicalWidth=i;
}

/** Sets the physical height value
  *
  * \param i The phyical height
  *
  */
void RainbruRPG::Terminal::ScrollingPanel::setPhysicalHeight(int i){
  physicalHeight=i;
}

/** Sets the logical width value
  *
  * \param i The logical width
  *
  */
void RainbruRPG::Terminal::ScrollingPanel::setLogicalWidth(int i){
  logicalWidth=i;
}

/** Sets the logical height value
  *
  * \param i The logical height
  *
  */
void RainbruRPG::Terminal::ScrollingPanel::setLogicalHeight(int i){
  logicalHeight=i;
}


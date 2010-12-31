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

/** \file menu.cpp
  * Implements a menu used in menubars
  *
  */

#include "menu.h"

/** The default constructor
  *
  */
RainbruRPG::Terminal::Menu::Menu(){
  this->name="";
  this->width=0;
  this->height=0;
}


/** The named constructor
  *
  * \param n the name (caption) of the menu
  *
  */
RainbruRPG::Terminal::Menu::Menu(const char* n){
  this->name=n;
  this->width=0;
  this->height=0;
}

/** The default destructor
  *
  */
RainbruRPG::Terminal::Menu::~Menu(){
  LOGI("Menu destructor");
}

/** Adds a MenuItem to he Menu
  *
  * It first increase the value of height. Then it push_back() the
  * MenuItem in itemList. Finally, if the lenght of the i->getName()
  * is bigger than width, width is up to date.
  *
  * \param i the MenuItem to be added.
  */
void RainbruRPG::Terminal::Menu::addItem(MenuItem* i){
  int j;

  this->height++;
  this->itemList.push_back( i );

  j=strlen(i->getName());

  if (j>this->width)
    this->width=j;

}

/** Get the name of the Menu
  *
  * \return the name value.
  *
  */
const char* RainbruRPG::Terminal::Menu::getName(){
  return this->name;
}

/** Get the width of the Menu
  *
  * The width is given by the largest menuItem.
  *
  * \return the width value.
  *
  */
unsigned int RainbruRPG::Terminal::Menu::getWidth(){
  return this->width;
}

/** Get the height of the Menu
  *
  * This value can be different from itemCount() if a scrolling if done.
  *
  * \return the height value.
  *
  */
unsigned int RainbruRPG::Terminal::Menu::getHeight(){
  return this->height;
}

/** Get all MenuItem previously added to the Menu
  *
  * \return the a itemList reference.
  *
  */
RainbruRPG::Terminal::tMenuItemList* RainbruRPG::Terminal::Menu::getItemList(){
  return &itemList;
}

/** Changes the name of the menu
  *
  * \param n The new name
  *
  */
void RainbruRPG::Terminal::Menu::setName(const char* n){
  this->name=n;
}

/** The number of MenuItem
  *
  * This value can be different from getHeight() if a scrolling if done.
  *
  */
unsigned int RainbruRPG::Terminal::Menu::itemCount(){
  return itemList.size();
}

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

/** \file menubar.cpp
  * Implements a menubar widget
  *
  */

#include "menubar.h"

/** The default constructor
  * 
  */
RainbruRPG::Terminal::MenuBar::MenuBar(){
  LOGI("MenuBar constructor");
}

/** The default destructor
  * 
  */
RainbruRPG::Terminal::MenuBar::~MenuBar(){
  LOGI("MenuBar destructor");
}

/** Add a Menu to the menuList
  *
  * It calls the push_back() method of the STL tMenuList. It performs
  * no control.
  *
  * \param m the Menu to add.
  */
void RainbruRPG::Terminal::MenuBar::addMenu(Menu* m){
  menuList.push_back(m);
}

/** Returns the number of menu contained in the menuList
  *
  * \return the value returned by the STL list.size() function.
  */
int RainbruRPG::Terminal::MenuBar::getSize(){
  return menuList.size();
}

/** Returns all the menu contained in this menubar
  *
  * \return the STL list containing all the added Menu.
  */
RainbruRPG::Terminal::tMenuList* 
RainbruRPG::Terminal::MenuBar::getMenuList(){
  return &menuList; 
}

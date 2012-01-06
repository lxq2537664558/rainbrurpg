/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file menuitem.cpp
  * Implements the item a menu 
  *
  */

#include "menuitem.h"

/** The default constructor
  *
  */
RainbruRPG::Terminal::MenuItem::MenuItem(){
  this->name="";
  actionSet=false;
}

/** The named constructor
  *
  * \param n the name of the created MenuItem
  */
RainbruRPG::Terminal::MenuItem::MenuItem(const char *n){
  this->name=n;
  actionSet=false;

}

/** The default destructor
  *
  */
RainbruRPG::Terminal::MenuItem::~MenuItem(){
}

/** Get the name of the MenuItem
  *
  * \return the name of the MenuItem
  */
const char* RainbruRPG::Terminal::MenuItem::getName(){
  return this->name;
}

/** Fire the action
  *
  * Return -1 if none action has been set, otherwise return the value
  * of the pointed function.
  */ 
int RainbruRPG::Terminal::MenuItem::fireAction(){
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
void RainbruRPG::Terminal::MenuItem::setAction(FuncPtr a){
  this->fptr=a;
  actionSet=true;

}

/** Changes the name of the menuitem
  *
  * \param n The new name
  *
  */
void RainbruRPG::Terminal::MenuItem::setName(const char* n){
  this->name=n;
}

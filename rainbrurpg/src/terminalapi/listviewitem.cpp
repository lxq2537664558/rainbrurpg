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

/** \file listviewitem.cpp
  * Implements an item of a a list view widget
  *
  */

#include "listviewitem.h"

#include <logger.h>

/** The default constructor 
  *
  */
RainbruRPG::Terminal::ListViewItem::ListViewItem(){

}

/** The default destructor 
  *
  */
RainbruRPG::Terminal::ListViewItem::~ListViewItem(){

}

/** Adds a column content
  *
  * \param c The content of the column to add
  *
  */
void RainbruRPG::Terminal::ListViewItem::addColumn(const char*c){
  columns.push_back(c);
}

/** Gets a column content
  *
  * \param i The column number
  *
  * \return The content of the column to add
  *
  */
const char* RainbruRPG::Terminal::ListViewItem::getColumn(unsigned int i){
  if (i>columns.size()){
    LOGW("Column number out of range");
    LOGCATS("getColumn parameter : ");
    LOGCATI(i);
    LOGCAT();
    return "";
  }
  else if(columns.empty()){
    LOGW("ListViewItem is empty");
    return "";
  }
  else{
    return columns[i];
  }
}

/** Returns the number of column
  *
  * \return The size of the column list
  *
  */
unsigned int RainbruRPG::Terminal::ListViewItem::columnCount(){
  return columns.size();
}

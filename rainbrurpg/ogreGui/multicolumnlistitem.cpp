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
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "multicolumnlistitem.h"

#include <logger.h>

/** The default constructor
  *
  */
RainbruRPG::OgreGui::MultiColumnListItem::MultiColumnListItem(){

}

/** A constructor
  *
  */
RainbruRPG::OgreGui::MultiColumnListItem::
MultiColumnListItem(const std::string&, ...){

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::MultiColumnListItem::~MultiColumnListItem(){

}

/** Get the item list
  *
  * \return The item list
  *
  */
const RainbruRPG::OgreGui::tMclItemList& 
RainbruRPG::OgreGui::MultiColumnListItem::getItemList(void){
  return mList;
}

/** Set the text of a cell
  *
  * \param index   The index to change
  * \param caption The new caption
  *
  */
void RainbruRPG::OgreGui::MultiColumnListItem::
setText( int index, const std::string& caption ){
  tMclItem* item=new tMclItem();
  item->isText=true;
  item->text=caption;

  mList.resize(index+1);
  mList[index]=item;
  LOGCATS("mList size() =");
  LOGCATI(mList.size());
  LOGCAT();
}



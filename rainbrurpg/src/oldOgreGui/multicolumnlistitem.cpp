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

/** \file multicolumnlistitem.cpp
  * Implements an item of a multi-column list widget
  *
  */

#include "multicolumnlistitem.h"

#include <logger.h>

#include "multicolumnlistcell.h"

#include <sstream>
#include <vcconstant.h>


/** The default constructor
  *
  */
RainbruRPG::OgreGui::MultiColumnListItem::MultiColumnListItem():
  mouseOver(false),
  mSelected(false),
  mVelocityCalculator(NULL),
  mInTransition(false),
  mAlpha(0.7f)
{
  mVelocityCalculator=new vcConstant();
  mVelocityCalculator->setTranslationLenght(0.7);
  mVelocityCalculator->setTransitionTime(400);
}

/** A constructor
  *
  */
RainbruRPG::OgreGui::MultiColumnListItem::
MultiColumnListItem(const std::string&, ...):
  mouseOver(false),
  mSelected(false)
{

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
const RainbruRPG::OgreGui::tMultiColumnListCellList& 
RainbruRPG::OgreGui::MultiColumnListItem::getCellList(void){
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
  MultiColumnListCell* item=new MultiColumnListCell(caption);

  mList.resize(index+1);
  mList[index]=item;
}

/** Set the mouse over status
  *
  * \param b The new mouse over status
  *
  */
void RainbruRPG::OgreGui::MultiColumnListItem::setMouseOver(bool b){
  if (b==false && mouseOver==true){
    // Starting transition
    mInTransition=true;
    mAlpha=0.7f;
    mVelocityCalculator->start();
  }

  mouseOver=b;
}

/** Is the mouse over this item
  *
  * \return The mouse over status
  *
  */
bool RainbruRPG::OgreGui::MultiColumnListItem::isMouseOver(void)const{
  return mouseOver;
}

/** Set if this item is selected
  *
  * \param b The new selected value
  *
  */
void RainbruRPG::OgreGui::MultiColumnListItem::setSelected(bool b){
  mSelected=b;
}

/** Is this selected selected ?
  *
  * \return Is this selected selected
  *
  */
bool RainbruRPG::OgreGui::MultiColumnListItem::isSelected(void)const{
  return mSelected;
}

/** Get a string representation od thif item
  *
  * \return A string that contains all columns text
  *
  */
std::string RainbruRPG::OgreGui::MultiColumnListItem::str(void)const{
  tMultiColumnListCellList::const_iterator iter;

  ostringstream oss;

  for (iter=mList.begin(); iter!=mList.end(); iter++){
    oss << (*iter)->getText();
  }

  return oss.str();
}

/** Get the alpha use din mouse over
  * 
  * \return The mouse over alpha value
  *
  */
float RainbruRPG::OgreGui::MultiColumnListItem::getMouseOverAlpha(void){
  bool stop;
  mAlpha-=mVelocityCalculator->getNextFrame(stop);
  if (stop==false){
    mVelocityCalculator->reset();
    mInTransition=false;
  }
  return mAlpha;
}

/** Is this item inmouse over transition
  *
  * \return \c true is we are in mouse over transition, otherwise 
  *         returns \c false
  *
  */
bool RainbruRPG::OgreGui::MultiColumnListItem::inTransition(void)const{
  return mInTransition;
}

/** Get the text of the given column
  *
  * \param vColumn The column index
  *
  * \return The column content as string
  *
  */
const std::string& RainbruRPG::OgreGui::MultiColumnListItem::
getString(int vColumn){
  return mList[vColumn]->getText();
}

/** Swap two cell by their column index
  *
  * This function is used when user moves a column.
  *
  * \param vCol1, vCol2 The indexes of the column to swap
  *
  */
void RainbruRPG::OgreGui::MultiColumnListItem::
swapColumns( int vCol1, int vCol2 ){
  MultiColumnListCell* item=mList[vCol2];
  mList[vCol2]=mList[vCol1];
  mList[vCol1]=item;
  item=NULL;
}

/** Toggles the selection of this item
  *
  * If mSelected was \c true, it becomes \c false, if it was \c false, it
  * become \c true.
  *
  */
void RainbruRPG::OgreGui::MultiColumnListItem::toggleSelection(void){
  mSelected=!mSelected;
}

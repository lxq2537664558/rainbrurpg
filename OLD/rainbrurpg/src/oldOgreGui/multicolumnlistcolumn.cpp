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

/** \file multicolumnlistcolumn.cpp
  * Implements the column of a multi-column list widget
  *
  */

#include "multicolumnlistcolumn.h"
#include "multicolumnlist.h"

#include <logger.h>

/** The constructor
  *
  * \param vCaption The caption
  * \param vWidth   The width in pixels
  *
  */
RainbruRPG::OgreGui::MultiColumnListColumn::
MultiColumnListColumn(const std::string& vCaption, int vWidth):
  mCaption(vCaption),
  mWidth(vWidth),
  mMinimumWidth(vWidth),
  mSelected(false),
  mSortPolicy(MCS_NONE),
  mParent(NULL),
  mIndex(-1),
  mVisible(true)
{

}

/** Get the caption
  *
  * \return This column's caption
  *
  */
const std::string& RainbruRPG::OgreGui::MultiColumnListColumn::
getCaption(void)const{
  return mCaption;
}

/** Get the width
  *
  * \return This column's width in pixels
  *
  */
int RainbruRPG::OgreGui::MultiColumnListColumn::getWidth(void)const{
  return mWidth;
}

/** Set if the mouse is over this column's header
  *
  * \param b The new value
  *
  */
void RainbruRPG::OgreGui::MultiColumnListColumn::setSelected(bool b){
  mSelected=b;
}

/** Tells if the mouse is over this column
  *
  * \return \c true if the mouse is over this column's header
  *
  */
bool RainbruRPG::OgreGui::MultiColumnListColumn::isSelected(void)const{
  return mSelected;
}

/** Togle the sort policy
  *
  * The sort policy will cycle through :
  * - MCS_NONE;
  * - MCS_ASCENDANT;
  * - MCS_DESCENDANT
  *
  */
void RainbruRPG::OgreGui::MultiColumnListColumn::toggleSort(void){
  switch (mSortPolicy){
  case MCS_NONE:
    mSortPolicy=MCS_ASCENDANT;
    break;
  case MCS_ASCENDANT:
    mSortPolicy=MCS_DESCENDANT;
    break;
  case MCS_DESCENDANT:
    mSortPolicy=MCS_NONE;
    break;
  };

  LOGA(mParent, _("Column's parent is NULL. Cannot apply sort"));
  LOGA(mIndex!=-1, _("Column's index is -1. Cannot apply sort"));

  if (mParent){
    mParent->setSort(mIndex, mSortPolicy);
  }
}

/** Set the parent and the index for this column
  *
  * This function is called by MultiColumnList to register itself as parent
  * and tell this column its index in column list. It is used when applying
  * sort in toggleSort() to apply change to the list by calling 
  * MultiColumnList::setSort().
  *
  * \param vParent The parent to apply sorting change to
  * \param vIndex  The index of this column in the parent's column list
  *
  */
void RainbruRPG::OgreGui::MultiColumnListColumn::
setParentIndex(MultiColumnList* vParent, int vIndex){
  mParent = vParent;
  mIndex  = vIndex;
}

/** Get the sort policy
  *
  * \return The value of mSortPolicy
  *
  */
tMultiColumnListColumnSortPolicy RainbruRPG::OgreGui::MultiColumnListColumn::
getSortPolicy(void) const{
  return mSortPolicy;
}

/** Set the sort policy to none
  * 
  *
  *
  */
void RainbruRPG::OgreGui::MultiColumnListColumn::resetSort(void){
  mSortPolicy=MCS_NONE;
}

/** Changes the width of this column
  *
  * \param vWidth The new width value
  *
  */
void RainbruRPG::OgreGui::MultiColumnListColumn::resize(int vWidth){
  if (vWidth > mMinimumWidth){
    mWidth = vWidth;
  }
  else{
    mWidth = mMinimumWidth;
  }
}

/** Set the minimum width
  *
  * \param vMinWidth The minimum width in pixels
  *
  */
void RainbruRPG::OgreGui::MultiColumnListColumn::
setMinimumWidth(int vMinWidth){
  mMinimumWidth = vMinWidth;
}

/** Change the visibility of this column
  *
  * This function set mParent's geometry dirty.
  *
  * \param vVisible The new value of mVisible
  *
  */
void RainbruRPG::OgreGui::MultiColumnListColumn::setVisible( bool vVisible ){
  mVisible = vVisible;
  if (mParent){
    /* Setting MultiColumnList geometry dirty to recompute
     * MultiColumnList::mLastColumnRight value.
     *
     */
    mParent->setGeometryDirty();
  }
}

/** Is this column visible
  *
  * \return The value of mVisible
  *
  */
bool RainbruRPG::OgreGui::MultiColumnListColumn::isVisible(void)const{
  return mVisible;
}

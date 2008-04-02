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

#include "multicolumnlist.h"

#include "multicolumnlistcolumn.h"
#include "multicolumnlistitem.h"

#include <logger.h>
#include <quadrenderer.h>

#include <OgreColourValue.h>

// Static data member initialization
int RainbruRPG::OgreGui::MultiColumnList::mCurrentSortedColumn = -1;
// End of static data member initialization

// Global functions implementation
/** Ascendant order sort of MultiColumnList item
  *
  * This is a comparison function used by MulticolumnList::setSort()
  * when it is used in parameter of std;;sort call.
  *
  * \param it1, it2 Items to compare
  *
  */
bool RainbruRPG::OgreGui::
compMclItemAsc( MultiColumnListItem* it1, MultiColumnListItem* it2){
  int col = MultiColumnList::mCurrentSortedColumn;

  return it1->getString(col) < it2->getString(col);
}

/** Descendant order sort of MultiColumnList item
  *
  * This is a comparison function used by MulticolumnList::setSort()
  * when it is used in parameter of std;;sort call.
  *
  * \param it1, it2 Items to compare
  *
  */
bool RainbruRPG::OgreGui::
compMclItemDesc( MultiColumnListItem*it1, MultiColumnListItem* it2){
  int col = MultiColumnList::mCurrentSortedColumn;

  return it1->getString(col) > it2->getString(col);
}
// End of global functions implementation



/** Constructor
  *
  * \param dim    The dimensions in pixels
  * \param parent The parent window
  * \param sid    The skin 
  *
  */
RainbruRPG::OgreGui::MultiColumnList::
MultiColumnList(Vector4 dim, BetaGUI::Window* parent, 
		RainbruRPG::OgreGui::OgreGuiSkinID sid):
  Widget(dim, (Widget*)parent, sid),
  mHeaderHeight(20),
  mAbsCorners(),
  selectedColumn(NULL),
  mouseOveredItem(NULL),
  selectedItem(NULL),
  mLastColumnRight(0),
  mCurrentSortPolicy(MCS_NONE),
  mToolTipText("Long time click to move column"),
  mDrawToolTip(false),
  mMovingColumn(-1)
{
  mSkin = SkinManager::getSingleton().getSkin(this);
  makeCorners();
}

/** Draws the widget
  *
  * \param qr The QuadRenderer used to draw
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::draw(QuadRenderer* qr){
  if (visible){
    if (geometryDirty){
      makeCorners();
      geometryDirty=false;
    }
    
    mSkin->drawMultiColumnList( qr, this );

    if (mDrawToolTip){
      mSkin->drawToolTip( qr, mToolTipDim, mToolTipText );
    }
  }
}

/** Add a new column
  *
  * \param vCaption The caption of this column
  * \param vWidth   The width in pixels
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::
addColumn( const std::string& vCaption, int vWidth ){
  
  MultiColumnListColumn* col=new MultiColumnListColumn(vCaption, vWidth);
  // Registering column index and parent
  col->setParentIndex(this, mColumnList.size());
  mColumnList.push_back(col);
  makeCorners();
}

/** Get the list of column
  *
  * \return The columns list as a onstant
  *
  */
const tMultiColumnListColumnList& RainbruRPG::OgreGui::MultiColumnList::
getColumnList(void){
  return mColumnList;
}

/** Pre-compute corners 
  *
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::makeCorners(void){
  mAbsCorners.top    = corners.top + parent->getTop();
  mAbsCorners.left   = corners.left + parent->getLeft();
  mAbsCorners.bottom = corners.bottom + parent->getTop();
  mAbsCorners.right  = corners.right + parent->getLeft();
  
  // compute mLastColumnRight
  mLastColumnRight=mAbsCorners.left;
  tMultiColumnListColumnList::const_iterator iter;
  for (iter=mColumnList.begin(); iter!=mColumnList.end(); iter++){
    mLastColumnRight+=(*iter)->getWidth();
  }
}

/** Get the absolute corners
  *
  * \return The corners from the screen top/left corner
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::MultiColumnList::
getAbsoluteCorners(void){
  return mAbsCorners;
}

/** Get the height of the header in pixels
  *
  * \return The header's height in pixels
  *
  */
int RainbruRPG::OgreGui::MultiColumnList::getHeaderHeight(void)const{
  return mHeaderHeight;
}

/** Get the list of items
  *
  * \return The item list
  *
  */
const tMultiColumnListItemList& RainbruRPG::OgreGui::MultiColumnList::
getItemList(void){
  if (mCurrentSortPolicy==MCS_NONE){
    return mItemList;
  }
  else{
    return mSortedItemList;
  }
}

/** Adds an item
  *
  * \param it The item to add
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::addItem( MultiColumnListItem* it ){
  mItemList.push_back( it );
  mSortedItemList.push_back( it );
}

/** Get the right position of the last column
  *      
  * This value is used to draw mouse-overed or selected item background.
  *
  * \note This value is computed in makeCorners
  *
  */
int RainbruRPG::OgreGui::MultiColumnList::getLastColumnRight(void)const{
  return mLastColumnRight;
}

/** Handles mouse events
  *
  * \param px, py The mouse position
  * \param event  The mouse event
  *
  */
bool RainbruRPG::OgreGui::MultiColumnList::
injectMouse( unsigned int px, unsigned int py, const MouseEvent& event){
  if (mCurrentSortPolicy == MCS_NONE){
    injectMouse( px, py, event, mItemList );
  }
  else{
    injectMouse( px, py, event, mSortedItemList );
  }
}

void RainbruRPG::OgreGui::MultiColumnList::
setSort(int vIndex, tMultiColumnListColumnSortPolicy vPolicy){
  if (mCurrentSortedColumn != -1 && mCurrentSortedColumn!=vIndex){
    mColumnList[mCurrentSortedColumn]->resetSort();
  }

  MultiColumnList::mCurrentSortedColumn = vIndex;
  mCurrentSortPolicy   = vPolicy;

  if (mCurrentSortPolicy == MCS_ASCENDANT){
    std::sort(mSortedItemList.begin(), mSortedItemList.end(), &compMclItemAsc);
  }
  else if (mCurrentSortPolicy == MCS_DESCENDANT){
    std::sort(mSortedItemList.begin(), mSortedItemList.end(), &compMclItemDesc);
  }
}

void RainbruRPG::OgreGui::MultiColumnList::
handleToolTip(unsigned int px, unsigned int py){
  px += 25;
  py += 30;

  mToolTipDim.left   = px;
  mToolTipDim.top    = py;
  mToolTipDim.right  = px+150;
  mToolTipDim.bottom = py+40;
  mDrawToolTip = true;
}

// return -1 if no column is moving
int RainbruRPG::OgreGui::MultiColumnList::getMovedColumnIndex(void)const{
  return mMovingColumn;
}


bool RainbruRPG::OgreGui::MultiColumnList::
injectMouse( unsigned int px, unsigned int py, const MouseEvent& event,
	     tMultiColumnListItemList vItemList ){

  bool LMB=event.isLeftMouseButtonPressed();

  tMultiColumnListColumnList::iterator colIter;
  int colLeft, colRight;

  unsigned int colIndex=0;

  if (px > corners.left && px < corners.right ){
    if (py > corners.top && py < corners.top + mHeaderHeight ){
      colLeft=corners.left;

      for (colIter=mColumnList.begin(); colIter!=mColumnList.end(); colIter++){
	colRight=colLeft+(*colIter)->getWidth();
	if (px > colLeft && px < colRight ){
	  // We are in column header
	  (*colIter)->setSelected(true);
	  if (mouseOveredItem )  mouseOveredItem->setMouseOver(false);
	  if (selectedColumn && selectedColumn!=(*colIter) ){
	    selectedColumn->setSelected(false);
	  }
	  selectedColumn=(*colIter);

	  if (event.isLeftButtonClick()){
	    LOGI("isLeftButtonClick=true");
	    selectedColumn->toggleSort();
	  }
	  else if (event.isLeftButtonLongClick()){
	    // Moving column
	    LOGCATS("Moving column ");
	    LOGCATI(colIndex);
	    LOGCAT();
	    mDrawToolTip=false;
	    mMovingColumn=colIndex;
	  }
	  else if (!LMB){
	    handleToolTip(px, py);
	  }
	  return true;
	}
	colLeft=colRight;
	colIndex++;
      }

    }
    else{
      mDrawToolTip=false;
      // An item should be selected
      int a=py - (corners.top + mHeaderHeight);
      int itemIdx=(int)a/20;

      if ( itemIdx < vItemList.size() ){
	if (LMB){
	  // Select item
	  if (selectedItem) selectedItem->setSelected(false);
	  selectedItem=vItemList[itemIdx];
	  selectedItem->setSelected(true);
	  // de-mouseover item
	  if (mouseOveredItem == selectedItem){
	    mouseOveredItem->setMouseOver(false);
	    mouseOveredItem=NULL;
	  }
	  return true;
	}
	else{
	  // Mouse over item
	  vItemList[itemIdx]->setMouseOver(true);
	  if (selectedColumn) selectedColumn->setSelected(false);
	  if (mouseOveredItem && mouseOveredItem!=vItemList[itemIdx]){
	    mouseOveredItem->setMouseOver(false);
	  }
	  mouseOveredItem=vItemList[itemIdx];
	}
	return true;
      }
    }
  }


  if (selectedColumn) selectedColumn->setSelected(false);
  if (mouseOveredItem )  mouseOveredItem->setMouseOver(false);
  return false;


}

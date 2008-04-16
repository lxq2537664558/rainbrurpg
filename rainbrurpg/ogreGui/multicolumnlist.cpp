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
#include "gameengine.h"
#include "tooltip.h"
#include "hscrollbar.h"
#include "vscrollbar.h"
#include "bggui.h"
#include "bgwindow.h"
#include "drawingdevsettings.h"

#include <logger.h>
#include <quadrenderer.h>

#include <OgreColourValue.h>

#define VSB_YPOS 2

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
  * \param vParent The parent window
  * \param sid    The skin 
  *
  */
RainbruRPG::OgreGui::MultiColumnList::
MultiColumnList(Vector4 dim, BetaGUI::Window* vParent, 
		RainbruRPG::OgreGui::OgreGuiSkinID sid):
  Widget(dim, (Widget*)vParent, sid),
  mHeaderHeight(20),
  mAbsCorners(),
  selectedColumn(NULL),
  mouseOveredItem(NULL),
  selectedItem(NULL),
  mLastColumnRight(0),
  mCurrentSortPolicy(MCS_NONE),
  mMovingColumn(-1),
  mToolTip(NULL),
  mMouseXDev(0),
  mResizedColumnIndex(-1),
  mResiedColumnRightPos(0),
  mVScrollBar(NULL),
  mHScrollBar(NULL),
  mGui(NULL)
{
  mSkin = SkinManager::getSingleton().getSkin(this);
  mGui = GameEngine::getSingleton().getOgreGui();
  LOGA( mGui, "GUI pointer is NULL, program should crash (segfault).");

  mToolTip=new ToolTip(Vector4(0, 0, 200, 50), 
		       "Long time click to move column. Right button for "
		       "contextual menu.",
		       vParent, sid);

  mDrawingDev = new DrawingDevSettings("MultiColumnList", 0, 0);
  mXDrawingDev = new DrawingDevSettings("MultiColumnList", 0, 0);

  setName("MultiColumnList");

  Vector4 sbDim( dim.z-16, VSB_YPOS, 14, dim.w-(VSB_YPOS + 18) );
  mVScrollBar=new VScrollBar(sbDim, parent);//, OSI_BETAGUI);
  //  this->addWidget(mVScrollBar);

  Vector4 sbDim2( 2, dim.w-16, dim.z-20, 14 );
  mHScrollBar=new HScrollBar(sbDim2, parent);
  //  this->addWidget(mHScrollBar);

  // Signals connection
  mHScrollBar->sigValueChanged.connect( sigc::mem_fun(this,
     &RainbruRPG::OgreGui::MultiColumnList::horizontalScrollBarValueChange));

  mVScrollBar->sigValueChanged.connect( sigc::mem_fun(this,
     &RainbruRPG::OgreGui::MultiColumnList::verticalScrollBarValueChange));


  makeCorners();
}

/** The destructor
  *
  */
RainbruRPG::OgreGui::MultiColumnList::~MultiColumnList(void){
  if (mVScrollBar){
    delete mVScrollBar;
    mVScrollBar=NULL;
  }

  if (mHScrollBar){
    delete mHScrollBar;
    mHScrollBar=NULL;
  }
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


    mToolTip->draw( qr );
    mVScrollBar->draw( qr );
    mHScrollBar->draw( qr );
  }
}

/** Add a new column
  *
  * \param vCaption The caption of this column
  * \param vWidth   The width in pixels
  *
  * \return The newly created column
  *
  */
MultiColumnListColumn* RainbruRPG::OgreGui::MultiColumnList::
addColumn( const std::string& vCaption, int vWidth ){
  
  MultiColumnListColumn* col=new MultiColumnListColumn(vCaption, vWidth);
  // Registering column index and parent
  col->setParentIndex(this, mColumnList.size());
  mColumnList.push_back(col);
  makeCorners();
  return col;
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
  handleScrollBarsVisibility();
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

  handleScrollBarsEvent( px, py, event, parent);
}

/** Set the sort of this list
  * 
  * With one call, we can set the column index and the policy we must apply.
  *
  * \param vIndex  The index of the column
  * \param vPolicy The sort policy
  *
  */
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

/** Move and show the tooltip
  *
  * \param px, py The mouse position
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::
handleToolTip(unsigned int px, unsigned int py){
  mToolTip->move( px + 25, py + 30 );
  mToolTip->show();
  
}

/** Get the index of the column we are moving 
  *
  * \return -1 if no column is moving
  *
  */
int RainbruRPG::OgreGui::MultiColumnList::getMovedColumnIndex(void)const{
  return mMovingColumn;
}

/** Handles mouse events on the given item list
  *
  * This function is used in sorted or unsorted item list according to
  * the mCurrentSortPolicy value.
  *
  * \param px, py    The mouse position
  * \param event     The mouse event
  * \param vItemList The item list we handle events for
  *
  * \return \c true if the event is used
  *
  */
bool RainbruRPG::OgreGui::MultiColumnList::
injectMouse( unsigned int px, unsigned int py, const MouseEvent& event,
	     tMultiColumnListItemList vItemList ){

  // Move the ToolTip, even outside the Widget if it is in transition
  if ( mToolTip->inTransition() )
    mToolTip->move( px + 25, py + 30 );


  bool LMB=event.isLeftMouseButtonPressed();


  // Resizing column
  if (mResizedColumnIndex!=-1){
    if (event.isLeftMouseButtonPressed()){
      mGui->setFocusedWidget(this);
      mColumnList[mResizedColumnIndex]
	->resize((px - mResiedColumnRightPos) + mMouseXDev);
      computeLastColumnRight();
      handleScrollBarsVisibility();
      makeCorners(); // To recompute VScrollBar's height
      return true;
    }
    else{
      LOGI("aze");
      mResizedColumnIndex=-1;
      mMouseXDev=0;
      mGui->disableFocusedWidget();
      return true;
    }
  }

  // Handling column headers events
  tMultiColumnListColumnList::iterator colIter;
  int colLeft, colRight;

  unsigned int colIndex=0;
  if (px > corners.left && px < corners.right ){
    if (py > corners.top && py < corners.top + mHeaderHeight ){
      colLeft=corners.left;

      for (colIter=mColumnList.begin(); colIter!=mColumnList.end(); colIter++){
	colRight=colLeft+(*colIter)->getWidth();
	// Resizing column
	if ( (px > colRight - COLUMN_RESIZE_SENSITIVITY) &&
	     (px < colRight + COLUMN_RESIZE_SENSITIVITY)){
	  if (LMB){
	    if (mResizedColumnIndex==-1 && mMovingColumn==-1){
	      mGui->setFocusedWidget(this);
	      mResizedColumnIndex=colIndex;
	      mMouseXDev = colRight - px;
	      mResiedColumnRightPos = colLeft;
	      return true;
	    }
	  }
	  else{
	    mResizedColumnIndex=-1;
	    return false;
	  }
	}
	else if ((px > colLeft + COLUMN_RESIZE_SENSITIVITY) && 
	    px < colRight - COLUMN_RESIZE_SENSITIVITY ){
	  // We are in column header, select it only if no column are moving
	  if (mMovingColumn == -1){
	    (*colIter)->setSelected(true);
	  }

	  if (mouseOveredItem )  mouseOveredItem->setMouseOver(false);
	  if (selectedColumn && selectedColumn!=(*colIter) ){
	    selectedColumn->setSelected(false);
	  }
	  selectedColumn=(*colIter);

	  if (event.isLeftButtonClick()){
	    mToolTip->hide();
	    selectedColumn->toggleSort();
	  }
	  else if (event.isLeftButtonLongClick()){
	    // Moving column
	    mToolTip->hide();
	    // Moving column only if no column is moving
	    if (mMovingColumn == -1){
	      mMovingColumn=colIndex;
	      mGui->setFocusedWidget(this);
	    }

	    handleMovingColumn(px, py, colLeft, colRight, colIndex);
	  }
	  else if (!LMB){
	    handleToolTip(px, py);
	    mMovingColumn=-1;
	    mGui->disableFocusedWidget();
	  }
	  return true;
	}
	colLeft=colRight;
	colIndex++;
      }

    }
    else{
      mToolTip->hide();
      // An item should be selected
      int a=py - (corners.top + mHeaderHeight);
      int itemIdx=(int)a/20;

      if ( itemIdx < vItemList.size() ){
	if (event.isLeftButtonClick()){
	  // Select item
	  if (selectedItem && selectedItem!=vItemList[itemIdx]){ 
	    selectedItem->setSelected(false);
	  }
	  selectedItem=vItemList[itemIdx];
	  selectedItem->toggleSelection();
	  // de-mouseover item
	  if (mouseOveredItem == selectedItem && selectedItem->isSelected()){
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
  mToolTip->hide();
  //  mMovingColumn=-1;
  return false;
}

/** Handling of the moving column
  *
  * Here, we know that a column is moving (mouse left button
  * long clik) and we check if we need a column swap.
  *
  * \param vPx, vPy  The mouse position
  * \param vColLeft  The left position of the moving column
  * \param vColRight The right position of the moving column
  * \param vColIndex The index of the moving column
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::
handleMovingColumn(int vPx, int vPy, int vColLeft, int vColRight, 
		   int vColIndex){

  // Limit clipping when moving a little column to a large one
  if (mMovingColumn < mColumnList.size()-1){
    int leftColDiff = mColumnList[mMovingColumn+1]->getWidth() - 
      mColumnList[mMovingColumn]->getWidth();
    if (leftColDiff>0){
      vColLeft += (leftColDiff/2);
    }
  }
  if (mMovingColumn > 1){
    int RightColDiff = mColumnList[mMovingColumn-1]->getWidth() - 
      mColumnList[mMovingColumn]->getWidth();
    if (RightColDiff>0){
      vColRight -= (RightColDiff/2);
    }
  }

  // Moving the column
  if ((vPx > vColLeft &&  vColIndex > mMovingColumn) ||
      (vPx < vColRight && vColIndex < mMovingColumn)){

    // Swapping column
    MultiColumnListColumn* item=mColumnList[vColIndex];
    mColumnList[vColIndex]=mColumnList[mMovingColumn];
    mColumnList[mMovingColumn]=item;

    // Swapping item's column
    tMultiColumnListItemList::iterator iter;
    for (iter=mItemList.begin(); iter!=mItemList.end(); iter++){
      (*iter)->swapColumns( mMovingColumn, vColIndex );
    }

    // The moving column doesn't change
    mMovingColumn=vColIndex;

  }
}

/** The horizontal value slot
  *
  * This function is connected to the scrollbar value changed signal.
  *
  * \param vValue The new scrollbar value
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::
horizontalScrollBarValueChange(int vValue){
  mDrawingDev->setDevX( vValue );
  mXDrawingDev->setDevX( vValue );
}

/** The vertical value slot
  *
  * This function is connected to the scrollbar value changed signal.
  *
  * \param vValue The new scrollbar value
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::
verticalScrollBarValueChange(int vValue){
    mDrawingDev->setDevY( vValue );
}

/** Is the horizontal scrollbar needed
  *
  * \return \c true if we need to draw horizontal scrollbar
  *
  */
bool RainbruRPG::OgreGui::MultiColumnList::isHorizontalScrollbarNeeded(void){
  if (mLastColumnRight > (corners.right - corners.left)){
    return true;
  }
  else{
    return false;
  }
}

/** Is the vertical scrollbar needed
  *
  * \return \c true if we need to draw vertical scrollbar
  *
  */
bool RainbruRPG::OgreGui::MultiColumnList::isVerticalScrollbarNeeded(void){
  unsigned int itemHeight;
  itemHeight = mHeaderHeight;
  itemHeight += (mItemList.size() * 20);
  
  if (itemHeight > (corners.bottom - corners.top)){
    return true;
  }
  else{
    return false;
  }
  
}

/** Changes the scrollbars visibility according to our needs
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::handleScrollBarsVisibility(void){
  mHScrollBar->setVisible(isHorizontalScrollbarNeeded());
  mVScrollBar->setVisible(isVerticalScrollbarNeeded());
}

/** Compute the absolute right position of the last column
  *
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::computeLastColumnRight(){
  mLastColumnRight=mAbsCorners.left;
  tMultiColumnListColumnList::const_iterator iter;
  for (iter=mColumnList.begin(); iter!=mColumnList.end(); iter++){
    mLastColumnRight+=(*iter)->getWidth();
  }
}

/** Pre-compute corners and other positions 
  *
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::makeCorners(void){
  mAbsCorners.top    = corners.top + parent->getTop();
  mAbsCorners.left   = corners.left + parent->getLeft();
  mAbsCorners.bottom = corners.bottom + parent->getTop();
  mAbsCorners.right  = corners.right + parent->getLeft();
  
  // compute mLastColumnRight
  computeLastColumnRight();

  // Set scrollbar visible (or not)
  handleScrollBarsVisibility();

  // Moves scrollbars
  mVScrollBar->move( corners.right - 16, corners.top 
		     + mHeaderHeight +2 );
  mHScrollBar->move( corners.left + 2, corners.bottom - 16 );

  // Resize scrollbars
  unsigned int vScrollHeight = (corners.bottom - corners.top) 
    - mHeaderHeight - 4;
  if (mHScrollBar->isVisible()){
    vScrollHeight -= mHScrollBar->getHeight();
  }
  mVScrollBar->setHeight( vScrollHeight );  

  unsigned int hScrollWidth = (corners.right - corners.left) -4;
  if (mVScrollBar->isVisible()){
    hScrollWidth -= mVScrollBar->getWidth();
  }
  mHScrollBar->setWidth( hScrollWidth );  

  // Computing scissor rectangles
  mItemsScissorRectangle=mAbsCorners;
  mItemsScissorRectangle.bottom-=2;
  mItemsScissorRectangle.top+=mHeaderHeight;

  mHeadersScissorRectangle=mAbsCorners;
  mHeadersScissorRectangle.top+=2;
  mHeadersScissorRectangle.bottom = mAbsCorners.top + mHeaderHeight - 2;

}

/** Get the scissor rectangle used when drawing items 
  *
  * \return The clip region used to draw items
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::MultiColumnList::
getItemsScissorRectangle(void)const{
  return mItemsScissorRectangle;
}

/** Get the drawing dev settings for items
  *
  * \return Drawing dev settings object pointer
  *
  */
DrawingDevSettings* RainbruRPG::OgreGui::MultiColumnList::
getDrawingDevSettings(void){
  return mDrawingDev;
}

/** Handles the scrollbars events
  *
  * \param px, py  The mouse pointer position
  * \param event   The mouse event object
  * \param vParent The MultiColumnList's parent
  *
  * \return \c true if the event is used, otherwise returns \c false
  *
  */
bool RainbruRPG::OgreGui::MultiColumnList::
handleScrollBarsEvent(unsigned int px, unsigned int py,  
		      const MouseEvent& event, Widget* vParent){
  bool hEvent=mHScrollBar->injectMouse( px, py, event );
  if (hEvent) return true;

  return mVScrollBar->injectMouse( px, py, event );
}

/** Get the drawing dev settings for headers
  *
  * \return Drawing dev settings object pointer
  *
  */
DrawingDevSettings* RainbruRPG::OgreGui::MultiColumnList::
getHeaderDrawingDevSettings(void){
  return mXDrawingDev;
}

/** Get the scissor rectangle used when drawing column headers 
  *
  * \return The clip region used to headers
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::MultiColumnList::
getHeadersScissorRectangle(void)const{
  return mHeadersScissorRectangle;
}


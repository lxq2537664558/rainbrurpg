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

#include "wdmulticolumnlist.h"

#include "multicolumnlist.h"
#include "multicolumnlistitem.h"
#include "multicolumnlistcell.h"
#include "multicolumnlistcolumn.h"
#include "multicolumnlistdebugsettings.h"

#include "quadrenderer.h"
#include "textsettings.h"
#include "bgwindow.h"

#include <logger.h>


/** The drawer constructor 
  *
  */
RainbruRPG::OgreGui::wdMultiColumnList::wdMultiColumnList():
  WidgetDrawer(),
  mWidgetParent(NULL),
  wasInit(false),
  tsMclColumnHeader(NULL),
  tsMclTextCell(NULL),
  mMclBorderColor(0.7f, 0.7f, 0.7f),
  itemBGColor( 0.4f, 0.8f, 0.4f ),
  selItemBGColor( 0.8f, 0.4f, 0.4f ),
  mDebugSettings(NULL),
  mCurrentMcl(NULL)
{
  // Debug settings
  mDebugSettings =  new MultiColumnListDebugSettings("MCL.ServerList", 4);

  // Text settings
  tsMclColumnHeader=new TextSettings( "Iconiv2.ttf",  10, 1.0f, 1.0f, 1.0f );
  tsMclTextCell=new TextSettings( "Iconiv2.ttf",  10, 1.0f, 1.0f, 1.0f );

  tsMclColumnHeader->setHorizontalAlignment(HAT_CENTER);
  tsMclColumnHeader->setVerticalAlignment(VAT_CENTER);

  // Texture settings
  mMclColumnNoSort=TextureManager::getSingleton()
   .load("mcl.nosort.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mMclColumnAscSort=TextureManager::getSingleton()
   .load("mcl.ascsort.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mMclColumnDescSort=TextureManager::getSingleton()
   .load("mcl.descsort.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

}
 
/** The draw destructor
  *
  */
RainbruRPG::OgreGui::wdMultiColumnList::~wdMultiColumnList(){
  delete mDebugSettings;
  mDebugSettings = NULL;

  delete tsMclColumnHeader;
  tsMclColumnHeader = NULL;

  delete tsMclTextCell;
  tsMclTextCell = NULL;

  mCurrentMcl = NULL;
}

/** Initializes the members depending on MultiColumnList
  *
  * This function is called from \ref draw() only once. It is not
  * called again when MultiColumnList geometry is dirty. Please see
  * \ref preDrawingComputation() if you need it.
  *
  * \param mcl The MultiColumnList to draw
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::init(MultiColumnList* mcl){
  mWidgetParent = mcl->getParent();
  wasInit = true;
}

/** Draw a cell of an item
  * 
  * \param qr    The QuadRenderer used to draw
  * \param vCell The Cell to be drawn
  * \param vRect The rectangle where we must draw the cell
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
drawOneItemCell(QuadRenderer* qr, MultiColumnListCell* vCell,
		const Rectangle& vRect){

  mDebugSettings->debugCell( qr, mCurrentMcl, vCell );


  if (vCell->isText()){
    qr->drawText(tsMclTextCell, vCell->getText(), vRect, true);
  }
}


/** Draws all the headers
  *
  * \param qr            The QuadRenderer used to draw
  * \param mcl           The MultiColumnList to draw
  * \param vMovingColumn The index of the column we are moving
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
drawAllHeaders(QuadRenderer* qr, MultiColumnList* mcl, int vMovingColumn){
  // Drawing columns header
  tMultiColumnListColumnList colList=mcl->getColumnList();
  tMultiColumnListColumnList::const_iterator iter;

  Ogre::Rectangle sr=qr->getClipRegion();

  qr->addDrawingDev(mcl->getHeaderDrawingDevSettings());
  
  int x=mMclAbsCorners.left;
  unsigned int colIndex=0;

  for(iter = colList.begin();iter != colList.end(); iter++){
    if ((*iter)->isVisible()){
      qr->setUseParentScissor(false);
      qr->setScissorRectangle(mcl->getHeadersScissorRectangle());
      qr->setUseParentScissor(true);

      if (colIndex == vMovingColumn){
	qr->enableGhost();
      }
  
      drawOneHeader(qr, (*iter), x);

      if (colIndex == vMovingColumn || colIndex == vMovingColumn-1){
	qr->disableGhost();
      }


     } // is column is visible
    x += (*iter)->getWidth();
    colIndex++;
  }
  
  qr->removeDrawingDev(mcl->getHeaderDrawingDevSettings());

}

/** Computation of values only if MultiColumnList's geometry was dirty
  *
  * This function is used to speed up the drawing. It is automatically
  * called from \ref soBetaGui::drawMultiColumnList when the geometryDirty
  * flag of the MultiColumnList is true before the drawing. You know the 
  * Widget moved or was resized recently.
  *
  * \param mcl The MultiColumnList that moved or resized
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
preDrawingComputation(MultiColumnList* mcl){
  mMclAbsCorners = mcl->getAbsoluteCorners();
  mMclHeaderBottomLine = mMclAbsCorners.top+mcl->getHeaderHeight();

  mColumnCaption=Ogre::Rectangle(mMclAbsCorners);
  mColumnCaption.bottom=mColumnCaption.top + mcl->getHeaderHeight();
  maxMclRight = mMclAbsCorners.right;
}

/** Draw the boder of the widget
  *
  * We use mMclAbsCorners to draw it.
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::drawBorder(QuadRenderer* qr){

  qr->drawRectangleLines(mMclAbsCorners, mMclBorderColor);

  //Header bottom line
  qr->drawLine( mMclAbsCorners.left, mMclHeaderBottomLine, 
		mMclAbsCorners.right,mMclHeaderBottomLine, 
		mMclBorderColor ); 

}

/** Draw a column header
  *
  * \param qr      The QuadRenderer used to draw
  * \param vHeader The header to be drawn
  * \param xLeft   The X position of the left line (in absolute position, 
  *                in pixels)
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
drawOneHeader(QuadRenderer* qr, MultiColumnListColumn* vHeader, int xLeft){
  

  int y1=mMclAbsCorners.top;
  int y2=mMclAbsCorners.bottom;

  Ogre::Rectangle headerBG, sortSignRect;
  Ogre::ColourValue headerBGColor( 0.4f, 0.4f, 0.8f );
  Ogre::ColourValue headerBGColorS( 0.6f, 0.6f, 0.9f );
  headerBG.top    = mColumnCaption.top    + HEADER_BG_SPACE;
  headerBG.bottom = mColumnCaption.bottom - HEADER_BG_SPACE;

  int xSortSign=((mColumnCaption.bottom-mColumnCaption.top)/2)-7;

  sortSignRect.top    = headerBG.top+xSortSign;
  sortSignRect.bottom = sortSignRect.top+12;

  // Header background and caption
  mColumnCaption.left  = xLeft;
  mColumnCaption.right = xLeft + vHeader->getWidth();
  headerBG.left   = mColumnCaption.left   + HEADER_BG_SPACE;
  headerBG.right  = mColumnCaption.right  - HEADER_BG_SPACE;
  
  sortSignRect.left  = headerBG.right - 14;
  sortSignRect.right = sortSignRect.left + 12;
  
  mColumnCaption.right-=16; // Remove sortSignRect size
  
  
  if (vHeader->isSelected()){
    qr->drawFilledRectangle( headerBG, headerBGColorS );
  }
  else{
    qr->drawFilledRectangle( headerBG, headerBGColor );
  }
  
  // Drawing header caption
  qr->drawText(tsMclColumnHeader, vHeader->getCaption(), 
	       mColumnCaption, true);
  
  // Drawing sort sign
  qr->setBlendMode(QBM_ALPHA);
  switch(vHeader->getSortPolicy()){
  case MCS_NONE:
    qr->setTexturePtr(mMclColumnNoSort);
    break;
  case MCS_ASCENDANT:
    qr->setTexturePtr(mMclColumnAscSort);
    break;
  case MCS_DESCENDANT:
    qr->setTexturePtr(mMclColumnDescSort);
    break;
  }
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(sortSignRect);
  
  
  // Drawing left line : we need to disable the scissor rectangle
  xLeft+=vHeader->getWidth();
  qr->setUseParentScissor(false);
  //  Rectangle parentWindowAbsCorners = mcl->getWindowParent()->getCorners();
  //  qr->setScissorRectangle(parentWindowAbsCorners);
  //  Avoid left line to get more to the right to the mcl right corners
  if ( xLeft < mMclAbsCorners.right ){
    qr->drawLine( xLeft, y1, xLeft, y2, mMclBorderColor );
  }
  qr->setUseParentScissor(true);
  
  
  qr->reset();

}

/** Draw one item in the list
  *
  * \param qr            The QuadRenderer object used to draw
  * \param vItem         The item to be drawn
  * \param vRect         The rectangle where the item is drawn
  * \param vColList      The MultiColumnList's column list
  * \param vMovingColumn The column we are currently moving
  * \param vDebug        Should we debug this drawing ?
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
drawOneItem(QuadRenderer* qr,MultiColumnListItem* vItem,const Rectangle& vRect,
	    const tMultiColumnListColumnList& vColList, int vMovingColumn,
	    bool vDebug){

  mDebugSettings->debugItem( qr, mCurrentMcl, vItem );

  int colId=0;
  tMultiColumnListCellList mil=vItem->getCellList();
  tMultiColumnListCellList::const_iterator mii;

  Rectangle itemRect(vRect);

  if (vItem->isSelected()){
    qr->drawFilledRectangle( vRect, selItemBGColor );
  }
  else if (vItem->isMouseOver()){
    qr->drawFilledRectangle( vRect, itemBGColor );
  }
  else if (vItem->inTransition()){
    // Using item's alpha
    float itemAlpha=vItem->getMouseOverAlpha();
    float currentAlpha = qr->setTempAlpha(itemAlpha);
    qr->drawFilledRectangle( vRect, itemBGColor );
    qr->setAlpha(currentAlpha);
  }
  
  // Drawing cells (we are using parent scissor)
  for (mii=mil.begin(); mii != mil.end(); mii++){
    if (vColList[colId]->isVisible()){
      if (colId == vMovingColumn){
	qr->enableGhost();
      }
      
      drawOneItemCell(qr, (*mii), itemRect  );
      
      itemRect.left+=vColList[colId]->getWidth();
      if (colId+1 < vColList.size()){
	itemRect.right=itemRect.left + vColList[colId+1]->getWidth();
      }
      else{
	itemRect.right = mColumnCaption.right -2;
      }
      
      
      if (colId == vMovingColumn){
	qr->disableGhost();
      }
      
    } // If column is visible
    colId++;
  } // For each cell in multicolumn list item
  
}

/** Draw the givenh MultiColumnList
  *
  * \param qr  The QuadRenderer used to draw
  * \param mcl The MultiColumnList to draw
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
draw(QuadRenderer* qr, MultiColumnList* mcl){

  mCurrentMcl = mcl;

  // Test initialization and init if needed
  // Call preDrawingComputation cause it is first drawing
  if (!wasInit){
    init(mcl);
    preDrawingComputation( mcl );
  }

  LOGA(mWidgetParent, "MultiColumnList parent poiner is NULL");

  // Get event driven values (cannot be got with preDrawingComputation)
  int movingColumn=mcl->getMovedColumnIndex();

  // Draws multicolumnlist
  drawBorder(qr);
  drawAllHeaders(qr, mcl, movingColumn);
  drawAllItems(qr, mcl, movingColumn);

  // Set the scissor rectangle as the parent window corners
  // It is used because, as the next widgets drawn are the ScrollBars
  // (please see MultiColumnList::draw() implementation), they will
  // be cut off be the parent scissor setting (the Window corners)
  qr->setUseParentScissor(false);
  qr->setScissorRectangle(mWidgetParent->getCorners());
  qr->setUseParentScissor(true);  

  mDebugSettings->reset();

}

/** Draws all items
  *
  * \param qr            The QuadRenderer ued to draw
  * \param mcl           The MultiColumnList
  * \param vMovingColumn The column currently moving
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
drawAllItems(QuadRenderer* qr, MultiColumnList* mcl, int vMovingColumn){
  // drawing items
  // Saves current parent scissor settings
  tMultiColumnListColumnList colList=mcl->getColumnList();
  Ogre::Rectangle sr=qr->getClipRegion();

  qr->addDrawingDev(mcl->getDrawingDevSettings());
  tsMclColumnHeader->setHorizontalAlignment(HAT_LEFT);

  tMultiColumnListItemList itemList=mcl->getItemList();
  tMultiColumnListItemList::const_iterator ili;

  Ogre::Rectangle itemRect(mMclAbsCorners);
  itemRect.left=mMclAbsCorners.left+5;
  itemRect.top=mColumnCaption.top + mcl->getHeaderHeight()+ HEADER_BG_SPACE;
  itemRect.bottom=itemRect.top+20;
  itemRect.right=itemRect.left+colList[0]->getWidth();

  Ogre::Rectangle itemBG(mMclAbsCorners);
  itemBG.left=mMclAbsCorners.left+5;
  itemBG.top=mColumnCaption.top + mcl->getHeaderHeight()+ HEADER_BG_SPACE;
  itemBG.bottom=itemBG.top+20;
  itemBG.right=mcl->getLastColumnRight()-5;

  // The header bottom corners, used to avoid item drawing over the headers
  int itemTop =  mcl->getAbsoluteCorners().top + mcl->getHeaderHeight();
  Ogre::Rectangle itemScissorRect(mMclAbsCorners);
  if (itemScissorRect.top < itemTop) itemScissorRect.top = itemTop;

  // Drawing items
  for (ili = itemList.begin(); ili != itemList.end(); ili++){
    
    qr->setUseParentScissor(false);
    qr->setScissorRectangle(itemScissorRect);
    qr->setUseParentScissor(true);
    
    drawOneItem(qr, (*ili), itemBG, colList, vMovingColumn );

    itemRect.left=mMclAbsCorners.left+5;
    itemRect.right=itemRect.left+colList[0]->getWidth();
    itemRect.top+=20;
    itemRect.bottom=itemRect.top+20;
    itemBG.top+=20;
    itemBG.bottom=itemBG.top+20;
  }

  qr->setUseParentScissor(false);
  // Restore parent scissor
  qr->setScissorRectangle(sr);
  qr->setUseParentScissor(true);  
  qr->removeDrawingDev(mcl->getDrawingDevSettings());
}

/** Reset this drawer
  *
  * If you call this, preDrawingComputation() will be call next time draw()
  * is called.
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::reset(){
  wasInit=false;
}

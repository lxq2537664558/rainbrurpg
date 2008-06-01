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
#include "multicolumnlistcolumn.h"
#include "multicolumnlistitem.h"
#include "multicolumnlistcell.h"

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
  mMclBorderColor(0.7f, 0.7f, 0.7f)
{

  tsMclColumnHeader=new TextSettings( "Iconiv2.ttf",  10, 1.0f, 1.0f, 1.0f );
  tsMclColumnHeader->setHorizontalAlignment(HAT_CENTER);
  tsMclColumnHeader->setVerticalAlignment(VAT_CENTER);


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
  delete tsMclColumnHeader;
  tsMclColumnHeader = NULL;
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


/** Draw the givenh MultiColumnList
  *
  * \param qr  The QuadRenderer used to draw
  * \param mcl The MultiColumnList to draw
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
draw(QuadRenderer* qr, MultiColumnList* mcl){

  // Test initialization and init if needed
  if (!wasInit) init(mcl);
  LOGA(mWidgetParent, "MultiColumnList parent poiner is NULL");

  // Get event driven values (cannot be got with preDrawingComputation)
  int movingColumn=mcl->getMovedColumnIndex();

  // Draws multicolumnlist
  drawBorder(qr);
  drawAllHeaders(qr, mcl, movingColumn);


  // drawing items
  // Saves current parent scissor settings
  tMultiColumnListColumnList colList=mcl->getColumnList();
  Ogre::Rectangle sr=qr->getClipRegion();

  qr->addDrawingDev(mcl->getDrawingDevSettings());
  tsMclColumnHeader->setHorizontalAlignment(HAT_LEFT);

  tMultiColumnListItemList itemList=mcl->getItemList();
  tMultiColumnListItemList::const_iterator ili;

  tMultiColumnListCellList mil;
  tMultiColumnListCellList::const_iterator mii;
  Ogre::ColourValue itemBGColor( 0.4f, 0.8f, 0.4f );
  Ogre::ColourValue selItemBGColor( 0.8f, 0.4f, 0.4f );


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

  int colId=0;
  // Drawing items
  for (ili = itemList.begin(); ili != itemList.end(); ili++){
    
    qr->setUseParentScissor(false);
    qr->setScissorRectangle(itemScissorRect);
    qr->setUseParentScissor(true);
    
    if ((*ili)->isSelected()){
      qr->drawFilledRectangle( itemBG, selItemBGColor );
    }
    else if ((*ili)->isMouseOver()){
      qr->drawFilledRectangle( itemBG, itemBGColor );
    }
    else if ((*ili)->inTransition()){
      // Using item's alpha
      float itemAlpha=(*ili)->getMouseOverAlpha();
      float currentAlpha = qr->setTempAlpha(itemAlpha);
      qr->drawFilledRectangle( itemBG, itemBGColor );
      qr->setAlpha(currentAlpha);
    }

    // Drawing cells (we are using parent scissor)
    mil=(*ili)->getCellList();
    for (mii=mil.begin(); mii != mil.end(); mii++){
      if (colList[colId]->isVisible()){
	if ((*mii)->isText()){
	  
	  if (colId==movingColumn){
	    qr->enableGhost();
	  }
	  
	  // Limit item scissor to MCL parent right 
	  if (itemScissorRect.right > mWidgetParent->getRight() ){
	    itemScissorRect.right = mWidgetParent->getRight();
	  }

	  // Apply the same limit to the bottom
	  if (itemScissorRect.bottom > mWidgetParent->getBottom() ){
	    itemScissorRect.bottom = mWidgetParent->getBottom();
	  }
	  
	  // Setting scissor rectangle to avoid item caption to exeed
	  // left line X position
	  qr->setUseParentScissor(false);
	  qr->setScissorRectangle(itemScissorRect);
	  qr->setUseParentScissor(true);
	  
	  qr->drawText(tsMclColumnHeader, (*mii)->getText(), itemRect, true);
	  itemRect.left+=colList[colId]->getWidth();
	  if (colId+1 < colList.size()){
	    itemRect.right=itemRect.left + colList[colId+1]->getWidth();
	  }
	  else{
	    itemRect.right = mColumnCaption.right -2;
	  }
	  
	  itemScissorRect.right = itemRect.right - 5 
	    - qr->getDrawingDevXSum();

	  if (colId==movingColumn){
	    qr->disableGhost();
	  }
	  
	} // if cell is text
      } // If column is visible
      colId++;
    } // For each cell in multicolumn list item
    colId=0;
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
  qr->reset();

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
  LOGI("wdMultiColumnList::preDrawingComputation called");
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
  // Avoid left line to get more to the right to the mcl right corners
  if ( xLeft < mMclAbsCorners.right ){
    qr->drawLine( xLeft, y1, xLeft, y2, mMclBorderColor );
  }
  qr->setUseParentScissor(true);
  
  
  qr->reset();

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


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

/** \file wdmulticolumnlist.cpp
  * Implements a class used to draw MultiColumnList
  *
  */

#include "wdmulticolumnlist.h"

#include "multicolumnlist.h"
#include "multicolumnlistitem.h"
#include "multicolumnlistcell.h"
#include "multicolumnlistcolumn.h"
#include "multicolumnlistdebugsettings.h"

#include "drawingdevsettings.h"
#include "quadrenderer.h"
#include "textsettings.h"
#include "vscrollbar.h"
#include "hscrollbar.h"
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
  mCurrentMcl(NULL),
  parentHorizontalScrollbarValue(0),
  parentVerticalScrollbarValue(0),
  parentUnderTitleY(0),
  parentLeftX(0)
{
  // Debug settings
  // mDebugSettings =  new MultiColumnListDebugSettings("MCL.ServerList", 3, 1);
  mDebugSettings =  new MultiColumnListDebugSettings("MCL.MCLTestWindow",3,2);
  mDebugSettings->setDebugFlags(0x31);
  mDebugSettings->disable();

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
  * \warning The scissor rectangle should not be modified here. It is
  *          set in the \ref wdMultiColumnList::drawOneItem "drawOneItem()"
  *          function and should not be set at the item's cell content.
  *
  * \param qr    The QuadRenderer used to draw
  * \param vCell The Cell to be drawn
  * \param vRect The rectangle where we must draw the cell
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
drawOneItemCell(QuadRenderer* qr, MultiColumnListCell* vCell,
		const Rectangle& vRect){

  mDebugSettings->debugCell( qr, mCurrentMcl, vCell, vRect );
  if (vCell->isText()){
    // The false is to deactivate wordwrap
    qr->drawText(tsMclTextCell, vCell->getText(), vRect, false);
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

  // Handle parent window scrollbar value
  Rectangle hsc = mcl->getHeadersScissorRectangle();
  hsc.top -= parentVerticalScrollbarValue;
  if (hsc.top < parentUnderTitleY)
    hsc.top = parentUnderTitleY;

  // Do not cut to the MCL left value
  hsc.left -= parentHorizontalScrollbarValue;
  if (hsc.left < parentLeftX)
    hsc.left = parentLeftX;

  // Iterates through column list and draw items
  for(iter = colList.begin();iter != colList.end(); iter++){
    if ((*iter)->isVisible()){

      
      qr->setUseParentScissor(false);
      qr->setScissorRectangle(hsc);
      qr->setUseParentScissor(true);

      if (colIndex == vMovingColumn){
	qr->enableGhost();
      }
  
      drawOneHeader(qr, (*iter), x);

      /* v0.0.5-181 : Moving column bug
       *
       * The bug was that the column header after the moved one and the 
       * items (all) text was not drawn when moving column.
       *
       * The following IF statement was :
       * if (colIndex == vMovingColumn || colIndex == vMovingColumn-1)
       *
       * If we remove the last part of the statement, the bug disappears :
       * if (colIndex == vMovingColumn)
       *
       */
      if (colIndex == vMovingColumn){
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
  * This function is also responsible of the scissor rectangles computation.
  * By example to avoid window to override the window scissor rectangle.
  *
  * \param mcl The MultiColumnList that moved or resized
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
preDrawingComputation(MultiColumnList* mcl){
  mMclAbsCorners = mcl->getAbsoluteCorners();
  mMclDrawnCorners = mMclAbsCorners;

  // Compute right scissor if parent
  Window* parent = dynamic_cast<Window*>(mcl->getParent());
  if (mcl->getParent()){
    int pRight = parent->getRight();
    pRight -= (parent->isVerticalScrollbarVisible()) ?
      parent->getVerticalScrollbar()->getWidth() : 0;

    if (pRight < mMclAbsCorners.right){
      mMclAbsCorners.right = pRight;
    }
    else{
      // Makes the line drawn
      mMclDrawnCorners.right--;
    }
  }

  // Compute bottom scissor if parent
  if (mcl->getParent()){
    int pBottom = parent->getBottom();
    pBottom  -= (parent->isHorizontalScrollbarVisible()) ?
      parent->getHorizontalScrollbar()->getHeight() : 0;

    if (pBottom < mMclAbsCorners.bottom){
      mMclAbsCorners.bottom = pBottom;
    }
    else{
      // Makes the line drawn
      mMclDrawnCorners.bottom--;
    }
  }

  // Handle parent scrollbar values
  parentVerticalScrollbarValue  = parent->getVerticalScrollbar()->getValue();
  parentHorizontalScrollbarValue= parent->getHorizontalScrollbar()->getValue();

  mMclHeaderBottomLine = mMclAbsCorners.top+mcl->getHeaderHeight();

  mColumnCaption=Ogre::Rectangle(mMclAbsCorners);
  mColumnCaption.bottom=mColumnCaption.top + mcl->getHeaderHeight();
  maxMclRight = mMclAbsCorners.right;

  // Compute parentUnderTitleY : We use the Skin::getTitleBarHeight()
  // function as the title bar height depend on the skin
  parentUnderTitleY = parent->getTop();
  Skin* woeSkin = SkinManager::getSingleton().getSkin(parent);
  parentUnderTitleY += woeSkin->getTitleBarHeight();

  // Get the parent left value
  parentLeftX = parent->getLeft();
}

/** Draw the boder of the widget
  *
  * We use mMclAbsCorners to draw it.
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::drawBorder(QuadRenderer* qr){

  Rectangle borderScissor(mMclAbsCorners);

  borderScissor.top -= parentVerticalScrollbarValue;
  if (borderScissor.top < parentUnderTitleY)
    borderScissor.top = parentUnderTitleY;

  borderScissor.left -= parentHorizontalScrollbarValue;
  if (borderScissor.left < parentLeftX)
    borderScissor.left = parentLeftX;


  qr->setUseParentScissor(false);
  qr->setScissorRectangle(borderScissor);
  qr->setUseParentScissor(true);

  mMclAbsCorners.right--;
  mMclAbsCorners.bottom--;

  qr->drawRectangleLines(mMclDrawnCorners, mMclBorderColor);

  //Header bottom line
  qr->drawLine( mMclAbsCorners.left, mMclHeaderBottomLine, 
		mMclAbsCorners.right,mMclHeaderBottomLine, 
		mMclBorderColor ); 

}

/** Draw a column header
  *
  * \note The scissor rectangle setting when calling this function
  *       is important because it is used to cut the header caption.
  *       The scissor right value when calling this function \b must be the 
  *       parent window right one.
  *
  * \param qr      The QuadRenderer used to draw
  * \param vHeader The header to be drawn
  * \param xLeft   The X position of the left line (in absolute position, 
  *                in pixels)
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
drawOneHeader(QuadRenderer* qr, MultiColumnListColumn* vHeader, int xLeft){
  
  // We get the right scissor point to cut header caption to it if needed
  int currentScissorRight = qr->getClipRegion().right;

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
  
  // Drawing sort sign
  //
  // The sort sign must be drawn *before* the header caption because
  // otherwise, the sortsign can be drawn outside the window
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
  qr->setScissorRectangle(sortSignRect);
  qr->drawRectangle(sortSignRect);

  // Drawing header caption
  //
  // Setting wordwrap to false prevent the header text to fall down when
  // the header width is too small to show the text entirely

  // We draw header caption only if needed
  if (mColumnCaption.left < currentScissorRight){
    // Cut the drawing to the current scissor if needed
    if (mColumnCaption.right > currentScissorRight){
      mColumnCaption.right = currentScissorRight;
    }

    // Handle the scissor deviation because QuadRenderer do not apply
    // DrawingDev to scissor rectangle settings
    Rectangle colCaptionScissor(mColumnCaption);

    colCaptionScissor.top -= parentVerticalScrollbarValue;
    if (colCaptionScissor.top < parentUnderTitleY)
      colCaptionScissor.top = parentUnderTitleY;

    colCaptionScissor.left -= parentHorizontalScrollbarValue;
    if (colCaptionScissor.left < parentLeftX)
      colCaptionScissor.left = parentLeftX;

    qr->setUseParentScissor(false);
    qr->setScissorRectangle(colCaptionScissor);
    qr->setUseParentScissor(true);  
    qr->drawText(tsMclColumnHeader, vHeader->getCaption(), 
		 mColumnCaption, false);
  }  

  // Drawing left line
  xLeft+=vHeader->getWidth();
  qr->setUseParentScissor(false);

  //  Avoid left line to get more to the right to the mcl right corners
  if ( xLeft < (mMclAbsCorners.right + parentHorizontalScrollbarValue )){
    // Compute scissor rectangle
    Rectangle leftLineScissor(mMclAbsCorners);
    leftLineScissor.top -= parentVerticalScrollbarValue;
    
    // Cut to the parentUnderTitleY value
    if ( leftLineScissor.top < parentUnderTitleY) 
      leftLineScissor.top = parentUnderTitleY;
    
    leftLineScissor.left -= parentHorizontalScrollbarValue;
    if (leftLineScissor.left < parentLeftX)
      leftLineScissor.left = parentLeftX;


    qr->setScissorRectangle(leftLineScissor);
    
    // Let the line go to the bottom of the list eventy if the parent scrollbar
    // value changed
    y2 += parentVerticalScrollbarValue;

    // Render the line
    qr->drawLine( xLeft, y1, xLeft, y2, mMclBorderColor );
  } 
  qr->setUseParentScissor(true);
  
  
  qr->reset();

}

/** Draw one item in the list
  *
  * This function do not use 
  * \ref RainbruRPG::OgreGui::QuadRenderer::useParentScissor 
  * "QuadRenderer::useParentScissor" ability to provide a fast draw (it
  * avoid two calls to 
  * \ref RainbruRPG::OgreGui::QuadRenderer::setUseParentScissor 
  * "QuadRenderer::setUseParentScissor" for each item's cell drawn). A
  * side effect is that you need to be sure the current scissor you
  * get in the \c vScissor parameter is correct when calling
  * this function from \ref wdMultiColumnList::drawAllItems "drawAllItems()".
  *
  * \note The scissor rectangle setting when calling this function is 
  *       important because it is used to cut the header caption. The 
  *       scissor right value when calling this function \b must be the 
  *       parent window right one.
  *
  * \param qr            The QuadRenderer object used to draw
  * \param vItem         The item to be drawn
  * \param vRect         The rectangle where the item is drawn
  * \param vColList      The MultiColumnList's column list
  * \param vMovingColumn The column we are currently moving
  * \param vScissor      The item scissor rectangle. should be modified.
  * \param vDebug        Should we debug this drawing ?
  *
  */
void RainbruRPG::OgreGui::wdMultiColumnList::
drawOneItem(QuadRenderer* qr,MultiColumnListItem* vItem,const Rectangle& vRect,
	    const tMultiColumnListColumnList& vColList, int vMovingColumn,
	    Rectangle vScissor, bool vDebug){

  int currentScissorRight;   // Used to cut caption to the right scissor
  Rectangle itemTextRect;    // Used to draw item text with margins
  Rectangle itemRect(vRect); // The background item rectangle
  int colId=0;               // The item column we are drawing

  currentScissorRight = qr->getClipRegion().right;
  mDebugSettings->debugItem( qr, mCurrentMcl, vItem, vRect );

  tMultiColumnListCellList mil=vItem->getCellList();
  tMultiColumnListCellList::const_iterator mii;


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

      itemTextRect = itemRect;
      itemTextRect.left += ITEM_INSIDE_MARGIN_TEXT;
      itemTextRect.top += ITEM_INSIDE_MARGIN_TOP;


      if (colId == vMovingColumn){
	qr->enableGhost();
      }
      
      vScissor.right = itemRect.left + vColList[colId]->getWidth() -
	ITEM_INSIDE_MARGIN_BACK;

      // Cut the item caption scissor to the current right scissor if needed
      if (vScissor.right > currentScissorRight){
	vScissor.right = currentScissorRight;
      }

      vScissor.left -= parentHorizontalScrollbarValue;
      if (vScissor.left < parentLeftX)
	vScissor.left = parentLeftX;


      if (vScissor.left < currentScissorRight){
	qr->setScissorRectangle(vScissor);
	drawOneItemCell(qr, (*mii), itemTextRect  );
      }

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
  itemBG.left=mMclAbsCorners.left+ITEM_INSIDE_MARGIN_BACK;
  itemBG.top=mColumnCaption.top + mcl->getHeaderHeight()+ HEADER_BG_SPACE;
  itemBG.bottom=itemBG.top+20;
  itemBG.right=mcl->getLastColumnRight() - ITEM_INSIDE_MARGIN_BACK;

  // The header bottom corners, used to avoid item drawing over the headers
  int itemTop =  mcl->getAbsoluteCorners().top + mcl->getHeaderHeight();
  Ogre::Rectangle itemScissorRect(mMclAbsCorners);
  if (itemScissorRect.top < itemTop) itemScissorRect.top = itemTop;

  // Handle parent window scrollbar value
  itemScissorRect.top -= parentVerticalScrollbarValue;
  if (itemScissorRect.top < parentUnderTitleY)
    itemScissorRect.top = parentUnderTitleY;

  itemScissorRect.left -= parentHorizontalScrollbarValue;
  if (itemScissorRect.left < parentLeftX)
    itemScissorRect.left = parentLeftX;


  // Drawing items
  for (ili = itemList.begin(); ili != itemList.end(); ili++){
    
    // Setting the item scissor to avoid a bug when
    // drawing item background
    qr->setUseParentScissor(false);
    qr->setScissorRectangle(itemScissorRect);
    drawOneItem(qr, (*ili), itemBG, colList, vMovingColumn, itemScissorRect );

    itemRect.left=mMclAbsCorners.left+ITEM_INSIDE_MARGIN_BACK;
    itemRect.right=itemRect.left + colList[0]->getWidth();
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

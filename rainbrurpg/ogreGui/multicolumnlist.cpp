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

#include <logger.h>
#include <quadrenderer.h>

#include <OgreColourValue.h>

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
  mAbsCorners()
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
  mColumnList.push_back(col);
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
  return mItemList;
}

/** Adds an item
  *
  * \param it The item to add
  *
  */
void RainbruRPG::OgreGui::MultiColumnList::addItem( MultiColumnListItem* it ){
  mItemList.push_back( it );
}

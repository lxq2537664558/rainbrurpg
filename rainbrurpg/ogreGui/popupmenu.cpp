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

#include "popupmenu.h"

#include "bgwindow.h"
#include "popupmenuitem.h"
#include "pmititle.h"
#include "pmiseparator.h"
#include "quadrenderer.h"

#include <logger.h>

/** The constructor
  *
  * \param vDim     The dimension of the menu in pixels
  * \param vCaption The menu caption
  * \param vParent  The menu parent
  * \param sid      The skin identifier
  *
  */
RainbruRPG::OgreGui::PopupMenu::
PopupMenu(Vector4 vDim, String vCaption, Widget* vParent,
	  RainbruRPG::OgreGui::OgreGuiSkinID sid):
  Widget( vDim, vParent, sid ),
  mSkin(NULL),
  mWidth(150),
  mTitle(NULL),
  mSeparator(NULL)
{
  mSkin  = SkinManager::getSingleton().getSkin(this);

  setCaption( vCaption );

  makeCorners();
}

/** The destructor
  *
  *
  *
  */
RainbruRPG::OgreGui::PopupMenu::~PopupMenu(){
  mSkin = NULL;

  if (mTitle){
    delete mTitle;
    mTitle = NULL;
    delete mSeparator;
    mSeparator = NULL;
  }
}

/** Change the caption of this menu
  *
  * \param vCaption The new caption
  *
  */
void RainbruRPG::OgreGui::PopupMenu::setCaption( const Ogre::String& vCaption){
  mCaption = vCaption;
  if ( vCaption != "" ){
    if (mTitle == NULL){
      mTitle = new pmiTitle(vCaption);
      mItemList.push_back( mTitle );
      mSeparator = new pmiSeparator();
      mItemList.push_back( mSeparator );
      
    }
    else{
      mTitle->setCaption(vCaption);
    }
  }
}

/** Change the width of this menu
  *
  * \param vWidth the new width in pixels
  *
  */
void RainbruRPG::OgreGui::PopupMenu::setWidth(unsigned int vWidth){
  mWidth = vWidth;
}

/** Get the caption of this menu
  *
  * \return The caption
  *
  */
const Ogre::String& RainbruRPG::OgreGui::PopupMenu::getCaption(void)const{
  return mCaption;
}

/** Get the width of this menu
  *
  * \return The width in pixels
  *
  */
unsigned int RainbruRPG::OgreGui::PopupMenu::getWidth(void)const{
  return mWidth;
}

/** Pre-computation of geometry
  *
  */
void RainbruRPG::OgreGui::PopupMenu::makeCorners(void){
  LOGI("PopupMenu::makeCorners called");
  mAbsCorners.top    = corners.top + parent->getTop();
  mAbsCorners.left   = corners.left + parent->getLeft();
  mAbsCorners.right  = corners.left + parent->getLeft() + mWidth;

  unsigned int currentX = mAbsCorners.left;
  unsigned int currentY = mAbsCorners.top;
 
  tPopupMenuItemList::iterator iter;
  for (iter = mItemList.begin(); iter != mItemList.end(); iter++){
    (*iter)->computeAbsCorners( currentX, currentY, mWidth );
    currentY += (*iter)->getHeight();
  }

  if (currentY == mAbsCorners.top)
    currentY += 20;

  corners.bottom = currentY - parent->getTop();
  mAbsCorners.bottom = currentY;
 
}

/** Draw this menu
  *
  * \param qr The QuadRenderer object pointer used to draw
  *
  */
void RainbruRPG::OgreGui::PopupMenu::draw(QuadRenderer* qr){
  if (visible){
    if (geometryDirty){
      makeCorners();
      geometryDirty=false;
    }

    // Get parent scissor rectangle settings and disable it
    Ogre::Rectangle sr=qr->getClipRegion();
    qr->setUseParentScissor(false);

    // Render!    
    mSkin->drawPopupMenu( qr, this );

    tPopupMenuItemList::iterator iter;
    for (iter = mItemList.begin(); iter != mItemList.end(); iter++){
      (*iter)->draw(qr);
    }

    // Re-set the parent scissor rectangle settings
    qr->setScissorRectangle(sr);
    qr->setUseParentScissor(true);

  }
}

/** Get the absolute corners
  *
  * \return The geometry corners from the screen top/left corner
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::PopupMenu::getAbsCorners(void)const{
  return mAbsCorners;
}

/** Add an item to this menu
  *
  * \param vItem The item to be added to the end of the menu
  *
  */
void RainbruRPG::OgreGui::PopupMenu::addItem(PopupMenuItem* vItem){
  mItemList.push_back(vItem);
}

bool RainbruRPG::OgreGui::PopupMenu::
injectMouse(unsigned int px, unsigned int py, const MouseEvent& vEvent){
  LOGI("PopupMenu::injectMouse called");

  tPopupMenuItemList::iterator iter;
  for (iter = mItemList.begin(); iter != mItemList.end(); iter++){
    if ((*iter)->injectMouse( px, py, vEvent )){
      return true;
    }
  }

  return false;
}


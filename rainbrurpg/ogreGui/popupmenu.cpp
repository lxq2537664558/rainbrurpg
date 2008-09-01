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

/** \file popupmenu.cpp
  * Implements a popup menu widgets
  *
  */

#include "popupmenu.h"

#include "bgwindow.h"
#include "popupmenuitem.h"
#include "pmititle.h"
#include "pmiseparator.h"
#include "quadrenderer.h"

#include <logger.h>
#include <vcconstant.h>

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
  mSeparator(NULL),
  mVelocityCalculator(NULL),
  mDropDown(false),
  mDropDownHeight(0)
{
  mSkin  = SkinManager::getSingleton().getSkin(this);

  mVelocityCalculator = new vcConstant();
  mVelocityCalculator->setTranslationLenght(0.7);
  mVelocityCalculator->setTransitionTime(150);

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

  if (mVelocityCalculator){
    delete mVelocityCalculator;
    mVelocityCalculator = NULL;
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
  mAbsCorners.top    = corners.top + parent->getTop();
  mAbsCorners.left   = corners.left + parent->getLeft();
  mAbsCorners.right  = corners.left + parent->getLeft() + mWidth;

  unsigned int currentX = mAbsCorners.left;
  unsigned int currentY = mAbsCorners.top;
 
  unsigned int cX = corners.left;
  unsigned int cY = corners.top;

  tPopupMenuItemList::iterator iter;
  for (iter = mItemList.begin(); iter != mItemList.end(); iter++){
    (*iter)->computeCorners( cX, cY, mWidth );
    (*iter)->computeAbsCorners( currentX, currentY, mWidth );
    currentY += (*iter)->getHeight();
    cY       += (*iter)->getHeight();
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
  if (visible || (!visible && mDropDown)){
    if (geometryDirty){
      makeCorners();
      geometryDirty=false;
    }

    Ogre::Rectangle newScissor = mAbsCorners;

    if (mDropDown){
      bool stop=true;
      mDropDownHeight += mVelocityCalculator->getNextFrame(stop);
      newScissor.bottom = newScissor.top + mDropDownHeight;
      if (stop==false){
	mVelocityCalculator->reset();
	mDropDown=false;
      }
    }

    if (mDropDownHeight > 0){

      // Adding shadow dev
      newScissor.right += 6;
      newScissor.bottom += 6;


      // Get parent scissor rectangle settings and disable it
      Ogre::Rectangle sr=qr->getClipRegion();
      qr->setUseParentScissor(false);
      
      qr->setScissorRectangle(newScissor);
      qr->setUseParentScissor(true);

      // Render!    
      mSkin->drawPopupMenu( qr, this );

      tPopupMenuItemList::iterator iter;
      for (iter = mItemList.begin(); iter != mItemList.end(); iter++){
	(*iter)->drawMouseOver(qr);
	(*iter)->draw(qr);
      }

      // Re-set the parent scissor rectangle settings
      qr->setScissorRectangle(sr);
      qr->setUseParentScissor(true);
    } // If mDropDownHeight > 0
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

/** Handles the mouse event
  *
  * \param px, py mouse position relative from the widnow top/left corner
  * \param vEvent The mouse event object
  *
  */
bool RainbruRPG::OgreGui::PopupMenu::
injectMouse(unsigned int px, unsigned int py, const MouseEvent& vEvent){
  tPopupMenuItemList::iterator iter;
  for (iter = mItemList.begin(); iter != mItemList.end(); iter++){
    (*iter)->handleMouseOver( px, py );
    if ((*iter)->injectMouse( px, py, vEvent )){
      return true;
    }
  }
  return false;
}

/** Is the given point in the menu
  *
  * \param px, py mouse position relative from the widnow top/left corner
  *
  */
bool RainbruRPG::OgreGui::PopupMenu::in(unsigned int px, unsigned int py)const{
  if (px > corners.left && px < corners.right){
    if (py > corners.top && py < corners.bottom){
      return true;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}

/** Hides this popup meu
  *
  * \note This function overrides the Widget's one to implement the PopupMenu
  *       drop down effect.
  *
  */
void RainbruRPG::OgreGui::PopupMenu::hide(){
  // 6 id the shadow height
  int height = mAbsCorners.bottom - mAbsCorners.top + 6;
  mDropDown = true;
  mVelocityCalculator->setTranslationLenght(-height);
  mVelocityCalculator->start();
  visible = false;
  mDropDownHeight = height;
}

/** Shows this popup meu
  *
  * \note This function overrides the Widget's one to implement the PopupMenu
  *       drop down effect.
  *
  */
void RainbruRPG::OgreGui::PopupMenu::show(){
  // 6 id the shadow height
  int height = mAbsCorners.bottom - mAbsCorners.top + 6;
  mDropDown = true;
  mVelocityCalculator->setTranslationLenght(height);
  mVelocityCalculator->start();
  visible = true;
  mDropDownHeight = 0;
}

/** Set the visibility status of this popup menu
  *
  * \note This function overrides the Widget's one to implement the PopupMenu
  *       drop down effect.
  *
  * \param vVisible The new visible status
  *
  */
void RainbruRPG::OgreGui::PopupMenu::setVisible(bool vVisible){
  if (visible != vVisible){
    visible = vVisible;
    if (visible){
      show();
    }
    else{
      hide();
    }
  }
}

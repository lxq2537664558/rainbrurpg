/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file popupmenuitem.cpp
  * Implements the base class for all menu items
  *
  */

#include "popupmenuitem.h"

#include "quadrenderer.h"
#include <vcconstant.h>
#include <logger.h>

/** The default constructor
  *
  */
RainbruRPG::OgreGui::PopupMenuItem::PopupMenuItem():
  mEnabled(false),
  mHeight(20),
  mVelocityCalculator(NULL),
  mMouseOverAlpha(0.0f),
  mInTransition(false)
{
  mVelocityCalculator = new vcConstant();
  mVelocityCalculator->setTranslationLenght(0.7);
  mVelocityCalculator->setTransitionTime(400);
}

/** The destructor
  *
  */
RainbruRPG::OgreGui::PopupMenuItem::~PopupMenuItem(){
  delete mVelocityCalculator;
  mVelocityCalculator = NULL;
}

/** Change the height of this item
  *
  * \param vHeight The height of this menu item
  *
  */
void RainbruRPG::OgreGui::PopupMenuItem::setHeight(unsigned int vHeight){
  mHeight = vHeight;
}

/** Get the height of this item
  *
  * \return The height of this menu item
  *
  */
unsigned int RainbruRPG::OgreGui::PopupMenuItem::getHeight(void)const{
  return mHeight;
}

/** Set the enable value
  *
  * \param vEnabled The new mEnabled value
  *
  */
void RainbruRPG::OgreGui::PopupMenuItem::setEnabled(bool vEnabled){
  mEnabled = vEnabled;
}

/** Get the enable value
  *
  * \return The mEnabled value
  *
  */
bool RainbruRPG::OgreGui::PopupMenuItem::getEnabled(void)const{
  return mEnabled;
}

/** Get the absolute corners rectangle
  *
  * \return The rectangle containing the item
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::PopupMenuItem::
getAbsCorners(void)const{
  return mAbsCorners;
}

/** Comput relatives corners
  *
  * This function is automatically called by PopupMenu when it moves. It
  * compute the corners rectangles of this item. 
  * Relatives corners are relative from the Window's top/left corner.
  *
  * \param vX, vY The position of the widget from the window 
  *               top/left point
  *
  * \param vWidth The width of the parent popup menu
  *
  */
void RainbruRPG::OgreGui::PopupMenuItem::
computeCorners(unsigned int vX, unsigned int vY, unsigned int vWidth){
  mCorners.left   = vX;
  mCorners.top    = vY;
  mCorners.right  = vX + vWidth;
  mCorners.bottom = vY + mHeight;

}

/** Compute the corners rectangle
  *
  * This function is automatically called by PopupMenu when it moves. It
  * compute the corners rectangles of this item. 
  *
  * \param vAbsX, vAbsY The position of the widget from the screen 
  *                     top/left point
  *
  * \param vWidth The width of the parent popup menu
  *
  */
void RainbruRPG::OgreGui::PopupMenuItem::
computeAbsCorners(unsigned int vAbsX, unsigned int vAbsY, unsigned int vWidth){
  mAbsCorners.left   = vAbsX;
  mAbsCorners.top    = vAbsY;
  mAbsCorners.right  = vAbsX + vWidth;
  mAbsCorners.bottom = vAbsY + mHeight;

  mImageCorners = mAbsCorners;
  mImageCorners.left += 5;
  mImageCorners.right = mImageCorners.left + 12;
  mImageCorners.top += 4;
  mImageCorners.bottom -= 4;


  mTextCorners = mAbsCorners;
  mTextCorners.left += 22;
}

/** Is this item enabled
  *
  * \return The value of mEnabled
  *
  */
bool RainbruRPG::OgreGui::PopupMenuItem::isEnabled(void)const{
  return mEnabled;
}

/** Is a point in this item
  *
  * \param vX, vY Position of the point in coordonates relative to the 
  *               window's top/left corner
  *
  */
bool RainbruRPG::OgreGui::PopupMenuItem::
in(unsigned int vX, unsigned int vY)const{
  if (vX > mCorners.left && vX < mCorners.right){
    if (vY > mCorners.top && vY < mCorners.bottom){
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

/** Handles the mouse over effect
  *
  * \param vX, vY The mouse position
  *
  */
void RainbruRPG::OgreGui::PopupMenuItem::
handleMouseOver(unsigned int vX, unsigned int vY){
  if (mEnabled){
    if (in(vX, vY) && mMouseOverAlpha < 0.2f){
      //     mMouseOverAlpha = 0.0f;
      mVelocityCalculator->setTranslationLenght(0.7);
      mVelocityCalculator->start();
      mInTransition = true;
    }
    else if (!in(vX, vY) &&  mMouseOverAlpha > 0.2f){
      //      mMouseOverAlpha = 0.7f;
      mVelocityCalculator->setTranslationLenght(-0.7);
      mVelocityCalculator->start();
      mInTransition = true;
    }
       
  }
}

/** Compute and return the mouse over alpha value
  *
  * \return The value of mMouseOverAlpha
  *
  */
float RainbruRPG::OgreGui::PopupMenuItem::getMouseOverAlpha(void){
  if (mInTransition){
    bool stop=true;
    mMouseOverAlpha+=mVelocityCalculator->getNextFrame(stop);
    if (stop==false){
      mVelocityCalculator->reset();
      mInTransition=false;
      if (mMouseOverAlpha < 0.0f) mMouseOverAlpha=0.0f;
    }
  }
  return mMouseOverAlpha;
}

/** Is this item in transition ?
  *
  * \return The value of mInTransition
  *
  */
bool RainbruRPG::OgreGui::PopupMenuItem::inTransition(void)const{
  return mInTransition;
}

/** Draw the mouse over effect
  *
  * \param qr The QuadRenderer object used to draw
  *
  */
void RainbruRPG::OgreGui::PopupMenuItem::drawMouseOver(QuadRenderer* qr){
  if (mEnabled){
    Ogre::ColourValue itemBGColor( 0.4f, 0.8f, 0.4f );
    float itemAlpha=getMouseOverAlpha();
    if (itemAlpha!=0.0f){
      // Using item's alpha
      float currentAlpha = qr->setTempAlpha(itemAlpha);
      qr->drawFilledRectangle( mAbsCorners, itemBGColor );
      qr->setAlpha(currentAlpha);
    }
  }
}

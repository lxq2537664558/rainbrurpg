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

#include "popupmenuitem.h"

/** The default constructor
  *
  */
RainbruRPG::OgreGui::PopupMenuItem::PopupMenuItem():
  mEnabled(false),
  mHeight(20)
{

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::PopupMenuItem::~PopupMenuItem(){

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

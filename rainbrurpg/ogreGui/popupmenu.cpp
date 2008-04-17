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
  mCaption(vCaption),
  mWidth(100)
{
  mSkin = SkinManager::getSingleton().getSkin(this);

  makeCorners();
}

/** The destructor
  *
  *
  *
  */
RainbruRPG::OgreGui::PopupMenu::~PopupMenu(){
  mSkin=NULL;
}

/** Change the caption of this menu
  *
  * \param vCaption The new caption
  *
  */
void RainbruRPG::OgreGui::PopupMenu::setCaption( const Ogre::String& vCaption){
  mCaption = vCaption;
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
  mAbsCorners.bottom = corners.bottom + parent->getTop();
  mAbsCorners.right  = corners.right + parent->getLeft();
 
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
    
    mSkin->drawPopupMenu( qr, this );
  }
}

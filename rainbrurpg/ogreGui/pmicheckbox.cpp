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

#include "pmicheckbox.h"

#include "quadrenderer.h"
#include "textsettings.h"

#include <logger.h>
#include <OgreTextureManager.h>

// pmiCheckBox static members initialisation
TexturePtr RainbruRPG::OgreGui::pmiCheckBox::mTxtOn = TexturePtr();
TexturePtr RainbruRPG::OgreGui::pmiCheckBox::mTxtOff = TexturePtr();
// End of pmiCheckBox static members initialisation

/** The check box item constructor
  *
  * \param vCaption The item caption
  *
  */
RainbruRPG::OgreGui::pmiCheckBox::pmiCheckBox(const Ogre::String& vCaption):
  PopupMenuItem(),
  mCaption(vCaption)
{
  mTxtOn = TextureManager::getSingleton()
    .load("bgui.check.on.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  mTxtOff = TextureManager::getSingleton()
    .load("bgui.check.off.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
}

/** The destructor
  *
  */
RainbruRPG::OgreGui::pmiCheckBox::~pmiCheckBox(){

}

/** Draw the check box
  *
  * \param qr The QuadRenderer used to draw
  *
  */
void RainbruRPG::OgreGui::pmiCheckBox::draw( QuadRenderer* qr){
  TextSettings* tsMclColumnHeader=new TextSettings( "Iconiv2.ttf", 
						    10, 1.0f, 1.0f, 1.0f );
  tsMclColumnHeader->setVerticalAlignment( VAT_CENTER );
  qr->setBlendMode(QBM_ALPHA);
  if (mCheck){
    qr->setTexturePtr(mTxtOn);
  }
  else{
    qr->setTexturePtr(mTxtOff);
  }
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->setScissorRectangle( mImageCorners );
  qr->drawRectangle(mImageCorners);
  qr->reset();

  qr->setScissorRectangle( mTextCorners );
  qr->drawText(tsMclColumnHeader, mCaption, mTextCorners, true);
  qr->reset();

}

/** Change the item caption
  *
  * \param vCaption The new caption
  *
  */
void RainbruRPG::OgreGui::pmiCheckBox::
setCaption( const Ogre::String& vCaption ){
  mCaption = vCaption;
}

/** Get the item caption
  *
  * \return The caption text
  *
  */
const Ogre::String& RainbruRPG::OgreGui::pmiCheckBox::getCaption(void)const{
  return mCaption;
}

bool RainbruRPG::OgreGui::pmiCheckBox::
injectMouse(unsigned int px, unsigned int py, const MouseEvent& event){

}

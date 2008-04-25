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

#include "pmititle.h"

#include "quadrenderer.h"
#include "textsettings.h"

#include <logger.h>

#include <OgreColourValue.h>

/** The named constructor
  *
  * \param vCaption The title content
  *
  */
RainbruRPG::OgreGui::pmiTitle::pmiTitle(const Ogre::String& vCaption):
  PopupMenuItem(),
  mCaption(vCaption)
{
  // Inherited members initialization
  mEnabled=false;

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::pmiTitle::~pmiTitle(){

}

/** Draw the title
  *
  * \param qr The QuadRenderer used to draw
  *
  */
void RainbruRPG::OgreGui::pmiTitle::draw( QuadRenderer* qr){
  TextSettings* tsMclColumnHeader=new TextSettings( "Iconiv2.ttf", 
						    12, 1.0f, 0.2f, 0.2f );
  tsMclColumnHeader->setHorizontalAlignment(HAT_CENTER);
  tsMclColumnHeader->setVerticalAlignment(VAT_CENTER);

  Ogre::ColourValue BGColor( 0.8f, 0.8f, 0.8f );

  qr->setScissorRectangle( mAbsCorners );
  qr->drawText(tsMclColumnHeader, mCaption, mAbsCorners, true);
  //  qr->drawFilledRectangle( mAbsCorners,  BGColor);
  qr->disableScissor();
  qr->reset();

}

/** Change the title caption
  *
  * \param vCaption The new caption
  *
  */
void RainbruRPG::OgreGui::pmiTitle::setCaption(const Ogre::String& vCaption){
  mCaption = vCaption;
}

/** Get the caption
  *
  * \return The title content
  *
  */
const Ogre::String& RainbruRPG::OgreGui::pmiTitle::getCaption(void)const{
  return mCaption;
}

bool RainbruRPG::OgreGui::pmiTitle::
injectMouse(unsigned int, unsigned int, const MouseEvent&){
  return false;
}

/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file resizegrip.cpp
  * Implements a resize grip for windows
  *
  */

#include "resizegrip.h"

#include "skin.h"
#include "quadrenderer.h"

#include <logger.h>

#include <OgreStringConverter.h>

/** The constructor
  *
  * \param dim          The dimensions 
  * \param callback     The callback of the button
  * \param G            The GUI object
  * \param parent       The parent window
  * \param sid          The skin ID (inherited by default)
  *
  */
RainbruRPG::OgreGui::ResizeGrip::
ResizeGrip(Vector4 dim, Callback callback, GUI *G, Widget* parent,
	   OgreGuiSkinID sid):
  Button(dim, "", "", callback, parent, sid),
  mSkin(NULL)
{
  setName("ResizeGrip");
  mSkin=SkinManager::getSingleton().getSkin(this);

}

/** The destructor
  *
  * The \link BetaGUI::Button::~Button() Button destructor \endlink is override 
  * because resize grip does not use mCP, and when we try to access 
  * \c mCP->getParent(), a segmentation fault occurs.
  *
  */
RainbruRPG::OgreGui::ResizeGrip::~ResizeGrip(){
  mSkin=NULL;
}

/** Draws the resize grip
  *
  * \param qr The QuadRenderer used to draw it
  *
  */
void RainbruRPG::OgreGui::ResizeGrip::draw(QuadRenderer* qr){
  int px=this->parent->getLeft()+corners.left;
  int py=this->parent->getTop()+corners.top;

  Vector4 dim(px, py, getWidth(), getHeight());
  qr->setAlpha( this->alpha );
  mSkin->drawResizeGrip(qr, dim, this->active);
}

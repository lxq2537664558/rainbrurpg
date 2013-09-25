/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file titlebar.cpp
  * Implements a Window's title bar
  *
  */

#include "titlebar.h"

#include "skin.h"
#include "quadrenderer.h"
#include "widget.h"

#include <logger.h>

#include <OgreStringConverter.h>


/** The constructor
  *
  * \param dim          The dimensions 
  * \param caption      The text of the button
  * \param callback     The callback of the button
  * \param G            The GUI object
  * \param parent       The parent window
  * \param sid          The skin ID (inherited by default)
  *
  */
RainbruRPG::OgreGui::TitleBar::
TitleBar(Vector4 dim, String caption, Callback callback, GUI* G, 
	 Widget* parent, OgreGuiSkinID sid):
  Button(dim, "", caption, callback, parent, sid)
{
  setName("TitleBar");
  mSkin=SkinManager::getSingleton().getSkin(this);

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::TitleBar::~TitleBar(){

}

/** Draws the titlebar
  *
  * \param qr The QuadRenderer used to draw the titlebar
  *
  */
void RainbruRPG::OgreGui::TitleBar::draw(QuadRenderer* qr){
  int px=this->parent->getLeft()+getLeft();
  int py=this->parent->getTop()+getTop();

  Vector4 dim(px, py, getWidth(), getHeight());
  qr->setAlpha( this->alpha );

  mSkin->drawTitleBar(qr, dim, mCaption, this->active);
}

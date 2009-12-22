/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file ogreGui/pushbutton.cpp
  * Implements a push button widget
  *
  */

#include "pushbutton.h"

#include "skin.h"
#include "bgwindow.h"
#include "quadrenderer.h"

#include <logger.h>
#include <OGRE/OgreStringConverter.h>

/** The constructor
  *
  * \param dim          The dimensions 
  * \param caption      The text of the button
  * \param c            The callback of the button
  * \param parent       The parent window
  * \param sid          The ID of the skin
  *
  */
RainbruRPG::OgreGui::PushButton::
PushButton(Vector4 dim, String caption, Callback c, Window* parent, 
	   OgreGuiSkinID sid): 
  BetaGUI::Button(dim, "", caption, c, parent, sid),
  mSkin(NULL),
  winParent(NULL)
{
  setName("PushButton");
  mSkin=SkinManager::getSingleton().getSkin(this);
  winParent=dynamic_cast<Window*>(this->parent);

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::PushButton::~PushButton(){
  mSkin=NULL;
  winParent=NULL;
}

/** Draws the resize grip
  *
  * \param qr The QuadRenderer used to draw it
  *
  */
void RainbruRPG::OgreGui::PushButton::draw(QuadRenderer* qr){
  Vector4 dim(corners.left, corners.top, getWidth(), getHeight());

  if (!mEnable) qr->enableGhost();

  mSkin->drawPushButton(qr, dim, mCaption, winParent, active, mEnable);
  if (!mEnable) qr->disableGhost();
}


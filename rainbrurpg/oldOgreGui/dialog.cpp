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

/** \file ogreGui/dialog.cpp
  * Implements a modal dialog for OgreGui
  *
  */

#include "dialog.h"

#include "quadrenderer.h"

#include <logger.h>

/** The dialog constructor
  *
  * \param vDim     The dimensions
  * \param vCaption The dialog caption
  * \param vGui     The GUI object
  * \param sid      The Skin 
  *
  */
RainbruRPG::OgreGui::Dialog::
Dialog( const Vector4& vDim, const String& vCaption, GUI* vGui,
	RainbruRPG::OgreGui::OgreGuiSkinID sid ):
  Window(vDim, OWT_MOVE, vCaption, vGui, sid)
{
  mSkin = SkinManager::getSingleton().getSkin(this);

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::Dialog::~Dialog(){

}

/** Draw the dialog
  *
  * \param qr The QuadRenderer used to draw
  *
  */
void RainbruRPG::OgreGui::Dialog::draw(QuadRenderer* qr){
  if (visible){
    // v0.0.5-191 : The following fix a bug when moving a dialog
    if (geometryDirty){
      makeCorners();
    }
    mSkin -> drawDialog(qr, this);
    if (mResizeGrip) mResizeGrip->draw(qr);
    if (mTitleBar)   mTitleBar->draw(qr);
    mScrollPane->draw( qr );
    qr->reset();
  }
}
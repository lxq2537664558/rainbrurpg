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

#include "label.h"

#include "bgwindow.h"
#include "quadrenderer.h"

#include <logger.h>


#include <OgreStringConverter.h>
#include <OgreOverlayManager.h>

/** The Label constructor
  *
  * \param dim     The dimensions as an Ogre Vector4
  * \param caption The caption of the label
  * \param parent  The parent widget
  * \param sid     The skin ID (inherited by default)
  *
  */
RainbruRPG::OgreGui::Label::
Label(Vector4 dim, String caption, BetaGUI::Window* parent,
      RainbruRPG::OgreGui::OgreGuiSkinID sid):
  Widget(dim, parent, sid),
  mCaption(caption),
  mSkin(NULL)
{
  setName("Label");
  mSkin = SkinManager::getSingleton().getSkin(this);
  mParentWindow = parent;

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::Label::~Label(){
  mSkin=NULL;
  mParentWindow=NULL;
}

/** Change the transparency of this label
  *
  * \param vAlpha The new transparency (between 0.0f and 1.0f)
  *
  */
void RainbruRPG::OgreGui::Label::setTransparency(float vAlpha){
  alpha=vAlpha;
}

/** Changes the caption of this button
  *
  * \param s The new caption as an Ogre string
  * 
  */
void RainbruRPG::OgreGui::Label::setCaption(const String& s){
  mCaption=s;
}

void RainbruRPG::OgreGui::Label::draw(QuadRenderer* qr){
  qr->setAlpha(alpha);
  mSkin->drawLabel(qr, corners, mCaption, mParentWindow);
}

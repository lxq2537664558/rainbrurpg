/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

#include <OGRE/OgreStringConverter.h>
#include <OGRE/OgreOverlayManager.h>

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
  Widget(parent, sid)
{

  SkinOverlay* sk=SkinManager::getSingleton().getSkin(this);
  Ogre::String uniqueName=parent->getOverLayContainer()->getName()+"t"
    +StringConverter::toString(parent->getGUI()->getUniqueId());

  this->setName(uniqueName);

  sk->createLabel(uniqueName, dim, caption, parent);
  this->contentOverlay=sk->getOverlayByName(uniqueName);
  
}

/** The destructor
  *
  */
RainbruRPG::OgreGui::Label::~Label(){
  OverlayManager::getSingleton().destroy(name);
}

/** Change the transparency of this label
  *
  * \param alpha The new transparency (between 0.0f and 1.0f)
  *
  */
void RainbruRPG::OgreGui::Label::setTransparency(float alpha){
  SkinOverlay* s=SkinManager::getSingleton().getSkin(this);

  s->setCaptionTransparency(contentOverlay, alpha);
}

/** Changes the caption of this button
  *
  * \param s The new caption as an Ogre string
  * 
  */
void RainbruRPG::OgreGui::Label::setCaption(const String& s){
  this->contentOverlay->setCaption(s);
}

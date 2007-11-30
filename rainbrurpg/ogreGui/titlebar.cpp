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

#include "titlebar.h"

#include "skinoverlay.h"

#include <logger.h>

#include <OGRE/OgreStringConverter.h>


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
	 Window* parent, OgreGuiSkinID sid):
  Button(dim, "", caption, callback, parent, sid)
{

  SkinOverlay* sk=SkinManager::getSingleton().getSkin(this);

  Ogre::String uniqueName=parent->getOverLayContainer()->getName()+"b"
    +StringConverter::toString(G->getUniqueId());
  this->setName(uniqueName);

  sk->createTitleBar(uniqueName, dim, caption, parent);
  mO=sk->getOverlayByName(uniqueName);
  mCP=sk->getOverlayByName(uniqueName+"c");

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::TitleBar::~TitleBar(){

}

/** Changes the transparency
  *
  * \param f The new alpha value
  *
  */
void RainbruRPG::OgreGui::TitleBar::setTransparency(float f){
  SkinOverlay* s=SkinManager::getSingleton().getSkin(this);
  s->setTransparency(mO, f);
  s->setCaptionTransparency(mCP, f);
}

/** Changes the width 
  *
  * \param ui The new width
  *
  */
void RainbruRPG::OgreGui::TitleBar::setWidth(unsigned int ui){
  width=ui;
  mO->setWidth(ui);
  mCP->setWidth(ui);
}

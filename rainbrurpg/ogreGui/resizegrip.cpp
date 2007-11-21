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

#include "resizegrip.h"
#include "skinoverlay.h"

#include <logger.h>

#include <OGRE/OgreStringConverter.h>

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
ResizeGrip(Vector4 dim, Callback callback, GUI *G, Window* parent,
	   OgreGuiSkinID sid):
  Button(dim, "", "", callback, parent, sid)
{

  SkinOverlay* sk=SkinManager::getSingleton().getSkin(this);
  Ogre::String uniqueName=parent->getOverLayContainer()->getName()+"b"
    +StringConverter::toString(G->getUniqueId());
  this->setName(uniqueName);

  sk->createResizeGrip(uniqueName, dim, parent);
  mO=sk->getOverlayByName(uniqueName);

}

/** The destructor
  *
  * The \link BetaGUI::Button::~Button() Button destructor \endlink is override 
  * because resize grip does not use mCP, and when we try to access 
  * \c mCP->getParent(), a segmentation fault occurs.
  *
  */
RainbruRPG::OgreGui::ResizeGrip::~ResizeGrip(){
  mO->getParent()->removeChild(mO->getName());
  mO=NULL;
}

// special case of button (no caption overlay)
void RainbruRPG::OgreGui::ResizeGrip::setTransparency(float f){
  SkinOverlay* s=SkinManager::getSingleton().getSkin(this);

  s->setTransparency(mO, f);

}

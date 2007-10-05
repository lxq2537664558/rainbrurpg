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
#include <OGRE/OgreStringConverter.h>

/** The constructor
  *
  * \param dim          The dimensions 
  * \param callback     The callback of the button
  * \param G            The GUI object
  * \param parent       The parent window
  *
  */
RainbruRPG::OgreGui::ResizeGrip::
ResizeGrip(Vector4 dim, Callback callback, GUI *G,Window* parent)
  :Button(dim, "", "", callback, parent)

{
  Skin* sk=SkinManager::getSingleton().getSkin(this->skinId);
  Ogre::String uniqueName=parent->getOverLayContainer()->getName()+"b"
    +StringConverter::toString(G->getUniqueId());

  sk->createResizeGrip(uniqueName, dim, parent);

  // Get the corresponding overlay if based on SkinOverlay
  SkinOverlay* sko=static_cast<SkinOverlay*>(sk);
  if (sko){
    mO=sko->getOverlayByName(uniqueName);
  }

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::ResizeGrip::~ResizeGrip(){

}

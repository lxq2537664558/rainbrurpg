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

#include "hscrollbar.h"

#include <logger.h>
#include "bgwindow.h"
#include "skinmanager.h"
#include "skin.h"
#include "mousepointer.h"

/** The constructor
  *
  * \param dim The scrollbar dimensions
  * \param win The parent
  * \param sid The skin identifier
  *
  */
RainbruRPG::OgreGui::HScrollBar::
HScrollBar(Vector4 dim, Widget* win, OgreGuiSkinID sid):
  ScrollBar(dim, win, sid),
  sk(NULL),
  mGUI(NULL)
{

  sk=SkinManager::getSingleton().getSkin(this);
  makeCorners();

  Window* winn=dynamic_cast<Window*>(win);
  LOGA(winn, "Cannot get parent Window. "
       "We're enable to change mouse cursor.");

  mGUI=winn->getGUI();

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::HScrollBar::~HScrollBar(){
  sk=NULL;
  mGUI=NULL;
}

/** Compute geometry of VScrollBar
  *
  * It is not automatically made for each frame, we use geometryDirty
  * to know id the parent has moved.
  *
  */
void RainbruRPG::OgreGui::HScrollBar::makeCorners(void){

}

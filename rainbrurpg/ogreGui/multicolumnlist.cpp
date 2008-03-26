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

#include "multicolumnlist.h"

#include <logger.h>
#include <quadrenderer.h>

#include <OgreColourValue.h>

RainbruRPG::OgreGui::MultiColumnList::
MultiColumnList(Vector4 dim, BetaGUI::Window* parent, 
		RainbruRPG::OgreGui::OgreGuiSkinID sid):
  Widget(dim, (Widget*)parent, sid)
{
  mSkin = SkinManager::getSingleton().getSkin(this);
}

void RainbruRPG::OgreGui::MultiColumnList::draw(QuadRenderer* qr){
  mSkin->drawMultiColumnList( qr, this );
}

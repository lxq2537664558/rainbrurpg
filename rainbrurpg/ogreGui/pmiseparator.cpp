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

#include "pmiseparator.h"

#include "quadrenderer.h"
#include <logger.h>

RainbruRPG::OgreGui::pmiSeparator::pmiSeparator():
  PopupMenuItem()
{
  setHeight(3);
}

RainbruRPG::OgreGui::pmiSeparator::~pmiSeparator(){

}

void RainbruRPG::OgreGui::pmiSeparator::draw( QuadRenderer* qr){
  LOGI("Drawing pmiSeparator");

  qr->setScissorRectangle(mAbsCorners);
  qr->drawLine (mAbsCorners.left,  mAbsCorners.top, 
		mAbsCorners.right, mAbsCorners.top, 
		ColourValue(0.8f, 0.8f, 0.8f));
  

  qr->drawLine (mAbsCorners.left,  mAbsCorners.top+1, 
		mAbsCorners.right, mAbsCorners.top+1, 
		ColourValue(0.0f, 0.0f, 0.0f));
  
  qr->reset();
  
}

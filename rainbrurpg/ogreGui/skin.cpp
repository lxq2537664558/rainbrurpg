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

#include "skin.h"

#include "bgbutton.h"
#include "quadrenderer.h"

#include <logger.h>

#include <OgreOverlayManager.h>
#include <OgreMaterialManager.h>
#include <OgreStringConverter.h>
#include <OgreTechnique.h>
#include <OgreTextureUnitState.h>
#include <OgreTextAreaOverlayElement.h>

/** Create a named skin 
  *
  * \param n The name of the new skin
  *
  */
RainbruRPG::OgreGui::Skin::Skin(std::string n):
  mTitleBarHeight(0)
{

}

/** Get the dialog border size
  *
  * This function is used by the \ref BetaGUI::Window "Window" 
  * constructor to place and resize
  * TitleBar and ResizeGrip according to the border size.
  *
  * \return The border size in pixels
  *
  */
unsigned int RainbruRPG::OgreGui::Skin::getDialogBorderSize(void){
  return this->dialogBorderSize;
}

/** Get the TitleBar's height in pixels
  *
  * \return The height of the TitleBar in pixels
  *
  */
int RainbruRPG::OgreGui::Skin::getTitleBarHeight(void){
  return mTitleBarHeight;
}

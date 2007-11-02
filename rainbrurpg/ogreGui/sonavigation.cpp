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

#include "sonavigation.h"
#include "bgwindow.h"

#include <logger.h>

#include <OGRE/OgreVector2.h>
#include <OGRE/OgreOverlayManager.h>
#include <OGRE/OgreOverlayContainer.h>

/** Default constructor
  *			   
  * It simply creates a SkinOverlay called \e soNavigation
  *
  */
RainbruRPG::OgreGui::soNavigation::soNavigation() : 
  SkinOverlay("soNavigation")
{
  mnPushButton="nav.button";
  fnPushButton="BlueHighway";
  fsPushButton=16;
}

void RainbruRPG::OgreGui::soNavigation::
createWindow(String name, Vector4 dim, String caption,BetaGUI::GUI* bg){

  this->createOverlay(name, dim, "", bg->getRootOverlay());
}

void RainbruRPG::OgreGui::soNavigation::
createResizeGrip(String, Vector4, Window*){
  LOGW("soNavigation cannot create ResizeGrip");

}

void RainbruRPG::OgreGui::soNavigation::
createTitleBar(String, Vector4, String, Window*){
  LOGW("soNavigation cannot create TitleBar");

}

void RainbruRPG::OgreGui::soNavigation::
createPushButton(String name, Vector4 dim, String caption, Window* win){
  LOGI("Creating a PushButton widget");
  this->createOverlay(name, dim, mnPushButton, win->getOverLayContainer());

  // vertically center the caption
  unsigned int dev=((dim.w-fsPushButton)/2)+2;
  dim.x+=dev;
  dim.y+=dev;

  this->createCaption(name+"c", dim, caption, 
	      fnPushButton, fsPushButton,win->getOverLayContainer());
}

void RainbruRPG::OgreGui::soNavigation::
createTextInput(String, Vector4, String, Window*){
  LOGW("soNavigation cannot create TextInput");

}

void RainbruRPG::OgreGui::soNavigation::
createLabel(String, Vector4, String, Window*){
  LOGW("soNavigation cannot create Label");

}


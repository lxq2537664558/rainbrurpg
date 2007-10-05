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

#include "sobetagui.h"

#include <logger.h>
#include "bgwindow.h"

#include <OGRE/OgreVector2.h>
#include <OGRE/OgreOverlayManager.h>
#include <OGRE/OgreOverlayContainer.h>

/** Default constructor
  *
  * It simply creates a SkinOverlay called \e soBetaGUI
  *
  */
RainbruRPG::OgreGui::soBetaGui::soBetaGui() 
: SkinOverlay("soBetaGUI"){
  mnWindow="bgui.window";
  mnResizeGrip="bgui.window.resize";
  mnTitleBar="bgui.window.titlebar";
}

/** Create a window using the BetaGUI skin
  *
  * It creates an overlay with a material named mnWindow.
  *
  * The name parameter must be application unique. It is the 
  * name of the Ogre overlay we create.
  *
  * \param name    The internal name of the window
  * \param dim     The window's dimension in pixels in a Ogre::Vector4 object
  * \param caption The title bar caption
  * \param bg      The BetaGUI::GUI object 
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
createWindow(String name, Vector4 dim, String caption, BetaGUI::GUI* bg){

  this->createOverlay(name, dim, mnWindow, bg->getRootOverlay());

}

/** Graphically create a ResizeGrip widget
  *
  * \param name    The internal name of the ResizeGrip (must be unique)
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param win     The parent window
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
createResizeGrip(String name, Vector4 dim, Window* win ){

  LOGI("Creating a ResizeGrip widget");
  this->createOverlay(name, dim, mnResizeGrip, win->getOverLayContainer());

}

/** Graphically create a TitleBar widget
  *
  * \param name    The internal name of the ResizeGrip (must be unique)
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param win     The parent window
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
createTitleBar(String name, Vector4 dim, Window* win ){

  LOGI("Creating a ResizeGrip widget");
  this->createOverlay(name, dim, mnTitleBar, win->getOverLayContainer());

}

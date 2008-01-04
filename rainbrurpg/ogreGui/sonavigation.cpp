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

#include "sonavigation.h"

#include "bgwindow.h"
#include "quadrenderer.h"

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
  mnWindow="nav.window";
  mnPushButton="nav.button";
  fnPushButton="BlueHighway";
  fsPushButton=16;
}

/** Draws a window using the navigation skin
  *
  * It creates an overlay with a material named mnWindow.
  *
  * The name parameter must be application unique. It is the 
  * name of the Ogre overlay we create.
  *
  * \warning This skin will not draw Window widget. Their are only used
  *          to add PushButton widgets for navigation purpose.
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The window's dimension in pixels in a Ogre::Vector4 object
  * \param caption The title bar caption
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawWindow(QuadRenderer* qr, Vector4 dim, String caption){

  //  this->createOverlay(name, dim, mnWindow, bg->getRootOverlay());
}

/** Create a window using the navigation skin
  *
  * For soNavigation, this borderWindow is not different than the normal one.
  *
  * \param name    The internal name of the window
  * \param dim     The window's dimension in pixels in a Ogre::Vector4 object
  * \param caption The title bar caption
  * \param bg      The BetaGUI::GUI object 
  *
  */
void RainbruRPG::OgreGui::soNavigation::
createDialog(String name, Vector4 dim, String caption,BetaGUI::GUI* bg){

  this->createOverlay(name, dim, mnWindow, bg->getDialogOverlay());
}


/** Draws a ResizeGrip widget
  *
  * \warning This widget is not supported by this skin. Nothing will
  *          be displayed if you use this skin in a window containing
  *          a ResizeGrip.
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param active  Is this resize grip active
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawResizeGrip(QuadRenderer* qr, Vector4 dim, bool active){
  LOGW("soNavigation cannot create ResizeGrip");

}

/** Graphically create a TitleBar widget
  *
  * \warning This widget is not supported by this skin. Nothing will
  *          be displayed if you use this skin in a window containing
  *          a TitleBar.
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param caption The rendered text
  * \param active  Is this title bar active ?
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawTitleBar(QuadRenderer* qr, Vector4 dim, String caption, bool active){
  LOGW("soNavigation cannot create TitleBar");

}

/** Graphically create a PushButton widget
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param caption The rendered text
  * \param win     The parent window
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawPushButton(QuadRenderer* qr, Vector4 dim, String caption, Window* win){
}

/** Graphically create a TextInput widget
  *
  * \warning This widget is not supported by this skin. Nothing will
  *          be displayed if you use this skin in a window containing
  *          a TextInput.
  *
  * \param name    The internal name of the ResizeGrip (must be unique)
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param caption The rendered text
  * \param parent  The parent window
  *
  */
void RainbruRPG::OgreGui::soNavigation::
createTextInput(String name, Vector4 dim, String caption, Window* parent){
  LOGW("soNavigation cannot create TextInput");

}

/** Graphically create a Label widget
  *
  * \warning This widget is not supported by this skin. Nothing will
  *          be displayed if you use this skin in a window containing
  *          a Label.
  *
  * \param name    The internal name of the ResizeGrip (must be unique)
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param caption The rendered text
  * \param parent  The parent window
  *
  */
void RainbruRPG::OgreGui::soNavigation::
createLabel(String name, Vector4 dim, String caption, Window* parent){
  LOGW("soNavigation cannot create Label");

}

/** Creates a vertical scrollbar
  *
  * \warning This widget is not supported by this skin. Nothing will
  *          be displayed if you use this skin in a window containing
  *          a VerticalScrollbar.
  *
  * \param name    The internal name of the ResizeGrip (must be unique)
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param parent  The parent window
  *
  *
  */
void RainbruRPG::OgreGui::soNavigation::
createVerticalScrollbar(const String& name, Vector4 dim, Window* parent){
  LOGW("soNavigation cannot create VerticalScrollbar");

}

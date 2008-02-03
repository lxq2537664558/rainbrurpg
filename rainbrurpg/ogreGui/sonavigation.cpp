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
#include "fontmanager.h"
#include "textsettings.h"

#include <logger.h>

#include <OgreVector2.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>

/** Default constructor
  *			   
  * It simply creates a SkinOverlay called \e soNavigation
  *
  */
RainbruRPG::OgreGui::soNavigation::soNavigation() : 
  SkinOverlay("soNavigation"),
  tsPushButton(NULL)
{
  tsPushButton=new TextSettings("Commonv2c.ttf", 14, 1.0f, 0.2f, 0.8f);
  tsPushButton->setVerticalAlignment( VAT_CENTER );
  tsPushButton->setHorizontalAlignment( HAT_CENTER );

  mPushButtonTexture=TextureManager::getSingleton()
    .load("nav.button.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mPushButtonActiveTexture=TextureManager::getSingleton()
    .load("nav.button.active.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

}

/** Destructor
  *
  */
RainbruRPG::OgreGui::soNavigation::~soNavigation(){
  delete tsPushButton;
  tsPushButton=NULL;
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
  * \param corners The window's dimension in pixels in a Ogre::Rectangle object
  * \param caption The title bar caption
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawWindow(QuadRenderer* qr, Rectangle corners, String caption){

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

  //  this->createOverlay(name, dim, mnWindow, bg->getDialogOverlay());
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
  * \param active  Is the mouse over this push button ?
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawPushButton(QuadRenderer* qr, Vector4 dim, String caption, 
	       Window* win, bool active){
  Rectangle corners;
  corners.left  = dim.x+win->getLeft();
  corners.top   = dim.y+win->getTop();
  corners.right = dim.x+dim.z+win->getLeft();
  corners.bottom= dim.y+dim.w+win->getTop();

  qr->setBlendMode(QBM_GLOBAL);
  qr->setScissorRectangle(corners);

  if (active){
    qr->setTexturePtr(mPushButtonActiveTexture);
  }
  else{
    qr->setTexturePtr(mPushButtonTexture);
  }

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(corners);

  qr->drawText(tsPushButton, caption, corners, false);
  qr->reset();
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

/** Draws a Label widget
  *
  * \warning This widget is not supported by this skin. Nothing will
  *          be displayed if you use this skin in a window containing
  *          a Label.
  *
  * \param qr       The QuadRenderer used to draw
  * \param dim      The widget's dimension in pixels in a 
  *                 Ogre::Rectangle object
  * \param caption  The rendered text
  * \param parent   The parent window
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawLabel(QuadRenderer* qr, Rectangle dim, String caption, Window* parent){
  LOGW("soNavigation cannot create Label");

}

/** Graphically create a TextInput widget
  *
  * \param qr       The QuadRenderer used to draw
  * \param dim      The widget's dimension in pixels in a 
  *                 Ogre::Rectangle object
  * \param caption  The rendered text
  * \param win      The parent window
  * \param active   Is the mouse over this push button ?
  * \param selStart The selection start
  * \param selEnd   The selection end
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawTextInput(QuadRenderer* qr, Ogre::Rectangle dim, String caption, 
	      Window* win, bool active, int selStart, int selEnd){
  LOGW("soNavigation cannot create TextInput");

}

/** Draw a vertical scrollbar
  * 
  * \param qr The QuadRenderer used to draw
  * \param vs The scrollbar to draw
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawVerticalScrollbar( QuadRenderer* qr, VScrollBar* vs ){
  LOGW("soNavigation cannot create VerticalScrollbar");

}

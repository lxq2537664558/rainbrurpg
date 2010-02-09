/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file sonavigation.cpp
  * Implements a skin that draw navigation buttons
  *
  * \note We must scope the Rectangle class with its namespace in this 
  *       file to avoid complications when cross-compiling to Win32
  *       platform.
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
  Skin("soNavigation"),
  tsPushButton(NULL),
  tsLabel(NULL)
{
  tsPushButton=new TextSettings("Commonv2c.ttf", 14, 1.0f, 0.2f, 0.8f);
  tsPushButton->setVerticalAlignment( VAT_CENTER );
  tsPushButton->setHorizontalAlignment( HAT_CENTER );

  tsLabel=new TextSettings( "Iconiv2.ttf", 12, 1.0f, 0.0f, 0.0f );

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
  * It draws nothings cause Window in navigation skin is transparent.
  *
  * \param qr      The QuadRenderer used to draw
  * \param corners The window's dimension in pixels in a Ogre::Rectangle object
  * \param caption The title bar caption
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawWindow(QuadRenderer* qr, Ogre::Rectangle corners, String caption){


}

/** Graphically create a PushButton widget
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param caption The rendered text
  * \param win     The parent window
  * \param active  Is the mouse over this push button ?
  * \param enable  Is the button enabled ?
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawPushButton(QuadRenderer* qr, Vector4 dim, String caption, 
	       Window* win, bool active, bool enable){
  Ogre::Rectangle corners;
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

/** Draws a label caption
  *
  * \note \c corners is the relative position from the label's parent.
  *
  * \param qr      The renderer used to draw
  * \param corners The rectangle where the caption is printed
  * \param caption The text to be drawn
  * \param parent  The label parent
  *
  */
void RainbruRPG::OgreGui::soNavigation::
drawLabel(QuadRenderer* qr, Ogre::Rectangle corners, String caption, 
	  Window* parent){

  corners.left  += parent->getLeft();
  corners.top   += parent->getTop();
  corners.right += parent->getLeft();
  corners.bottom+= parent->getTop();

  qr->drawText(tsLabel, caption, corners, false);
  qr->reset();
}

/** Get the minimal height of the vertical scrollbar
  *
  * As soNavigation does not handle the Window TitleBar and ScrollBars
  * this function always return zero.
  *
  * \return Always 0
  *
  */
int RainbruRPG::OgreGui::soNavigation::getVScrollBarMinHeight(void){
  return 0;
}

/** Get the minimal width of the horizontal scrollbar
  *
  * As soNavigation does not handle the Window TitleBar and ScrollBars
  * this function always return zero.
  *
  * \return Always 0
  *
  */
int RainbruRPG::OgreGui::soNavigation::getHScrollBarMinWidth(void){
  return 0;
}

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

#include "mousepointer.h"

#include <logger.h>
#include <gameengine.h>
#include <quadrenderer.h>
#include <OgreRenderSystem.h>

/** The constructor
  *
  * Here we compute the screenCenterX and screenCenterY values and
  * load the Ogre texture (mTexture) using the Ogre TextureManager.
  *
  */
RainbruRPG::OgreGui::MousePointer::MousePointer():
  mState(MPS_ARROW),
  pointerWidth(32),
  pointerHeight(32)
{
  mTexture.setNull();

  // Get the size of the render window
  RenderWindow* mRenderWindow=GameEngine::getSingleton().getRenderWindow();
  unsigned int w=mRenderWindow->getWidth();
  unsigned int h=mRenderWindow->getHeight();

  // Compute the screen center
  screenCenterX=w/2;
  screenCenterY=h/2;
  
  // Set the mouse to the screen center
  mousePosX=screenCenterX;
  mousePosY=screenCenterY;

  // Load the texture
  mTexture=TextureManager::getSingleton()
    .load("bgui.pointer.png",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::MousePointer::~MousePointer(){
  TextureManager::getSingleton().unload("bgui.pointer.png");
  mTexture.setNull();
}

/** Draws the mouse pointer
  *
  * \param qr The QuadRenderer used to draw
  *
  */
void RainbruRPG::OgreGui::MousePointer::draw(QuadRenderer* qr){
  Rectangle corners;
  corners.left  =mousePosX;
  corners.top   =mousePosY;
  corners.right =mousePosX+pointerWidth;
  corners.bottom=mousePosY+pointerHeight;

  qr->setScissorRectangle(corners);
  qr->setTexturePtr(mTexture);

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->setBlendMode(QBM_ALPHA);
  qr->drawRectangle(corners);
  qr->reset();
}

/** Change the position of the mouse pointer
  *
  * \param x, y The position in pixels
  *
  */
void RainbruRPG::OgreGui::MousePointer::
setPosition(unsigned int x, unsigned int y){
  mousePosX=x;
  mousePosY=y;
}

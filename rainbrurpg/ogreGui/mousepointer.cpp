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
  pointerWidth(48),
  pointerHeight(48)
{
  mNormalTexture.setNull();
  mMoveTexture.setNull();
  mResizeTexture.setNull();

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
  mNormalTexture=TextureManager::getSingleton()
    .load("bgui.pointer.png",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mMoveTexture=TextureManager::getSingleton()
    .load("bgui.pointer.move.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mResizeTexture=TextureManager::getSingleton()
    .load("bgui.pointer.resize.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mTextTexture=TextureManager::getSingleton()
    .load("bgui.pointer.text.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
}

/** The destructor
  *
  */
RainbruRPG::OgreGui::MousePointer::~MousePointer(){
  TextureManager::getSingleton().unload("bgui.pointer.png");
  mNormalTexture.setNull();

  TextureManager::getSingleton().unload("bgui.pointer.move.png");
  mMoveTexture.setNull();

  TextureManager::getSingleton().unload("bgui.pointer.resize.png");
  mResizeTexture.setNull();

  TextureManager::getSingleton().unload("bgui.pointer.text.png");
  mTextTexture.setNull();
}

/** Draws the mouse pointer
  *
  * \param qr The QuadRenderer used to draw
  *
  */
void RainbruRPG::OgreGui::MousePointer::draw(QuadRenderer* qr){
  // Removing 16 pixels because
  Rectangle corners;
  corners.left  =mousePosX-16;
  corners.top   =mousePosY-16;
  corners.right =(mousePosX-16)+pointerWidth;
  corners.bottom=(mousePosY-16)+pointerHeight;

  qr->setBlendMode(QBM_ALPHA);
  qr->setScissorRectangle(corners);

  switch(mState){
  case MPS_ARROW:
    qr->setTexturePtr(mNormalTexture);
    break;

  case MPS_MOVE:
    qr->setTexturePtr(mMoveTexture);
    break;

  case MPS_RESIZE:
    qr->setTexturePtr(mResizeTexture);
    break;

  case MPS_TEXT:
    qr->setTexturePtr(mTextTexture);
    break;
  }

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
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

/** Change the state of this mouse pointer
  *
  * \param s The new state
  *
  */
void RainbruRPG::OgreGui::MousePointer::setState(tMousePointerState s){
  mState=s;
}

/** Get the state of this mouse pointer
  *
  * \return The mouse state
  *
  */
tMousePointerState RainbruRPG::OgreGui::MousePointer::getState(void) const{
  return mState;
}

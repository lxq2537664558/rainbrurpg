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

#include "staticimage.h"

#include "quadrenderer.h"

#include <logger.h>
#include <OgreMaterialManager.h>
#include <OgreResourceGroupManager.h>

/** The static image constructor
  *
  * \param dim    The position and dimension in pixels
  * \param parent The parent widget
  * \param sid    The Skin identifier
  *
  */
RainbruRPG::OgreGui::StaticImage::
StaticImage(Vector4 dim, Widget* parent, OgreGuiSkinID sid):
  Widget(dim, parent, sid),
  texture(NULL),
  alphaMode(QBM_NONE)
{

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::StaticImage::~StaticImage(){
  texture.setNull();
}

/** Draw the texture
  *
  * \param qr The QuadRenderer used to draw the texture
  *
  */
void RainbruRPG::OgreGui::StaticImage::draw(QuadRenderer* qr){
  qr->setBlendMode(alphaMode);
  qr->setTexturePtr(texture);
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->setAlpha(1.0f);
  qr->drawRectangle(corners);
  qr->reset();
}

/** Set the texture name and loads the Ogre texture
  *
  * \param n The texture name
  *
  */
void RainbruRPG::OgreGui::StaticImage::setTextureName(const std::string& n){
  this->textureName=n;

  try{
    texture=TextureManager::getSingleton()
      .load(n, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
	    TEX_TYPE_2D, MIP_DEFAULT, 1.0f, false, PF_A8R8G8B8);
  }
  catch(...){
    LOGE("An exception occured");
  }
}

/** Get the current texture name
  *
  * \return The current texture name
  *
  */
const std::string& RainbruRPG::OgreGui::StaticImage::
getTextureName(void)const{
  return this->textureName;
}

/** Moves the object
  *
  * \param vX, vY The new position in pixels
  *
  */
void RainbruRPG::OgreGui::StaticImage::setPosition(int vX, int vY){
  // e must remain height and width
  int width=getWidth();
  int height=getHeight();

  corners.left=vX;
  corners.top =vY;
  corners.right=vX+width;
  corners.bottom=vY+height;

}

/** Resize the object
  *
  * \param vW, vH The new sizes in pixels
  *
  */
void RainbruRPG::OgreGui::StaticImage::resize(int vW, int vH){
  corners.right=corners.left+vW;
  corners.bottom=corners.top+vH;
}

/** Set the alpha mode of this image
  *
  * \param bm The new blend mode
  *
  */
void RainbruRPG::OgreGui::StaticImage::setAlphaMode(tQuadRendererBlendMode bm){
  alphaMode=bm;
}

/** Get the alpha mode of this image
  *
  * \return The blend mode
  *
  */
tQuadRendererBlendMode RainbruRPG::OgreGui::StaticImage::
getAlphaMode(void) const{
  return alphaMode;
}

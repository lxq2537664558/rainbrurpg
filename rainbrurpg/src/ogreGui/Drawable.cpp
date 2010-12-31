/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file Drawable.cpp
  *
  * Implements an ogreGui drawable object
  *
  */

#include "Drawable.hpp"

#include <cstdlib> // for NULL
#include <logger.h>

#include <OgreTextureManager.h>
#include <OgreResourceGroupManager.h>
#include <OgreException.h>

#include "Brush.hpp"

/** The constructor
  *
  * \param vParent   The parent used for dirty flag propagation (can be NULL).
  * \param vRelative The placement of the widget
  * \param vSkinName The skin name. If an empty string is passed, the
  *                  parent's skin name will be used.
  *
  */
RainbruRPG::OgreGui::Drawable::
Drawable(Drawable* vParent, const Ogre::Rectangle& vRelative, 
	 const std::string& vSkinName):
  mParent(vParent),
  mRelative(vRelative)
#ifdef RB_DIRTY_FLAG
  ,mDirty(true)
#endif
{
  setSkinName(vSkinName);
}

/** The constructor
  *
  * \param vParent   The parent used for dirty flag propagation (can be NULL).
  * \param vX1, vY1  The position of the left/top corner relative to parent
  * \param vX2, vY2  The position of the right/bottom corner relative to parent
  * \param vSkinName The skin name. If an empty string is passed, the
  *                  parent's skin name will be used.
  *
  */
RainbruRPG::OgreGui::Drawable::
Drawable(Drawable* vParent, int vX1, int vY1, int vX2, int vY2, 
	 const std::string& vSkinName):
  mParent(vParent)
#ifdef RB_DIRTY_FLAG
  ,mDirty(true)
#endif
{
  mRelative.left   = vX1;
  mRelative.top    = vY1;
  mRelative.right  = vX2;
  mRelative.bottom = vY2;

  setSkinName(vSkinName);
}


/** The destructor
  *
  */
RainbruRPG::OgreGui::Drawable::~Drawable(void){
  mParent = NULL;
}

/** Set the value of the dirty flag
  *
  * If vDirty is \c true and mParent is not NULL, propagate the
  * dirty flag to parent.
  *
  * \param vDirty The new value for dirty flag
  *
  */
void RainbruRPG::OgreGui::Drawable::setDirty(bool vDirty){
#ifdef RB_DIRTY_FLAG
  mDirty = vDirty;

  // Propagation only for true
  if (vDirty && mParent) mParent->setDirty(true);
#endif
}

/** Get the parent
  *
  * \return The Drawable's parent (can be NULL)
  *
  */
RainbruRPG::OgreGui::Drawable* 
RainbruRPG::OgreGui::Drawable::getParent(void) const{
  return mParent;
}

/** Compute the absolute bounding box and scissor rectangle
  *
  * \param vParentX       The absolute parent X
  * \param vParentY       The absolute parent Y
  * \param vParentScissor The parent scissor rectangle
  *
  */
void RainbruRPG::OgreGui::Drawable::
compute(int vParentX, int vParentY, const Ogre::Rectangle& vParentScissor){
  computeAbsolute(vParentX, vParentY);
  adjustScissor(vParentScissor);
}

/** Compute the absolute bounding box
  *
  * \param vParentX The absolute parent X
  * \param vParentY The absolute parent Y
  *
  */
void RainbruRPG::OgreGui::Drawable::
computeAbsolute(int vParentX, int vParentY){
  mAbsolute.left   = mRelative.left   + vParentX;
  mAbsolute.right  = mRelative.right  + vParentX;
  mAbsolute.top    = mRelative.top    + vParentY;
  mAbsolute.bottom = mRelative.bottom + vParentY;
}

/** Adjust the scissor rectangle
  *
  * Based on the parent scissor passed in parameter and the absolute
  * rectangle.
  *
  * \param r The parent scissor.
  *
  */
void RainbruRPG::OgreGui::Drawable::
adjustScissor(const Ogre::Rectangle& r){
  mScissor.left  = (r.left  > mAbsolute.left)  ? r.left  : mAbsolute.left;
  mScissor.right = (r.right < mAbsolute.right) ? r.right : mAbsolute.right;
  mScissor.top   = (r.top   > mAbsolute.top)   ? r.top   : mAbsolute.top;
  mScissor.bottom= (r.bottom< mAbsolute.bottom)? r.bottom: mAbsolute.bottom;
}

/** Return the absolute rectangle 
  *
  * \return The actual dimensions
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::Drawable::getAbsolute(void)const{
  return mAbsolute;
}

/** Return the absolute scissor rectangle 
  *
  * \return The actual scissor
  *
  */
const Ogre::Rectangle& RainbruRPG::OgreGui::Drawable::getScissor(void)const
{
  return mScissor;
}

/** Get the skin name
  *
  *
  *
  */
const std::string& RainbruRPG::OgreGui::Drawable::getSkinName(void)const
{
  return mSkinName;
}

/** Change the current texture pointer
  *
  * \param vTexture The new texture pointer
  *
  */
void RainbruRPG::OgreGui::Drawable::setTexturePtr(Ogre::TexturePtr vTexture)
{
  mTexture = vTexture;
}

/** Returns the current texture pointer
  *
  * \return The content of mTexture
  *
  */
const Ogre::TexturePtr& RainbruRPG::OgreGui::Drawable::getTexturePtr(void) const
{
  return mTexture;
}

/** Set the current skin's name
  *
  * \param vSkinName The new skin name or the parent's skin name if 
  *        empty string.
  *
  */
void RainbruRPG::OgreGui::Drawable::setSkinName(const std::string& vSkinName)
{
  if (vSkinName == "" && mParent){
    mSkinName = mParent->getSkinName();
  }
  else{
    mSkinName = vSkinName;
  }
}

/** Load a texture by its filename and return it
  *
  * \param vTextureName The filename of the image file
  *
  * \throw RainbruRPG::Exception::TextureNotFoundException if the 
  *        texture cannot be found
  */
void RainbruRPG::OgreGui::Drawable::
loadTexture(const std::string& vTextureName)
  throw(TextureNotFoundException)
{
  try{
    mTexture = Ogre::TextureManager::getSingleton()
      .load(vTextureName, ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  }
  catch(const Ogre::FileNotFoundException& e){
    throw TextureNotFoundException(vTextureName);
  }
  
}

/** Load a texture by its file and skin name and return it
  *
  * \param vSkinName    The skin name
  * \param vTextureName The filename of the image file
  *
  */
void RainbruRPG::OgreGui::Drawable::
loadSkinnableTexture(const std::string& vSkinName, const std::string& vTextureName)
  throw(TextureNotFoundException,SkinNotFoundException)
{
  string textureName = vSkinName + "." + vTextureName;

  try{
    loadTexture(textureName);
  }
  catch(const TextureNotFoundException& e){
    try{
      textureName = "default." + vTextureName;
      loadTexture(textureName);
      throw SkinNotFoundException(vSkinName, vTextureName);
    }
    catch(const TextureNotFoundException& e){
      throw e;
    }
  }
}

/** A basic rectangle drawing function
  *
  * \param vBrush The brush object used to draw primitives
  *
  */
void RainbruRPG::OgreGui::Drawable::draw(Brush* vBrush)
{
  LOGCATS("Drawable::draw() for object ");
  LOGCATI((long int)(this));
  LOGCAT();

  vBrush->setBlendMode(BBM_GLOBAL);
  vBrush->setTexturePtr(mTexture);
  vBrush->setScissorRectangle(mScissor);
  vBrush->setUvMap(0.0, 0.0, 1.0, 1.0);
  vBrush->drawRectangle(mAbsolute);
  vBrush->reset();
}

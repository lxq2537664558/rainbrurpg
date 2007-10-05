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

#include "skinoverlay.h"

#include <OGRE/OgreOverlayManager.h>

/** Create a named skin based on Ogre::Overlay
  *
  * \param n The name of the new skin
  *
  */
RainbruRPG::OgreGui::SkinOverlay::SkinOverlay(std::string n) 
  :Skin(n){

}

/** Get an Ogre Overlay by its name
  *
  * This function is usefull to get an overlay after it was created. By 
  * example, if you need it to create a child. Please note that this
  * function does not control the pointer validity, so the returned 
  * one can be NULL.
  *
  * \param s The Ogre name of an overlay
  *
  * \return The Ogre overlay 
  *
  */
Ogre::OverlayContainer* RainbruRPG::OgreGui::SkinOverlay::
getOverlayByName(Ogre::String s){

  Ogre::OverlayElement* oe=Ogre::OverlayManager::getSingleton()
    .getOverlayElement(s);

  return static_cast<Ogre::OverlayContainer*>(oe);
}

/** Create a generic overlay
  *
  * This method should be called by all SkinOverlay's subclasses if
  * the parent is an Ogre::Overlay. It internally use createOverlayImpl
  * to create the Overlay.
  *
  * \sa createOverlay(String, Vector4, String, OverlayContainer*)
  *
  * \param name         The overlay name (must be unique)
  * \param dim          The overlay dimensions
  * \param materialName The overlay material name
  * \param parent       The parent overlay
  *
  */
void RainbruRPG::OgreGui::SkinOverlay::
createOverlay(String name, Vector4 dim,String materialName, Overlay* parent){

  OverlayContainer* e=createOverlayImpl(name, dim, materialName);
  parent->add2D(e);
  e->show();
}

/** Create a generic overlay
  *
  * This method should be called by all SkinOverlay's subclasses if
  * the parent is an Ogre::OverlayContainer. It internally use createOverlayImpl
  * to create the Overlay.
  *
  * \sa createOverlay(String, Vector4, String, Overlay*) 
  *
  * \param name         The overlay name (must be unique)
  * \param dim          The overlay dimensions
  * \param materialName The overlay material name
  * \param parent       The parent overlay
  *
  */
void RainbruRPG::OgreGui::SkinOverlay::
createOverlay(String name, Vector4 dim,String materialName, 
	      OverlayContainer* parent)
{

  OverlayContainer* e=createOverlayImpl(name, dim, materialName);
  parent->addChild(e);
  e->show();
}

/** Graphically creates an overly
  *
  * This fucntion is used by createOverlay(...) method to avoid
  * repeated code.
  *
  * \sa createOverlay(String, Vector4, String, Overlay*),
  *     createOverlay(String, Vector4, String, OverlayContainer*)
  *
  * \param name         The overlay name (must be unique)
  * \param dim          The overlay dimensions
  * \param materialName The overlay material name
  *
  */
Ogre::OverlayContainer* RainbruRPG::OgreGui::SkinOverlay::
createOverlayImpl(String name, Vector4 dim, String materialName){
  OverlayContainer* e=static_cast<OverlayContainer*>
    (OverlayManager::getSingleton().createOverlayElement("Panel", name));
  
  e->setMetricsMode(GMM_PIXELS);
  e->setDimensions(dim.z,dim.w);
  e->setPosition(dim.x,dim.y);
  e->setMaterialName(materialName);

  return e;
}

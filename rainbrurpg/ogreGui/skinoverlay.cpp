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

#include "bgbutton.h"

#include <logger.h>

#include <OGRE/OgreOverlayManager.h>
#include <OGRE/OgreMaterialManager.h>
#include <OGRE/OgreStringConverter.h>

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

/** Graphically creates an overlay
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

/** Graphically creates a text
  *
  * \param name     The overlay name (must be unique)
  * \param dim      The overlay dimensions
  * \param caption  The text to draw
  * \param fontName The Ogre font name
  * \param fontSize The Font size
  * \param parent   The parent container
  *
  */
void RainbruRPG::OgreGui::SkinOverlay::
createCaption(String name, Vector4 dim, String caption, 
	      String fontName, unsigned int fontSize, 
	      OverlayContainer* parent ){

  OverlayContainer* e=static_cast<OverlayContainer*>
    (OverlayManager::getSingleton().createOverlayElement("TextArea", name));
  
  e->setMetricsMode(GMM_PIXELS);
  e->setDimensions(dim.z,dim.w);
  e->setPosition(dim.x,dim.y);

  e->setCaption(caption);
  e->setParameter("font_name",fontName);
  e->setParameter("char_height",StringConverter::toString(fontSize));

  parent->addChild(e);
  e->show();
}

/** Handles the mouse over event on a button
  *
  * Buttons can are in two modes : normal and activate. The activate
  * mode is for mouse over event.
  *
  * \param button The button that is changed
  * \param active Is the button active (on mouse over), if \c false
  *               it is in normal mode.
  *
  */
void RainbruRPG::OgreGui::SkinOverlay::
activateButton(Button* button, bool active){

  String s;
  /*  s="activateButton ";
  s+=button->getName();
  LOGI(s.c_str());
  */

  Ogre::OverlayContainer* buttonOverlay= getOverlayByName(button->getName());


  if (buttonOverlay){
    String materialName=buttonOverlay->getMaterialName();

    if (active){
      ResourcePtr ma=MaterialManager::getSingleton()
	.getByName(materialName+".active");

      if(!ma.isNull()){
	buttonOverlay->setMaterialName(materialName+".active");
      }
#ifdef RAINBRU_RPG_DEBUG
      else{
	// Cannot get the .active material
	s="Cannot get material `";
	s+=materialName;
	s+=".active";
	s+="`";
	LOGW(s.c_str());
      }
#endif

    }
    else{ // deactivate
      // if materialName contains ".active"
      if (materialName.find(".active")!=string::npos){
	// We trucate materialName to remove ".active"
	materialName.resize(materialName.size()-7);
	buttonOverlay->setMaterialName(materialName);
      }
    }
  }
  else{
    LOGW("Cannot get button's overlay");
  }

}

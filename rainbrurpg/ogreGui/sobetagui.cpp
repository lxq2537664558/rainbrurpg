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
#include "bgwindow.h"


#include <logger.h>

#include <OGRE/OgreVector2.h>
#include <OGRE/OgreOverlayManager.h>
#include <OGRE/OgreOverlayContainer.h>
#include <OGRE/OgreBorderPanelOverlayElement.h>

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
  mnPushButton="bgui.button";
  mnDialogBorder="bgui.dialog.border";

  fnTitleBar="BlueHighway";
  fsTitleBar=20;	       
  fnPushButton="BlueHighway";
  fsPushButton=10;

  mnTextInput="bgui.textinput";

  fnCaption="BlueHighway";
  fsCaption=12;

  dialogBorderSize=1;
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
  * \param caption The rendered text
  * \param win     The parent window
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
createTitleBar(String name, Vector4 dim, String caption, Window* win ){
  this->createOverlay(name, dim, mnTitleBar, win->getOverLayContainer());

  // vertically center the caption
  unsigned int dev=((dim.w-fsTitleBar)/2)+1;
  dim.x+=dev;
  dim.y+=dev;

  this->createCaption(name+"c", dim, caption, 
	      fnTitleBar, fsTitleBar,win->getOverLayContainer());
}

/** Graphically create a PushButton widget
  *
  * \param name    The internal name of the ResizeGrip (must be unique)
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param caption The rendered text
  * \param win     The parent window
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
createPushButton(String name, Vector4 dim, String caption, Window* win ){
  LOGI("Creating a PushButton widget");
  this->createOverlay(name, dim, mnPushButton, win->getOverLayContainer());

  // vertically center the caption
  unsigned int dev=((dim.w-fsPushButton)/2)+2;
  dim.x+=dev;
  dim.y+=dev;

  this->createCaption(name+"c", dim, caption, 
	      fnPushButton, fsPushButton,win->getOverLayContainer());


}

/** Graphically create a TextInput widget
  *
  * \param name    The internal name of the ResizeGrip (must be unique)
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param caption The rendered text
  * \param parent  The parent window
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
createTextInput(String name, Vector4 dim, String caption, Window* parent){

  this->createOverlay(name, dim, mnTextInput, parent->getOverLayContainer());

  // vertically center the caption
  unsigned int dev=((dim.w-fsCaption)/2)+2;
  dim.x+=dev;
  dim.y+=dev;

  this->createCaption(name+"c", dim, caption, 
	      fnCaption, fsCaption, parent->getOverLayContainer());

}

/** Graphically create a Label widget
  *
  * \param name    The internal name of the ResizeGrip (must be unique)
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param caption The rendered text
  * \param parent  The parent window
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
createLabel(String name, Vector4 dim, String caption, Window* parent){
  // vertically center the caption
  unsigned int dev=((dim.w-fsCaption)/2)+2;
  dim.x+=dev;
  dim.y+=dev;

  this->createCaption(name, dim, caption, 
	      fnCaption, fsCaption, parent->getOverLayContainer());

}

/** Create a window with a border
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
createDialog(String name, Vector4 dim, String caption, BetaGUI::GUI* bg){
  LOGI("createBorderWindow called");

  BorderPanelOverlayElement* e=static_cast<BorderPanelOverlayElement*>
    (OverlayManager::getSingleton().createOverlayElement("BorderPanel", name));
  
  e->setMetricsMode(GMM_PIXELS);
  e->setDimensions(dim.z,dim.w);
  e->setPosition(dim.x,dim.y);

  // Border
  e->setBorderSize(dialogBorderSize);
  e->setBorderMaterialName(mnDialogBorder);
  e->setLeftBorderUV        (0.0000, 0.9961, 0.0039, 0.0039);
  e->setRightBorderUV       (0.9961, 0.9961, 1.0000, 0.0039);
  e->setTopBorderUV         (0.0039, 1.0000, 0.9961, 0.9961);
  e->setBottomBorderUV      (0.0039, 0.0039, 0.9961, 0.0000);
  e->setTopLeftBorderUV     (0.0000, 1.0000, 0.0039, 0.9961);
  e->setTopRightBorderUV    (0.9961, 1.0000, 1.0000, 0.9961);
  e->setBottomLeftBorderUV  (0.0000, 0.0039, 0.0039, 0.0000);
  e->setBottomRightBorderUV (0.9961, 0.0039, 1.0000, 0.0000);

  // If material name is empty, no material is applied
  String materialName=mnWindow;

  if (!materialName.empty()){
    e->setMaterialName(materialName);
    setTransparency(e, 0.0);
  }

  // Add it and show it
  bg->getDialogOverlay()->add2D(e);
  e->show();
}


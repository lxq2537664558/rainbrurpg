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
#include "quadrenderer.h"
#include "fontmanager.h"
#include "font.h"

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
RainbruRPG::OgreGui::soBetaGui::soBetaGui(): 
  SkinOverlay("soBetaGUI"),
  titleFont(NULL)
{
  mnWindow="bgui.window";
  mnTitleBar="bgui.window.titlebar";
  mnResizeGrip="bgui.window.resize";
  mnPushButton="bgui.button";
  mnDialogBorder="bgui.dialog.border";

  fnPushButton="BlueHighway";
  fsPushButton=10;

  mnTextInput="bgui.textinput";

  fnCaption="BlueHighway";
  fsCaption=12;

  dialogBorderSize=1;

  titleFont=FontManager::getSingleton().getFont("Commonv2c.ttf", 16);
}

/** Create a window using the BetaGUI skin
  *
  * It creates an overlay with a material named mnWindow.
  *
  * The name parameter must be application unique. It is the 
  * name of the Ogre overlay we create.
  *
  * \note Here is the implementation of the font texture debugger. Please
  *       see the \c DEBUG_FONT_TEXTURE_QUAD and \c DEBUG_FONT_TTF_NAME
  *       macros in fontmanager.h for further informations.
  *
  * \param qr      The QuaRdRenderer used to draw
  * \param dim     The window's dimension in pixels in a Ogre::Vector4 object
  * \param caption The title bar caption
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
drawWindow(QuadRenderer* qr, Vector4 dim, String caption){
  // Draw the window background
  Rectangle corners;
  corners.left=dim.x;
  corners.top =dim.y;
  corners.right=dim.x+dim.z;
  corners.bottom=dim.y+dim.w;

  qr->setScissorRectangle(dim.x, dim.y, dim.x+dim.z, dim.y+dim.w);
  qr->setMaterialName(mnWindow);

#ifndef DEBUG_FONT_TEXTURE_QUAD
  LOGW("Cannot get DEBUG_FONT_TEXTURE_QUAD value");
#endif

#ifndef DEBUG_FONT_TTF_NAME
  LOGW("Cannot get DEBUG_FONT_TEXTURE_NAME value");
#endif

#if (DEBUG_FONT_TEXTURE_QUAD==true)
  Font* f1=FontManager::getSingleton().getFont(DEBUG_FONT_TTF_NAME, 48);
  MaterialPtr m1=MaterialManager::getSingleton().getByName(mnWindow);
  TextureUnitState* tus=m1->getTechnique(0)->getPass(0)->getTextureUnitState(0);
  tus->setTextureName(f1->getTextureName());
#endif

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(corners);
  qr->reset();
}

/** Graphically create a ResizeGrip widget
  *
  * \param qr      The quad renderer used to draw the image
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param active  Is this resizegrip active ?
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
drawResizeGrip(QuadRenderer* qr, Vector4 dim, bool active ){
  Rectangle corners;
  corners.left=dim.x;
  corners.top =dim.y;
  corners.right=dim.x+dim.z;
  corners.bottom=dim.y+dim.w;


  qr->setScissorRectangle(dim.x, dim.y, dim.x+dim.z, dim.y+dim.w);

  if (active){
    qr->setMaterialName(mnResizeGrip+".active");
  }
  else{
    qr->setMaterialName(mnResizeGrip);
  }

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(corners);
  qr->reset();
}

/** Graphically create a TitleBar widget
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param caption The rendered text
  * \param active  Is this title ar active ?
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
drawTitleBar(QuadRenderer* qr, Vector4 dim, String caption, bool active ){
  Rectangle corners;
  corners.left=dim.x;
  corners.top =dim.y;
  corners.right=dim.x+dim.z;
  corners.bottom=dim.y+dim.w;

  qr->setScissorRectangle(dim.x, dim.y, dim.x+dim.z, dim.y+dim.w);

  if (active){
    qr->setMaterialName(mnTitleBar+".active");
  }
  else{
    qr->setMaterialName(mnTitleBar);
  }

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(corners);

  qr->drawText(titleFont, "TitleBar", corners);

  qr->reset();
}

/** Graphically create a PushButton widget
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param caption The rendered text
  * \param win     The parent window
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
drawPushButton(QuadRenderer* qr, Vector4 dim, String caption, Window* win ){
  Rectangle corners;

  corners.left  = dim.x+win->getX();
  corners.top   = dim.y+win->getY();
  corners.right = dim.x+dim.z+win->getX();
  corners.bottom= dim.y+dim.w+win->getY();


  qr->setMaterialName(mnWindow);
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(corners);
  qr->reset();


  //  this->createCaption(name+"c", dim, caption, 
  //	      fnPushButton, fsPushButton,win->getOverLayContainer());


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

/** Creates a vertical scrollbar
  *
  * \param name    The internal name of the ResizeGrip (must be unique)
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param parent  The parent window
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
createVerticalScrollbar( const String& name, Vector4 dim, Window* parent){

  LOGI("Creating a VerticalScrollbar");
  OverlayContainer* oc =parent->getOverLayContainer();

  int bodyMidHeight=dim.w-(14*4);

  dim.w=14;
  this->createOverlay(name+"ta", dim, "bgui.vscrollbar.toparrow", oc);

  dim.y+=14;
  this->createOverlay(name+"bt", dim, "bgui.vscrollbar.bodytop", oc);

  dim.y+=14;
  dim.w=bodyMidHeight;
  this->createOverlay(name+"bm", dim, "bgui.vscrollbar.bodymid", oc);

  dim.y+=bodyMidHeight;
  dim.w=14;
  this->createOverlay(name+"bb", dim, "bgui.vscrollbar.bodybot", oc);

  dim.y+=14;
  this->createOverlay(name+"ba", dim, "bgui.vscrollbar.botarrow", oc);


  // Creates the cursor
  dim.y-=(14*2)+bodyMidHeight;
  this->createOverlay(name+"c", dim, "bgui.vscrollbar.cursor", oc);
}

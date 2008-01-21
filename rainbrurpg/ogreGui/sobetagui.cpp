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

#include <dumpogreobject.h>

/** Default constructor
  *			   
  * It simply creates a SkinOverlay called \e soBetaGUI
  *
  */
RainbruRPG::OgreGui::soBetaGui::soBetaGui(): 
  SkinOverlay("soBetaGUI"),
  titleFont(NULL),
  buttonFont(NULL)
{
  mnDialogBorder="bgui.dialog.border";

  fnPushButton="BlueHighway";
  fsPushButton=10;

  mnTextInput="bgui.textinput";

  fnCaption="BlueHighway";
  fsCaption=12;

  dialogBorderSize=1;

  titleFont=FontManager::getSingleton().getFont("Commonv2c.ttf", 16);
  buttonFont=FontManager::getSingleton().getFont("Iconiv2.ttf", 12);

  // Initialize textures
  mWindowTexture=TextureManager::getSingleton()
    .load("bgui.window.png",ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mTitleBarTexture=TextureManager::getSingleton()
    .load("bgui.window.titlebar.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mTitleBarActiveTexture=TextureManager::getSingleton()
    .load("bgui.window.titlebar.active.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mResizeGripTexture=TextureManager::getSingleton()
    .load("bgui.window.resize.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mResizeGripActiveTexture=TextureManager::getSingleton()
    .load("bgui.window.resize.active.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);



  mPushButtonTexture=TextureManager::getSingleton()
    .load("bgui.button.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mPushButtonActiveTexture=TextureManager::getSingleton()
    .load("bgui.button.active.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::soBetaGui::~soBetaGui(){
  TextureManager::getSingleton().unload("bgui.window.png");
  mWindowTexture.setNull();

  TextureManager::getSingleton().unload("bgui.window.titlebar.png");
  mTitleBarTexture.setNull();

  TextureManager::getSingleton().unload("bgui.window.titlebar.active.png");
  mTitleBarActiveTexture.setNull();

  TextureManager::getSingleton().unload("bgui.window.resize.png");
  mResizeGripTexture.setNull();

  TextureManager::getSingleton().unload("bgui.window.resize.active.png");
  mResizeGripActiveTexture.setNull();

  TextureManager::getSingleton().unload("bgui.button.png");
  mPushButtonTexture.setNull();

  TextureManager::getSingleton().unload("bgui.button.active.png");
  mPushButtonActiveTexture.setNull();

}

/** Create a window using the BetaGUI skin
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
drawWindow(QuadRenderer* qr, Rectangle corners, String caption){
  // Draw the window background
  qr->setBlendMode(QBM_GLOBAL);
  qr->setScissorRectangle(corners);
  qr->setTexturePtr(mWindowTexture);
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


  qr->setBlendMode(QBM_GLOBAL);
  qr->setScissorRectangle(dim.x, dim.y, dim.x+dim.z, dim.y+dim.w);

  if (active){
    qr->setTexturePtr(mResizeGripActiveTexture);
  }
  else{
    qr->setTexturePtr(mResizeGripTexture);
  }
  
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(corners);
  qr->reset();
}

/** Graphically create a TitleBar widget
  *
  * dim's x and y member are the top left corner position, dim.z is the
  * width and dim.w is the height. The parent position is already added
  * to the top left corner position.
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The widget's dimension in pixels in a Ogre::Vector4 object
  * \param caption The rendered text
  * \param active  Is this title is active ?
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
drawTitleBar(QuadRenderer* qr, Vector4 dim, String caption, bool active ){
  Rectangle corners;
  corners.left=dim.x;
  corners.top =dim.y;
  corners.right=dim.x+dim.z;
  corners.bottom=dim.y+dim.w;

  qr->setBlendMode(QBM_GLOBAL);
  qr->setScissorRectangle(dim.x, dim.y, dim.x+dim.z, dim.y+dim.w);

  if (active){
    qr->setTexturePtr(mTitleBarActiveTexture);
  }
  else{
    qr->setTexturePtr(mTitleBarTexture);
  }
  
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(corners);

  // false = no wordwrap
  ColourValue cv(8.0f, 0.2f, 0.4f);
  corners.left+=5;
  qr->drawText(titleFont, cv, caption, corners, false, VAT_CENTER, HAT_LEFT);

  qr->reset();
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
void RainbruRPG::OgreGui::soBetaGui::
drawPushButton(QuadRenderer* qr, Vector4 dim, 
	       String caption, Window* win, bool active ){

  Rectangle corners;
  corners.left  = dim.x+win->getLeft();
  corners.top   = dim.y+win->getTop();
  corners.right = dim.x+dim.z+win->getLeft();
  corners.bottom= dim.y+dim.w+win->getTop();

  Rectangle scissor=win->getCorners();

  qr->setBlendMode(QBM_GLOBAL);
  qr->setScissorRectangle(scissor);

  if (active){
    qr->setTexturePtr(mPushButtonActiveTexture);
  }
  else{
    qr->setTexturePtr(mPushButtonTexture);
  }

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(corners);

  // false = no wordwrap
  ColourValue cv(4.0f, 0.2f, 0.8f);
  qr->drawText(buttonFont, cv, caption, corners, false, VAT_CENTER, HAT_CENTER);
  qr->reset();
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
  /*
  this->createOverlay(name, dim, mnTextInput, parent->getOverLayContainer());

  // vertically center the caption
  unsigned int dev=((dim.w-fsCaption)/2)+2;
  dim.x+=dev;
  dim.y+=dev;

  this->createCaption(name+"c", dim, caption, 
	      fnCaption, fsCaption, parent->getOverLayContainer());
  */
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
  /*
  // vertically center the caption
  unsigned int dev=((dim.w-fsCaption)/2)+2;
  dim.x+=dev;
  dim.y+=dev;

  this->createCaption(name, dim, caption, 
	      fnCaption, fsCaption, parent->getOverLayContainer());

  */
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
  /*  String materialName=mnWindow;

  if (!materialName.empty()){
    e->setMaterialName(materialName);
    setTransparency(e, 0.0);
  }
  */
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

  /*
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

  */
}

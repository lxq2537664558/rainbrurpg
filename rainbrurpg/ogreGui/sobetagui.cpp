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
#include "textsettings.h"
#include "vscrollbar.h"
#include "hscrollbar.h"

#include <logger.h>

#include <OgreVector2.h>
#include <OgreOverlayManager.h>
#include <OgreOverlayContainer.h>
#include <OgreBorderPanelOverlayElement.h>

#include <dumpogreobject.h>

/** Default constructor
  *			   
  * It simply creates a SkinOverlay called \e soBetaGUI
  *
  */
RainbruRPG::OgreGui::soBetaGui::soBetaGui(): 
  Skin("soBetaGUI"),
  tsTitleBar(NULL),
  tsPushButton(NULL),
  tsLabel(NULL),
  tsTextInput(NULL)
{
  // Define here as it is a field of Skin
  mTitleBarHeight=22;

  tsTitleBar=new TextSettings( "Commonv2c.ttf", 16, 1.0f, 0.2f, 0.4f );
  tsTitleBar->setVerticalAlignment( VAT_CENTER );

  tsPushButton=new TextSettings( "Iconiv2.ttf", 12, 1.0f, 0.2f, 0.8f );
  tsPushButton->setVerticalAlignment( VAT_CENTER );
  tsPushButton->setHorizontalAlignment( HAT_CENTER );


  tsLabel=new TextSettings( "Iconiv2.ttf", 10, 1.0f, 1.0f, 1.0f );
  tsTextInput=new TextSettings( "Iconiv2.ttf", 10, 1.0f, 1.0f, 1.0f );


  mnDialogBorder="bgui.dialog.border";
  mnTextInput="bgui.textinput";

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

  mTextInputTexture=TextureManager::getSingleton()
    .load("bgui.textinput.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mTextInputActiveTexture=TextureManager::getSingleton()
    .load("bgui.textinput.active.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);


  // ScrollBar
  mVerticalScrollBarTopArrow=TextureManager::getSingleton()
    .load("bgui.vscrollbar.toparrow.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  
  mVerticalScrollBarBottomArrow=TextureManager::getSingleton()
    .load("bgui.vscrollbar.botarrow.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  
  mVerticalScrollBarBodyTop=TextureManager::getSingleton()
    .load("bgui.vscrollbar.bodytop.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mVerticalScrollBarBodyBot=TextureManager::getSingleton()
    .load("bgui.vscrollbar.bodybot.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  
  mVerticalScrollBarBodyMid=TextureManager::getSingleton()
    .load("bgui.vscrollbar.bodymid.png",
	  ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
  
  mVerticalScrollBarCursor=TextureManager::getSingleton()
    .load("bgui.vscrollbar.cursor.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mVerticalScrollBarTopArrowActive=TextureManager::getSingleton()
    .load("bgui.vscrollbar.toparrow.active.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

 mVerticalScrollBarBotArrowActive=TextureManager::getSingleton()
   .load("bgui.vscrollbar.botarrow.active.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

 mVerticalScrollBarCursorActive=TextureManager::getSingleton()
   .load("bgui.vscrollbar.cursor.active.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

 // Horizontal scrollbar
 mHorizontalScrollBarLeftArrow=TextureManager::getSingleton()
   .load("bgui.hscrollbar.leftarrow.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

 mHorizontalScrollBarRightArrow=TextureManager::getSingleton()
   .load("bgui.hscrollbar.rightarrow.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

 mHorizontalScrollBarBodyLeft=TextureManager::getSingleton()
   .load("bgui.hscrollbar.bodyleft.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

 mHorizontalScrollBarBodyMid=TextureManager::getSingleton()
   .load("bgui.hscrollbar.bodymid.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

 mHorizontalScrollBarBodyRight=TextureManager::getSingleton()
   .load("bgui.hscrollbar.bodyright.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

 mHorizontalScrollBarCursor=TextureManager::getSingleton()
   .load("bgui.hscrollbar.cursor.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);



mHorizontalScrollBarLeftArrowActive=TextureManager::getSingleton()
   .load("bgui.hscrollbar.leftarrow.active.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mHorizontalScrollBarRightArrowActive=TextureManager::getSingleton()
   .load("bgui.hscrollbar.rightarrow.active.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

  mHorizontalScrollBarCursorActive=TextureManager::getSingleton()
   .load("bgui.hscrollbar.cursor.active.png",
	 ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::soBetaGui::~soBetaGui(){

  delete tsTitleBar;
  tsTitleBar=NULL;

  delete tsPushButton;
  tsPushButton=NULL;

  delete tsLabel;
  tsLabel=NULL;

  delete tsTextInput;
  tsTextInput=NULL;

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

  TextureManager::getSingleton().unload("bgui.textinput.png");
  mTextInputTexture.setNull();

  TextureManager::getSingleton().unload("bgui.textinput.active.png");
  mTextInputActiveTexture.setNull();



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
  * \param corners The window's dimension in pixels in a Ogre::Rectangle object
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
  qr->setScissorRectangle(corners);

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
  corners.left+=5;
  qr->drawText( tsTitleBar, caption, corners, false );
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
  qr->drawText(tsPushButton, caption, corners, false);
  qr->reset();
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

void RainbruRPG::OgreGui::soBetaGui::
drawLabel(QuadRenderer* qr, Rectangle corners, String caption, 
	  Window* parent){

  corners.left  += parent->getLeft();
  corners.top   += parent->getTop();
  corners.right += parent->getLeft();
  corners.bottom+= parent->getTop();

  qr->drawText(tsLabel, caption, corners, false);
  qr->reset();
}

/** Draws a TextInput widget
  *
  * \warning This widget is not supported by this skin. Nothing will
  *          be displayed if you use this skin in a window containing
  *          a TextInput.
  *
  * \param qr       The QuadRenderer used to draw
  * \param corners  The widget's dimension in pixels in a 
  *                 Ogre::Rectangle object
  * \param caption  The rendered text
  * \param win      The parent window
  * \param vActive  Is the mouse over this push button ?
  * \param selStart The selection start
  * \param selEnd   The selection end
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
drawTextInput(QuadRenderer* qr, Rectangle corners, String caption,  
	      Window* win, bool vActive, int selStart, int selEnd){

  corners.left  += win->getLeft();
  corners.top   += win->getTop();
  corners.right += win->getLeft();
  corners.bottom+= win->getTop();

  Rectangle scissor=win->getCorners();

  qr->setBlendMode(QBM_GLOBAL);
  qr->setScissorRectangle(scissor);

  if (vActive){
    qr->setTexturePtr(mTextInputActiveTexture);
  }
  else{
    qr->setTexturePtr(mTextInputTexture);
  }

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(corners);

  // Draw text
  corners.left  += 4;
  qr->drawText(tsTextInput, caption, corners, false);
  qr->reset();
}

/** Draw a vertical scrollbar
  * 
  * \param qr The QuadRenderer used to draw
  * \param vs The scrollbar to draw
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
drawVerticalScrollbar(QuadRenderer* qr, VScrollBar* vs ){

  qr->setBlendMode(QBM_GLOBAL);
  qr->setScissorRectangle(vs->getTopArrowCorners());

  if ( vs->isTopArrowActive() )
    qr->setTexturePtr(mVerticalScrollBarTopArrowActive);
  else
    qr->setTexturePtr(mVerticalScrollBarTopArrow);

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(vs->getTopArrowCorners());
  qr->reset();

  qr->setScissorRectangle(vs->getBottomArrowCorners());

  if ( vs->isBottomArrowActive() )
    qr->setTexturePtr(mVerticalScrollBarBotArrowActive);
  else
    qr->setTexturePtr(mVerticalScrollBarBottomArrow);

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(vs->getBottomArrowCorners());
  qr->reset();

  qr->setScissorRectangle(vs->getBodyTopCorners());
  qr->setTexturePtr(mVerticalScrollBarBodyTop);
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(vs->getBodyTopCorners());
  qr->reset();


  qr->setScissorRectangle(vs->getBodyBotCorners());
  qr->setTexturePtr(mVerticalScrollBarBodyBot);
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(vs->getBodyBotCorners());
  qr->reset();


  qr->setScissorRectangle(vs->getBodyMidCorners());
  qr->setTexturePtr(mVerticalScrollBarBodyMid);
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(vs->getBodyMidCorners());
  qr->reset();


  qr->setScissorRectangle(vs->getCursorCorners());
  
  if ( vs->isCursorActive() )
    qr->setTexturePtr(mVerticalScrollBarCursorActive);
  else
    qr->setTexturePtr(mVerticalScrollBarCursor);
  
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(vs->getCursorCorners());
  qr->reset();

}

/** Draws a horizontal scrollbar
  *
  * \param qr The QuadRenderer object
  * \param hs The scroll bar to draw
  *
  */
void RainbruRPG::OgreGui::soBetaGui::
drawHorizontalScrollbar(QuadRenderer*qr, HScrollBar* hs ){

  qr->setBlendMode(QBM_GLOBAL);
  
  // Left arrow
  qr->setScissorRectangle(hs->getLeftArrowCorners());
  if (hs->isLeftArrowActive()){
    qr->setTexturePtr(mHorizontalScrollBarLeftArrowActive);
  }
  else{
    qr->setTexturePtr(mHorizontalScrollBarLeftArrow);
  }
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(hs->getLeftArrowCorners());
  qr->reset();

  // Right arrow
  qr->setScissorRectangle(hs->getRightArrowCorners());
  if (hs->isRightArrowActive()){
    qr->setTexturePtr(mHorizontalScrollBarRightArrowActive);
  }
  else{
    qr->setTexturePtr(mHorizontalScrollBarRightArrow);
  }

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(hs->getRightArrowCorners());
  qr->reset();

  // Left body
  qr->setScissorRectangle(hs->getBodyLeftCorners());
  qr->setTexturePtr(mHorizontalScrollBarBodyLeft);
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(hs->getBodyLeftCorners());
  qr->reset();

  // Middle body
  qr->setScissorRectangle(hs->getBodyMidCorners());
  qr->setTexturePtr(mHorizontalScrollBarBodyMid);
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(hs->getBodyMidCorners());
  qr->reset();

  // Right body
  qr->setScissorRectangle(hs->getBodyRightCorners());
  qr->setTexturePtr(mHorizontalScrollBarBodyRight);
  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(hs->getBodyRightCorners());
  qr->reset();

  // Cursor
  qr->setScissorRectangle(hs->getCursorCorners());

  if (hs->isCursorActive()){
    qr->setTexturePtr(mHorizontalScrollBarCursorActive);
  }
  else{
    qr->setTexturePtr(mHorizontalScrollBarCursor);
  }

  qr->setUvMap(0.0, 0.0, 1.0, 1.0);
  qr->drawRectangle(hs->getCursorCorners());
  qr->reset();

}

void RainbruRPG::OgreGui::soBetaGui::
drawMultiColumnList(QuadRenderer*qr, MultiColumnList* mcl ){
  LOGI("soBetaGui::drawMultiColumnList");
  qr->setBlendMode(QBM_GLOBAL);
  qr->drawLine(10, 40, 120, 150, Ogre::ColourValue( 1.0f, 0.0f, 0.0f, 1.0f ));
  qr->reset();
  
}

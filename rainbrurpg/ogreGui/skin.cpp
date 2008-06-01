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

#include "skin.h"

#include "bgbutton.h"
#include "quadrenderer.h"

#include <logger.h>

#include <OgreOverlayManager.h>
#include <OgreMaterialManager.h>
#include <OgreStringConverter.h>
#include <OgreTechnique.h>
#include <OgreTextureUnitState.h>
#include <OgreTextAreaOverlayElement.h>

/** Create a named skin 
  *
  * \param vName The name of the new skin
  *
  */
RainbruRPG::OgreGui::Skin::Skin(const std::string& vName):
  mTitleBarHeight(0),
  mName(vName)
{

}

/** Get the dialog border size
  *
  * This function is used by the \ref BetaGUI::Window "Window" 
  * constructor to place and resize
  * TitleBar and ResizeGrip according to the border size.
  *
  * \return The border size in pixels
  *
  */
unsigned int RainbruRPG::OgreGui::Skin::getDialogBorderSize(void){
  return this->dialogBorderSize;
}

/** Get the TitleBar's height in pixels
  *
  * \return The height of the TitleBar in pixels
  *
  */
int RainbruRPG::OgreGui::Skin::getTitleBarHeight(void){
  return mTitleBarHeight;
}

/** Log a message for an unimplemented function
  *
  * \param vFunctionName unimplemented function's name
  *
  */
void RainbruRPG::OgreGui::Skin::
logUnimplementedFunction(const std::string& vFunctionName){
  std::string l;
  l += vFunctionName;
  l += " function unimplemented for skin ";
  l += mName;
  LOGW(l.c_str());
}


/** Create a window
  *
  * Please see the sub-class documentation for implementation
  * details.
  *
  * \param qr      The QuadRenderer used to draw
  * \param corners The window's dimension in pixels in a 
  *                Ogre::Rectangle object
  * \param caption The title bar caption
  *
  */
void RainbruRPG::OgreGui::Skin::drawWindow(QuadRenderer*qr, Rectangle corners, 
					   String caption){
  logUnimplementedFunction("drawWindow");
}

/** Graphically create a ResizeGrip widget
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The widget's dimension in pixels in a 
  *                Ogre::Vector4 object
  * \param active  Is this ersize grip is active ?
  *
  */
void RainbruRPG::OgreGui::Skin::
drawResizeGrip(QuadRenderer*qr, Vector4 dim, bool active){
  logUnimplementedFunction("drawResizeGrip");

}

/** Graphically create a TitleBar widget
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The widget's dimension in pixels in a 
  *                Ogre::Vector4 object
  * \param caption The rendered text
  * \param active  Is this titlebar active
  *
  */
void RainbruRPG::OgreGui::Skin::
drawTitleBar(QuadRenderer* qr, Vector4 dim, String caption, bool active){
  logUnimplementedFunction("drawTitleBar");

}

/** Graphically create a PushButton widget
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The widget's dimension in pixels in a 
  *                Ogre::Vector4 object
  * \param caption The rendered text
  * \param parent  The parent window
  * \param active  Is the mouse over this push button ?
  *
  */
void RainbruRPG::OgreGui::Skin::
drawPushButton(QuadRenderer*qr, Vector4 dim, String caption, 
	       Window* parent, bool active){
  logUnimplementedFunction("drawPushButton");

}

/** Graphically create a TextInput widget
  *
  * \param qr       The QuadRenderer used to draw
  * \param dim      The widget's dimension in pixels in a 
  *                 Ogre::Rectangle object
  * \param caption  The rendered text
  * \param win      The parent window
  * \param active   Is the mouse over this push button ?
  * \param selStart The selection start
  * \param selEnd   The selection end
  *
  */
void RainbruRPG::OgreGui::Skin::
drawTextInput(QuadRenderer* qr, Rectangle dim, String caption, Window* win, 
	      bool active, int selStart, int selEnd){
  logUnimplementedFunction("drawTextInput");

}

/** Graphically create a Label widget
  *
  * \param qr      The QuadRenderer used to draw
  * \param dim     The widget's dimension in pixels in a 
  *                Ogre::Vector4 object
  * \param caption The rendered text
  * \param parent  The parent window
  *
  */
void RainbruRPG::OgreGui::Skin::
drawLabel(QuadRenderer*qr, Rectangle dim, String caption, Window* parent){
  logUnimplementedFunction("drawLabel");

}

/** Draw a tool tip
  *
  * \param qr The QuadRenderer used to draw
  * \param tt The ToolTip
  *
  */
void RainbruRPG::OgreGui::Skin::
drawToolTip(QuadRenderer*qr, ToolTip* tt){
  logUnimplementedFunction("drawToolTip");

}

/** Draw a vertical scrollbar
  *  
  * \param qr The QuadRenderer used to draw
  * \param sb The scrollbar to draw
  *
  */
void RainbruRPG::OgreGui::Skin::
drawVerticalScrollbar(QuadRenderer*qr, VScrollBar* sb ){
  logUnimplementedFunction("drawVerticalScrollbar");

}

/** Draws a horizontal scrollbar
  *
  * \param qr The QuadRenderer object
  * \param hs The scroll bar to draw
  *
  */
void RainbruRPG::OgreGui::Skin::
drawHorizontalScrollbar(QuadRenderer*qr, HScrollBar* hs ){
  logUnimplementedFunction("drawHorizontalScrollbar");
}

/** Draws a MultiColumnList
  *
  * \param qr          The QuadRenderer used to draw
  * \param mcl         The MultiColumnList to draw
  * \param geoWasDirty Was the widget's geometryDirty flag on before this draw?
  *                    (The widget moved or is resized).
  *
  */
void RainbruRPG::OgreGui::Skin::
drawMultiColumnList(QuadRenderer*qr, MultiColumnList* mcl, bool geoWasDirty ){
  logUnimplementedFunction("drawMultiColumnList");

}

/** Draws a popup menu widget
  *
  * \param qr The QuadRenderer used to draw
  * \param pm The PopupMenu to be drawn
  *
  */
void RainbruRPG::OgreGui::Skin::drawPopupMenu(QuadRenderer*qr, PopupMenu* pm){
  logUnimplementedFunction("drawPopupMenu");

}

/** Draws a Dialog widget
  *
  * \param vQr     The QuadRenderer used to draw
  * \param vDialog The PopupMenu to be drawn
  *
  */
void RainbruRPG::OgreGui::Skin::drawDialog(QuadRenderer* vQr, Dialog* vDialog){
  logUnimplementedFunction("drawDialog");

}

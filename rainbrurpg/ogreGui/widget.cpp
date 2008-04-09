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

#include "widget.h"

#include <logger.h>
#include "bgwindow.h"


/** A constructor passing the skin identifier
  *
  * \param dim The dimensions of the widget in pixels
  * \param sid The SkinIdentifier
  * \param P   The parent widget
  *
  */
RainbruRPG::OgreGui::Widget::
Widget(Vector4 dim, Widget* P, RainbruRPG::OgreGui::OgreGuiSkinID sid):
  skinId(sid),
  parent(P),
  frameOverlay(NULL),
  alpha(0.0f),
  geometryDirty(false),
  visible(true)
{
  corners.left   = dim.x;
  corners.top    = dim.y;
  corners.right  = dim.x+dim.z;
  corners.bottom = dim.y+dim.w;

  // Doesn't test the parent pointer for Window as a Window
  // has always NULL parent
  Window* win=dynamic_cast<Window*>(this);
  if (win!=NULL){
    LOGA(parent, "Widget's parent is NULL");
  }
}    

/** Destructor
  *
  */
RainbruRPG::OgreGui::Widget::~Widget(){

}

/** Get the skin identifier of this widget
  *
  * \return The current skin identifier
  *
  */
RainbruRPG::OgreGui::OgreGuiSkinID 
RainbruRPG::OgreGui::Widget::getSkinId(void){

  return this->skinId;
}

/** Change this widget's name
  *
  * \param s The new widget's name
  *
  */
void RainbruRPG::OgreGui::Widget::setName(const Ogre::String& s){
  this->name=s;
}

/** Get the name of the widget
  *
  * \return The widget's name
  *
  */
const Ogre::String& RainbruRPG::OgreGui::Widget::getName(void){
  return this->name;
}

/** Get the widget's parent
  *
  * \return The parent widget
  *
  */
RainbruRPG::OgreGui::Widget* RainbruRPG::OgreGui::Widget::getParent(){
  return this->parent;
}

/** Handle a mouse event
  *
  * If you create a new widget, you may override this function if your
  * widget handles mouse events and return \c true to stop the event handling
  * loop.
  *
  * The position of the mouse is render window wide.
  *
  * \param x     The position of the mouse pointer in pixels
  * \param y     The position of the mouse pointer in pixels
  * \param event The mouse event
  *
  * \return \c true if the event is handled, \c false if not.
  *
  */
bool RainbruRPG::OgreGui::Widget::
injectMouse(unsigned int x, unsigned int y, const MouseEvent& event){
  return false;
}

/** Change the X position of the widget
  *
  * \param i The new X position in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::corners corners \endlink (member)
  *
  */
void RainbruRPG::OgreGui::Widget::setLeft(int i){
  corners.left=i;
  geometryDirty=true;
}

/** Change the Y position of the widget
  *
  * \param i The new Y position in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::corners corners \endlink (member)
  *
  */
void RainbruRPG::OgreGui::Widget::setTop(int i){
  corners.top=i;
  geometryDirty=true;
}

/** Change the width of the widget
  *
  * \param i The new width in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::corners corners \endlink (member)
  *
  */
void RainbruRPG::OgreGui::Widget::setWidth(int i){
  corners.right=corners.left+i;
  geometryDirty=true;
}

/** Change the height of the widget
  *
  * \param i The new height in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::corners corners \endlink (member)
  *
  */
void RainbruRPG::OgreGui::Widget::setHeight(int i){
  corners.bottom=corners.top+i;
  geometryDirty=true;
}

/** Get the width of this widget
  *
  * \return The width in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::corners corners \endlink (member)
  *
  */
int RainbruRPG::OgreGui::Widget::getWidth(void) const{
  return corners.right-corners.left;
}

/** Get the height of this widget
  *
  * \return The height in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::corners corners \endlink (member)
  *
  */
int RainbruRPG::OgreGui::Widget::getHeight(void) const{
  return corners.bottom-corners.top;
}

/** A pure virtual function used to set the transparency of the widget
  *
  * \param f A float number between 0.0f (fully transparent) and 
  *          1.0f (opaque).
  *
  */
void RainbruRPG::OgreGui::Widget::setTransparency(float f){
  alpha=f;
}

/** Resize this widget
  *
  * This resizes the widget, moves its resizeGrip and resize its TitleBar.
  *
  * \param px The mouse pointer position in pixels
  * \param py The mouse pointer position in pixels
  *
  */
void RainbruRPG::OgreGui::Widget::resize(int px, int py){
  int height, width;
  width=px-corners.left;
  height=py-corners.top;
  geometryDirty=true;
}

/** Move this widget
  *
  * This moves the widget and set the geometryDirty flag to \c true.
  *
  * \param px The new left position
  * \param py The new top position
  *
  */
void RainbruRPG::OgreGui::Widget::move(int px, int py){
  int width  = corners.right - corners.left;
  int height = corners.bottom - corners.top;

  corners.left=px;
  corners.top=py;

  // Negative position is forbiden
  if (corners.left<0) corners.left=0;
  if (corners.top<0)  corners.top=0;

  corners.right=corners.left+width;
  corners.bottom=corners.top+height;
  geometryDirty=true;
}

/** Set this widget's geometry dirty
  *
  * \sa \ref RainbruRPG::OgreGui::Widget::geometryDirty "geometryDirty" 
  *     (member).
  *
  */
void RainbruRPG::OgreGui::Widget::setGeometryDirty(void){

  geometryDirty=true;

}

/** Hide this widget
  *
  */
void RainbruRPG::OgreGui::Widget::hide(){
  visible=false;
}

/** Set this widget visible
  *
  */
void RainbruRPG::OgreGui::Widget::show(){
  visible=true;
}

/** Is ths widget visible ?
  *
  * \return \c true if this window is visible otherwise return \c false
  *
  */
bool RainbruRPG::OgreGui::Widget::isVisible(){
  return this->visible;
}

/** Change the visibility state of this widget
  *
  * \param b The new value
  *
  */
void RainbruRPG::OgreGui::Widget::setVisible(bool b){
  visible=b;
}

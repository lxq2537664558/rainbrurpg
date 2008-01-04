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
  x(dim.x),
  y(dim.y),
  width(dim.z),
  height(dim.w),
  alpha(0.0f)
{

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
  * \param x               The position of the mouse pointer in pixels
  * \param y               The position of the mouse pointer in pixels
  * \param leftMouseButton The mouse left button state ( \c true if pressed
  *                        \c false if released)
  *
  * \return \c true if the event is handled, \c false if not.
  *
  */
bool RainbruRPG::OgreGui::Widget::
injectMouse(unsigned int x, unsigned int y, bool leftMouseButton){
  return false;
}

/** Change the X position of the widget
  *
  * \param i The new X position in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::x x \endlink (member)
  *
  */
void RainbruRPG::OgreGui::Widget::setX(int i){
  this->x=i;
}

/** Change the Y position of the widget
  *
  * \param i The new Y position in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::y y \endlink (member)
  *
  */
void RainbruRPG::OgreGui::Widget::setY(int i){
  this->y=i;
}

/** Change the width of the widget
  *
  * \param i The new width in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::width width \endlink (member)
  *
  */
void RainbruRPG::OgreGui::Widget::setWidth(int i){
  this->width=i;
}

/** Change the height of the widget
  *
  * \param i The new height in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::height height \endlink (member)
  *
  */
void RainbruRPG::OgreGui::Widget::setHeight(int i){
  this->height=i;
}

/** Get the X position of this widget
  *
  * \return The X position in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::x x \endlink (member)
  *
  */
int RainbruRPG::OgreGui::Widget::getX(void){
  return this->x;
}

/** Get the Y position of this widget
  *
  * \return The Y position in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::y y \endlink (member)
  *
  */
int RainbruRPG::OgreGui::Widget::getY(void){
  return this->y;
}

/** Get the width of this widget
  *
  * \return The width in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::width width \endlink (member)
  *
  */
int RainbruRPG::OgreGui::Widget::getWidth(void){
  return this->width;
}

/** Get the height of this widget
  *
  * \return The height in pixels
  *
  * \sa \link RainbruRPG::OgreGui::Widget::height height \endlink (member)
  *
  */
int RainbruRPG::OgreGui::Widget::getHeight(void){
  return this->height;
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

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

#include "widget.h"

#include <logger.h>
#include "bgwindow.h"


/** A constructor passing the skin identifier
  *
  * \param sid The SkinIdentifier
  * \param P   The parent widget
  *
  */
RainbruRPG::OgreGui::Widget::
Widget(Widget* P, RainbruRPG::OgreGui::OgreGuiSkinID sid):
  skinId(sid),
  parent(P),
  frameOverlay(NULL)
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

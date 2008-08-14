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

/** \file optionbutton.cpp
  * Implements a button for the launcher's options editor
  *
  *
  */

#include "optionbutton.h"

/** A constructuion that initialize the m_caption
  *
  * It will create a button without icon if you do not call
  * setIconFileName() later. It initialize foxPanelId to -1.
  *
  * \param caption The caption (the shown text) of the button
  */
RainbruRPG::Options::OptionButton::OptionButton(const char* caption){
  LOGW("You are creating a OptionButton without an Icon");
  this->setCaption(caption);
  foxPanelId=-1;
}

/** A constructor that initialize m_caption and m_iconFilename
  *
  * \param caption The caption (the shown text) of the button
  * \param filename The filename of the icon
  *
  */
RainbruRPG::Options::OptionButton::OptionButton(const char* caption, 
						const char* filename){

  this->setCaption(caption);
  this->setIconFilename(filename);
}


/** Set the caption of the OptionButton
  *
  * It logs a warning message if the caption string is empty.
  *
  * \param caption The caption (the shown text) of the button
  *
  */
void RainbruRPG::Options::OptionButton::setCaption(const char* caption){
  if (strlen(caption)==0){
    LOGW("You are setting an empty caption");
  }
  this->m_caption=caption;
}

/** Set the caption of the OptionButton
  *
  * It logs a warning message if the filename string is empty.
  *
  * \param filename The filename of the icon
  *
  */
void RainbruRPG::Options::OptionButton::setIconFilename(const char* filename){
  if (strlen(filename)==0){
    LOGW("You are setting an empty icon filename");
  }
  this->m_iconFilename=filename;
}

/** Get the caption
  *
  * \return The caption of this OptionButton
  *
  */
const char* RainbruRPG::Options::OptionButton::getCaption(){
  return m_caption;
}

/** Get the filename of the icon
  *
  * \return The filename of the icon
  *
  */
const char* RainbruRPG::Options::OptionButton::getIconFilename(){
  return this->m_iconFilename;
}

/** Change the fox panel identifier
  *
  *
  * \param i the new value for foxPanelId
  *
  * \sa foxPanelId, getFoxPanelId()
  *
  */
void RainbruRPG::Options::OptionButton::setFoxPanelId(int i){
  this->foxPanelId=i;
}

/** get the identifier of the associated fox panel
  *
  *
  *
  * \return the value of foxPanelId or -1 if setFoxPanelId() was never 
  *         called
  *
  * \sa foxPanelId, setFoxPanelId()
  *
  */
int RainbruRPG::Options::OptionButton::getFoxPanelId(){
  return this->foxPanelId;
}

/** Adds an OptionAttribute
  *
  * \param it The attribute to add
  *
  */
void RainbruRPG::Options::OptionButton::add(OptionAttribute* it){
  attrbList.push_back( it );
}

/** Get the list of attribute
  *
  * \return A pointer to the STL OptionAttribute list
  *
  */
RainbruRPG::Options::tOptionAttributeList* 
RainbruRPG::Options::OptionButton::getAttributeList(){
  return &attrbList;
}

/** Graphically update the attributes content
  *
  * It simply calls update() for all OptionAttribute
  *
  * \sa OptionAttribute::update()
  *
  */
void RainbruRPG::Options::OptionButton::update(){

  tOptionAttributeList::const_iterator iter;

  // Iterate through list and output each element.
  for (iter=attrbList.begin(); iter != attrbList.end(); iter++){
    (*iter)->update();
  }
}

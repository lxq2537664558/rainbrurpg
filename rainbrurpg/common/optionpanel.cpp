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

#include "optionpanel.h"


/** A constructor setting the caption
  *
  * \param caption The caption of the panel
  *
  */
RainbruRPG::Options::OptionPanel::OptionPanel(const char* caption){
  this->setCaption(caption);
}


/** Sets the caption of this panel
  *
  * \param caption The caption of the panel
  *
  */
void RainbruRPG::Options::OptionPanel::setCaption(const char* caption){
  if (strlen(caption)==0){
    LOGW("You are setting an empty caption");
  }
  this->m_caption=caption;
}

/** Get the caption of the panel
  *
  * \return the caption of the panel
  *
  */
const char* RainbruRPG::Options::OptionPanel::getCaption(){
  return this->m_caption;
}

/** Adds an OptionButton
  *
  * \param ob The button to add to this panel
  *
  */
void RainbruRPG::Options::OptionPanel::add(OptionButton* ob){
  if (ob)
    buttonList.push_back(ob);
  else 
    LOGW ("You are adding a NULL OptionButton pointer");
}

/** Get the OptionButton list
  *
  * \return The OptionButton list
  *
  */
RainbruRPG::Options::tOptionButtonList* 
RainbruRPG::Options::OptionPanel::getButtonList(){

  return &buttonList;
}

/** Get the number of buttons
  *
  * It gives the size of the buttonList.
  *
  * \return the number of buttons of this panel
  *
  */
unsigned int RainbruRPG::Options::OptionPanel::buttonCount(){
  return buttonList.size();
}

/** Returns a pointer to an existing OptionButton
  *
  * Iterates through the OptionButton list, if the name passed in
  * parameter is used, return a pointer to this, otherwise, returns \c NULL.
  *
  * This function uses std::strcmp.
  *
  * \param n The caption of the button to search
  *
  * \return A pointer to the existing button or \c NULL if not found.
  *
  * \sa OptionButton
  */
RainbruRPG::Options::OptionButton* 
RainbruRPG::Options::OptionPanel::getButtonByName(const char* n){

  OptionButton* ret=NULL;

  tOptionButtonList::const_iterator iter;

  // Iterate through list and output each element.
  for (iter=buttonList.begin(); iter != buttonList.end(); iter++){
    const char*name=(*iter)->getCaption();

    if (strcmp(name, n)==0)
      ret=(*iter);

  }

  return ret;


}

/** Graphically update the attributes content
  *
  * It simply calls update() for all OptionButton
  *
  * \sa OptionButton::update()
  *
  */
void RainbruRPG::Options::OptionPanel::update(){

  tOptionButtonList::const_iterator iter;
  
  // Iterate through list and output each element.
  for (iter=buttonList.begin(); iter != buttonList.end(); iter++){
    (*iter)->update();
  }
}

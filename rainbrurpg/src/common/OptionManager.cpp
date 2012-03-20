/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file OptionManager.cpp
  * Implements the option manager singleton
  *
  */

#include "OptionManager.hpp"

#include "XmlOptions.hpp"

/** Initialize the OptionManager
  *
  * It sets damage to \c false and creates a new Options instance.
  *
  */
void RainbruRPG::Options::OptionManager::init(){
  LOGI(_("Initializing OptionManager"));
  this->damage=false;
  options=new Options();
}

/** Adds an OptionPanel
  *
  * It simply push_back the given OptionPanel to the panelList.
  *
  * \param op The OptionPanel to add
  *
  */
void RainbruRPG::Options::OptionManager::add(OptionPanel* op){
  this->panelList.push_back(op);
}

/** Get the panel list
  *
  * \return A stl list of OptionPanel
  *
  */
RainbruRPG::Options::tOptionPanelList* 
RainbruRPG::Options::OptionManager::getPanelList(){
  return &this->panelList;
}

/** Return the size of the panelList
  *
  * \return The number of panel
  */
unsigned int RainbruRPG::Options::OptionManager::panelCount(){
  return this->panelList.size();
}

/** Destructs the OptionManager
  *
  * It delete the Options instance.
  *
  */
void RainbruRPG::Options::OptionManager::cleanup(){
  options->~Options();
  options=NULL;
}


/** Returns a pointer to an existing OptionPanel
  *
  * Iterates through the OptionPanel list, if the name passed in
  * parameter is used, return a pointer to this, otherwise, returns \c NULL.
  *
  * This function uses std::strcmp.
  *
  * \param n The caption of the panel to search
  *
  * \return A pointer to the existing panel or \c NULL if not found.
  *
  * \sa OptionPanel
  */
RainbruRPG::Options::OptionPanel* 
RainbruRPG::Options::OptionManager::getPanelByName(const char* n){

  OptionPanel* ret=NULL;

  tOptionPanelList::const_iterator iter;

  // Iterate through list and output each element.
  for (iter=panelList.begin(); iter != panelList.end(); iter++){
    const char*name=(*iter)->getCaption();

    if (strcmp(name, n)==0)
      ret=(*iter);

  }

  return ret;

}

/** Returns a pointer to an existing OptionButton
  *
  * Iterates through the OptionPanel list, if the first name passed in
  * parameter is used, we search in its button list for a button.
  *
  * This function uses std::strcmp.
  *
  * \param p The caption of the panel to search
  * \param b The caption of the button to search
  *
  * \return A pointer to the existing button or \c NULL if not found.
  *
  * \sa OptionPanel, OptionButton
  */
RainbruRPG::Options::OptionButton* 
RainbruRPG::Options::OptionManager::getButtonByName(const char* p, 
						    const char* b){


  OptionButton* ret=NULL;

  OptionPanel* panel=getPanelByName(p);

  if (panel){
    ret=panel->getButtonByName(b);
  }
  else{
    GTS_TIN(str);
    // TRANSLATORS: The parameter is a OptionPanel object name
    sprintf(str, _("Cannot get the OptionPanel named '%s'"), p);
    LOGW(str);
  }

  return ret;
}

/** Graphically update the attributes content
  *
  * It simply calls update() for all OptionPanel
  *
  * \sa OptionPanel::update()
  *
  */
void RainbruRPG::Options::OptionManager::update(){
  tOptionPanelList::const_iterator iter;

  // Iterate through list and output each element.
  for (iter=panelList.begin(); iter != panelList.end(); iter++){
    (*iter)->update();
  }
}

/** Sets the damage of the OptionManager
  *
  * \param b Ther new value of damage
  *
  * \sa damage
  *
  */
void RainbruRPG::Options::OptionManager::setDamage(bool b){
  this->damage=b;
}

/** Gets the damage value
  *
  * \return The value of damage
  *
  * \sa damage
  *
  */
bool RainbruRPG::Options::OptionManager::isDamage(){
  return damage;
}

/** Creates attributes of Options
  *
  * It simply calls createAttributes on options
  *
  */
void RainbruRPG::Options::OptionManager::createAttributes(){
  options->createAttributes();
}

/** Set the default attributes of the options
  *
  * It simply calls setDefaultValues on options
  *
  */
void RainbruRPG::Options::OptionManager::setAttributesDefaultValues(){
  options->setDefaultValues();
}

/** Save the current snapshot with the given name
  *
  * \param c The name of the snapshot to save
  *
  */
void RainbruRPG::Options::OptionManager::saveCurrentSnapshot(const char* c){
  xmlOptions o;
  o.saveSnapshot(c, &panelList);
}

/** Loads the snapshot with the given name
  *
  * \param c The name of the snapshot to load
  *
  */
void RainbruRPG::Options::OptionManager::loadSnapshot(const char* c){
  GTS_TIN(str);
  // TRANSLATORS: The parameter is the name of an option snapshot.
  sprintf(str, _("Loading options snapshots named '%s'"), c);
  LOGI(str);

  xmlOptions o;
  o.loadSnapshot( c, &panelList);
  update();
}

/** Deletes the snapshot with the given name
  *
  * \param c The name of the snapshot to delete
  *
  */
void RainbruRPG::Options::OptionManager::deleteSnapshot(const char* c){
  xmlOptions o;
  o.deleteSnapshot(c);
}

/** Set the LastUse value
  *
  * It calls xmlOptions::setLastUse()
  *
  * \param c The new LastUse value
  *
  */
void RainbruRPG::Options::OptionManager::setLastUse(const char* c){
  xmlOptions o;
  o.setLastUse(c);
}

/** Get the LastUse value
  *
  * It calls xmlOptions::getLastUse()
  *
  * \return The LastUse value
  *
  */
const char* RainbruRPG::Options::OptionManager::getLastUse(){
  xmlOptions o;
  return o.getLastUse();
}


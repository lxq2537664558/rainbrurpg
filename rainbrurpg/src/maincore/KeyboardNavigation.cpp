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

/** \file KeyboardNavigation.cpp
  * Implements a class that provides keyboard navigation and selection
  *
  * This code was originally found in the official CEGUI wiki :
  * http://www.cegui.org.uk/wiki/index.php/Tab_Order
  *
  */

#include "KeyboardNavigation.hpp"

/*void RainbruRPG::Gui::KeyboardNavigation::setParent(const CEGUI::String& window){

  parentName=window;

  // Parent will feed the tab and shift+tab navigation to the 
  // list of monitored widgets
  CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

  wmgr.getWindow(window)->subscribeEvent(CEGUI::Window::EventCharacterKey,
       CEGUI::Event::Subscriber(&KeyboardNavigation::_onCharacterKey, this));

  wmgr.getWindow(window)->subscribeEvent(CEGUI::Window::EventActivated,
       CEGUI::Event::Subscriber(&KeyboardNavigation::_onParentActivated, this));
}
*/
/*void RainbruRPG::Gui::KeyboardNavigation::addWidget(const CEGUI::String& window){
  // Add a widget to the list of widget navigation
  CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

  wmgr.getWindow(window)->subscribeEvent(CEGUI::Window::EventCharacterKey,
	CEGUI::Event::Subscriber(&KeyboardNavigation::_onCharacterKey, this));
  wmgr.getWindow(window)->subscribeEvent(CEGUI::Window::EventActivated,
	CEGUI::Event::Subscriber(&KeyboardNavigation::_onActivated,	this));
  HACKED_FOCUS_LOSS(window);

  if(!_tabNavigation.size()){
    // Activate the first widget by default
    wmgr.getWindow(window)->activate(); 
    HACKED_FOCUS_GAIN(window);
  }
  _tabNavigation.push_back(window);
  // Reset the iterator after each modification to the vector
  _lastKnownFocus = _tabNavigation.begin(); 
}
*/
/*void RainbruRPG::Gui::KeyboardNavigation::
addWidget(const CEGUI::TabControl* tabControl){

  // Add every tab buttons of a tab control
  CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
  CEGUI::Window* tabPaneButtons = wmgr.getWindow(tabControl->getName() 
						 + "__auto_TabPane__Buttons");
  for(size_t idx = 0; idx < tabPaneButtons->getChildCount(); idx++){
    addWidget(tabPaneButtons->getChildAtIdx(idx)->getName());
  }
}
*/


/** Clears the widget list
  *
  * This fucntion is used to reinitialize a already in use KeyboardNavigation.
  *
  */
void RainbruRPG::Gui::KeyboardNavigation::clear(){
  //  _tabNavigation.clear();;
  //  _lastKnownFocus=_tabNavigation.begin();
}


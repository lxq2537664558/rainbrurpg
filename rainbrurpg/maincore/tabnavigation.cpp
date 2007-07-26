/*
 *  Copyright 2006 Jerome PASQUIER
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

/* This code was found in the official CEGUI wiki :
 * http://www.cegui.org.uk/wiki/index.php/Tab_Order
 */



#include "tabnavigation.h"

/* These provide a visual focus cue when the scheme does not provide one
 *	 for every widget, such as TaharezLook's PushButton */
#define HACKED_FOCUS_GAIN(window) CEGUI::WindowManager::getSingleton().getWindow(window)->setAlpha(1.0f)
#define HACKED_FOCUS_LOSS(window) CEGUI::WindowManager::getSingleton().getWindow(window)->setAlpha(0.7f)

/* You can deactivate these hacked focus functions by defining the
 * macro as a comment:
#define HACKED_FOCUS_GAIN(window) //
#define HACKED_FOCUS_LOSS(window) //
 */


/** Specifies the parent or container.
  *
  * Used to trap Tab and Shift+Tab keys and relay them to the 
  * list of tab navigation. 
  *
  * \param window The name of the window to add
  *
  */
void RainbruRPG::Core::TabNavigation::setParent(const CEGUI::String& window){
  // Parent will feed the tab and shift+tab navigation to the list of monitored widgets
  CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

  wmgr.getWindow(window)->subscribeEvent(CEGUI::Window::EventCharacterKey,
       CEGUI::Event::Subscriber(&TabNavigation::_onCharacterKey, this));

  wmgr.getWindow(window)->subscribeEvent(CEGUI::Window::EventActivated,
       CEGUI::Event::Subscriber(&TabNavigation::_onParentActivated, this));
}

/** Adds a widget to the list of tab navigation.
  *
  * The order in which they are added corresponds to the tab order. 
  *
  * \param window The name of the window to add
  *
  */
void RainbruRPG::Core::TabNavigation::addWidget(const CEGUI::String& window){
  // Add a widget to the list of widget navigation
  CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

  wmgr.getWindow(window)->subscribeEvent(CEGUI::Window::EventCharacterKey,	CEGUI::Event::Subscriber(&TabNavigation::_onCharacterKey, this));
  wmgr.getWindow(window)->subscribeEvent(CEGUI::Window::EventActivated,		CEGUI::Event::Subscriber(&TabNavigation::_onActivated,	this));
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

/** Adds a TabControl widget.
  *
  * Its tab buttons will be added to the list of tab navigation. 
  *
  * \param tabControl A pointer to the Tab Control to add
  *
  */
void RainbruRPG::Core::TabNavigation::
addWidget(const CEGUI::TabControl* tabControl){

  // Add every tab buttons of a tab control
  CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
  CEGUI::Window* tabPaneButtons = wmgr.getWindow(tabControl->getName() 
						 + "__auto_TabPane__Buttons");
  for(size_t idx = 0; idx < tabPaneButtons->getChildCount(); idx++){
    addWidget(tabPaneButtons->getChildAtIdx(idx)->getName());
  }
}



/** Ensures that the last known focused widget regains input. 
  *
  * \param e The event
  *
  */
bool RainbruRPG::Core::TabNavigation::
_onParentActivated(const CEGUI::EventArgs& e){

  // Parent is being activated, activate the widget with the last known focus
  if(_tabNavigation.size() && _lastKnownFocus != _tabNavigation.end()){
    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    CEGUI::Window* window = wmgr.getWindow(*_lastKnownFocus);
    if(window)
      window->activate();
  }
  return true;
}

/** Handles non-tab key activation
  *
  * This will ensure that the next tab key navigation will start from
  * the relevant widget. 
  *
  * \param e The event
  *
  */
bool RainbruRPG::Core::TabNavigation::_onActivated(const CEGUI::EventArgs& e){

  // A focus widget has been activated without tabbing (could be a mouse click)
  CEGUI::String currentlyFocused = 
    static_cast<const CEGUI::WindowEventArgs&>(e).window->getName();

  if(_tabNavigation.size() 
     && (_lastKnownFocus == _tabNavigation.end()
	 || (*_lastKnownFocus).compare(currentlyFocused))	)
    {
      if(_lastKnownFocus != _tabNavigation.end())
	{
	  // These curly braces are IMPORTANT!!!
	  HACKED_FOCUS_LOSS(*_lastKnownFocus);
	}
      for(_lastKnownFocus = _tabNavigation.begin(); _lastKnownFocus != _tabNavigation.end(); _lastKnownFocus++)
	{
	  if(!(*_lastKnownFocus).compare(currentlyFocused))
	    {
	      HACKED_FOCUS_GAIN(currentlyFocused);
	      return true;
	    }
	}
      // Can't figure out who has the focus
      _lastKnownFocus = _tabNavigation.begin();
      HACKED_FOCUS_GAIN(*_lastKnownFocus);
    }
  return true;
}

/** Traps the Tab and Shift+Tab key and activates the next or previous 
  * widget accordingly. 
  *
  * \param e The event
  *
  */
bool RainbruRPG::Core::TabNavigation::
_onCharacterKey(const CEGUI::EventArgs& e){

  // Handle Tab (next) and Shift+Tab (previous) widget navigation
  assert(_tabNavigation.size() && "Don't simply call setParent(), also call addWidget()");
  // Tab or Shift+Tab
  if(static_cast<const CEGUI::KeyEventArgs&>(e).codepoint == 9){
    // Identify who currently has the focus
    CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
    std::vector<CEGUI::String>::iterator itFocus, itCurrent;
    if(_lastKnownFocus != _tabNavigation.end() && wmgr.getWindow(*_lastKnownFocus)->isActive())
      {
	// The last known focus is still in focus
	itCurrent = _lastKnownFocus;
      }
    else
      {
	// Figure out who (if anyone) has the focus
	for(itCurrent = _tabNavigation.begin(); itCurrent != _tabNavigation.end(); itCurrent++)
	  {
	    if(wmgr.getWindow(*itCurrent)->isActive())
	      {
		// Found who has the focus
		break;
	      }
	  }
	if(itCurrent == _tabNavigation.end())
	  {
	    // We did not find who had the focus
	    // Someone not in our list of monitored widgets has STOLEN the focus!
	    // Use the last known focus or, if that's invalid, the first widget
	    itCurrent = _lastKnownFocus != _tabNavigation.end() ? _lastKnownFocus : _tabNavigation.begin();
	  }
      }
    
    // Change the focus
    itFocus = itCurrent; // The search starts from the currently focused
    CEGUI::Window* newWidget = 0;
    do
      {
	if(static_cast<const CEGUI::KeyEventArgs&>(e).sysKeys & CEGUI::Shift)
	  {
	    // Search previous
	    if(itFocus == _tabNavigation.begin())
	      itFocus = --_tabNavigation.end();
	    else
	      itFocus--;
	  }
	else
	  {
	    // Search next
	    itFocus++;
	    if(itFocus == _tabNavigation.end())
	      itFocus = _tabNavigation.begin();
	  }
	newWidget = wmgr.getWindow(*itFocus);
	if(newWidget->isVisible() && !newWidget->isDisabled())
	  {
	    // We have found a valid focus target
	    _lastKnownFocus = itFocus;
	    break;
	  }
	newWidget = 0;
      } while(itFocus != itCurrent); // Iterate while we're on a different widget
    
    if(newWidget)
      {
	// Remove the focus from this widget
	HACKED_FOCUS_LOSS(*itCurrent);
	
	// Give the focus to this widget
	newWidget->activate();
	HACKED_FOCUS_GAIN(newWidget->getName());
	return true;
      }
  }
  return false;
}

/** Clears the widget list
  *
  * This fucntion is used to reinitialize a already in use TabNavigation.
  *
  */
void RainbruRPG::Core::TabNavigation::clear(){
  _tabNavigation.clear();;
  _lastKnownFocus=_tabNavigation.begin();
}

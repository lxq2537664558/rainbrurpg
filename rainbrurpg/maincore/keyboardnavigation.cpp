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



#include "keyboardnavigation.h"

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
void RainbruRPG::Gui::KeyboardNavigation::setParent(const CEGUI::String& window){

  parentName=window;

  // Parent will feed the tab and shift+tab navigation to the 
  // list of monitored widgets
  CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();

  wmgr.getWindow(window)->subscribeEvent(CEGUI::Window::EventCharacterKey,
       CEGUI::Event::Subscriber(&KeyboardNavigation::_onCharacterKey, this));

  wmgr.getWindow(window)->subscribeEvent(CEGUI::Window::EventActivated,
       CEGUI::Event::Subscriber(&KeyboardNavigation::_onParentActivated, this));
}

/** Adds a widget to the list of tab navigation.
  *
  * The order in which they are added corresponds to the tab order. 
  *
  * \param window The name of the window to add
  *
  */
void RainbruRPG::Gui::KeyboardNavigation::addWidget(const CEGUI::String& window){
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

/** Adds a TabControl widget.
  *
  * Its tab buttons will be added to the list of tab navigation. 
  *
  * \param tabControl A pointer to the Tab Control to add
  *
  */
void RainbruRPG::Gui::KeyboardNavigation::
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
bool RainbruRPG::Gui::KeyboardNavigation::
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
bool RainbruRPG::Gui::KeyboardNavigation::_onActivated(const CEGUI::EventArgs& e){

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
bool RainbruRPG::Gui::KeyboardNavigation::
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
  * This fucntion is used to reinitialize a already in use KeyboardNavigation.
  *
  */
void RainbruRPG::Gui::KeyboardNavigation::clear(){
  _tabNavigation.clear();;
  _lastKnownFocus=_tabNavigation.begin();
}

/** Select the server immediately next to the one currently selected
  *
  * It is called when the user press the 'key down' key.
  *
  * \param mcl The MultiColumnList to apply the selection move
  *
  */
void RainbruRPG::Gui::KeyboardNavigation::
selectNext(CEGUI::MultiColumnList* mcl){
  int row=getSelectedRow(mcl);
  row+=1;
  setRowSelectState(mcl, row, true, RSD_DOWN);
}

/** Select the previous server to the one currently selected
  *
  * It is called when the user press the 'key up' key.
  *
  * \param mcl The MultiColumnList to apply the selection move
  *
  */
void RainbruRPG::Gui::KeyboardNavigation::
selectPrevious(CEGUI::MultiColumnList* mcl){
  int row=getSelectedRow(mcl);
  setRowSelectState(mcl, --row, true, RSD_UP);

}


/** Set a row selected or not and move the scrollbar
  *
  * This function is used by selectNext() and selectPrevious() to
  * select a given row. It is also responsible of the scrolling 
  * of the list widget. But for this last thing, we shoul know 
  * the direction of the user moves (key down or key up). It
  * is the purpose of the third parameter.
  *
  * The index of the first row is always 0. If \c row is greater than
  * \c serverList->getRowCount(), the last item will be selected 
  * and no error will be throwed.
  *
  * \param mcl   The MultiColumnList you apply the state change on
  * \param row   The index of the row to change
  * \param state Is this item is now selected ?
  * \param dir   The user move direction
  *
  */
void RainbruRPG::Gui::KeyboardNavigation::
setRowSelectState(CEGUI::MultiColumnList* mcl,int row, bool state, 
		  tRowSelectionDirection dir){

  if (row<mcl->getRowCount()){
    mcl->setItemSelectState(CEGUI::MCLGridRef(row, 0), state);
    mcl->setItemSelectState(CEGUI::MCLGridRef(row, 1), state);
    mcl->setItemSelectState(CEGUI::MCLGridRef(row, 2), state);

    // Set the vertial scrollbar scrolling
    CEGUI::ListboxItem * item=mcl->getFirstSelectedItem();
    // Get an item height
    float itemHeight=item->getPixelSize().d_height;
    // Get the list heiht
    float listHeight=mcl->getPixelSize().d_height;
    float listMiddle=(listHeight/2)-itemHeight;

    CEGUI::Scrollbar* vsb=mcl->getVertScrollbar();
    float sp=vsb->getScrollPosition();

    float relItemTop=(row*itemHeight)-sp;

    if (dir==RSD_UP){
      if (relItemTop<listMiddle-itemHeight){
	vsb->setScrollPosition(sp-itemHeight);
      }
    }
    else if (dir==RSD_DOWN){
      if (relItemTop>listMiddle){
	vsb->setScrollPosition(sp+itemHeight);
      }
    }
    else if (dir==RSD_PGUP){
      if (row<2){
	setRowSelectState(mcl, 0, true, RSD_HOME);
      }
      else{
	float y=(row*itemHeight)-listMiddle;
	vsb->setScrollPosition(y);
      }
    }
    else if (dir==RSD_PGDOWN){
      if (row >mcl->getRowCount()-2){
	setRowSelectState(mcl, mcl->getRowCount()-1, true, RSD_END);
      }
      else{
	float y=(row*itemHeight)-listMiddle;
	vsb->setScrollPosition(y);
      }
    }  
    else if (dir==RSD_HOME){
      vsb->setScrollPosition(0);
    }
    else if (dir==RSD_END){
      vsb->setScrollPosition(listHeight);
    }    
  }
}


/** Get the row index of the selected server
  *
  * The index of the first row is 0.
  *
  * \param mcl The MultiColumnList you want the selected row index for.
  *
  * \return The row index or -1 if none server is selected
  *
  */
int RainbruRPG::Gui::KeyboardNavigation::
getSelectedRow(CEGUI::MultiColumnList* mcl){

  CEGUI::ListboxItem * it=mcl->getFirstSelectedItem();
  if (it){
    // There is already a selected item
    for (int i=0; i<mcl->getRowCount(); i++){
      if (mcl->isItemSelected(CEGUI::MCLGridRef(i, 0))){
	return i;
      }
    }
  }
  else{
    // No item was selected
    return -1;
  }

}

/** The ServerList key listener
  *
  * This function is called when a key is pressed in the 
  * serverlist. It provide the keyboard-based selection of a server.
  *
  * The down and up key moves the selection by one item. The Return or 
  * Enter key will call onConnectClicked().
  *
  * This function is possible cause of gsMenuBase::keyPressed() which is
  * the keyboard mapping beetwen OIS and CEGUI for all gsMenuBase based
  * subclasses.
  *
  * \param e The CEGUI event 
  *
  */
bool RainbruRPG::Gui::KeyboardNavigation::
onListKeyDown(const CEGUI::EventArgs& e){

  // Get the active MultiColumnList
  CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
  CEGUI::Window* win=wmgr.getWindow(parentName);
  CEGUI::Window* win2=win->getActiveChild();

  /* Fix a segfault
   *
   * A SEGFAULT occurs if you use the mouse on a MultiColumnList's
   * child then press a moving key. CEGUI will auto-create several
   * childs called <MultiColumnList_Name>__auto_vscrollbar__, 
   * <MultiColumnList_Name>__auto_vscrollbar__ and others to draw
   * the scroll bars. But these child are the active one when selected.
   *
   * The previous line (win->getActiveChild() returns a scrollbar
   * component and when I cast it to CEGUI::MultiColumnList*, we have a
   * SEGFAULT. The following while statement recursively check if 
   * we have '__auto_' in the active widget name and get its parent if
   * it is true.
   *
   */
  CEGUI::String activeChildName=win2->getName();
  while (activeChildName.find("__auto_")!=CEGUI::String::npos){
    LOGW("The active child is not the list :");
    LOGCATS("Its name :");
    LOGCATS(win2->getName().c_str());
    LOGCATS(" its parent is :");
    LOGCATS(win2->getParent()->getName().c_str());
    LOGCATS(" checking its parent!");
    LOGCAT();

    win2=win2->getParent();
    activeChildName=win2->getName();
  }
  

  CEGUI::MultiColumnList* list=static_cast<CEGUI::MultiColumnList*>(win2);

  if (list==NULL){
    LOGE("It is not a MultiColumnList");
  }

  // Get the keyboard scanCode
  CEGUI::KeyEventArgs evt=static_cast<const CEGUI::KeyEventArgs&>(e);
  CEGUI::Key::Scan sc=evt.scancode;
  
  if (sc==CEGUI::Key::ArrowDown){
    LOGI("ArrowDown pressed in serverlist");
    selectNext(list);

  }
  else if(sc==CEGUI::Key::ArrowUp){
    LOGI("ArrowDown pressed in serverlist");
    selectPrevious(list);
  }
  else if(sc==CEGUI::Key::PageUp){
    selectPreviousPage(list);
  }
  else if(sc==CEGUI::Key::PageDown){
    selectNextPage(list);
  }
  else if(sc==CEGUI::Key::Home){
    setRowSelectState(list, 0, true, RSD_HOME);
  }
  else if(sc==CEGUI::Key::End){
    LOGI("KeyEnd pressed");
    setRowSelectState(list, list->getRowCount()-1, true, RSD_END);
  }
  else if (sc==CEGUI::Key::Return){
    // If a row is selected
    if (getSelectedRow(list)!=-1){
      CEGUI::EventArgs ea;
      list->fireEvent(MULTI_COLUMN_LIST_ENTER_EVENT_NAME, ea);
    }
  }
}

/** Add the keyboard selection support for the named MultiColumnList
  *
  * This adds the keyboard selection handle to the MultiColumnWidget
  * (a CEGUI widget) you gave the name. It is automatically added
  * to the tab navigation list.
  *
  * \note The MultiColumnList widget \b must be a child of the parent
  *       set with the setParent() function.
  *
  * \param mclName The name of the MultiColumnList to add
  * \param ss      The callback of the Enter/Return key
  *
  * \sa setParent().
  *
  */
void RainbruRPG::Gui::KeyboardNavigation::
addMultiColumnList(const CEGUI::String& mclName, 
		   const CEGUI::SubscriberSlot& ss){


  addWidget(mclName);

  // Get a MultiColumnList pointer
  CEGUI::WindowManager& wmgr = CEGUI::WindowManager::getSingleton();
  CEGUI::Window* win=wmgr.getWindow(mclName);
  CEGUI::MultiColumnList* list=static_cast<CEGUI::MultiColumnList*>(win);


  list->subscribeEvent(CEGUI::Window::EventKeyDown, 
    CEGUI::Event::Subscriber(&KeyboardNavigation::onListKeyDown,this));

  list->subscribeEvent(MULTI_COLUMN_LIST_ENTER_EVENT_NAME, ss);

}

/** Select the server on the next page
  *
  * It is called when the user press the 'page down' key. The page size is
  * defined in keyboardnavigation.h (\c MULTI_COLUMN_LIST_PAGE_SIZE).
  *
  * 
  *
  * \param mcl The MultiColumnList to apply the selection move
  *
  */
void RainbruRPG::Gui::KeyboardNavigation::
selectNextPage(CEGUI::MultiColumnList* mcl){
  LOGI("selectNextPage called");
  int row=getSelectedRow(mcl);
  row+=MULTI_COLUMN_LIST_PAGE_SIZE;

  if (row>mcl->getRowCount()-1)
    row=mcl->getRowCount()-1;

  setRowSelectState(mcl, row, true, RSD_PGDOWN);
}

/** Select the server on the previous page
  *
  * It is called when the user press the 'page up' key. The page size is
  * defined in keyboardnavigation.h (\c MULTI_COLUMN_LIST_PAGE_SIZE).
  *
  * 
  *
  * \param mcl The MultiColumnList to apply the selection move
  *
  */
void RainbruRPG::Gui::KeyboardNavigation::
selectPreviousPage(CEGUI::MultiColumnList* mcl){
  LOGI("selectPreviousPage called");
  int row=getSelectedRow(mcl);
  row-=MULTI_COLUMN_LIST_PAGE_SIZE;
  if (row<0) row=0;
  setRowSelectState(mcl, row, true, RSD_PGUP);
}

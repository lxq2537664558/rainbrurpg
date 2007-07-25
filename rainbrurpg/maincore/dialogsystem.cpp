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

/* This code was found in the official CEGUI wiki :
 * http://www.cegui.org.uk/wiki/index.php/DialogSystem
 */

#include "dialogsystem.h"
#include "assert.h"

/** The default constructor
  *
  * The dialog is not modal by default.
  *
  */
RainbruRPG::Gui::DialogSystem::DialogSystem(){
  m_modal  = false;
}

/** Return whether data within the window is modified
  *
  * An 'Apply' button must be specified
  *
  * \return \c true if the data was modified, otherwise \c false.
  *
  */
bool RainbruRPG::Gui::DialogSystem::isModified(){
  assert(!m_apply.empty() && "The isModified() function requires "
	 "that you specify an \"Apply\" button");
  return !CEGUI::WindowManager::getSingleton().getWindow(m_apply)->isDisabled();
}

/** Open the window
  *
  * Set the window enable and visible.
  *
  * \return The result of the doLoad function call
  *
  */
bool RainbruRPG::Gui::DialogSystem::doOpen(){
  // Open the window
  assert(!m_window.empty() && "You have forgotten to call initialise()");
  if(m_modal){
    // Displaying a modal window disables its parent
    assert(!m_parent.empty() && "The value of m_modal or m_parent "
	   "has become corrupted");
    CEGUI::WindowManager::getSingleton().getWindow(m_parent)->setEnabled(false);
  }

  // Display the window
  CEGUI::WindowManager::getSingleton().getWindow(m_window)->setVisible(true);
  CEGUI::WindowManager::getSingleton().getWindow(m_window)->activate();

  // Load the data into the widgets
  return doLoad();
}

/** Populate the window widgets with data
  *
  * \note This can also be used to simulate an undo for every widget
  *	  present in the window
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Gui::DialogSystem::doLoad(){
  // Disable the apply button since there are no modifications
  if(!m_apply.empty())
    CEGUI::WindowManager::getSingleton().getWindow(m_apply)->setEnabled(false);

  return true;
}

/** Update the data with the inputs from the widgets
  *
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Gui::DialogSystem::doSave(){
  // Disable the apply button since there are no modifications
  if(!m_apply.empty())
    CEGUI::WindowManager::getSingleton().getWindow(m_apply)->setEnabled(false);

  return true;
}

/** Closes the window
  *
  * If the window is modal, its parent is enabled. The dialog is hidden
  * but not destroyed.
  *
  * \return Always \c true
  *
  */
bool RainbruRPG::Gui::DialogSystem::doClose(){
  // Close the window
  assert(!m_window.empty() && "You have forgotten to call initialise()");
  
  if(m_modal){
    // Closing a modal window enables its parent
    assert(!m_parent.empty() && "The value of m_modal or m_parent "
	   "has become corrupted");
    CEGUI::WindowManager::getSingleton().getWindow(m_parent)->setEnabled(true);
    CEGUI::WindowManager::getSingleton().getWindow(m_parent)->activate();
  }

  CEGUI::WindowManager::getSingleton().getWindow(m_window)->setVisible(false);

  return true;
}

/** Initialise the window system
  *
  * Specifying a parent makes this window modal
  *
  * \note If the parent name is empty, an focus problem could occur :
  *       When you close the dialog, the other window should not 
  *       recover their focus. Or the message is not deactivated at 
  *       startup.
  *
  * \param window  The window to set visible
  * \param visible Is \c window become visible ?
  * \param parent  The parent Window for a modal dialog or nothing for a
  *                normal one
  *
  */
void RainbruRPG::Gui::DialogSystem::
initialise(const CEGUI::String& window, bool visible, 
	   const CEGUI::String& parent){

  // Specifying a parent makes this window modal
  m_window = window;
  CEGUI::WindowManager::getSingleton().getWindow(m_window)->setVisible(visible);
  m_parent = parent;
  m_modal  = !m_parent.empty();

  if (m_parent.empty()){
    LOGW("Calling DialogSystem::initialise without a valid parent name could "
	 "cause a focus problem to occur when closing the dialog.");
  }

  if(!visible && !m_parent.empty())
    CEGUI::WindowManager::getSingleton().getWindow(m_window)->deactivate();

}

/** Subscribe an event
  *
  * \param widget      The widget's name we subscribe an event for
  * \param widgetEvent The name of the event you subscribe
  * \param action      The dialog action
  *
  */
void RainbruRPG::Gui::DialogSystem::bindEvent(const CEGUI::String& widget, 
			     const CEGUI::String& widgetEvent, 
			     tDialogSystemEvents action){


  // Subscribe to events
  CEGUI::Window* widgetHandle = CEGUI::WindowManager::getSingleton()
    .getWindow(widget);

  switch(action){
  case DSE_OPEN:
    widgetHandle->subscribeEvent(widgetEvent, 
	CEGUI::Event::Subscriber(&DialogSystem::onOpen, this));
    break;
  case DSE_OK:
    widgetHandle->subscribeEvent(widgetEvent, 
	CEGUI::Event::Subscriber(&DialogSystem::onOk, this));
    break;
  case DSE_CANCEL:
    widgetHandle->subscribeEvent(widgetEvent, 
	CEGUI::Event::Subscriber(&DialogSystem::onCancel, this));
    break;
  case DSE_ESCAPE:
    widgetHandle->subscribeEvent(widgetEvent, 
	CEGUI::Event::Subscriber(&DialogSystem::onEscape, this));
    break;
  case DSE_APPLY:
    widgetHandle->subscribeEvent(widgetEvent, 
	CEGUI::Event::Subscriber(&DialogSystem::onApply, this));
    m_apply = widget;
    break;
  case DSE_MODIFIED:
    if(!m_apply.empty())
      widgetHandle->subscribeEvent(widgetEvent, 
	CEGUI::Event::Subscriber(&DialogSystem::onModified, this));
    break;
  }
}

/** The open event
  *
  * \param e The event argument (not yet used)
  *
  * \return always \c true
  *
  */
bool RainbruRPG::Gui::DialogSystem::onOpen(const CEGUI::EventArgs& e){
  // Open the window
  return doOpen();
}

/** The OK event
  *
  * The OK button was pressed. Saves and close the window
  *
  * \param e An unused event argument structure
  *
  * \return always \c true
  *
  */
bool RainbruRPG::Gui::DialogSystem::onOk(const CEGUI::EventArgs& e){
  return doClose();
}

/** The 'cancel' button was pressed
  *
  * Respond by closing the window without saving the data
  *
  * \param e An unused event argument structure
  *
  * \return always \c true
  *
  */
bool RainbruRPG::Gui::DialogSystem::onCancel(const CEGUI::EventArgs& e){
  return doClose();
}

/** The 'escape' key was pressed
  *
  * Respond by closing the dialog without saving the data
  *
  * \note that Win32AppHelper::doDirectInputEvents() intercepts this key
  * This means that the escape key will NOT reach here
  *
  * \param e An unused event argument structure
  *
  * \return always \c true
  *
  */
bool RainbruRPG::Gui::DialogSystem::onEscape(const CEGUI::EventArgs& e){
  const CEGUI::KeyEventArgs& keyArgs = 
    static_cast<const CEGUI::KeyEventArgs&>(e);

  if(keyArgs.scancode == CEGUI::Key::Escape){
    return doClose();
  }
  else
    return false;
}

/** The 'apply' button was pressed
  *
  * Respond by saving the data without closing the window
  *
  * \param e An unused event argument structure
  *
  * \return always \c true
  *
  */
bool RainbruRPG::Gui::DialogSystem::onApply(const CEGUI::EventArgs& e){
  return doSave();
}

/** A widget within the window was modified
  *
  * Respond by enabling the 'apply' button
  *
  * \param e An unused event argument structure
  *
  * \return always \c true
  *
  */
bool RainbruRPG::Gui::DialogSystem::onModified(const CEGUI::EventArgs& e){
  CEGUI::WindowManager::getSingleton().getWindow(m_apply)->setEnabled(true);
  return true;
}

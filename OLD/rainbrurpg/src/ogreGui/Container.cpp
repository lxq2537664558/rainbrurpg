/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file Container.cpp
  *
  * Implements an ogreGui container
  *
  */

#include "Container.hpp"

#include <Focusable.hpp>
#include <Brush.hpp>

#include <Logger.hpp>

/** A default container constructor
  *
  */
RainbruRPG::OgreGui::Container::
Container(Widget* vParent, const string& vName, 
	  int vX1, int vY1, int vX2, int vY2):
  Widget(vParent, vName, vX1, vY1, vX2, vY2),
  WidgetList(vName),
  mFocused(NULL)
{

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::Container::~Container()
{

}

/** The key pressed event handling function
  *
  * It simply returns the result of the focused widget's key pressed
  * function or return false if no widget has the focus.
  *
  * \param vEvent the OIS key event
  *
  * \return \c true if the the event is consummed otherwise returns \c false.
  *
  */
bool RainbruRPG::OgreGui::Container::keyPressed(const OIS::KeyEvent& vEvent)
{
  if (mFocused)
    return mFocused->keyPressed(vEvent);
  else
    return false;
}

/** The key released event handling function
  *
  * It handles the focus cycling of widget list with \c TAB and \c shift-Tab
  * keus.
  *
  * \param vEvent the OIS key event
  *
  * \return \c true if the the event is consummed otherwise returns \c false.
  *
  */
bool RainbruRPG::OgreGui::Container::keyReleased(const OIS::KeyEvent& vEvent)
{
  // Prevent a segfault if WidgetList is empty
  if (empty())
    return false;

  bool ret = false;

  if (vEvent.key == OIS::KC_TAB){
    mFocused = WidgetList::focusNext();
    ret = true;
  }
  else if (vEvent.key == OIS::KC_TAB || vEvent.key == OIS::KC_LSHIFT){
    mFocused = WidgetList::focusPrevious();
    ret = true;
  }

  if (mFocused){
    ret = mFocused->keyReleased(vEvent);
  }

  return ret;
}

bool RainbruRPG::OgreGui::Container::mouseMoved(const OIS::MouseEvent& vEvent)
{
  // Should propagate event on all childs
  // until the first that return true
}

bool RainbruRPG::OgreGui::Container::
mousePressed(const OIS::MouseEvent& vEvent,const OIS::MouseButtonID& vButton)
{
  // Should propagate event on all childs
  // until the first that return true
}

bool RainbruRPG::OgreGui::Container::
mouseReleased(const OIS::MouseEvent& vEvent,const OIS::MouseButtonID& vButton)
{
  // Should propagate event on all childs
  // until the first that return true
}

/** A basic childs drawing function
  *
  * \param vBrush The brush object used to draw primitives
  *
  */
void RainbruRPG::OgreGui::Container::draw(Brush* vBrush)
{
  Drawable::draw(vBrush);
  //  vBrush->reset();
  tWidgetList::iterator iter;
  for (iter = mList.begin(); iter != mList.end(); iter++){
    (*iter)->draw(vBrush);
  }
  // vBrush->reset(); // Really needed ?
}

/** Compute the absolute bounding box and scissor rectangle
  *
  * \param vParentX       The absolute parent X
  * \param vParentY       The absolute parent Y
  * \param vParentScissor The parent scissor rectangle
  *
  */
void RainbruRPG::OgreGui::Container::
compute(int vParentX, int vParentY, const Ogre::Rectangle& vParentScissor){
  computeAbsolute(vParentX, vParentY);
  adjustScissor(vParentScissor);

  tWidgetList::iterator iter;
  for (iter = mList.begin(); iter != mList.end(); iter++){
    (*iter)->compute(mAbsolute.left, mAbsolute.top, mScissor);
  }
  setDirty(false);
}

/** Adds a widget to the end of the list
  *
  * \param vWidget The widget to be added
  *
  */
void RainbruRPG::OgreGui::Container::push_back(Widget* vWidget){
  WidgetList::push_back(vWidget);
  vWidget->setDirty(true);
}

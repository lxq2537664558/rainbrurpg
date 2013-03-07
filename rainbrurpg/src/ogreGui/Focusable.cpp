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

/** \file Focusable.cpp
  *
  * Implements an ogreGui focusable object.
  *
  */

#include "Focusable.hpp"

/** C=The constructor
  *
  * \param vCanTakeFocus Can this take the keyboard focus ?
  *
  */
RainbruRPG::OgreGui::Focusable::Focusable(bool vCanTakeFocus):
  mCanTakeFocus(vCanTakeFocus),
  mFocus(false)
{

}

/** Is this one enable to take the keyboard focus
  *
  * \return Return \c true if this can.
  *
  */
bool RainbruRPG::OgreGui::Focusable::canTakeFocus()const{
  return mCanTakeFocus;
}

/** Changes the ability to take the focus
  *
  * If the object had the focus before the call, it is
  * set to \c false.
  *
  * \param vCanTakeFocus Can this take the keyboard focus ?
  *
  */
void RainbruRPG::OgreGui::Focusable::setCanTakeFocus(bool vCanTakeFocus){
  mCanTakeFocus = vCanTakeFocus;
  mFocus = false;
}

/** Handles a key pressed event
  *
  * When reimplemented, this function must return \c true if the
  * event is consumed.
  *
  * \param vEvent The key Event
  *
  * \return \c false to say the event is not consumed
  *
  */
bool RainbruRPG::OgreGui::Focusable::keyPressed(const OIS::KeyEvent& vEvent)
{
  return false;
}

/** Handles a key released event
  *
  * When reimplemented, this function must return \c true if the
  * event is consumed.
  *
  * \param vEvent The key Event
  *
  * \return \c false to say the event is not consumed
  *
  */
bool RainbruRPG::OgreGui::Focusable::keyReleased(const OIS::KeyEvent& vEvent)
{
  return false;
}

/** Handles a mouse moved event
  *
  * When reimplemented, this function must return \c true if the
  * event is consumed.
  *
  * \param vEvent The mouse Event
  *
  * \return \c false to say the event is not consumed
  *
  */
bool RainbruRPG::OgreGui::Focusable::mouseMoved(const OIS::MouseEvent& vEvent)
{
  return false;
}

/** Handles a mouse button pressed event
  *
  * When reimplemented, this function must return \c true if the
  * event is consumed.
  *
  * \param vEvent The mouse Event
  * \param vButton The mouse button
  *
  * \return \c false to say the event is not consumed
  *
  */
bool RainbruRPG::OgreGui::Focusable::
mousePressed(const OIS::MouseEvent& vEvent, const OIS::MouseButtonID& vButton)
{
  return false;
}

/** Handles a mouse button released event
  *
  * When reimplemented, this function must return \c true if the
  * event is consumed.
  *
  * \param vEvent The mouse Event
  * \param vButton The mouse button
  *
  * \return \c false to say the event is not consumed
  *
  */
bool RainbruRPG::OgreGui::Focusable::
mouseReleased(const OIS::MouseEvent& vEvent, const OIS::MouseButtonID& vButton)
{
  return false;
}

/** Set the focus status of this object
  *
  * If the object can not take the focus, the focus status will
  * always be false.
  *
  * \param vFocus The new focus status
  *
  */
void RainbruRPG::OgreGui::Focusable::setFocus(bool vFocus)
{
  if (mCanTakeFocus)
    this->mFocus = vFocus;
 
}
 
/** Has this object currently the focus ?
  *
  * \return \c true if this object currently has the focus
  *
  */
bool RainbruRPG::OgreGui::Focusable::hasFocus()
{
  return this->mFocus;
}

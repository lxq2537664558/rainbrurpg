/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file inputwrapper.cpp
  * Implements a class defining some mouse and keyboard wrapping
  *
  */

#include "inputwrapper.h"

/** The default constructor
  *
  */
RainbruRPG::Core::InputWrapper::InputWrapper(){
  mouseMenuSensibility=1.0f;

  // standard keys definition
  forward = OIS::KC_Z;
  backward= OIS::KC_S;
  left    = OIS::KC_Q;
  right   = OIS::KC_D;
}

/** The default destructor
  *
  */
RainbruRPG::Core::InputWrapper::~InputWrapper(){

}

/** Get the mouse move sensibility used in menus
  *
  * \return The mouse sensibility factor
  *
  */
float RainbruRPG::Core::InputWrapper::getMouseMenuSensibility(){
  return mouseMenuSensibility;
}

/** Get the forward keycode
  *
  * \return The keycode for moving forward
  *
  */
OIS::KeyCode RainbruRPG::Core::InputWrapper::getForward(){
  return forward;
}

/** Get the backward keycode
  *
  * \return The keycode for moving backward
  *
  */
OIS::KeyCode RainbruRPG::Core::InputWrapper::getBackward(){
  return backward;
}

/** Get the left keycode
  *
  * \return The keycode for moving left
  *
  */
OIS::KeyCode RainbruRPG::Core::InputWrapper::getLeft(){
  return left;
}

/** Get the right keycode
  *
  * \return The keycode for moving right
  *
  */
OIS::KeyCode RainbruRPG::Core::InputWrapper::getRight(){
  return right;
}

/*
 *  Copyright 2006-2010 Jerome PASQUIER
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
  mCanTakeFocus(vCanTakeFocus)
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
  * \param vCanTakeFocus Can this take the keyboard focus ?
  *
  */
void RainbruRPG::OgreGui::Focusable::setCanTakeFocus(bool vCanTakeFocus){
  mCanTakeFocus = vCanTakeFocus;
}

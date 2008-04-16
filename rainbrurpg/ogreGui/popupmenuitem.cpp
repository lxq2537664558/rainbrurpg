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

#include "popupmenuitem.h"

/** The default constructor
  *
  */
RainbruRPG::OgreGui::PopupMenuItem::PopupMenuItem():
  mHeight(20)
{

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::PopupMenuItem::~PopupMenuItem(){

}

/** Change the height of this item
  *
  * \param vHeight The height of this menu item
  *
  */
void RainbruRPG::OgreGui::PopupMenuItem::setHeight(unsigned int vHeight){
  mHeight = vHeight;
}

/** Get the height of this item
  *
  * \return The height of this menu item
  *
  */
unsigned int RainbruRPG::OgreGui::PopupMenuItem::getHeight(void)const{
  return mHeight;
}

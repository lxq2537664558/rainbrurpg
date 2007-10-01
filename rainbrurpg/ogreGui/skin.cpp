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

#include "skin.h"

#include <logger.h>

/** Create a skin with a name
  *
  * \param n The name of the skin
  *
  */
RainbruRPG::OgreGui::Skin::Skin(std::string n)
  :name(n){

  std::string s;
  s="Creating skin `";
  s+=this->name;
  s+="`";
  LOGI(s.c_str());

}

/** Get the name of the skin
  *
  * \return The skin's name in std::string format
  *
  */
std::string RainbruRPG::OgreGui::Skin::getName(void){
  return this->name;
}

/** Change the skin name
  *
  * \param s The new skin's name
  *
  */
void RainbruRPG::OgreGui::Skin::setName(std::string s){
  this->name=s;
}

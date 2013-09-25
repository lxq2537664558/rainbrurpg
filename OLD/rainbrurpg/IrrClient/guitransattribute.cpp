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

#include "guitransattribute.h"
#include "stringconv.h"
#include "gameengine.h"

#include <stdlib.h>

#include "logger.h"

RainbruRPG::Exception::GuiTransAttribute::GuiTransAttribute()
                                    :IntAttribute("guitransparency"){
  LOGI("Constructing GuiTransAttribute...");
  readOnly=false;
}

void RainbruRPG::Exception::GuiTransAttribute::setValue(int i){
  LOGI("========Setting GuiTransAttribute value...");
  GameEngine::getSingleton().setGuiTransparency((s32)i);

}

/** Get the actual Frame Per Second value
  *
  * This value is given by the GameEngine's IrrlichtDriver and
  * convert to a \c char* by the StringConv singleton
  */
const char* RainbruRPG::Exception::GuiTransAttribute::getValueText(){

  int gui=GameEngine::getSingleton().getGuiTransparency();

 std::string buffer= RainbruRPG::Core::StringConv::getSingleton().itos(gui);

 return buffer.c_str();

}

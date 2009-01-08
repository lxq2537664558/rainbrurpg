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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#include "cocore.h"

RainbruRPG::Exception::coCore::coCore()
                              :ConsoleObject("core"){
  LOGI("Constructing a coCore object...");
  this->setDesc("The GameEngine object");

  // Creating Attribute instance
  ShowStatsAttribute *ssa=new ShowStatsAttribute();
  ssa->setValueText("on");

  FpsAttribute *fpa=new FpsAttribute();

  GuiTransAttribute *gta=new GuiTransAttribute();

  // Adding read-write attribute
  this->attrbList.push_back(ssa);
  this->attrbList.push_back(gta);

  // Adding read-only attribute
  this->attrbList.push_back(fpa);


}

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

/** \file gamestate.cpp
  * Declares a base abstract class of all the GameStates
  *
  */

#include "gamestate.h"

/** A default protected constructor 
  *
  * This constructor is defined protected as this class shoiuld not
  * be created directly. Use subclasses
  *
  */ 
RainbruRPG::Core::GameState::GameState(){
  LOGI("Initializing game state super-class");
  isInit=false;
}

/** A destructor 
  *
  */ 
RainbruRPG::Core::GameState::~GameState(){
}

/** Return true if the init function was call
  *
  */
bool RainbruRPG::Core::GameState::wasInit(){
  return this->isInit;
}

/** Get the type of state
  *
  * \return The type of this state
  *
  */
tGameStateType RainbruRPG::Core::GameState::getStateType(){
  return this->stateType;
}

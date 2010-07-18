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

/** \file gamestate.cpp
  * Declares a base abstract class of all the GameStates
  *
  */

#include "gamestate.h"

#include "gameengine.h"

#include <OgreViewport.h>
#include <Container.hpp>

using namespace Ogre;

/** A default protected constructor 
  *
  * This constructor is defined protected as this class should not
  * be created directly. Use subclasses.
  *
  * \note The name is used when changing state. Its name is its identifier,
  *       so the name must be non-null and unique.
  *
  * \param vName The name of the gamestate
  * \param vType The type of the game state
  *
  */ 
RainbruRPG::Core::GameState::
GameState(const string& vName, const tGameStateType& vType):
  name(vName),
  stateType(vType),
  mContainer(NULL)
{
  LOGI(_("Initializing game state super-class"));
  isInit=false;

  // Container with NULL parent

  Viewport* mViewport=GameEngine::getSingleton().getViewport();
  int winWidth=mViewport->getActualWidth();
  int winHeight=mViewport->getActualHeight();

  mContainer = new Container(NULL, vName + "/Container", 0, 0, 
			     winWidth, winHeight);
}

/** A destructor 
  *
  */ 
RainbruRPG::Core::GameState::~GameState(){
  delete mContainer;
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
const tGameStateType& RainbruRPG::Core::GameState::getStateType()const{
  return this->stateType;
}

/** Change the name of this gamestate
  *
  * \param vName The new name
  *
  */
void RainbruRPG::Core::GameState::setName(const string& vName){
  this->name = vName;
}

/** Get the name of this gamestate
  *
  * \return The current name
  *
  */
const string& RainbruRPG::Core::GameState::getName(void)const{
  return this->name;
}

void RainbruRPG::Core::GameState::draw(Brush* vBrush)
{
  // if dirty: mContainer->compute(0,0);
  mContainer->draw(vBrush);
}

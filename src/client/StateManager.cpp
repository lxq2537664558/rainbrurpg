/*
 * Copyright 2011-2016 Jerome Pasquier
 *
 * This file is part of rainbrurpg-client.
 *
 * rainbrurpg-client is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * rainbrurpg-client is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with rainbrurpg-client.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "StateManager.hpp"

#include "GameEngine.hpp"
#include "GameState.hpp"
#include "Logger.hpp"

static Rpg::Logger static_logger("state", Rpg::LT_BOTH);

StateManager::StateManager(GameEngine* ge):
  mCurrentState(NULL),
  mGameEngine(ge)
{

}

StateManager::~StateManager()
{
  mGameEngine = NULL;
}

/* Returns the current gamestate. 
 *
 * May return a NULL pointer.
 *
 */
GameState*
StateManager::getCurrentState() const
{
  return mCurrentState;
}

void
StateManager::setCurrentState(GameState* gs)
{
  LOGI("Switching to" << gs->getName() << "game state");

  if (mCurrentState)
    mCurrentState->exit(mGameEngine);

  // Actually changing gamestate
  mCurrentState = gs;
  gs->enter(mGameEngine);
}

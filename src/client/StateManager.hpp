/*
 * Copyright 2011-2017 Jerome Pasquier
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

#ifndef _STATE_MANAGER_HPP_
#define _STATE_MANAGER_HPP_

// Forward declarations
class GameState;
class GameEngine;
// End of forward declarations

/* The GameState manager
 *
 * This is used to be publicly inherited by GameEngine, passing
 * itself (this) as argument.
 *
 */
class StateManager
{
public:
  StateManager(GameEngine*);
  ~StateManager();

  GameState* getCurrentState()const;
  void setCurrentState(GameState*);
 
protected:
  GameState* mCurrentState;

private:
  GameEngine* mGameEngine;

};

#endif // !_STATE_MANAGER_HPP_

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

#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <string>

// Forward declaration
class GameEngine;
// End of forward declaration

using namespace std;

/* The base class of all game states
 *
 */
class GameState
{
public:

  GameState(const string&);
  virtual ~GameState();
  
  virtual void enter(GameEngine*)=0;
  virtual void exit(GameEngine*)=0;

  const string& getName()const;
  
private:
  string mName; // The state name, only for debuging purpose
};

#endif // !_GAME_STATE_HPP_

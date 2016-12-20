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

using namespace std;

// Forward declaratiobs
class GameEngine;
// End of forward declaratiobs

typedef struct
{
  int width;
  int height;
}ResolutionHandlerResult;

/** A class used to detect current resolution
  * 
  * We use multiple ways to detect window size because simply reading
  * Ogre configuration may fail.
  *
  */
class ResolutionHandler
{
public:
  ResolutionHandler();
  ~ResolutionHandler();
  
  const ResolutionHandlerResult& probe(GameEngine*);

protected:
  // Top-level probing functions
  bool probeFromCfg();
  bool probeFromWindow();

  // Low level (unit tested function
  bool probeFromString(const std::string&);
  bool probeFromInts(int, int);

  ResolutionHandlerResult* mResult; // protected to be used in unit tests

private:
  GameEngine* mGameEngine;
};

#endif // !_GAME_STATE_HPP_

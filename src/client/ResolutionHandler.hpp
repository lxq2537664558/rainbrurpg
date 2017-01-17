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

#ifndef _RESOLUTION_HANDLER_HPP_
#define _RESOLUTION_HANDLER_HPP_

#include <string>

#include "Exception.hpp"

using namespace std;

// Forward declaratiobs
class GameEngine;
namespace Ogre
{
  class RenderWindow;
}
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
  
  string probe(GameEngine*);
  
protected:
  // Top-level probing functions
  bool probeFromWindow(const Ogre::RenderWindow* rw);

  // Low level (unit tested function
  bool probeFromString(const std::string&);

  string resultToString(const ResolutionHandlerResult&)const;
  
  ResolutionHandlerResult* mResult; // protected to be used in unit tests

private:
  GameEngine* mGameEngine;
};

#endif // !_RESOLUTION_HANDLER_HPP_

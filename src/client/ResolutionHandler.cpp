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

#include "ResolutionHandler.hpp"

#include "GameEngine.hpp"

ResolutionHandler::ResolutionHandler():
  mGameEngine(NULL)
{
  mResult = new ResolutionHandlerResult();
}

ResolutionHandler::~ResolutionHandler()
{
  delete mResult;
  mGameEngine = NULL;
}

/** Probe the actual resolution
  * 
  * \return the found resolution ot throw an exception
  *
  */
const ResolutionHandlerResult&
ResolutionHandler::probe(GameEngine* ge)
{
  mGameEngine = ge;

  if (!probeFromCfg() && probeFromWindow())
    throw "Resolution not found";
  
  return *mResult;
}

bool
ResolutionHandler::probeFromCfg()
{

}

bool
ResolutionHandler::probeFromWindow()
{

}

bool
ResolutionHandler::probeFromString(const std::string&)
{
  
}

bool
ResolutionHandler::probeFromInts(int, int)
{

}

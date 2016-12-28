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

#include <boost/regex.hpp>
#include <stdexcept>   // Uses std::invalid_argument

#include <OgreRenderSystem.h>
#include <OgreConfigOptionMap.h>

#include <iostream>

using namespace Ogre;

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
  
  ConfigOptionMap com = ge->getRenderSystem()->getConfigOptions();
  string res = com["Video Mode"].currentValue;

  
  
  if (!probeFromString(res))
    if (!probeFromWindow(ge->getRenderWindow()))
      throw "Resolution not found";
  
  return *mResult;
}

bool
ResolutionHandler::probeFromWindow(const Ogre::RenderWindow* rw)
{
  if (rw == NULL)
    return false;

  mResult->width = rw->getWidth();
  mResult->height = rw->getHeight();
  return true;
}

bool
ResolutionHandler::probeFromString(const std::string& text)
{
  string regx = "^[[:space:]]*([[:digit:]]*)[[:space:]]*x[[:space:]]*([[:digit:]]*)[[:space:]]*$";
  boost::regex e(regx);
  boost::smatch what;
  
  if(boost::regex_search(text, what, e, boost::match_extra))
    {
      try
	{
	  mResult->width = stoi(std::string(what[1].first, what[1].second));
	  mResult->height = stoi(std::string(what[2].first, what[2].second));
      }
      catch (const std::invalid_argument& ia)
	{
	  // stoi throw this if it can't convert string to int
	  return false;
	}
      return true;
    }
  else
    return false;
}

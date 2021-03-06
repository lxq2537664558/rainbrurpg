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

#ifndef _OGRE_CFG_SAVER_HPP_
#define _OGRE_CFG_SAVER_HPP_

#include <string>

#include <OGRE/OgreConfigOptionMap.h>

// forward declarations
namespace Ogre
{
  class RenderSystem;
}
// End of forward declarations

using namespace std;
using namespace Ogre;

/** Helper to save Ogre configuration to a text file
  *
  *
  */
class OgreCfgSaver
{
public:
  OgreCfgSaver(const string&, RenderSystem*, ConfigOptionMap*);
};

#endif // _OGRE_CFG_SAVER_HPP_

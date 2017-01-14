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

#ifndef _TEMP_MESSAGE_HPP_
#define _TEMP_MESSAGE_HPP_

#include <string>

using namespace std;

// Forward declarations
namespace CEGUI
{
  class GeometryBuffer;
  class Font;
}
class GameEngine;
// End of forward declarations


/** Used to draw a temporary centere message using GeometryBuffers
  *
  *
  *
  */
class TempMessage
{
public:
  TempMessage(GameEngine*);
  ~TempMessage();

  void print(const string&, int);
  void countdown();
  void draw();

private:
  GameEngine* mEngine;
  CEGUI::GeometryBuffer* mBuffer;
  CEGUI::Font* mFont;
  int remaining;  // The remaining time in seconds
  int midscreen; // The midwidth of the screen
};

#endif // !_TEMP_MESSAGE_HPP_

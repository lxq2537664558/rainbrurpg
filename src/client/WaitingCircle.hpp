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

#ifndef _WAITING_CIRCLE_HPP_
#define _WAITING_CIRCLE_HPP_

#include <CEGUI/CEGUI.h>

#include <string>
#include <vector>

// Forward declaration
class GameEngine;
// End of forward declaration

/** Implement a waiting indication
  *
  */
class WaitingCircle
{
public:
  WaitingCircle(const std::string message = "", float animationTime = 1.0f);
  ~WaitingCircle();

  void 	draw();

protected:
  virtual void 	updateSelf (float);
  void debug();

  void updateBuffer();
  
private:
  std::string mMessage;       // The message to be printed
  std::vector<CEGUI::Image*> mImages;
  CEGUI::GeometryBuffer* mScreenBuffer;
  CEGUI::Rectf mScreenArea;
  CEGUI::Rectf mDrawArea;
  
  float updateTime;   // Change image every x seconds
  float currentTime;  // Needed to compare elapsed and update time 
  float currentImage; // Currently drawn image
};

#endif // !_WAITING_CIRCLE_HPP_

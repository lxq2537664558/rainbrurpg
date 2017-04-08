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

#ifndef _ANIMATED_IMAGE_HPP_
#define _ANIMATED_IMAGE_HPP_

#include <CEGUI/CEGUI.h>

#include <vector>

// Forward declaration
class GameEngine;
// End of forward declaration

/** Implement a waiting indication
  *
  * May be renamed AnimatedImage
  *
  */
class AnimatedImage : public CEGUI::DefaultWindow
{
public:
  AnimatedImage(GameEngine*, float animationTime = 1.0f);
  ~AnimatedImage();

protected:
  virtual void 	drawSelf (const CEGUI::RenderingContext &);
  virtual void 	updateSelf (float);
  void debug();
  
  
private:
  std::vector<CEGUI::GeometryBuffer*> mBuffers;
  CEGUI::Image* mBackground;
 
  float updateTime;   // Change image every x seconds
  float currentTime;  // Needed to compare elapsed and update time 
  float currentImage; // Currently drawn image
};

#endif // !_ANIMATED_IMAGE_HPP_

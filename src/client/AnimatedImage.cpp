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

#include "AnimatedImage.hpp"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "Logger.hpp"

#include "GameEngine.hpp"

using namespace CEGUI;

static Rpg::Logger static_logger("waiting-circle", Rpg::LT_BOTH);

AnimatedImage::AnimatedImage(GameEngine* ge):
  DefaultWindow("AnimatedImage", "waitingCircle1")
{
  ImageManager::getSingleton().loadImageset("waiting.imageset");
  mImages[0] = &ImageManager::getSingleton().get("WaitingCircle/Img1");
  gb = &ge->getOgreRenderer()->createGeometryBuffer();
  mImages[0]->render(*gb, Vector2f(0.0f, 0.0f));
}

AnimatedImage::~AnimatedImage()
{

}
  
void
AnimatedImage::drawSelf (const RenderingContext &ctx)
{
  LOGI("Drawing waiting-circle");
  ctx.surface->addGeometryBuffer(RQ_OVERLAY , *gb);
  //  mImages[0]->render();
  
}

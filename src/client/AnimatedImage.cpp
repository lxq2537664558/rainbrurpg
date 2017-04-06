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
  mImages.resize(8);
  try
    {
      ImageManager::getSingleton().loadImageset("waiting.imageset");
      mImages[0] = &ImageManager::getSingleton().get("WaitingCircle/Img4");
      gb = &ge->getOgreRenderer()->createGeometryBuffer();
      CEGUI::Rectf area= CEGUI::Rectf(0.0f, 64.0f, 64.0f, 0.0f);
      mImages[0]->render(*gb, Vector2f(0.0f, 0.0f));
    }
  catch (std::exception e)
    {
      LOGE("There was an error in AnimatedImage::AnimatedImage()");
    }
  show(); 
}

AnimatedImage::~AnimatedImage()
{

}

void
AnimatedImage::debug()
{
  int batch = (int)gb->getBatchCount();
  int vert = (int)gb->getVertexCount();
 
  LOGI("Drawing waiting-circle with" << batch << "batches and"
       << vert << "vertexes");
  bool clip = gb->isClippingActive();
  if (clip)
    {
      LOGI("Clipping : enabled"  );
    }
  else
    {
      LOGI("Clipping : disabled"  );
    }

}


void
AnimatedImage::drawSelf (const RenderingContext &ctx)
{
  gb->setClippingActive(false);
  debug();
  ctx.surface->addGeometryBuffer(RQ_BASE , *gb);
  ctx.surface->draw();
  //  mImages[0]->render();
  
}

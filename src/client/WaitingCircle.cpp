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

#include "WaitingCircle.hpp"

#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "Logger.hpp"

#include "GameEngine.hpp"
#include <iostream>

using namespace CEGUI;

static Rpg::Logger static_logger("waiting-circle", Rpg::LT_BOTH);

/**
  *
  * \param animationTime The full animation in seconds
  *
  */
WaitingCircle::WaitingCircle(const string message, float animationTime):
  updateTime(0),
  currentTime(0),
  currentImage(0),
  mScreenBuffer(NULL)
{
  // This need to come from the imageSet.size()
  int imageNumber = 8;
  mImages.resize(imageNumber);
  updateTime = animationTime / imageNumber; // Per-image time
  mScreenArea = CEGUI::System::getSingletonPtr()->getRenderer()
    ->getDefaultRenderTarget().getArea();
  //  crn.getSize().d_height
  mDrawArea = Rectf(0.0f, 0.0f, 32.0f, 32.0f);
  
  ImageManager::getSingleton().loadImageset("waiting.imageset");
  for (int i = 0; i< imageNumber; ++i)
    {
      LOGI("Incrementing i to" << i);
      ostringstream oss;
      
      oss << "WaitingCircle/Img" << i + 1;
      mImages[i] = &ImageManager::getSingleton().get(oss.str());

    }

  mScreenBuffer = &CEGUI::System::getSingletonPtr()->getRenderer()
    ->createGeometryBuffer();

  updateBuffer();
}

WaitingCircle::~WaitingCircle()
{

}

void
WaitingCircle::debug()
{
  int batch = (int)mScreenBuffer->getBatchCount();
  int vert = (int)mScreenBuffer->getVertexCount();
  /*
  CEGUI::Colour brush = CEGUI::Colour(1.0f, 1.0f, 1.0f);
  mBackground->render( mBuffers[currentImage], Vector2f( 0.0f, 0.0f ),
		       Sizef( 100.0f, 100.0f ) ,
		       new Rectf(0.0f, 0.0f, 64.0f, 64.0f), ColourRect(brush));
  */
  LOGI("Drawing waiting-circle with" << batch << "batches and"
       << vert << "vertexes");
  bool clip = mScreenBuffer->isClippingActive();
  if (clip)
    {
      LOGI("Clipping : enabled"  );
    }
  else
    {
      LOGI("Clipping : disabled"  );
    }
  /* Rectf clipr = gb->getClipRect();
  cout << "Clipping rect " << clipr << endl;
  */
}


void
WaitingCircle::draw()
{
  debug();
  /*  ctx.surface->addGeometryBuffer(ctx.queue , *mBuffers[currentImage]); // RQ_BASE
  ctx.surface->draw();
  */
  mScreenBuffer->draw();
}

void
WaitingCircle::updateSelf (float elapsed)
{
  currentTime += elapsed;
  if (currentTime > updateTime)
    {
      LOGI("Changing image after" << currentTime << "seconds");
      currentTime = 0;
      currentImage++;
      if (currentImage == 8)
	currentImage = 0;
      
    }
}

void
WaitingCircle::updateBuffer()
{
  mScreenBuffer->reset();
  mScreenBuffer->setClippingRegion(mScreenArea);
  mScreenBuffer->setTranslation(CEGUI::Vector3f(
		mScreenArea.getSize().d_width - 64,
		    mScreenArea.getSize().d_height - 64, 0.0f));
  mImages[currentImage]->render(*mScreenBuffer, mDrawArea, 0,
				ColourRect(0xFFFFFFFF));
}

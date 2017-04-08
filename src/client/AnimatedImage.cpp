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
#include <iostream>

using namespace CEGUI;

static Rpg::Logger static_logger("waiting-circle", Rpg::LT_BOTH);

/**
  *
  * \param animationTime The full animation in seconds
  *
  */
AnimatedImage::AnimatedImage(GameEngine* ge, float animationTime):
  DefaultWindow("AnimatedImage", "AnimatedImage"),
  mBackground(NULL),
  updateTime(0),
  currentTime(0),
  currentImage(0)
{
  // This need to come from the imageSet.size()
  int imageNumber = 8;
  mBuffers.resize(imageNumber);
  updateTime = animationTime / imageNumber; // Per-image time
  

  
  ImageManager::getSingleton().loadImageset("waiting.imageset");
  for (int i = 0; i< imageNumber; ++i)
    {
      LOGI("Incrementing i to" << i);
      ostringstream oss;
      
      oss << "WaitingCircle/Img" << i + 1;
      CEGUI::Image* img = &ImageManager::getSingleton().get(oss.str());
      mBuffers[i] = &ge->getOgreRenderer()->createGeometryBuffer();
      img->render(*mBuffers[i], Vector2f(0.0f, 0.0f), Sizef(1.0f, 1.0f));

    }
  /*
  CEGUI::Rectf area= CEGUI::Rectf(0.0f, 64.0f, 64.0f, 0.0f);
  mImages[0] = &ImageManager::getSingleton().get("WaitingCircle/Img4");
  mImages[0]->render(*gb, Vector2f(0.0f, 0.0f), Sizef(1.0f, 1.0f));
  */
  mBackground = &ImageManager::getSingleton()
    .get("TaharezLook/MultiListSelectionBrush");

  // position a quarter of the way in from the top-left of parent.
  this->setPosition( UVector2( UDim( 0.0f, 0.0f ), UDim( 0.0f, 0.0f ) ) );
  // set size to be half the size of the parent
  this->setSize( USize( UDim( 1.0f, 0.0f ), UDim( 1.0f, 0.0f ) ) );

  show();
  /*  
  Image brush = ImagesetManager::getSingleton().get( "BlenderTheme" ).getImage( "ClientBrush" );
  brush.draw( *gb, Vector2( 0, 0 ), Size( 100, 100 ), new Rect(0, 0, 100, 100),  0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF );
  */
}

AnimatedImage::~AnimatedImage()
{

}

void
AnimatedImage::debug()
{
  int batch = (int)mBuffers[currentImage]->getBatchCount();
  int vert = (int)mBuffers[currentImage]->getVertexCount();
  /*
  CEGUI::Colour brush = CEGUI::Colour(1.0f, 1.0f, 1.0f);
  mBackground->render( mBuffers[currentImage], Vector2f( 0.0f, 0.0f ),
		       Sizef( 100.0f, 100.0f ) ,
		       new Rectf(0.0f, 0.0f, 64.0f, 64.0f), ColourRect(brush));
  */
  LOGI("Drawing waiting-circle with" << batch << "batches and"
       << vert << "vertexes");
  bool clip = mBuffers[currentImage]->isClippingActive();
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
AnimatedImage::drawSelf (const RenderingContext &ctx)
{
  debug();
  ctx.surface->addGeometryBuffer(ctx.queue , *mBuffers[currentImage]); // RQ_BASE
  ctx.surface->draw();
}

void
AnimatedImage::updateSelf (float elapsed)
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

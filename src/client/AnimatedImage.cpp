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

AnimatedImage::AnimatedImage(GameEngine* ge):
  DefaultWindow("AnimatedImage", "AnimatedImage")
{
  mImages.resize(8);
  gb = &ge->getOgreRenderer()->createGeometryBuffer();
  try
    {
      ImageManager::getSingleton().loadImageset("waiting.imageset");
      mImages[0] = &ImageManager::getSingleton().get("WaitingCircle/Img4");
      CEGUI::Rectf area= CEGUI::Rectf(0.0f, 64.0f, 64.0f, 0.0f);
      mImages[0]->render(*gb, Vector2f(0.0f, 0.0f), Sizef(64.0f, 64.0f));
    }
  catch (std::exception e)
    {
      LOGE("There was an error in AnimatedImage::AnimatedImage()");
    }

  //  lbi->setSelectionBrushImage("TaharezLook/MultiListSelectionBrush");
  mImages[1] = &ImageManager::getSingleton()
    .get("TaharezLook/MultiListSelectionBrush");
  CEGUI::Colour brush = CEGUI::Colour(1.0f, 1.0f, 1.0f);
  mImages[1]->render( *gb, Vector2f( 0.0f, 0.0f ) /* position */,
		      Sizef( 100.0f, 100.0f ) /* size */,
		      new Rectf(0.0f, 0.0f, 64.0f, 64.0f), ColourRect(brush));

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
  /* Rectf clipr = gb->getClipRect();
  cout << "Clipping rect " << clipr << endl;
  */
}


void
AnimatedImage::drawSelf (const RenderingContext &ctx)
{
  debug();
  ctx.surface->addGeometryBuffer(ctx.queue , *gb); // RQ_BASE
  ctx.surface->draw();
}

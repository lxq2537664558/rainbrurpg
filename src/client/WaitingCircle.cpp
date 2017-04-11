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
  mMessage(message),
  updateTime(0),
  currentTime(0),
  currentImage(0),
  mScreenBuffer(NULL),
  visible(true),
  mFont(NULL)
{
  // This need to come from the imageSet.size()
  int imageNumber = 8;
  mImages.resize(imageNumber);
  updateTime = animationTime / imageNumber; // Per-image time

  mScreenArea = CEGUI::System::getSingletonPtr()->getRenderer()
    ->getDefaultRenderTarget().getArea();
  mDrawArea = Rectf(0.0f, 0.0f, 32.0f, 32.0f);

  // Load all images
  ImageManager::getSingleton().loadImageset("waiting.imageset");
  for (int i = 0; i< imageNumber; ++i)
    {
      LOGI("Incrementing i to" << i);
      ostringstream oss;
      
      oss << "WaitingCircle/Img" << i + 1;
      mImages[i] = &ImageManager::getSingleton().get(oss.str());

    }

  // Load the message font
  string fontname = "DejaVuSans-10-NoScale";
  if(! CEGUI::FontManager::getSingleton().isDefined(fontname))
    LOGE("'" << fontname << "' font is undefined");
  
  mFont = &CEGUI::FontManager::getSingleton().get(fontname);

  
  // Create only one GeometryBuffer object
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
}


void
WaitingCircle::draw()
{
  if (visible)
    mScreenBuffer->draw();
}

void
WaitingCircle::update(float elapsed)
{
  if (!visible)
    return;
    
  currentTime += elapsed;
  if (currentTime > updateTime)
    {
      currentImage++;
      currentTime = 0;
      
      if (currentImage > 7)
	  currentImage = 0;

      updateBuffer();
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

  float te = mFont->getTextExtent(mMessage) + 10;
  mFont->drawText(*mScreenBuffer, mMessage, CEGUI::Vector2f(64 - te, 38),
		  0, CEGUI::Colour(0xFFFFFFFF));
}

void
WaitingCircle::show()
{
  visible = true;
}

void
WaitingCircle::hide()
{
  visible = false;
}

bool
WaitingCircle::isVisible()
{
  return visible;
}

void
WaitingCircle::setVisible(bool v)
{
  visible = v;
}

/*
 * Copyright 2011-2016 Jerome Pasquier
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

#include "TempMessage.hpp"

#include <CEGUI/System.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <CEGUI/GeometryBuffer.h>
#include <CEGUI/Vector.h>
#include <CEGUI/Font.h>
/*
#include <CEGUI/Window.h>
#include <CEGUI/GUIContext.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/GeometryBuffer.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <CEGUI/Vector.h>
*/
#include "GameEngine.hpp"

using namespace CEGUI;

TempMessage::TempMessage(GameEngine* ge):
  mEngine(ge),
  mBuffer(NULL),
  mFont(NULL),
  remaining(0),
  midscreen(0)
{
  // The font object
  mFont = &CEGUI::FontManager::getSingleton().get("DejaVuSans-12");

  // Create the geometry buffer
  const Rectf scrn(ge->getOgreRenderer()->getDefaultRenderTarget().getArea());
  mBuffer = &ge->getOgreRenderer()->createGeometryBuffer();
  mBuffer->setClippingRegion(scrn);
  mBuffer->setTranslation(CEGUI::Vector3f(0.0f, scrn.getSize().d_height - 20, 0.0f));
  
  midscreen = scrn.getSize().d_width / 2;
}

TempMessage::~TempMessage()
{
  mEngine->getOgreRenderer()->destroyGeometryBuffer(*mBuffer);
}

/** Draw the given text for n seconds */
void
TempMessage::print(const string& str, int seconds)
{
  int width = mFont->getTextExtent(str);

  mFont->drawText(*mBuffer, str, CEGUI::Vector2f(midscreen - (width/2), 0), 0,
		  CEGUI::Colour(0xFFFFFFFF));
  remaining = seconds;
}

/** Should be called every seconds */
void
TempMessage::countdown()
{
  if (remaining > 0)
    {
      --remaining;
    }
  else if (remaining == 0)
    {
      mBuffer->reset();
    }
}

void
TempMessage::draw()
{
  mBuffer->draw();
}

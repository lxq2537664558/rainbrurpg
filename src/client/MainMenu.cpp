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

#include "MainMenu.hpp"

#include <CEGUI/System.h>
#include <CEGUI/Window.h>
#include <CEGUI/GUIContext.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/widgets/PushButton.h>
#include <CEGUI/GeometryBuffer.h>
#include <CEGUI/RendererModules/Ogre/Renderer.h>
#include <CEGUI/Vector.h>

#include "Logger.hpp"
#include "GameEngine.hpp"
#include "NyiDialog.hpp"

#include "config.h" // Uses VERSTRING

using namespace CEGUI;

static Rpg::Logger static_logger("state", Rpg::LT_BOTH);

MainMenu::MainMenu():
  GameState("MainMenu"),
  mGameEngine(NULL),
  mNyiLocalTest(NULL),
  mNyiNetworkPlay(NULL),
  mNyiOptions(NULL),
  mLogoGeometry(NULL),
  mVersionGeometry(NULL),
  mFpsGeometry(NULL)
{

}

MainMenu::~MainMenu()
{
  mGameEngine = NULL;

  if (mNyiLocalTest)
    delete mNyiLocalTest;
  
  if (mNyiNetworkPlay)
    delete mNyiLocalTest;

  if (mNyiOptions)
    delete mNyiOptions;
}

void
MainMenu::enter(GameEngine* ge)
{
  LOGI("Entering MainMenu gamestate");

  if (!ge)
    LOGE("MainMenu gamestate received a NULL GameEngine pointer");
  
  mGameEngine = ge;
  
  //  Loading the main menu
  loadLayout("menu.layout");

  // Get screen size
  const Rectf scrn(ge->getOgreRenderer()->getDefaultRenderTarget().getArea());
  
  // Create logo geometry buffer
  mLogoGeometry = &ge->getOgreRenderer()->createGeometryBuffer();

  ImageManager::getSingleton().addFromImageFile("rpgLogo","rpglogo.png");
  ImageManager::getSingleton().get("rpgLogo").render(*mLogoGeometry,
	 Rectf(0, 0, 500, 70), 0, ColourRect(0xFFFFFFFF));
  mLogoGeometry->setClippingRegion(scrn);
  mLogoGeometry->setTranslation(Vector3f((scrn.getSize().d_width/2)-250, 38.0f, 0.0f));

  // Add a version buffer
  mVersionGeometry = &ge->getOgreRenderer()->createGeometryBuffer();
  mVersionGeometry->setClippingRegion(scrn);
  mVersionGeometry->setTranslation(CEGUI::Vector3f(10.0f, scrn.getSize().d_height - 20, 0.0f));
  CEGUI::Font* fnt = &CEGUI::FontManager::getSingleton().get("DejaVuSans-12");
  fnt->drawText(*mVersionGeometry, VERSTRING, CEGUI::Vector2f(0, 0), 0,
                        CEGUI::Colour(0xFFFFFFFF));

  // Add a FPS + stats buffer (a line of text = 20.0 height)
  mFpsGeometry = &ge->getOgreRenderer()->createGeometryBuffer();
  mFpsGeometry->setClippingRegion(scrn);
  mFpsGeometry->setTranslation(CEGUI::Vector3f(scrn.getSize().d_width - 150, scrn.getSize().d_height - 60, 0.0f));
  fnt->drawText(*mFpsGeometry, "No update slot", CEGUI::Vector2f(0, 0), 0,
                        CEGUI::Colour(0xFFFFFFFF));

  
  // Handle events
  addEvent("root/GameMenu/Exit", CEGUI::PushButton::EventClicked,
	   CEGUI::Event::Subscriber(&MainMenu::onExit, this));
  addEvent("root/GameMenu/LocalTest", CEGUI::PushButton::EventClicked,
	   CEGUI::Event::Subscriber(&MainMenu::onLocalTest, this));
  addEvent("root/GameMenu/NetworkPlay", CEGUI::PushButton::EventClicked,
	   CEGUI::Event::Subscriber(&MainMenu::onNetworkPlay, this));
  addEvent("root/GameMenu/Options", CEGUI::PushButton::EventClicked,
	   CEGUI::Event::Subscriber(&MainMenu::onNetworkPlay, this));

}

void
MainMenu::exit(GameEngine* ge)
{
  // Remove GeometryBuffer objects
  ge->getOgreRenderer()->destroyGeometryBuffer(*mLogoGeometry);
  ge->getOgreRenderer()->destroyGeometryBuffer(*mVersionGeometry);
  ge->getOgreRenderer()->destroyGeometryBuffer(*mFpsGeometry);

}

/* The callback for the menu.layout's exit button
 *
 */
bool
MainMenu::onExit(const CEGUI::EventArgs& evt)
{
  mGameEngine->shutdown();
  return true;
}


/* The callback for the 'Local Test' button
 *
 */
bool
MainMenu::onLocalTest(const CEGUI::EventArgs&)
{
  if (!mNyiLocalTest)
    mNyiLocalTest = new NyiDialog("Local Test", "nyiLocalTest");
    
  mNyiLocalTest->show();
  return true;
}

/** The Network Play menu callback
 *
 */
bool
MainMenu::onNetworkPlay(const CEGUI::EventArgs&)
{
  if (!mNyiNetworkPlay)
    mNyiNetworkPlay = new NyiDialog("Network play", "nyiNetworkPlay");
    
  mNyiNetworkPlay->show();
  return true;
}

/** The Options button menu callback
 *
 */
bool
MainMenu::onOptions(const CEGUI::EventArgs&)
{
  if (!mNyiOptions)
    mNyiOptions = new NyiDialog("Options", "nyiOptions");
    
  mNyiOptions->show();
  return true;
}
				
void
MainMenu::drawOverlay()
{
  mLogoGeometry->draw();
  mVersionGeometry->draw();
  mFpsGeometry->draw();
}

/* FPS update function
 *
 */
void
MainMenu::hudUpdate()
{

}

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

#include "Logger.hpp"
#include "GameEngine.hpp"

using namespace CEGUI;

static Rpg::Logger static_logger("state", Rpg::LT_BOTH);

MainMenu::MainMenu():
  GameState("MainMenu"),
  mGameEngine(NULL)
{

}

MainMenu::~MainMenu()
{
  mGameEngine = NULL;
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

  // Handle events
  addEvent("root/GameMenu/Exit", CEGUI::PushButton::EventClicked,
	   CEGUI::Event::Subscriber(&MainMenu::onExit, this));
}

void
MainMenu::exit(GameEngine*)
{

}


/* The callback for the menu.layout's exit button
 *
 */
bool
MainMenu::onExit(const CEGUI::EventArgs& evt)
{
  mGameEngine->shutdown();
}

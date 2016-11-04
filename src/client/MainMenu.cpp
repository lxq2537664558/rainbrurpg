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
#include "NyiDialog.hpp"

using namespace CEGUI;

static Rpg::Logger static_logger("state", Rpg::LT_BOTH);

MainMenu::MainMenu():
  GameState("MainMenu"),
  mGameEngine(NULL),
  mNyiLocalTest(NULL)
{

}

MainMenu::~MainMenu()
{
  mGameEngine = NULL;

  if (mNyiLocalTest)
    delete mNyiLocalTest;
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
  addEvent("root/GameMenu/LocalTest", CEGUI::PushButton::EventClicked,
	   CEGUI::Event::Subscriber(&MainMenu::onLocalTest, this));

  /*
    CEGUI::PushButton* btnLocalTest = (CEGUI::PushButton *)menuWindow->
    getChild("GameMenu/LocalTest");
  btnLocalTest->subscribeEvent(CEGUI::PushButton::EventClicked, CEGUI::Event::Subscriber(&GameEngine::onLocalTest, this));
  */
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

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
#include <CEGUI/GUIContext.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>

#include "Logger.hpp"

using namespace CEGUI;

static Rpg::Logger static_logger("state", Rpg::LT_BOTH);

MainMenu::MainMenu():
  GameState("MainMenu")
{

}

MainMenu::~MainMenu()
{

}

void
MainMenu::enter(GameEngine*)
{
  LOGI("Entering MainMenu gamestate");

  //  Loading the main menu
  GUIContext* context = &System::getSingleton().getDefaultGUIContext();
  WindowManager *wmgr = WindowManager::getSingletonPtr();
  Window* root = wmgr->createWindow("DefaultWindow", "Root");
  context->setRootWindow(root);
  Window* menuWindow = wmgr->loadLayoutFromFile("menu.layout");
  root->addChild(menuWindow);
  
}

void
MainMenu::exit(GameEngine*)
{

}

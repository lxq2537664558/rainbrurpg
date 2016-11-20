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

#include "GameState.hpp"

#include <CEGUI/Window.h>

#include "Logger.hpp"

#include "GameEngine.hpp"

static Rpg::Logger static_logger("state", Rpg::LT_BOTH);

using namespace CEGUI;

GameState::GameState(const string& name):
  mName(name),
  mRoot(NULL)
{

}

GameState::~GameState()
{
  mRoot = NULL;
}
  
const string&
GameState::getName()const
{
  return mName;
}

/* Load a CEGUI layout from a file
 *
 */
CEGUI::Window*
GameState::loadLayout(const string& filename)
{
  Window* w;
  
  if (!WindowManager::getSingletonPtr())
    LOGE("Can't get a valid CEGUI WindowManager");

  if (!mRoot)
    {
      // Create it only the first time
      mRoot = WindowManager::getSingletonPtr()->
	createWindow("DefaultWindow", "Root");
      System::getSingleton().getDefaultGUIContext().setRootWindow(mRoot);
    }
 
  try{
    w = WindowManager::getSingletonPtr()->loadLayoutFromFile(filename);
    mRoot->addChild(w);
  }
  catch (...){
    LOGE("Can't load CEGUI layout");
  }
  return w;
}

/* Subscribe an event to a CEGUI window/button
 *
 * /param button The name of the button is the CEGUI way (i.e. something like
 *        "root/GameMenu/Exit").
 * /param event the CEGUI event name (i.e. CEGUI::PushButton::EventClicked).
 * /param callback A CEGUI event subscriber (i.e. CEGUI::Event::
 *        Subscriber(&GameEngine::onExit, this).
 *
 */

void
GameState::addEvent(const string& button, const CEGUI::String& event,
		    CEGUI::Event::Subscriber callback)
{
  mRoot->getChild(button)->subscribeEvent(event, callback);
}

/* Overlay drawing handler
 *
 * This function is called for every frame when it's time to draw CEGUI
 * overlays. Override it if tou need to draw some CEGUI GeometryBuffer.
 *
 */
void
GameState::drawOverlay()
{
  
}

/* A function called every second
 *
 * Override this if you need to update things about once per second.
 *
 */
void
GameState::hudUpdate()
{

}

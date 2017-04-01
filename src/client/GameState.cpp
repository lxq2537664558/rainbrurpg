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
 * To remove the created window, simply destroy it using :
 * CEGUI::WindowManager::getSingleton().destroyWindow(windowPtr)
 *
 *
 * \param filename   The layout filename.
 * \param windowName The to-be-returned CEGUI window name.
 *
 */
CEGUI::Window*
GameState::loadLayout(const string& filename, const string& windowName)
{
  Window *w, *ret;
  
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
    ret = mRoot->getChild(windowName);
  }
  catch (...){
    LOGE("Can't load CEGUI layout");
  }
  return ret;
}

/** Destroys the root window
  *
  * If you don't call this, you may have a CEGUI when registering event
  * (something like 'root/GameMenu/Exit' is not attached to Element at 'Root').
  *
  */
void GameState::destroyRootWindow()
{
  if (mRoot)
    {
      CEGUI::WindowManager::getSingleton().destroyWindow(mRoot);
      mRoot = NULL;
    }
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
  
  LOGI("Connecting button " << button << ")");
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

/** Send a pressed key event
  *
  * \return true if you're the last event user (consume event)
  *
  */
bool
GameState::keyPressed( const OIS::KeyEvent&)
{
  return false;
}

/** Send a released key event
  *
  * \return true if you're the last event user (consume event)
  *
  */
bool
GameState::keyReleased( const OIS::KeyEvent&)
{
  return false;
}

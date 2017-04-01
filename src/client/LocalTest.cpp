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

#include <CEGUI/Window.h>
#include <CEGUI/WindowManager.h>
#include <CEGUI/CEGUI.h>

#include <time.h>       // Uses time 
#include <cstdlib>      // Uses srand, rand

#include "LocalTest.hpp"

#include "GameEngine.hpp"

#include "Server.hpp"
#include "Logger.hpp"

using namespace std;
using namespace CEGUI;

static Rpg::Logger static_logger("state", Rpg::LT_BOTH);

LocalTest::LocalTest():
  GameState("LocalTest"),
  mGameEngine(NULL),
  mMenuWindow(NULL)
{

  // Just to test for thze serverlib library
  Server* s = new Server(STT_EMBEDDED);
  
}

LocalTest::~LocalTest()
{

}
  
void
LocalTest::enter(GameEngine* ge)
{
  // Keep a pointer to GameEngine to be able to go back to MainMenu
  mGameEngine = ge;
  
  mMenuWindow = loadLayout("local_test.layout", "LocalTestWin");

  WindowManager& winMgr = WindowManager::getSingleton();
  TabControl* winTabControl = static_cast<TabControl*>(mMenuWindow->getChild("TabControl"));
  winTabControl->setTabHeight(UDim(0.15f, 0.0f)); // Make the tab buttons a little bigger
  Window* tabPage = mMenuWindow->getChild("TabPane1");
  tabPage->setText("  New world  ");
  winTabControl->addTab(tabPage);
  tabPage->setProperty("Size", "{{1,0},{1,0}}");
  tabPage->setProperty("Position", "{{0,0},{0,0}}");

  Window* tabPage2 = mMenuWindow->getChild("TabPane2");
  tabPage2->setText("  Existing world  ");
  winTabControl->addTab(tabPage2);
  tabPage2->setProperty("Size", "{{1,0},{1,0}}");
  tabPage2->setProperty("Position", "{{0,0},{0,0}}");

  randomSeed();

  // Handle events
  addEvent("LocalTestWin/TabControl/TabPane1/btnRandom",
	   CEGUI::PushButton::EventClicked,
	   CEGUI::Event::Subscriber(&LocalTest::randomSeed, this));
  addEvent("LocalTestWin/btnBack", CEGUI::PushButton::EventClicked,
	   CEGUI::Event::Subscriber(&LocalTest::onBack, this));

  LOGI("LocalTest signals successfully registered");
  
}


void
LocalTest::exit(GameEngine*)
{
  CEGUI::WindowManager::getSingleton().destroyWindow(mMenuWindow);
  mMenuWindow = NULL;
}


void
LocalTest::save(StateSaver*)
{

}


void
LocalTest::restore(StateSaver*)
{

}

/** Get a new random seed and set it to the GUI text box.
  *
  *
  */
void
LocalTest::randomSeed()
{
  Window* teSeed = mMenuWindow->getChild("TabControl/TabPane1/ebSeed");
  srand(time(NULL));
  teSeed->setText(std::to_string(rand()));
}

/** Go back to the main menu */
bool
LocalTest::onBack(const CEGUI::EventArgs&)
{
  mGameEngine->toMainMenu();
}

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

#include "Server.hpp"

using namespace std;
using namespace CEGUI;

LocalTest::LocalTest():
  GameState("LocalTest"),
  mMenuWindow(NULL)
{

  // Just to test for thze serverlib library
  Server* s = new Server(STT_EMBEDDED);
  
}

LocalTest::~LocalTest()
{

}
  
void
LocalTest::enter(GameEngine*)
{
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

}


void
LocalTest::exit(GameEngine*)
{
  CEGUI::WindowManager::getSingleton().destroyWindow(mMenuWindow);
  
}


void
LocalTest::save(StateSaver*)
{

}


void
LocalTest::restore(StateSaver*)
{

}

void
LocalTest::randomSeed()
{
  Window* teSeed = mMenuWindow->getChild("TabControl/TabPane1/ebSeed");
  srand(time(NULL));
  teSeed->setText(std::to_string(rand()));
}


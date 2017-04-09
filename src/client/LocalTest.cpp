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

//#include <time.h>       // Uses time 
//#include <cstdlib>      // Uses srand, rand

#include "LocalTest.hpp"

#include "GameEngine.hpp"
#include "WaitingCircle.hpp"

#include "Server.hpp"
#include "Logger.hpp"
#include "Seed.hpp"

using namespace std;
using namespace CEGUI;

static Rpg::Logger static_logger("state", Rpg::LT_BOTH);

LocalTest::LocalTest():
  GameState("LocalTest"),
  mGameEngine(NULL),
  mMenuWindow(NULL),
  lbWorlds(NULL),
  mWaiting(NULL)
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

  // Add some existing worlds
  lbWorlds = static_cast<Listbox*>
    (mMenuWindow->getChild("TabControl/TabPane2/lbExisting"));
  lbWorlds->setMultiselectEnabled(false);
  lbWorlds->setSortingEnabled(true);

  // Add some summy worlds to test for selection
  addWorld("World 1");
  addWorld("World A");
  addWorld("World lplp");
  
  // Handle events
  addEvent("LocalTestWin/TabControl/TabPane1/btnRandom",
	   CEGUI::PushButton::EventClicked,
	   CEGUI::Event::Subscriber(&LocalTest::randomSeed, this));
  addEvent("LocalTestWin/btnBack", CEGUI::PushButton::EventClicked,
	   CEGUI::Event::Subscriber(&LocalTest::onBack, this));
  addEvent("LocalTestWin/btnBack", CEGUI::PushButton::EventClicked,
	   CEGUI::Event::Subscriber(&LocalTest::onBack, this));
  addEvent("LocalTestWin/TabControl", CEGUI::TabControl::EventSelectionChanged,
  	   CEGUI::Event::Subscriber(&LocalTest::onTabChange, this));
  addEvent("LocalTestWin/TabControl/TabPane2/lbExisting",
	   CEGUI::TabControl::EventSelectionChanged,
	   CEGUI::Event::Subscriber(&LocalTest::onSelectionChange, this));
  
  LOGI("LocalTest signals successfully registered");

  // AnimatedImage* wic = new AnimatedImage(ge);
  /*  ImageManager::getSingleton().loadImageset("waiting.imageset");
  CEGUI::Window *wic = CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/StaticImage","PrettyWindow" );
  wic->setProperty("Image","WaitingCircle/Img1");
  lbWorlds->addChild(wic);
  */
  mWaiting = new WaitingCircle();
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
  RLGL::Seed s;
  s.randomize();
  teSeed->setText(s.to_s());
  check();
}

/** Go back to the main menu */
bool
LocalTest::onBack(const CEGUI::EventArgs&)
{
  mGameEngine->toMainMenu();
}

bool
LocalTest::keyPressed( const OIS::KeyEvent& )
{
  check();
  return true;
}

bool
LocalTest::onTabChange(const CEGUI::EventArgs&)
{
  check();
  return true;
}


/** Check for the playability of the form
  *
  * This function shouldn't change the existing worlds list box selection
  * to avoid an infinite loop.
  *
  */
void
LocalTest::check()
{
  // Must enable play button ?
  bool play = false;
  
  // Get the active Tabcontrol
  TabControl* tc=static_cast<TabControl*>(mMenuWindow->getChild("TabControl"));
  int sel = tc->getSelectedTabIndex();

  if (sel ==0 ) /* New world tab */
    {
      // Must test if name and seed aren't empty
      bool s1 = !mMenuWindow->getChild("TabControl/TabPane1/ebSeed")
	->getText().empty();
      bool s2 = !mMenuWindow->getChild("TabControl/TabPane1/ebName")
	->getText().empty();
      play = s1 && s2;
    }
  else /* Existing world tab */
    {
      // Must test if a world is selected
      Listbox* lb = static_cast<Listbox*>
	(mMenuWindow->getChild("TabControl/TabPane2/lbExisting"));
      
      play = lb->getSelectedCount() != 0;
    }

  // Change the Play button state
  Window* btnPlay = mMenuWindow->getChild("btnPlay");
  if (play)
    btnPlay->setProperty("Disabled", "False");
  else
    btnPlay->setProperty("Disabled", "True");
    
}

/** Event handler fired when the existing worlds list box selection changed
  *
  */
bool
LocalTest::onSelectionChange(const CEGUI::EventArgs&)
{
  check();
  return true;
}

void
LocalTest::addWorld(const string& worldName)
{
  // lbWorlds
  ListboxTextItem* lbi = new ListboxTextItem(worldName, 1);
  lbi->setSelectionColours(CEGUI::Colour(0.0f, 0.0f, 0.8f));
  lbi->setTextColours(CEGUI::Colour(0xFFFFFFFF));
  lbi->setSelectionBrushImage("TaharezLook/MultiListSelectionBrush");
  lbWorlds->addItem(lbi);
}

void
LocalTest::drawOverlay()
{
  LOGI("in LocalTest::drawOverlay()");
  mWaiting->draw();
}

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

#ifndef _LOCAL_TEST_HPP_
#define _LOCAL_TEST_HPP_

#include "GameState.hpp"

#include <LocalWorldsListener.hpp>

// Forward declaration
class GameEngine;
class WaitingCircle;
namespace CEGUI
{
  class Listbox;
  class Window;
}
// End of forward declaration


class LocalTest: public GameState, public RLGL::LocalWorldsListener
{
public:
  LocalTest();
  virtual ~LocalTest();

  void enter(GameEngine*);
  void exit(GameEngine*);
  void save(StateSaver*);
  void restore(StateSaver*);

  virtual bool keyPressed( const OIS::KeyEvent& );
  virtual void drawOverlay();
  virtual void update(float);
  void check();

  void addWorld(const string&);

  // Overides from LocalWorldsListener
  virtual void parsingStarted(int);
  virtual void parsingFinished();
  virtual void gotWorld(const std::string&); 

  // Getters and setters
  string getSeed();
  void setSeed(const string&);
  
protected:
  bool onBack(const CEGUI::EventArgs&);
  bool onTabChange(const CEGUI::EventArgs&);
  bool onSelectionChange(const CEGUI::EventArgs&);
  
  void randomSeed();
  
private:
  GameEngine* mGameEngine;    // To be able to go back to MainMenu
  CEGUI::Window* mMenuWindow;
  CEGUI::Listbox* lbWorlds; // Existing worlds listbox
  WaitingCircle* mWaiting;
};

#endif  // !_LOCAL_TEST_HPP_

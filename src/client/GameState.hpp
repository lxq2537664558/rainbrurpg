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

#ifndef _GAME_STATE_HPP_
#define _GAME_STATE_HPP_

#include <string>
#include <CEGUI/String.h>
#include <CEGUI/Event.h>

// Forward declaration
namespace CEGUI
{
  class Window;
}
class GameEngine;
class StateSaver;
// End of forward declaration

using namespace std;

/* The base class of all game states
 *
 */
class GameState
{
public:

  GameState(const string&);
  virtual ~GameState();
  
  virtual void enter(GameEngine*)=0;
  virtual void exit(GameEngine*)=0;

  virtual void save(StateSaver*)=0;
  virtual void restore(StateSaver*)=0;
  
  virtual void drawOverlay();
  virtual void hudUpdate();

  const string& getName()const;
  
protected:
  CEGUI::Window* loadLayout(const string&, const string&);
  void addEvent(const string&, const CEGUI::String&,CEGUI::Event::Subscriber);

private:
  string mName;         // The state name, only for debuging purpose
  CEGUI::Window* mRoot; // The root window for all CEGUI layouts
};

#endif // !_GAME_STATE_HPP_

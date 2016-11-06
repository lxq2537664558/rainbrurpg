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

#ifndef _MAIN_MENU_HPP_
#define _MAIN_MENU_HPP_

#include "GameState.hpp"

#include <CEGUI/EventArgs.h>

// Forward declaration
class GameEngine;
class NyiDialog;
namespace CEGUI
{
  class GeometryBuffer;
}
// End of forward declaration

/* The MainMenu game state
 *
 */
class MainMenu: public GameState
{
public:
  MainMenu();
  ~MainMenu();

  virtual void enter(GameEngine*);
  virtual void exit(GameEngine*);

  virtual void drawOverlay();
  
protected:
  bool onExit(const CEGUI::EventArgs&);
  bool onLocalTest(const CEGUI::EventArgs&);
  bool onNetworkPlay(const CEGUI::EventArgs&);
  bool onOptions(const CEGUI::EventArgs&);
  
private:
  GameEngine* mGameEngine;    // Keep a pointer to be able to shutdown

  NyiDialog* mNyiLocalTest;   // NotYetImpl. dialog for the LocalTest button
  NyiDialog* mNyiNetworkPlay; // NotYetImpl. dialog for the NetworkPlay button
  NyiDialog* mNyiOptions;     // NotYetImpl. dialog for the Options button

  CEGUI::GeometryBuffer* mLogoGeometry;    // The logo overlay
  CEGUI::GeometryBuffer* mVersionGeometry; // Where we print version-revision
};

#endif //!_MAIN_MENU_HPP_

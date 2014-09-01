/*
 * Copyright 2011-2014 Jerome Pasquier
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

#ifndef _GAME_ENGINE_HPP_
#define _GAME_ENGINE_HPP_

#include <string>

#include <OgreFrameListener.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h> // for Ogre::WindowEventListener

// Forward declarations
namespace OIS
{
  class InputManager;
  class Keyboard;
  class Mouse;
}
// End of forward declarations

class GameEngine: public Ogre::FrameListener,
		  public Ogre::WindowEventListener
{
public:
  GameEngine(void);
  virtual ~GameEngine(){};

protected:
  // Ogre::FrameListener
  virtual bool frameRenderingQueued(const Ogre::FrameEvent&);
  virtual void windowClosed(Ogre::RenderWindow*);

  void setupResources(const std::string&);

private:
  Ogre::RenderWindow* mWindow;

  OIS::InputManager* mInputManager;
  OIS::Keyboard* mKeyboard;
  OIS::Mouse* mMouse;

  Ogre::String mResourcesCfg;

};

#endif // !_GAME_ENGINE_HPP_

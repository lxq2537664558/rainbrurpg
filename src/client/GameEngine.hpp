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

#ifndef _GAME_ENGINE_HPP_
#define _GAME_ENGINE_HPP_

#include <string>

#include <OgreFrameListener.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h> // for Ogre::WindowEventListener

#include <OISEvents.h>
#include <OISMouse.h>
#include <OISKeyboard.h>

#include <CEGUI/CEGUI.h>

// Forward declarations
namespace Ogre
{
  class Root;
}
namespace OIS
{
  class InputManager;
  class Keyboard;
}
// End of forward declarations

class GameEngine: public Ogre::FrameListener,
		  public Ogre::WindowEventListener,
		  public OIS::MouseListener,
		  public OIS::KeyListener
{
public:
  GameEngine(void);
  virtual ~GameEngine(){};

  void run();

protected:
  // Ogre::FrameListener
  virtual bool frameRenderingQueued(const Ogre::FrameEvent&);
  virtual void windowClosed(Ogre::RenderWindow*);
  // OIS::MouseListener
  bool mouseMoved( const OIS::MouseEvent&);
  bool mousePressed( const OIS::MouseEvent&, OIS::MouseButtonID);
  bool mouseReleased( const OIS::MouseEvent&, OIS::MouseButtonID);
  // OIS::KeyListener
  bool keyPressed( const OIS::KeyEvent&);
  bool keyReleased( const OIS::KeyEvent&);

  void setupResources(void);
  CEGUI::MouseButton convertButton(OIS::MouseButtonID);
  void initializeCegui();
  
private:
  Ogre::Root* mRoot;
  Ogre::RenderWindow* mWindow;

  OIS::InputManager* mInputManager;
  OIS::Keyboard* mKeyboard;
  OIS::Mouse* mMouse;

  Ogre::String mResourcesCfg;
  bool mShutdown;
  Ogre::SceneManager* mSceneMgr;

  CEGUI::GUIContext* mContext;
};

#endif // !_GAME_ENGINE_HPP_

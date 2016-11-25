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
#include <map>

#include <OgreFrameListener.h>
#include <OgreRenderWindow.h>
#include <OgreWindowEventUtilities.h> // for Ogre::WindowEventListener
#include <OgreTimer.h>

#include <OISEvents.h>
#include <OISMouse.h>
#include <OISKeyboard.h>

#include <CEGUI/CEGUI.h>

#include "StateManager.hpp"

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
namespace CEGUI
{
  class OgreRenderer;
  class GeometryBuffer;
}
class MainMenu;
class TempMessage;
// End of forward declarations

using namespace std;

/** A map used to override Ogre configuration when restarting engine
  *
  * Instead of switch fullscreen using a boolean, we set
  * the new confiuration in this map. All configuration in this
  * map will override the current Renderer's ConfigMapOption.
  *
  */
typedef map<string,string> tOgreCfgOverride; 

class GameEngine: public Ogre::FrameListener,
		  public Ogre::WindowEventListener,
		  public OIS::MouseListener,
		  public OIS::KeyListener,
		  public StateManager
{
public:
  GameEngine(void);
  virtual ~GameEngine();

  void run();
  bool running();
  bool restarting();
  void shutdown();
  void reconfigure();
  
  CEGUI::OgreRenderer* getOgreRenderer()const;
  Ogre::RenderWindow* getRendererWindow()const;
  
protected:
  // Ogre::FrameListener
  virtual bool frameRenderingQueued(const Ogre::FrameEvent&);
  virtual void windowClosed(Ogre::RenderWindow*);
  virtual void windowResized(Ogre::RenderWindow* rw);
  // OIS::MouseListener
  bool mouseMoved( const OIS::MouseEvent&);
  bool mousePressed( const OIS::MouseEvent&, OIS::MouseButtonID);
  bool mouseReleased( const OIS::MouseEvent&, OIS::MouseButtonID);
  // OIS::KeyListener
  bool keyPressed( const OIS::KeyEvent&);
  bool keyReleased( const OIS::KeyEvent&);

  void setupResources(void);
  CEGUI::MouseButton convertButton(OIS::MouseButtonID);
  void initialiseCegui();
  void initialiseOgre();
  void initialiseOIS();
  void shutdownOgre();
  
  // CEGUI events
  bool onOptions(const CEGUI::EventArgs&);
  bool overlayHandler(const CEGUI::EventArgs&);

  string getNextResolution(bool*);
  string getPreviousResolution(bool*);
  
private:
  Ogre::Root* mRoot;
  Ogre::RenderWindow* mWindow;

  OIS::InputManager* mInputManager;
  OIS::Keyboard* mKeyboard;
  OIS::Mouse* mMouse;

  Ogre::String mResourcesCfg;
  bool mShutdown;
  bool mRestart; //!< Used to reconfigure Ogre (i.e. for fullscreen
  Ogre::SceneManager* mSceneMgr;

  CEGUI::GUIContext* mContext;
  CEGUI::OgreRenderer* mRenderer;

  Ogre::Timer mTimer;
  MainMenu* mMainMenu;
  TempMessage* mTempMsg; // A temporary message buffer
  tOgreCfgOverride mCfgOverride; // Ogre configuration override map
  string mRestartMessage;  // The temporary message printed at reconfiguration
};

#endif // !_GAME_ENGINE_HPP_

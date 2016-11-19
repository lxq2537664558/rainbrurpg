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

#include <Logger.hpp> // Before headers to avoid std::list/Ogre::list conflict

#include "GameEngine.hpp"

#include <iostream>
#include <sstream>

#include <Ogre.h>
#include <OIS.h>

#include <CEGUI/RendererModules/Ogre/Renderer.h>

#include "MainMenu.hpp"

using namespace std;
using namespace Ogre;

static Rpg::Logger static_logger("engine", Rpg::LT_BOTH);

GameEngine::GameEngine(void):
  StateManager(this),
  mWindow(NULL),
  mInputManager(NULL),
  mKeyboard(NULL),
  mMouse(NULL),
  mResourcesCfg("resources.cfg"),
  mShutdown(false),
  mRestart(false),
  mToFullscreen(false), // do not interfere with Ogre's configdialog
  mSceneMgr(NULL),
  mContext(NULL),
  mRenderer(NULL),
  mMainMenu(NULL)
{

  mMainMenu = new MainMenu();
  
  //  log("Starting Ogre::Root");
  mRoot = new Root();
  if (!mRoot->showConfigDialog())
    {
      mShutdown=true;
      return;
    }

  //    log("Creating rendering window");
  mWindow = mRoot->initialise(true, "RainbruRPG");
      
  // Create the SceneManager, in this case a generic one
  mSceneMgr = mRoot->createSceneManager(ST_GENERIC, "ExampleSMInstance");

  // Create the camera
  Camera* mCamera = mSceneMgr->createCamera("PlayerCam");
      
  // Create one viewport, entire window
  Ogre::Viewport* vp = mWindow->addViewport(mCamera);
  vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

  // Initialize OIS
  OIS::ParamList pl;   
  size_t windowHnd = 0;
  std::ostringstream windowHndStr; 
#if defined OIS_LINUX_PLATFORM
  mWindow->getCustomAttribute( "WINDOW", &windowHnd ); 
  windowHndStr << windowHnd; 
  
  pl.insert(std::make_pair(string("WINDOW"), windowHndStr.str())); 
  pl.insert(std::make_pair(string("x11_mouse_grab"),
			   std::string("false"))); 
  pl.insert(std::make_pair(std::string("x11_mouse_hide"),
			   std::string("true"))); 

#else
  mWindow->getCustomAttribute( "HWND", &windowHnd );
  windowHndStr << windowHnd;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_FOREGROUND" )));
  pl.insert(std::make_pair(std::string("w32_mouse"), std::string("DISCL_NONEXCLUSIVE"))); 

#endif

  mInputManager = OIS::InputManager::createInputSystem( pl );
  if (!mInputManager)
    cerr << "OIS inputmanager object is null" << endl;
  
  // Get mouse and keyboard
  try
    {
      mKeyboard = static_cast<OIS::Keyboard*>
	(mInputManager->createInputObject(OIS::OISKeyboard, true));
      LOGI("OIS keyboard correctly initialized");
	  
    }
  catch (OIS::Exception e){
    LOGE("Error while initialize IOS keyboard "<< e.eFile 
	 << ":" << e.eText);
  }

  try 
    {
      mMouse = static_cast<OIS::Mouse*>
	(mInputManager->createInputObject(OIS::OISMouse, true));
      LOGI("OIS mouse correctly initialized");
      
      // Initialize OIS mouse metrics
      unsigned int width, height, depth;
      int top, left;
      mWindow->getMetrics(width, height, depth, left, top);
      const OIS::MouseState &ms = mMouse->getMouseState();
      ms.width = width;
      ms.height = height;
    }
  catch (OIS::Exception e){
    LOGE("Error while initialize IOS mouse "<< e.eFile << ":" << e.eText);
  }

  // Set OIS event callbacks
  mKeyboard->setEventCallback(this);
  mMouse->setEventCallback(this);
  
  // Alter the camera aspect ratio to match the viewport
  mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) /
			  Ogre::Real(vp->getActualHeight()));
  
  // Set ambient light
  mSceneMgr->setAmbientLight(Ogre::ColourValue(0.0, 0.0, 0.0));
  
  // Create a light
  Ogre::Light* l = mSceneMgr->createLight("MainLight");
  l->setPosition(20,80,50);
  
  mRoot->addFrameListener(this);
  
  WindowEventUtilities::addWindowEventListener(mWindow, this);

}

GameEngine::~GameEngine()
{
  Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
  //  windowClosed(mWindow);
  delete mRoot;
}

void
GameEngine::initializeCegui()
{
  // Initialize CEGUI
  mRenderer  = &CEGUI::OgreRenderer::bootstrapSystem();

  CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
  CEGUI::Font::setDefaultResourceGroup("Fonts");
  CEGUI::Scheme::setDefaultResourceGroup("Schemes");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
  CEGUI::WindowManager::setDefaultResourceGroup("Layouts");
}

/** Return true to continue rendering, false to drop out of the rendering loop
  *
  */
bool GameEngine::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
  if (mShutdown || mRestart || mWindow->isClosed())
    return false;
  
  mMouse->capture();
  mKeyboard->capture();

  return true;
}

void
GameEngine::run()
{
  LOGE("GameEngine::run() called...");
  
  setupResources();
  initializeCegui();
  
  CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");
  CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
  //  CEGUI::SchemeManager::getSingleton().createFromFile("VanillaCommonDialogs.scheme");

  // Get the CEGUI's default context
  mContext = &CEGUI::System::getSingleton().getDefaultGUIContext();
  mContext->getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

  // Move CEGUI mouse to (0,0)
  CEGUI::Vector2f mousePos = mContext->getMouseCursor().getPosition();  
  mContext->injectMouseMove(-mousePos.d_x,-mousePos.d_y);

  setCurrentState(mMainMenu);

  // This line in needed to make the CEGUI::GeometryBuffer objects actually
  // appear
  CEGUI::System::getSingleton().getDefaultGUIContext().clearGeometry(CEGUI::RQ_OVERLAY);
  
  mContext->subscribeEvent(CEGUI::RenderingSurface::EventRenderQueueStarted,
	      CEGUI::Event::Subscriber(&GameEngine::overlayHandler,  this));
  
  // Start rendering
  LOGI("Staring rendering loop");
  mRoot->startRendering();

}

void GameEngine::setupResources(void)
{
  LOGI("Setting up resources");
  // Load resource paths from config file
  Ogre::ConfigFile cf;
  cf.load(mResourcesCfg);
  // Go through all sections & settings in the file
  Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
  Ogre::String secName, typeName, archName;
  while (seci.hasMoreElements())
    {
      secName = seci.peekNextKey();
      Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
      Ogre::ConfigFile::SettingsMultiMap::iterator i;
      for (i = settings->begin(); i != settings->end(); ++i)
	{
	  typeName = i->first;
	  archName = i->second;
	  Ogre::ResourceGroupManager::getSingleton()
	    .addResourceLocation(archName, typeName, secName);
	}
    }
  LOGI("All resources groups added");
  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void 
GameEngine::windowClosed(Ogre::RenderWindow* rw)
{
  mShutdown = true;
  
  //Only close for window that created OIS (the main window in these demos)
  if( rw == mWindow )
    {
      if( mInputManager )
	{
	  mInputManager->destroyInputObject( mMouse );
	  mInputManager->destroyInputObject( mKeyboard );
	  
	  OIS::InputManager::destroyInputSystem(mInputManager);
	  mInputManager = NULL;
	}
    }
}

bool  
GameEngine::mouseMoved( const OIS::MouseEvent& evt )
{
  mContext->injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
  
  // Scroll wheel.
  if (evt.state.Z.rel)
    mContext->injectMouseWheelChange(evt.state.Z.rel / 120.0f);

  return true;
}

bool  
GameEngine::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
  mContext->injectMouseButtonDown(convertButton(id));
  return true;
}

bool  
GameEngine::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
  mContext->injectMouseButtonUp(convertButton(id));
  return true;
}

bool  
GameEngine::keyPressed( const OIS::KeyEvent& evt )
{
  mContext->injectKeyDown((CEGUI::Key::Scan)evt.key);
  mContext->injectChar((CEGUI::Key::Scan)evt.text);

  switch (evt.key)
    {
    case OIS::KC_ESCAPE: 
      mShutdown = true;
      break;
    case OIS::KC_RETURN: /* Alt+Enter to switch fullscreen mode */
      if (mKeyboard->isModifierDown(OIS::Keyboard::Alt))
	{
	  mRestart = true;
	  mToFullscreen = !mWindow->isFullScreen();
	}
    default:
      break;
    }

  return true;
}

bool  
GameEngine::keyReleased( const OIS::KeyEvent& evt )
{
  mContext->injectKeyUp((CEGUI::Key::Scan)evt.key);
  return true;
}

CEGUI::MouseButton 
GameEngine::convertButton(OIS::MouseButtonID buttonID)
{
    switch (buttonID)
    {
    case OIS::MB_Left:
        return CEGUI::LeftButton;
 
    case OIS::MB_Right:
        return CEGUI::RightButton;
 
    case OIS::MB_Middle:
        return CEGUI::MiddleButton;
 
    default:
        return CEGUI::LeftButton;
    }
}

void GameEngine::shutdown()
{
  mShutdown = true;
}

bool GameEngine::running()
{
  return !mShutdown;
}

bool
GameEngine::overlayHandler(const CEGUI::EventArgs& args)
{
    if (static_cast<const CEGUI::RenderQueueEventArgs&>(args).queueID != CEGUI::RQ_OVERLAY)
        return false;

    mCurrentState->drawOverlay();
    
    // Update FPS stats every second
    if (mTimer.getMilliseconds() > 1000)
      {
	mCurrentState->hudUpdate();
	mTimer.reset();
      }
    return true;
}

void
GameEngine::windowResized(Ogre::RenderWindow* rw)
{
  unsigned int width, height, depth;
  int left, top;
  rw->getMetrics(width, height, depth, left, top);
 
  const OIS::MouseState &ms = mMouse->getMouseState();
  ms.width = width;
  ms.height = height;
}

/* A simple getter for the current CEGUI OgreRenderer
 *
 * Make this pointer available to game states, i.e. to create
 * CEGUI GeometryBufer objects.
 *
 */
CEGUI::OgreRenderer*
GameEngine::getOgreRenderer()const
{
  return mRenderer;
}

/* Get the Ogre renderer window created during initialization
 *
 */
Ogre::RenderWindow*
GameEngine::getRendererWindow()const
{
  return mWindow;
}

bool
GameEngine::restarting()
{
  return mRestart;
}

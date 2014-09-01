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

#include <Logger.hpp> // Before headers to avoid std::list/Ogre::list conflict

#include "GameEngine.hpp"
#include "LoadingBar.hpp"

#include <iostream>

#include <Ogre.h>
#include <OIS.h>

#include <CEGUI/RendererModules/Ogre/Renderer.h>

using namespace std;
using namespace Ogre;

static Rpg::Logger static_logger("engine", Rpg::LT_BOTH);

GameEngine::GameEngine(void):
  mWindow(NULL),
  mInputManager(NULL),
  mKeyboard(NULL),
  mMouse(NULL),
  mResourcesCfg("resources.cfg"),
  mShutdown(false)
{

  //  log("Starting Ogre::Root");
  mRoot = new Root();
  if (mRoot->showConfigDialog())
    {
      //    log("Creating rendering window");
      mWindow = mRoot->initialise(true, "RainbruRPG");
      
      // Create the SceneManager, in this case a generic one
      SceneManager* mSceneMgr = mRoot->
	createSceneManager(ST_GENERIC, "ExampleSMInstance");

      /*      SceneNode* headNode = mSceneMgr->getRootSceneNode()
	->createChildSceneNode("HeadNode");

      Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
      headNode->attachObject(ogreHead);
      */
   
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
			       std::string("false"))); 

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
      mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
 
      // Create a light
      Ogre::Light* l = mSceneMgr->createLight("MainLight");
      l->setPosition(20,80,50);

      mRoot->addFrameListener(this);
 
      // Initialize CEGUI
      CEGUI::OgreRenderer& mRenderer = CEGUI::OgreRenderer::bootstrapSystem();

      CEGUI::ImageManager::setImagesetDefaultResourceGroup("Imagesets");
      CEGUI::Font::setDefaultResourceGroup("Fonts");
      CEGUI::Scheme::setDefaultResourceGroup("Schemes");
      CEGUI::WidgetLookManager::setDefaultResourceGroup("LookNFeel");
      CEGUI::WindowManager::setDefaultResourceGroup("Layouts");

      WindowEventUtilities::addWindowEventListener(mWindow, this);
    }
}

bool GameEngine::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
  mMouse->capture();
  mKeyboard->capture();

  if (mShutdown)
    return false;


  if(mWindow->isClosed())
    return false;

  return true;
}

void
GameEngine::run()
{

  setupResources();

  LoadingBar* lb = new LoadingBar();
  lb->start(mWindow, 1, 1, 0.75);

  //  if (current_gamestate != NULL)
  // current_gamestate->run(this);

  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  CEGUI::SchemeManager::getSingleton().createFromFile("VanillaSkin.scheme");
  CEGUI::SchemeManager::getSingleton().createFromFile("VanillaCommonDialogs.scheme");
  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().
    setDefaultImage("Vanilla-Images/MouseArrow");


  // Align CEGUI mouse with OIS mouse
  const OIS::MouseState state = mMouse->getMouseState();
  CEGUI::Vector2f mousePos = CEGUI::System::getSingleton().
    getDefaultGUIContext().getMouseCursor().getPosition(); 
  CEGUI::System::getSingleton().getDefaultGUIContext()
    .injectMouseMove(state.X.abs-mousePos.d_x,state.Y.abs-mousePos.d_y);
  CEGUI::Window *guiRoot = CEGUI::WindowManager::getSingleton()
    .loadLayoutFromFile("menu.layout"); 
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow(guiRoot);


  lb->finish();

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
}

void 
GameEngine::windowClosed(Ogre::RenderWindow* rw)
{
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
  CEGUI::GUIContext& sys = CEGUI::System::getSingleton().getDefaultGUIContext();
  sys.injectMouseMove(evt.state.X.rel, evt.state.Y.rel);
  // Scroll wheel.
  if (evt.state.Z.rel)
    sys.injectMouseWheelChange(evt.state.Z.rel / 120.0f);

  return true;
}

bool  
GameEngine::mousePressed( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
  CEGUI::System::getSingleton().getDefaultGUIContext().
    injectMouseButtonDown(convertButton(id));
  return true;
}

bool  
GameEngine::mouseReleased( const OIS::MouseEvent& evt, OIS::MouseButtonID id )
{
  CEGUI::System::getSingleton().getDefaultGUIContext().
    injectMouseButtonUp(convertButton(id));
  return true;
}

bool  
GameEngine::keyPressed( const OIS::KeyEvent& evt )
{
  CEGUI::GUIContext& context = CEGUI::System::getSingleton().
    getDefaultGUIContext();
  context.injectKeyDown((CEGUI::Key::Scan)evt.key);
  context.injectChar((CEGUI::Key::Scan)evt.text);

  switch (evt.key)
    {
    case OIS::KC_ESCAPE: 
      mShutdown = true;
      break;
    default:
      break;
    }

  return true;
}

bool  
GameEngine::keyReleased( const OIS::KeyEvent& evt )
{
  CEGUI::System::getSingleton().getDefaultGUIContext().
    injectKeyUp((CEGUI::Key::Scan)evt.key);
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

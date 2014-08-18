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

#include "GameEngine.hpp"
#include "Logger.hpp"

#include <iostream>

#include <Ogre.h>
#include <OIS.h>

using namespace std;
using namespace Ogre;

static Rpg::Logger static_logger("engine", Rpg::LT_BOTH);

GameEngine::GameEngine(void):
  mResourcesCfg("resources.cfg")
{

  //  log("Starting Ogre::Root");
  Root* mRoot = new Root();
  setupResources("Bootstrap");
  if (mRoot->showConfigDialog())
    {
      //    log("Creating rendering window");
      mWindow = mRoot->initialise(true, "RainbruRPG");
      
      // Create the SceneManager, in this case a generic one
      SceneManager* mSceneMgr = mRoot->
	createSceneManager(ST_GENERIC, "ExampleSMInstance");

      setupResources("General");
      SceneNode* headNode = mSceneMgr->getRootSceneNode()
	->createChildSceneNode("HeadNode");

      Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");
      headNode->attachObject(ogreHead);
      
   
      // Create the camera
      Camera* mCamera = mSceneMgr->createCamera("PlayerCam");
      
      // Create one viewport, entire window
      Ogre::Viewport* vp = mWindow->addViewport(mCamera);
      vp->setBackgroundColour(Ogre::ColourValue(0,0,0));


      // Initialize OIS
      OIS::InputManager* m_InputManager;
      OIS::ParamList pl;   
      size_t windowHnd = 0;
      std::ostringstream windowHndStr; 
#if defined OIS_LINUX_PLATFORM
      mWindow->getCustomAttribute( "GLXWINDOW", &windowHnd ); 
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

      m_InputManager = OIS::InputManager::createInputSystem( pl );
      if (!m_InputManager)
	cerr << "OIS inputmanager object is null" << endl;

  // Get mouse and keyboard
  try{
    OIS::Keyboard* m_Keyboard = static_cast<OIS::Keyboard*>(m_InputManager->createInputObject(OIS::OISKeyboard, true));
    LOGI("OIS keyboard correctly initialized");

  }
  catch (OIS::Exception e){
    LOGE("Error while initialize IOS keyboard "<< e.eFile << ":" << e.eText);
  }

  try {
    OIS::Mouse* m_Mouse = static_cast<OIS::Mouse*>(m_InputManager->createInputObject(OIS::OISMouse, true));
    // Initialize OIS mouse metrics
    unsigned int width, height, depth;
    int top, left;
    mWindow->getMetrics(width, height, depth, left, top);
    const OIS::MouseState &ms = m_Mouse->getMouseState();
    ms.width = width;
    ms.height = height;
  }
  catch (OIS::Exception e){
    cerr << "An error occurs while initialize IOS mouse 1(" 
	 << e.eFile << ":" << e.eText << ")" << endl;
  }

  // Create the GUI manager
  //  OgreBites::SdkTrayManager* mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", mRenderWindow, m_Mouse, 0); // The 0 is of type SdkTrayListener* 


      // Alter the camera aspect ratio to match the viewport
      mCamera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));


      // Set ambient light
      mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
 
      // Create a light
      Ogre::Light* l = mSceneMgr->createLight("MainLight");
      l->setPosition(20,80,50);

      mRoot->addFrameListener(this);
      mRoot->startRendering();

    }

}

bool GameEngine::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
    if(mWindow->isClosed())
        return false;

    return true;
}

void GameEngine::setupResources(const std::string& section)
{
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
	if (secName == section)
	  {
	    LOGI("resources section name match" << secName << "... loading.");
	
	    Ogre::ConfigFile::SettingsMultiMap::iterator i;
	    for (i = settings->begin(); i != settings->end(); ++i)
	      {
		typeName = i->first;
		archName = i->second;
		Ogre::ResourceGroupManager::getSingleton()
		  .addResourceLocation(archName, typeName, secName);
	      }
	  }
    }
}

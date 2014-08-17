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

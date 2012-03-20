/*
 *  Copyright 2006-2012 Jerome PASQUIER
 * 
 *  This file is part of RainbruRPG.
 *
 *  RainbruRPG is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  RainbruRPG is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with RainbruRPG; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

/** \file environmentsetup.h
  * Declares a class that creates the Ogre environment for the game/editor
  *
  * Modifications :
  * - 28 aug 2009 : Translated messages with gettext
  * - 14 aug 2008 : Single file documentation
  *
  */
#ifndef ENVIRONMENT_SETUP_H
#define ENVIRONMENT_SETUP_H

#include <ogreimport.h>

#include <XmlObjectList.hpp>
#include <ObjectMesh.hpp>
#include <ObjectPos.hpp>

#include <string>

#include <RainbruDef.hpp> // For the GNU gettext stuff

using namespace Ogre;

namespace RainbruRPG{
  namespace Core{

    /** Creates the Ogre environment for the game/editor
      *
      * It creates a suitable SceneManager, the Camera and so on.
      * The Ogre renderWindow \b must be created before using this class 
      * because the render window creation is different for GameEngine and 
      * OgreView.
      *
      */
    class EnvironmentSetup{
    public:
      EnvironmentSetup( Ogre::RenderWindow*,
			const char* sceneMgrName="DefaultSceneManager",
			const char* cameraName="CameraName");

      ~EnvironmentSetup();

      void createSceneManager();
      void createCamera();
      void createViewport();
      void createLight();

      Ogre::RenderWindow* getRenderWindow();
      Ogre::SceneManager* getSceneManager();
      Ogre::Camera* getCamera();
      Ogre::Viewport* getViewPort();

    private:
      void addObjects();
      void addMesh(const std::string&,  const char*, ObjectPos op);

      void treatObjectMesh(ObjectMesh* om);

      /** The Ogre scene manager */
      Ogre::RenderWindow* mRenderWindow;
      /** The Ogre scene manager */
      Ogre::SceneManager* mSceneMgr;
      /** The Ogre camera */
      Ogre::Camera* mCamera;
      /** The Ogre viewport */
      Ogre::Viewport* mVp;
      /** The main scene light */
      Ogre::Light* mainLight;

      /** The name of the scene manager */
      const char* sceneManagerName;
      /** The name of the camera */
      const char* cameraName;

    };

  }
}

#endif // ENVIRONMENT_SETUP_H

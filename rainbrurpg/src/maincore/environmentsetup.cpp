/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file environmentsetup.cpp
  * Implements a class that creates the Ogre environment for the game/editor
  *
  */

#include "environmentsetup.h"

#include <logger.h>

/** The default constructor
  *
  * \param renderWindow The Ogre render window
  * \param sceneMgrName The Ogre scene manager name
  * \param cameraName   The Ogre camera name
  *
  *
  */
RainbruRPG::Core::EnvironmentSetup::
EnvironmentSetup( Ogre::RenderWindow* renderWindow, 
		  const char* sceneMgrName, 
		  const char* cameraName){

  LOGI(_("Starting environment setup"));

  this->mRenderWindow=renderWindow;
  this->sceneManagerName=sceneMgrName;
  this->cameraName=cameraName;

  LOGI(_("Creating SceneManeger"));
  createSceneManager();
  LOGI(_("Creating camera"));
  createCamera();
  LOGI(_("Creating viewport"));
  createViewport();
  LOGI(_("Creating light"));
  createLight();
  LOGI(_("Initialising Ogre resources"));
  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

  LOGI(_("Starting adding objects"));
  addObjects();
  LOGI(_("Environment correctly setup"));
}

/** The default destructor
  *
  */
RainbruRPG::Core::EnvironmentSetup::~EnvironmentSetup(){

}

/** Creates a Ogre SceneManager with a custom name
  *
  * The type of the SceneManager is PagingLandScapeSceneManager.
  *
  */
void RainbruRPG::Core::EnvironmentSetup::createSceneManager(){
  mSceneMgr=Ogre::Root::getSingleton().
    createSceneManager("PagingLandScapeSceneManager", sceneManagerName); 

  mSceneMgr->setWorldGeometry( "paginglandscape2.cfg" );

}

/** Creates and position the Camera
  *
  */
void RainbruRPG::Core::EnvironmentSetup::createCamera(){
  mCamera=mSceneMgr->createCamera(cameraName);
  mCamera->setPosition(Vector3(800,200,1200));
  mCamera->lookAt(Vector3(0,0,0));

}

/** Creates the Viewport
  *
  */
void RainbruRPG::Core::EnvironmentSetup::createViewport(){
  mVp = mRenderWindow->addViewport(mCamera);
  mVp->setBackgroundColour(ColourValue(0.58, 0.65, 0.76, 1));

  TextureManager::getSingleton().setDefaultNumMipmaps(5);
  MaterialManager::getSingleton()
    .setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
  
  MaterialManager::getSingleton().setDefaultAnisotropy(2);
  mCamera->setAspectRatio(Real(mVp->getActualWidth()) 
			  / Real(mVp->getActualHeight()));

}

/** Get the Ogre render window
  *
  * \return The Ogre RenderWindow
  *
  */
Ogre::RenderWindow* RainbruRPG::Core::EnvironmentSetup::getRenderWindow(){
  return mRenderWindow;
}

/** Get the created Ogre scene manager
  *
  * The name of the scene manager is sceneManagerName.
  *
  * \return The Ogre SceneManager
  *
  */
Ogre::SceneManager* RainbruRPG::Core::EnvironmentSetup::getSceneManager(){
  return mSceneMgr;
}

/** Get the created Ogre camera
  *
  * The name of the camera is cameraName.
  *
  * \return The Ogre Camera
  *
  */
Ogre::Camera* RainbruRPG::Core::EnvironmentSetup::getCamera(){
  return mCamera;
}

/** Get the created Ogre view port
  *
  * \return The Ogre view port
  *
  */
Ogre::Viewport* RainbruRPG::Core::EnvironmentSetup::getViewPort(){
  return mVp;
}

/** Creates the ambient light
  *
  */
void RainbruRPG::Core::EnvironmentSetup::createLight(){
  mSceneMgr->setAmbientLight(ColourValue(1, 1, 1));
  mainLight = mSceneMgr->createLight("Main Light");
  mainLight->setPosition(0, 100, -500);
}

/** Adds a mesh to the current sceneManager
  *
  * \param name The name of the entity that will be created
  * \param filename The name of the .mesh file
  * \param op The position of the mesh
  *
  */
void RainbruRPG::Core::EnvironmentSetup::addMesh(const std::string& name, 
					   const char* filename,
					   ObjectPos op){

  // the name is not used
  std::string posName=op.getName();

  // Position
  double px=op.getPosX();
  double py=op.getPosY();
  double pz=op.getPosZ();

  // Orientation
  double rw=op.getRotW();
  double rx=op.getRotX();
  double ry=op.getRotY();
  double rz=op.getRotZ();

  // Mesh
  Entity *ent = mSceneMgr->createEntity( posName.c_str(), filename );
  ent->setCastShadows( true );
  Ogre::SceneNode* sn=mSceneMgr->getRootSceneNode()
    ->createChildSceneNode( Vector3( px, py, pz ) );

  sn->setOrientation(rw, rx, ry, rz);
  sn->attachObject( ent );

}

/** Adds the objects in xmlObjectList
  *
  */
void RainbruRPG::Core::EnvironmentSetup::addObjects(){
  xmlObjectList xol;
  ObjectMeshList* meshList=xol.getMeshList();

  ObjectMeshList::const_iterator iter;
  for (iter=meshList->begin(); iter != meshList->end(); iter++){
    treatObjectMesh((*iter));
    
  }
}

/** Treats an ObjectMesh
  *
  * The position of the given ObjectMesh will be add to the current
  * scene manager using the addMesh function
  *
  * \param om The ObjectMesh to add
  *
  */
void RainbruRPG::Core::EnvironmentSetup::treatObjectMesh(ObjectMesh* om){
  std::string name=om->getName();
  const char* meshfile=om->getMeshFile();


  ObjectPosList poslist= om->getPosList();
  ObjectPosList::const_iterator iter;
  for (iter=poslist.begin(); iter != poslist.end(); iter++){
    addMesh(name, meshfile,(*iter));
  }

}


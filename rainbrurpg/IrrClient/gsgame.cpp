/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

#include "gsgame.h"

#include <logger.h>
#include "gameengine.h"

/** The constructor of the game state
  *
  */
void RainbruRPG::Core::gsGame::init(){
  isInit=true;
  triangleSelector=true;

  this->irrDevice  = GameEngine::getSingleton().getIrrlichtDevice();
  this->driverType = GameEngine::getSingleton().getDriverType();
  this->irrDriver  = GameEngine::getSingleton().getIrrlichtDriver();
  this->irrSmgr    = GameEngine::getSingleton().getIrrlichtSmgr();
  this->irrGui     = GameEngine::getSingleton().getIrrlichtGui();

  debug=true;
  debugTriangleSelection=true;
  debugModelSelection=true;
  debugBillboard=false;

  selectedSceneNode = 0;
  lastSelectedSceneNode = 0;

  loadExampleMap();

  initTriangleSelector();
  initCamera();
  initExampleFaeries(); 
  if (debug&&debugBillboard)  initBillboard();
  createGui();
}

/** The destructor of the game state
  *
  */
void RainbruRPG::Core::gsGame::cleanup(){
  LOGI("    Cleaning up gsGame game state...");
  //  delete irrCamera;
   delete irrSelector;
   this->irrDevice=NULL;
  // delete q3node;
  // delete q3levelmesh;

  this->irrDevice  = NULL;
  //  this->driverType = NULL;
  this->irrDriver  = NULL;
  this->irrSmgr    = NULL;
  this->irrGui     = NULL;
  this->bill       = NULL;
  selectedSceneNode = NULL;
  lastSelectedSceneNode= NULL;
}

/** Loads an example Quake 3 map
  *
  */
void RainbruRPG::Core::gsGame::loadExampleMap(){
  LOGI("Loading example Quake 3 map...");
  irrDevice->getFileSystem()->addZipFileArchive("../data/3d/map-20kdm2.pk3");
  q3levelmesh = irrSmgr->getMesh("20kdm2.bsp");

  q3node = 0;
	
  if (q3levelmesh)
    q3node = irrSmgr->addOctTreeSceneNode(q3levelmesh->getMesh(0));
  else
    LOGE("Error while loading example Quake 3 map");  
}


/** Initialize a Irrlicht's triangle selector
  *
  **/
void RainbruRPG::Core::gsGame::initTriangleSelector(){
  LOGI("Setting up Triangle selector...");
  // Create a triangleSelector and attached it to the q3node

  irrSelector = 0;
  
  if (q3node)	{		
    q3node->setPosition(core::vector3df(-1370,-130,-1400));
    
    irrSelector = irrSmgr->createOctTreeTriangleSelector(q3levelmesh->getMesh(0), q3node, 128);
    q3node->setTriangleSelector(irrSelector);
    irrSelector->drop();
  }
}


/** Initialize a Irrlicht FPS style camera 
  *
  *
  * \todo Verifier la présence de \c selector
  */
void RainbruRPG::Core::gsGame::initCamera(){

  LOGI("Setting up camera...");
  // Création de la camera et du responseAnimator (ne passe pas a travers les murs )
  irrCamera =  irrSmgr->addCameraSceneNodeFPS(0, 100.0f, 300.0f, -1,0,0, true);
  irrCamera->setPosition(core::vector3df(-100,50,-150));
  
  scene::ISceneNodeAnimator* anim = irrSmgr->createCollisionResponseAnimator(
	  irrSelector, irrCamera, core::vector3df(30,50,30),
	  core::vector3df(0,-3,0), core::vector3df(0,50,0));
  irrCamera->addAnimator(anim);
  anim->drop();
}



/** The drawing method
  * 
  * This method is called by the GameEngine for each frame. It just
  * calls the Irrlicht draw function. It also calls the drawDebug()
  * method if \c debug is set to \c true.
  *
  */
void RainbruRPG::Core::gsGame::run(){
  irrDriver->beginScene(true, true, 0);
  
  irrSmgr->drawAll();
  if (debug) drawDebug();
  
  // draw gui
  irrGui->drawAll();
  
  // On a fini d'écrire	    
  irrDriver->endScene();
}

/** Initialize 3 animated faeries for sample purpose
  *
  *
  */
void RainbruRPG::Core::gsGame::initExampleFaeries(){
  // add 3 animated faeries.
  faerieMaterial.Texture1 = irrDriver->getTexture("../data/3d/faerie2.bmp");
  faerieMaterial.Lighting = true;
  scene::IAnimatedMeshSceneNode* node = 0;
  scene::IAnimatedMesh* faerie = irrSmgr->getMesh("../data/3d/faerie.md2");
  
  if (faerie)    {
      node = irrSmgr->addAnimatedMeshSceneNode(faerie);
      node->setPosition(core::vector3df(-70,0,-90));
      node->setMD2Animation(scene::EMAT_RUN);
      node->getMaterial(0) = faerieMaterial;
      
      node = irrSmgr->addAnimatedMeshSceneNode(faerie);
      node->setPosition(core::vector3df(-70,0,-30));
      node->setMD2Animation(scene::EMAT_SALUTE);
      node->getMaterial(0) = faerieMaterial;
      
      node = irrSmgr->addAnimatedMeshSceneNode(faerie);
      node->setPosition(core::vector3df(-70,0,-60));
      node->setMD2Animation(scene::EMAT_JUMP);
      node->getMaterial(0) = faerieMaterial;
    }
  
  faerieMaterial.Texture1 = 0;
  faerieMaterial.Lighting = false;
  
  // Add a light
  irrSmgr->addLightSceneNode(0, core::vector3df(-60,100,400),
			  video::SColorf(1.0f,1.0f,1.0f,1.0f),
			  600.0f);
}

/** Creates the gui of the game GameState
  *
  * Do nothing.
  */
void RainbruRPG::Core::gsGame::createGui(){

}

/** Pause the game GameState
  *
  * It will stop the Irrlicht Device timer and disable the player's
  * camera input. You may call resume() to continue playing. 
  *
  *
  */
void RainbruRPG::Core::gsGame::pause(){
  LOGI("state Game in pause...");

  // stop the Irrlicht Engine
  irrDevice->getTimer()->stop();

  // Disabled camera input
  irrCamera->setInputReceiverEnabled(false);

}

/** Resume the game after a pause() call
  *
  * It reinitialize the erGame event receiver, send it to the Irrlicht device
  * and set the mouse cursor invisible.
  *
  */
void RainbruRPG::Core::gsGame::resume(){
  LOGI("state Game in Resume...");

  erGame receiver;
  // GameEngine::getSingleton().getIrrlichtDevice()->setEventReceiver(&receiver);

  if (irrDevice==0)
    LOGE("Try to setting an EventReceiver on a NULL Irrlicht Device");

  // stop the Irrlicht Engine
  irrDevice->getTimer()->start();

  // Disabled camera input
  irrCamera->setInputReceiverEnabled(true);

  irrDevice->getCursorControl()->setVisible(false);
}

/** Add a billboard scene node to the Irrlicht scene manager for
  * debugging purpose
  *
  * It creates a billboard with the image file \c
  * data/3d/particle.bmp.
  */
void RainbruRPG::Core::gsGame::initBillboard(){
  // add billboard
  bill = irrSmgr->addBillboardSceneNode();
  bill->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR );
  bill->setMaterialTexture(0, irrDriver->getTexture("../data/3d/particle.bmp"));
  bill->setMaterialFlag(video::EMF_LIGHTING, false);
  bill->setMaterialFlag(video::EMF_ZBUFFER, false);
  bill->setSize(core::dimension2d<f32>(20.0f, 20.0f));
}

/** The begug drawing method
  *
  * It is called by the run() method only if \c debug is set to \c
  * true. It will refresh all the debugging tools (billboard, triangle
  * and model selection).
  *
  */
void RainbruRPG::Core::gsGame::drawDebug(){
  // On cree une ligne entre la caméra et le LookAt-target
  // On demande au collision manager quel triangle est traversé
  // On affiche le billboard
  core::line3d<f32> line;
  line.start = irrCamera->getPosition();
  line.end = line.start + (irrCamera->getTarget() - 
			   line.start).normalize() * 1000.0f;
  
  core::vector3df intersection;
  core::triangle3df tri;
  
  if (irrSmgr->getSceneCollisionManager()->getCollisionPoint( line, 
      irrSelector, intersection, tri)){

    if (debugBillboard)bill->setPosition(intersection);
    
    irrDriver->setTransform(video::ETS_WORLD, core::matrix4());
    irrDriver->setMaterial(faerieMaterial);

    // To debug the triangle selector
    if (debugTriangleSelection)
      irrDriver->draw3DTriangle(tri, video::SColor(0,255,0,0));
  }

  if (debugModelSelection){
    selectedSceneNode = irrSmgr->getSceneCollisionManager()->
                 getSceneNodeFromCameraBB(irrCamera);
  
    if (lastSelectedSceneNode)
      lastSelectedSceneNode->setMaterialFlag(video::EMF_LIGHTING, true);
    
    if (selectedSceneNode == q3node || selectedSceneNode == bill)
      selectedSceneNode = 0;
    
    if (selectedSceneNode)
    selectedSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
    
    lastSelectedSceneNode = selectedSceneNode;
  }
}

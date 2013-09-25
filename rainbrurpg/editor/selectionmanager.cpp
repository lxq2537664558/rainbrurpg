/*
 *  Copyright 2006-2007 Jerome PASQUIER
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

#include "selectionmanager.h"

#include <logger.h>

/** The default constructor
  *
  */
RainbruRPG::Editor::SelectionManager::SelectionManager(){
  sceneManager=NULL;
  camera=NULL;
  handleNode=NULL;
  handleEntity=NULL;

  cameraToHandle=-80.0f;
}

/** The default destructor
  *
  */
RainbruRPG::Editor::SelectionManager::~SelectionManager(){
  sceneManager=NULL;
  camera=NULL;
  handleNode=NULL;
  handleEntity=NULL;
}

/** Initialize the selection manager with the given SceneManager and Camera
  *
  * \param sm The scene manager
  * \param cam The Ogre camera used to compute handles position
  *
  */
void RainbruRPG::Editor::SelectionManager::
init(Ogre::SceneManager* sm, Ogre::Camera* cam)
{
  sceneManager=sm;
  camera=cam;
}

/** Select an object, starting a new selection
  *
  * \param s The name of the object to be selected
  *
  */
void RainbruRPG::Editor::SelectionManager::selectNewObject(Ogre::String s){
  if (checkSceneManager()){
    highlightObject(s);
  }
}

/** Select an object, adding it to the current selection
  *
  * \param s The name of the object to be selected
  *
  */
void RainbruRPG::Editor::SelectionManager::selectAddObject(Ogre::String s){
  if (checkSceneManager()){

  }
}

/** A generic function to test the SceneManager
  *
  * \return \c true if sceneManager is valid, otherwise returns \c false
  *
  */
bool RainbruRPG::Editor::SelectionManager::checkSceneManager(){
  if (sceneManager==NULL || camera==NULL){
    LOGW("The scene manager or camera pointer is/are not valid");
    return false;
  }
  else{
    return true;
  }


}

/** Creates the highlight entity for a named object
  *
  * \param name The object name
  *
  */
void RainbruRPG::Editor::SelectionManager::highlightObject(Ogre::String name){

  if (name.compare("")==0){
    LOGW("SelectionManager::highlightObject: The object name is empty");
  }
  else{
    Ogre::Entity* entity=  sceneManager->getEntity(name);

    if (!entity){
      LOGW("Cannot get Entity by name");
    }
    else{
      
      // Delete the last selection highlight
      if ( isNodeHighLighted ){
	LOGI("Deleting last selection highlight");
	
	// Detach and destroy entity
	highLightNode->detachObject(highLightEntity);
	sceneManager->destroyEntity(highLightEntity);
	highLightEntity=NULL;
	
	// Destroy SceneNode
	sceneManager->destroySceneNode(highLightNode->getName());
	highLightNode=NULL;
	isNodeHighLighted=false;
      }
      
      // Ogre::AxisAlignedBox aab=ent->getBoundingBox();
      LOGI("Creating selection highlight");
      entity->setRenderQueueGroup(90);
      highLightEntity = entity->clone(entity->getName() + "Outline");
      highLightEntity->setRenderQueueGroup(91);
      highLightEntity->setMaterialName("Outline");
      
      highLightNode = entity->getParentSceneNode()
	->createChildSceneNode(entity->getParentNode()->getName() + "Outline");
      
      highLightNode->setScale(Ogre::Vector3(1.05,1.05,1.05));
      highLightNode->attachObject(highLightEntity);
      isNodeHighLighted=true;

      createMoveHandle();
    }
  }
}

/** Creates the move handle
  *
  * This method creates the entities that will be use for handle the
  * moving ability of an object with the mouse. It is a mesh called
  * \c moveHandle.mesh with a material named MoveHandle.
  *
  */
void RainbruRPG::Editor::SelectionManager::createMoveHandle(){

      if ( handleEntity && handleNode ){
	LOGI("Deleting last selection highlight");
	
	// Detach and destroy entity
	handleNode->detachObject(handleEntity);
	sceneManager->destroyEntity(handleEntity);
	handleEntity=NULL;
	
	// Destroy SceneNode
	sceneManager->destroySceneNode(handleNode->getName());
	handleNode=NULL;
      }



  // Creates a ray from the camera to the object
  // fixme getDirection must come from the object
  Ogre::Ray camObj= Ogre::Ray();
  camObj.setOrigin(camera->getPosition());

  Ogre::Quaternion camOrientation=camera->getOrientation();

  camObj.setDirection(camOrientation.zAxis());

  
  /*
  // Compute the position of the handle
  //  Ogre::Vector3 haPos= Ogre::Vector3(0.0f, 0.0f, 0.0f );
  Ogre::Vector3 haPos= camObj.getPoint(cameraToHandle);

  // Creates entity
  handleEntity = sceneManager
    ->createEntity( "moveHandle", "moveHandle.mesh" );

  handleEntity->setCastShadows( false );
  handleNode=sceneManager->getRootSceneNode()
    ->createChildSceneNode( haPos );

  handleEntity->setMaterialName("MoveHandle");

  //  sn->setOrientation(rw, rx, ry, rz);
  handleNode->attachObject( handleEntity );
  */

}

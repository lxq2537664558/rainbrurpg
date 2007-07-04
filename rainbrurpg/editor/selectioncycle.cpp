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

#include "selectioncycle.h"

#include <logger.h>
#include <OgreMovableObject.h>


/** The default constructor
  *
  */
RainbruRPG::Editor::SelectionCycle::SelectionCycle(){
  lastEntityName="";
  lastQuery=NULL;
}

/** The default destructor
  *
  */
RainbruRPG::Editor::SelectionCycle::~SelectionCycle(){
  lastEntityName="";
  lastQuery=NULL;
}

/** Compare two Ogre RaySceneQueryResult
  *
  * \return \c true if equal, \c false otherwise
  *
  */
bool RainbruRPG::Editor::SelectionCycle::
compare(Ogre::RaySceneQueryResult* r1, 
	Ogre::RaySceneQueryResult* r2)

{

  Ogre::RaySceneQueryResult::const_iterator iter1, iter2;
  Ogre::RaySceneQueryResultEntry* entry;
  Ogre::MovableObject* mo1;
  Ogre::MovableObject* mo2;


  if (r1->size()!=r2->size()){
    return false;
  }
  else{
    iter2=r2->begin();
    for (iter1=r1->begin(); iter1!=r1->end(); iter1++){
      mo1=(*iter1).movable;
      mo2=(*iter2).movable;
      if (mo1!=mo2){
	return false;
      }
      iter2++;
    }
  }
  return true;

}

/** Returns the name of the next Entity to select
  *
  * \param rsqr The result of the RaySceneQuery
  *
  * \return The name of the Entity
  *
  */
Ogre::String RainbruRPG::Editor::SelectionCycle::
getNextEntity(Ogre::RaySceneQueryResult& rsqr){

  LOGI("SelectionCycle::getNextEntity called");

  Ogre::String ret="";

  if (this->lastQuery){
    if (this->compare(lastQuery, &rsqr)){
      // Get the entity following the entity named lastEntityName
      LOGI("The same SceneQuery was already found");
    }
    else{
      // Get the very first entity
      //    lastQuery=NULL;
      LOGI("The SceneQuery changed");
      return getFirstEntityName(&rsqr);
    }
  }
  else{
    LOGI("lastquery NULL, assuming first selection");
    return getFirstEntityName(&rsqr);
  }

  lastQuery=new Ogre::RaySceneQueryResult(rsqr);
  if (!lastQuery){
    LOGW("Creating copy RaySceneQueryResult FAILED");
  }

  return ret;
}

/** Get the first entity name in a RaySceneQueryResult
  *
  * \param query The suery result we search in
  *
  * \return The name of the first Entity found or "" if not found
  *
  */
Ogre::String RainbruRPG::Editor::SelectionCycle::
getFirstEntityName(Ogre::RaySceneQueryResult* query){

  LOGI("SelectionCycle::getFirstEntityName called");
  Ogre::String ret="";

  if (!query){
    LOGW("Invalid query received");
  }
  else{
    bool found=false;
    Ogre::RaySceneQueryResult::iterator itr = query->begin();

    for (itr = query->begin(); itr != query->end(); itr++){
      if (itr->movable->getMovableType().compare("Entity")==0){
	if (!found){
	  ret=itr->movable->getName();
	  found=true;
	  return ret;
	}
      }
    }
    
    if (!found){
      LOGI("No selectable Entity was found");
    }
  }
  return ret;
}

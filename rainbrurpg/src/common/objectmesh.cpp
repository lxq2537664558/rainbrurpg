/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file objectmesh.cpp
  * Implements a static mesh that can have multiple instances
  *
  */
#include "objectmesh.h"

#include "logger.h"

/** The default constructor
  *
  */
RainbruRPG::Core::ObjectMesh::ObjectMesh(){
  //  posList=new ObjectPosList();
}

/** The copy constructor
  *
  * \param obj The object to copy
  *
  */
RainbruRPG::Core::ObjectMesh::ObjectMesh(const ObjectMesh& obj){
  //  posList=new ObjectPosList();

}


/** The constructor
  *
  * \param name The name of this obejct
  * \param mesh The mesh filename
  *
  */
RainbruRPG::Core::ObjectMesh::ObjectMesh(std::string name, const char* mesh){
  this->name=name;
  this->meshfile=mesh;
  //  posList=new ObjectPosList();
}

/** The default destructor
  *
  */
RainbruRPG::Core::ObjectMesh::~ObjectMesh(){

  /*  ObjectPosList::const_iterator iter;
  for (iter=posList->begin(); iter != posList->end(); iter++){
    (*iter)->~ObjectPos();
  }
  */

  // deleting pos object
  posList.clear();

  // Deleting poslist
  //  delete posList;
  //  posList=NULL;
}

/** Changes the name of this object
  *
  * \param n The new name
  *
  */
void RainbruRPG::Core::ObjectMesh::setName(std::string n){
  name=n;
}

/** Gets the name of this object
  *
  * \return The name
  *
  */
std::string RainbruRPG::Core::ObjectMesh::getName(){
  return name;
}

/** Sets the filename of the mesh
  *
  * Do not set the directory. The mesh will be loaded by Ogre and it
  * will search in the ressources already loaded.
  *
  * \param n The new mesh filename
  *
  */
void RainbruRPG::Core::ObjectMesh::setMeshFile(const char*n){
  meshfile=n;
}

/** Gets the filename of the mesh
  *
  * \return The name of the mesh file
  *
  */
const char* RainbruRPG::Core::ObjectMesh::getMeshFile(){
  return meshfile;
}

/** Gets the list of positioning instance for this object
  *
  * \return The ObjectPos list
  *
  */
RainbruRPG::Core::ObjectPosList RainbruRPG::Core::ObjectMesh::getPosList(){
  return posList;
}

/** Adds a ObjectPos
  *
  * This function use the ObjectPos copy constructor to add a
  * new object. The instance you add can be a local instance, deleted
  * after this call.
  *
  * \param pos The ObjectPos to add
  * 
  */
void RainbruRPG::Core::ObjectMesh::addPos(const ObjectPos& pos){
  //  objPos=new ObjectPos(pos);
  posList.push_back(pos);
  //  objPos=NULL;
}

/** Get an ObjectPos by its name
  *
  * \param name The name of the ObjectPos you want
  *
  * \return The ObjectPos pointer if found or NULL if not found
  *
  */
const RainbruRPG::Core::ObjectPos&
RainbruRPG::Core::ObjectMesh::getPosByName(const std::string& name){

  std::string omName;
  bool found=false;

  ObjectPos pos;

  ObjectPosList::const_iterator iter;
  for (iter=posList.begin(); iter != posList.end(); iter++){
    pos=(*iter);
    omName=pos.getName();

    // The given name was found
    if (omName.compare(name)==0){
      found=true;
      return (*iter);
    }
  }

  // No object found
  if (!found){
    GTS_LIT(str);
    // TRANSLATORS: The parameter is the name of an ObjectPos.
    sprintf(str, _("ObjectPos '%s' not found."), name.c_str());
    LOGW(str);
  }

}

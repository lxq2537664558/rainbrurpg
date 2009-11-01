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

/** \file xmlobjectlist.cpp
  * Implements a class that read and create the objects in \c config/objects.xml
  *
  */

#include "xmlobjectlist.h"
#include "globaluri.h"

/** The default constructor
  *
  */
RainbruRPG::Core::xmlObjectList::xmlObjectList(){
  LOGI(_("Loading object list"));

  RainbruRPG::Network::GlobalURI gu;
  std::string confStr= gu.getUserDirFile("objects.xml");
  this->filename=confStr.c_str();
  doc=NULL;

  meshList=new ObjectMeshList();

  // Loading the document
  doc=new TiXmlDocument( this->filename );
  doc->LoadFile();
  root =doc->RootElement();

  treatAllObjects();
  LOGI(_("Object list correctly loaded"));
}

/** The default destructor
  *
  */
RainbruRPG::Core::xmlObjectList::~xmlObjectList(){
  // Deleting TinyXml object
  delete doc;
  doc=NULL;

  ObjectMeshList::const_iterator iter;
  for (iter=meshList->begin(); iter != meshList->end(); iter++){
    (*iter)->~ObjectMesh();
  }

  meshList->clear();
  delete meshList;
  meshList=NULL;
}

/** Gets all Object xml node and treat them
  *
  */
void RainbruRPG::Core::xmlObjectList::treatAllObjects(){
  if (root){
    TiXmlNode* childNode = root->FirstChild( "Object" );
    if (childNode){
      TiXmlElement* child= childNode->ToElement();

      for( child; child; child=child->NextSiblingElement() ){
	treatOneObject(child);
      }
    }
    else{
      LOGW(_("Empty object list found"));
    }
  }
  else{
    LOGW(_("Can not get a valid root element for ObjectList"));
  }
}

/** Treat one object xml node
  *
  * \param elem The xml object node
  *
  */
void RainbruRPG::Core::xmlObjectList::treatOneObject(TiXmlElement* elem){
  const char* type=elem->Attribute("type");
  const char* name=elem->Attribute("name");
  const char* meshfile=elem->Attribute("meshfile");

  ObjectMesh* mesh=new ObjectMesh(name, meshfile);
  meshList->push_back(mesh);

  TiXmlNode* childNode = elem->FirstChild( "Pos" );
  if (childNode){
    TiXmlElement* child= childNode->ToElement();

    for( child; child; child=child->NextSiblingElement() ){
      treatOneMesh(child, mesh);
    }
  }
  else{
    GTS_LIT(str);
    // TRANSLATORS: The parameter is an object name.
    sprintf(str,_("Empty position list found for mesh %s"), name);
    LOGW(str);
  }
  mesh=NULL;
}

/** Treat one single mesh position
  *
  * The Mesh xml element will be added to the given ObjectMesh in a 
  * ObjectPos instance.
  *
  * \param elem The Pos xml node
  * \param mesh The parent ObjectMesh
  *
  */
void RainbruRPG::Core::xmlObjectList::treatOneMesh( TiXmlElement* elem, 
						    ObjectMesh* mesh){

  double dx, dy, dz;
  double rw, rx, ry, rz;

  elem->QueryDoubleAttribute("x", &dx);
  elem->QueryDoubleAttribute("y", &dy);
  elem->QueryDoubleAttribute("z", &dz);

  elem->QueryDoubleAttribute("rw", &rw);
  elem->QueryDoubleAttribute("rx", &rx);
  elem->QueryDoubleAttribute("ry", &ry);
  elem->QueryDoubleAttribute("rz", &rz);

  std::string name=elem->GetText();

  ObjectPos pos;
  pos.setName(name);
  pos.setPosX(dx);
  pos.setPosY(dy);
  pos.setPosZ(dz);

  pos.setRotW(rw);
  pos.setRotX(rx);
  pos.setRotY(ry);
  pos.setRotZ(rz);
  mesh->addPos(pos);
}

/** Return a pointer to the meshList
  *
  * The list pointed will be destructed with this class.
  *
  * \return The meshList
  *
  */
ObjectMeshList* RainbruRPG::Core::xmlObjectList::getMeshList(){
  return meshList;
}

/** Return a pointer to an ObjectMesh
  *
  * \param name The name of the Obect you want
  *
  * \return The ObjectMash if it was found or \c NULL if an object with this
  *         name does not exist
  *
  */
ObjectMesh* RainbruRPG::Core::xmlObjectList::
getObjectMeshByName(const std::string& name){

  std::string omName;
  bool found=false;

  ObjectMeshList::const_iterator iter;
  for (iter=meshList->begin(); iter != meshList->end(); iter++){
    omName=(*iter)->getName();

    // The given name was found
    if (omName.compare(name)==0){
      found=true;
      return (*iter);
    }
  }

  // No object found
  if (!found)
    return NULL;

}

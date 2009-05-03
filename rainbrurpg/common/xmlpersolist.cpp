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

/** \file xmlpersolist.cpp
  * Implements a class that read the character list
  *
  */

#include "xmlpersolist.h"

/** The default constructor
  *
  * It calls the refresh() function.
  */
RainbruRPG::Network::xmlPersoList::xmlPersoList(){
  refresh();
}

/** Refresh the xml document
  *
  * It calls loadDocument() to reload the xml file.
  *
  * \return \c false if the operation failed, otherwise \c true.
  */
bool RainbruRPG::Network::xmlPersoList::refresh(){
  bool ret;

  GlobalURI gu;
  filename=gu.getXmlAdress("persos.xml");

  bool success= CurlFileToXml::perform();

  if (success){
    loadDocument(this);
    ret=true;
  }
  else{
    long resp=CurlFileToXml::getServerResponse();
    GTS_MID(str);
    sprintf(str, _("An error occured while getting xmlPersoList."
		   "Server response was : %d"), resp);
    LOGW(str);
    correctlyLoaded=false;
    ret=false;
  }

  return ret;
}


/** The default destructor
  *
  *
  */
RainbruRPG::Network::xmlPersoList::~xmlPersoList(){
  doc=NULL;
  root=NULL;
}

/** Loads the xml document
  *
  * \param cgf A pointer to the CurlFileToXml instance used to get 
  *        the xml file.
  */
void RainbruRPG::Network::xmlPersoList::loadDocument(
                                         CurlFileToXml* cgf){

  doc=cgf->getXmlDocument();
  if (doc){
    root =doc->RootElement();
    correctlyLoaded=true;
  }
  else{
    correctlyLoaded=false;
    LOGW(_("An error occured while getting xmlPlayerList"));
  }
}

/** returns the next persoId
  *
  * \return A string representing the next persoId.
  */
const char* RainbruRPG::Network::xmlPersoList::getNextId(){
    return getXMLTextFromName(root, "NextId");
}

/** Get the persoList
  *
  * \return A pointer to a list of account/perso
  *
  */
RainbruRPG::Network::tPersoList* 
RainbruRPG::Network::xmlPersoList::getPersoList(){

  tPersoList* list=new tPersoList();

  if (doc){
    TiXmlHandle docHandle( doc );
    TiXmlElement* child = docHandle.FirstChild( "PersoList" )
      .FirstChild( "Player" ).Element();
    
    for( child; child; child=child->NextSiblingElement() ){

      tPersoListItem* pli=new tPersoListItem();
      pli->name=child->Attribute("name");

      feedPersoList(child, pli);

      // This test avoid a last list element with NULL name
      // It is due to TinyXML (returns NULL is Attribute("name")
      // not found)
      if (pli->name!=NULL){
	list->push_back(pli);
      }
    }
  }

  return list;
}

/** Feed the persolist of the given tPersoListItem with the given TiXmlElement
  * 
  * \param elem The 'Player' xml node
  * \param it   The account object to feed
  *
  */
void RainbruRPG::Network::xmlPersoList::
feedPersoList(TiXmlElement* elem, tPersoListItem* it){
  if (elem && it){
    TiXmlHandle docHandle( elem );
    TiXmlElement* child = docHandle.FirstChild( "Perso" ).Element();

    for( child; child; child=child->NextSiblingElement() ){

      tPersoSubListItem* subIt=new tPersoSubListItem();
      subIt->persoId=getXMLTextFromName(child, "Id");


      TiXmlHandle docHandle2( child );
      TiXmlElement* child2 = docHandle2.FirstChild( "Timestamp" ).Element();

      subIt->creation=child2->Attribute("creation");
      it->persoList.push_back(subIt);

    }
  }
}

/** Get an account by its name
  *
  * If you know the account name and you want all its perso, use this.
  *
  * \param name The name of the account you want a perso list for
  *
  * \return The tPersoListItem or \c NULL if not found
  *
  */
RainbruRPG::Network::tPersoListItem* 
RainbruRPG::Network::xmlPersoList::getAccountByName(const std::string& name){

  tPersoList* pl=this->getPersoList();

  tPersoList::const_iterator iter;
  for (iter=pl->begin(); iter != pl->end(); iter++){
    if (name==(*iter)->name){
      return (*iter);
    }
  }

  return NULL;
}

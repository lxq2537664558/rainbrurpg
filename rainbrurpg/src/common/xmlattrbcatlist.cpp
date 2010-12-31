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

/** \file xmlattrbcatlist.cpp
  * Implements a class that read the XML file of the attribute categories list
  *
  */

#include "xmlattrbcatlist.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::xmlAttrbCatList::xmlAttrbCatList(){
  refresh();

}

/** Reloads the document and refreshes all data
  *
  * \return \c true if the operation is successfull, otherwise 
  *         returns \c false
  *
  */
bool RainbruRPG::Network::Ident::xmlAttrbCatList::refresh(){
  bool ret;

  GlobalURI gu;
  filename=gu.getXmlAdress("persoattrbcat.xml");

  bool success= CurlFileToXml::perform();

  if (success){
    loadDocument(this);
    ret=true;
  }
  else{
    long resp=CurlFileToXml::getServerResponse();
    GTS_LIT(str);
    sprintf(str, _("An error occured while getting xmlAccountList. "
		   "Server response was : %d"), resp);
    LOGE(str);
    correctlyLoaded=false;
    ret=false;
  }

  return ret;
}


/** The default destructor
  *
  *
  */
RainbruRPG::Network::Ident::xmlAttrbCatList::~xmlAttrbCatList(){
  doc=NULL;
  root=NULL;
}

/** Loads the xml document or creates it if it does not exist
  *
  * It use the CurlFileToXml to get the document. If the document cannot
  * be get this way, we log a warning message and set correctlyLoaded
  * to \c false.
  *
  * \param cgf A pointer to a valid CurlFileToXml instance.
  *
  *
  */
void RainbruRPG::Network::Ident::xmlAttrbCatList::loadDocument(
                                         CurlFileToXml* cgf){

  doc=cgf->getXmlDocument();
  if (doc){
    root =doc->RootElement();
    correctlyLoaded=true;
  }
  else{
    correctlyLoaded=false;
    LOGW(_("An error occured while getting xmlAttrbCatList"));
  }
}

/** Returns the player list from the xml file
  *
  * This function is used by the PlayerList class to get the
  * playerlist. This list is then iterates and we can feed the list of
  * player names.
  *
  * \return A list of player
  */
RainbruRPG::Network::Ident::tAttrbCatList* RainbruRPG::Network::Ident::
                                  xmlAttrbCatList::getAttrbCatList(){

  tAttrbCatList* pl= new tAttrbCatList();

  TiXmlHandle docHandle( doc );
  TiXmlElement* child = docHandle.FirstChild( "PersoAttrbCat" )
                                  .FirstChild( "Category" ).Element();

  for( child; child; child=child->NextSiblingElement() ){

    tAttrbCatListItem* it=new tAttrbCatListItem();

    it->name= getXMLTextFromName(child, "Name");
    it->desc= getXMLTextFromName(child, "Desc");
    it->tab= getXMLTextFromName(child, "Tab");

    pl->push_back(it);
  }
  return pl;
}

/** Return an attribute's category
  *
  * \param catName The name od the category you want
  *
  * \return The category if found or \c NULL if not
  *
  */
RainbruRPG::Network::Ident::tAttrbCatListItem* RainbruRPG::Network::Ident::
              xmlAttrbCatList::getAttrbCat(const char* catName){

  bool found=false;

  tAttrbCatList::const_iterator iter;

  tAttrbCatList* pl=this->getAttrbCatList();
  
  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){

      // We have the good category
      if (strcmp(catName, (*iter)->name )==0){
	found=true;
	return (*iter);

      }
    }
  }

  if (!found)
    return NULL;
}

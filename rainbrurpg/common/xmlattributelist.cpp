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

/** \file xmlattributelist.cpp
  * Implements a class used to read the XML file of the attribute list
  *
  */

#include "xmlattributelist.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::xmlAttributeList::xmlAttributeList(){
  refresh();
}

/** Reloads the document and refreshes all data
  *
  * \return \c true if the operation is successfull, otherwise 
  *         returns \c false
  *
  */
bool RainbruRPG::Network::Ident::xmlAttributeList::refresh(){
  bool ret;

  GlobalURI gu;
  //  const char* filename=;
  //  const char* filename="http://127.0.0.1/rpg/persoattrb.xml";
  filename=gu.getXmlAdress("persoattrb.xml");

  bool success= CurlFileToXml::perform();

  if (success){
    if (loadDocument(this)){
      ret=true;
    }
    else{
      ret=false;
      correctlyLoaded=false;
    }
  }
  else{
    long resp=CurlFileToXml::getServerResponse();
    GTS_LIT(str);
    // TRANSLATORS: The parameter is a numerical error code.
    sprintf(str, _("An error occured while getting xmlAttrbibuteList. "
		   "Server response was : %d"), resp);
    LOGE(str)
    correctlyLoaded=false;
    ret=false;
  }

  return ret;
}


/** The default destructor
  *
  *
  */
RainbruRPG::Network::Ident::xmlAttributeList::~xmlAttributeList(){
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
  * \return \c true if the xml document was correctly loaded
  *
  */
bool RainbruRPG::Network::Ident::xmlAttributeList::loadDocument(
                                         CurlFileToXml* cgf){

  doc=cgf->getXmlDocument();
  if (doc){
    root =doc->RootElement();
    correctlyLoaded=true;
    return true;
  }
  else{
    correctlyLoaded=false;
    LOGW(_("An error occured while getting xmlAttributeList"));
    return false;
  }
}

/** Get the list of attribute
  *
  * \return a poionter to a tAttributeList
  *
  */
RainbruRPG::Network::Ident::tAttributeList* RainbruRPG::Network::Ident::
                                  xmlAttributeList::getAttributeList(){

  if (correctlyLoaded){

    tAttributeList* pl= new tAttributeList();
    
    TiXmlHandle docHandle( doc );
    TiXmlElement* child = docHandle.FirstChild( "PersoAttributes" )
      .FirstChild( "Attribute" ).Element();
    
    for( child; child; child=child->NextSiblingElement() ){
      
      tAttributeListItem* it=new tAttributeListItem();
      
      it->name  = getXMLTextFromName(child, "Name");
      it->cat   = getXMLTextFromName(child, "Cat");
      it->type  = getXMLTextFromName(child, "Type");
      it->param1= getXMLTextFromName(child, "Param1");
      it->param2= getXMLTextFromName(child, "Param2");
      it->desc  = getXMLTextFromName(child, "Desc");
      
      pl->push_back(it);
    }
    return pl;
  }
  else{
    LOGE("Cannot get attribute list, document not loaded");
    return NULL;
  }
}

/** Get an attribute by name or \c NULL if not found
  *
  * \param attrbName the name of the attribute you want
  *
  * \return The attribute if found
  *
  */
RainbruRPG::Network::Ident::tAttributeListItem* RainbruRPG::Network::Ident::
              xmlAttributeList::getAttribute(const char* attrbName){

  bool found=false;

  tAttributeList::const_iterator iter;

  tAttributeList* pl=this->getAttributeList();
  
  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){

      // We have the good category
      if (strcmp(attrbName, (*iter)->name )==0){
	found=true;
	return (*iter);

      }
    }
  }

  if (!found)
    return NULL;
}

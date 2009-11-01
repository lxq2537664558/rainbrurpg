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

/** \file xmlbonusfilelist.cpp
  * Implements a class that read a BonusFile XML list
  *
  */

#include "xmlbonusfilelist.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::xmlBonusFileList::xmlBonusFileList(){
  refresh();
}

/** Reloads the document and refreshes all data
  *
  * \return \c true if the operation is successfull, otherwise 
  *         returns \c false
  *
  */
bool RainbruRPG::Network::Ident::xmlBonusFileList::refresh(){
  bool ret;

  GlobalURI gu;

  CurlFileToXml cgf;
  filename=gu.getXmlAdress("bonusfilelist.xml");
  bool success= CurlFileToXml::perform();

  if (success){
    if (loadDocument(&cgf)){
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
    sprintf(str, _("An error occured while getting xmlBonusFileList. "
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
RainbruRPG::Network::Ident::xmlBonusFileList::~xmlBonusFileList(){
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
bool RainbruRPG::Network::Ident::xmlBonusFileList::loadDocument(
                                         CurlFileToXml* cgf){

  doc=cgf->getXmlDocument();
  if (doc){
    root =doc->RootElement();
    correctlyLoaded=true;
    return true;
  }
  else{
    correctlyLoaded=false;
    LOGW(_("An error occured while getting xmlBonusFileList"));
    return false;
  }
}

/** Get the list of available bonusfile
  *
  * \return A stl list of bonusfile
  *
  * \todo Some memory leaks may appear
  */
RainbruRPG::Network::Ident::tBonusFileList* RainbruRPG::Network::Ident::
xmlBonusFileList::getBonusFileList(){
  
  if (correctlyLoaded){
    tBonusFileList * cl=new tBonusFileList();
    
    TiXmlHandle docHandle( doc );
    TiXmlElement* child = docHandle.FirstChild( "BonusFileList" )
      .FirstChild( "BonusFile" ).Element();
    
    for( child; child; child=child->NextSiblingElement() ){
      
      tBonusFileListItem* it=new tBonusFileListItem();
      
      it->name      = getXMLTextFromName(child, "Name");
      it->filename  = getXMLTextFromName(child, "File");
      it->desc      = getXMLTextFromName(child, "Desc");
      
      cl->push_back(it);
    }
    return cl;
  }
  else{
    LOGE(_("Cannot get BonusFile list, document not loaded"));
    return NULL;
  }

}


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

#include "xmlbonusfilelist.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::xmlBonusFileList::xmlBonusFileList(){
  LOGI("Creates xmlBonusFileList");
  refresh();
}

/** Reloads the document and refreshes all data
  *
  * \return \c true if the operation is successfull, otherwise 
  *         returns \c false
  *
  */
bool RainbruRPG::Network::Ident::xmlBonusFileList::refresh(){
  LOGI("xmlBonusFileList refresh function called");
  bool ret;

  GlobalURI gu;

  CurlFileToXml cgf;
  cgf.setFilename(gu.getXmlAdress("bonusfilelist.xml"));
  bool success= cgf.perform();

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
    long resp=cgf.getServerResponse();
    LOGE("An error occured while getting xmlBonusFile");
    cout << "Last server response : " << resp << endl;
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
    LOGI("xmlBonusFile correctly loaded"); 
    return true;
  }
  else{
    correctlyLoaded=false;
    LOGW("An error occured while getting xmlBonusFile");
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
    LOGE("Cannot get BonusFile list, document not loaded");
    return NULL;
  }

}

/** Get the text of the child element of a node
  *
  * \param child The XML node we search the text in
  * \param nodeName The name of the node we search the text of
  *
  * \return The text of the node if found or an empty string if not
  *
  */
const char* RainbruRPG::Network::Ident::xmlBonusFileList::
                getXMLTextFromName(TiXmlElement*child, const char* nodeName){

  TiXmlText* textNode;

  TiXmlNode* node=child->FirstChild(nodeName);
  if (node && node->FirstChild()){
    textNode=node->FirstChild()->ToText();
    if (textNode)
      return  textNode->Value();
    
    else  // !textNode
      return  "";
  }
  else    // !node
    return  "";
}


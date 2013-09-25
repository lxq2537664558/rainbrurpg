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

#include "xmlbonusfile.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::xmlBonusFile::xmlBonusFile(std::string fn){
  LOGI("Creates xmlBonusFile");
  this->filename=fn;
  refresh();
}

/** Reloads the XML document
  *
  * It uses CurlFileToXml to get the XML file and send it to TinyXml
  *
  * \return \c true if no error occurs
  *
  */
bool RainbruRPG::Network::Ident::xmlBonusFile::refresh(){
  LOGI("xmlBonusFile refresh function called");
  bool ret;

  GlobalURI gu;
  //  const char* filename=;
  //  const char* filename="http://127.0.0.1/rpg/persoattrb.xml";
  CurlFileToXml cgf;
  cgf.setFilename(gu.getXmlAdress(this->filename.c_str()));
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
RainbruRPG::Network::Ident::xmlBonusFile::~xmlBonusFile(){
  doc=NULL;
  root=NULL;
}

/** Loads the xml document or creates it if it does not exist
  *
  * \param cgf The CurlFileToXml instance used to get the XML file
  *
  * \return \c true if no error occured
  *
  */
bool RainbruRPG::Network::Ident::xmlBonusFile::loadDocument(
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

/** Get the list of the choices available in this bonusFile
  *
  * \return a tBonusFileChoiceList structure pointer
  *
  */
RainbruRPG::Network::Ident::tBonusFileChoiceList* RainbruRPG::Network::Ident::
xmlBonusFile::getChoiceList(){
  
  if (correctlyLoaded){
    tBonusFileChoiceList * cl=new tBonusFileChoiceList();
    
    TiXmlHandle docHandle( doc );
    TiXmlElement* child = docHandle.FirstChild( "BonusFile" )
      .FirstChild( "Choice" ).Element();
    
    for( child; child; child=child->NextSiblingElement() ){
      
      tBonusFileChoiceListItem* it=new tBonusFileChoiceListItem();
      
      it->name  = getXMLTextFromName(child, "Name");
      it->desc  = getXMLTextFromName(child, "Desc");
      
      cl->push_back(it);
    }
    return cl;
  }
  else{
    LOGE("Cannot get choice list, document not loaded");
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
const char* RainbruRPG::Network::Ident::xmlBonusFile::
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

/** Get a modifier list from the name of the choice
  *
  * \return The content of a choice (a tBonusModifierList structure pointer)
  *
  */
RainbruRPG::Network::Ident::tBonusModifierList* 
RainbruRPG::Network::Ident::xmlBonusFile::
                    getModifierList(const char* choiceName){

  const char* name;
  TiXmlElement* modRoot;

  if (correctlyLoaded){
    // Creates the returned list
    tBonusModifierList* cl=new tBonusModifierList();

    // First, we get the god choice
    TiXmlHandle docHandle( doc );
    TiXmlElement* child = docHandle.FirstChild( "BonusFile" )
      .FirstChild( "Choice" ).Element();
    
    for( child; child; child=child->NextSiblingElement() ){
      name  = getXMLTextFromName(child, "Name");
      if (strcmp ( choiceName, name)==0){
	// We have the good choice
	// We now get the 'AttributesModifiers' element
	modRoot=child->FirstChild("AttributesModifiers")->ToElement();
	// Next, get all the 'Modifier' nodes
	return makeModifierList(modRoot);
      }
    }
    return cl;

  }
  else{
    LOGE("Cannot get modifiers list, document not loaded");
    return NULL;

  }
}

/** Creates a tBonusModifierList structure from a XML 'AttributesModifiers'
  * node
  *
  * \param modRoot the 'AttributesModifiers' node
  *
  * \return A tBonusModifierList representing the xml tree
  */
RainbruRPG::Network::Ident::tBonusModifierList* 
RainbruRPG::Network::Ident::xmlBonusFile::
makeModifierList(TiXmlElement* modRoot){

    tBonusModifierList* cl=new tBonusModifierList();
    
    TiXmlHandle docHandle( modRoot );
    TiXmlElement* child = docHandle.FirstChild( "Modifier" )
      .Element();
    
    for( child; child; child=child->NextSiblingElement() ){
      
      tBonusModifierListItem* it=new tBonusModifierListItem();
      
      it->attrb  = getXMLTextFromName(child, "Attrb");
      it->mod  = getXMLTextFromName(child, "Mod");
      
      cl->push_back(it);
    }

    return cl;
}

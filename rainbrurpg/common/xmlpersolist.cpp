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

#include "xmlpersolist.h"

/** The default constructor
  *
  * It calls the refresh() function.
  */
RainbruRPG::Network::xmlPersoList::xmlPersoList(){
  LOGI("Creation xmlPersoList");
  refresh();

}

/** Refresh the xml document
  *
  * It calls loadDocument() to reload the xml file.
  *
  * \return \c false if the operation failed, otherwise \c true.
  */
bool RainbruRPG::Network::xmlPersoList::refresh(){
  LOGI("xmlPersoList refresh function called");
  bool ret;

  GlobalURI gu;
  const char* filename=gu.getXmlAdress("persos.xml");

  CurlFileToXml cgf;
  cgf.setFilename(filename);

  bool success= cgf.perform();

  if (success){
    loadDocument(&cgf);
    ret=true;
  }
  else{
    long resp=cgf.getServerResponse();
    LOGW("An error occured while getting xmlPersoList");
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
    LOGI("xmlPlayerList correctly loaded"); 
  }
  else{
    correctlyLoaded=false;
    LOGW("An error occured while getting xmlPlayerList");
  }
}

/** Returns the text element from the \c child and the given node
  * name.
  *
  * \param child The xml element where we must search the node.
  * \param nodeName The node's name we must find in \c child.
  *
  * \return The text store in the \c child's node defined by \c
  * nodeName. Returns an empty string ("") if none child was found.
  */  
const char* RainbruRPG::Network::xmlPersoList::
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

/** returns the next persoId
  *
  * \return A string representing the next persoId.
  */
const char* RainbruRPG::Network::xmlPersoList::getNextId(){
    return getXMLTextFromName(root, "NextId");
}

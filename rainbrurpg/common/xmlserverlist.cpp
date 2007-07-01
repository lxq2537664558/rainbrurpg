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

#include "xmlserverlist.h"
#include "globaluri.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::xmlServerList::xmlServerList(){
  refresh();
}

/** Get the xml file and load it
  *
  * \return \c true if no error occured
  *
  */
bool RainbruRPG::Network::Ident::xmlServerList::refresh(){
  GlobalURI gu;
  std::string fn=gu.getXmlAdress("servers.xml");

  CurlFileToXml::setFilename(fn.c_str());
  CurlFileToXml::perform();
  doc=CurlFileToXml::getXmlDocument();

}

/** The default destructor
  *
  *
  */
RainbruRPG::Network::Ident::xmlServerList::~xmlServerList(){
  doc=NULL;
  root=NULL;
}

/** Get the child text of the given child
  *
  * \param child The parent of the wanted text
  * \param nodeName The node name of the text you want
  *
  * \return The text of the named child's node of child
  *
  */
const char* RainbruRPG::Network::Ident::xmlServerList::getXMLTextFromName (
					       TiXmlElement* child, 
					       const char* nodeName){

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

/** Get the list of servers
  *
  * It creates a new instance of tServerList and returns it.
  *
  * \return The server list
  *
  */
RainbruRPG::Network::Ident::tServerList* 
RainbruRPG::Network::Ident::xmlServerList::getServerList(){

  TiXmlNode* node;

  tServerList* pl= new tServerList();

  TiXmlHandle docHandle( doc );
  TiXmlElement* child = docHandle.FirstChild( "ServerList" )
                                  .FirstChild( "Server" ).Element();

  for( child; child; child=child->NextSiblingElement() ){

    tServerListItem *it=new tServerListItem();

    // Get the creation timestamp
    xmlTimestamp xts;
    it->creation= xts.getCTimeS("creation", child);

    it->name= getXMLTextFromName(child, "Name");
    it->uniqueName= getXMLTextFromName(child, "UniqueName");
    it->description= getXMLTextFromName(child, "Desc");
    it->ipAddress= getXMLTextFromName(child, "Ip");
    it->port= getXMLTextFromName(child, "Port");
    it->ftp= getXMLTextFromName(child, "Ftp");
    it->techNote= getXMLTextFromName(child, "TechNote");
    const char* mc=getXMLTextFromName(child, "MaxClients");
    const char* ac=getXMLTextFromName(child, "ActClients");
    const char* tc=getXMLTextFromName(child, "Type");
    it->maxClients=StringConv::getSingleton().stoi(mc);
    it->actClients=StringConv::getSingleton().stoi(ac);
    it->type=StringConv::getSingleton().stoi(tc);

    pl->push_back(it);
  }
  return pl;
}

/** Test if a server name is already in use
  *
  * \param n The server name to test
  *
  * \return \c true if the given name is already in use, otherwise \c false
  *
  */
bool RainbruRPG::Network::Ident::xmlServerList::isServerExisting(
						 const char* n){
  tServerList::const_iterator iter;

  tServerList* pl=this->getServerList();
  
  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){
      if (strcmp(n, (*iter)->name )==0){
	return true;
      }
    }
  }

  return false;
}

/** Get a single server by its name
  *
  * \param n The name of the wanted server
  *
  * \return The server or NULL if not found
  *
  */
RainbruRPG::Network::Ident::tServerListItem* 
RainbruRPG::Network::Ident::xmlServerList::
getServerByName(const char* n){
  bool found=false;

  tServerList::const_iterator iter;
  tServerList* pl=this->getServerList();
  
  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){

      // We have the good server
      if (strcmp(n, (*iter)->name )==0){
	found=true;
	return (*iter);

      }
    }
  }

  if (!found)
    return NULL;
}

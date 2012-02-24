/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file xmlserverlist.cpp
  * Implements a class that read the server list
  *
  */

#include "xmlserverlist.h"
#include "GlobalUri.hpp"

/** The default constructor
  *
  * After a call to this, the class is ready to use, you can
  * call getServerList().
  *
  */
RainbruRPG::Network::Ident::xmlServerList::xmlServerList():
  doc(NULL),
  root(NULL)
{
  refresh();
}

/** Get the xml file and load it
  *
  * \return \c true if no error occured
  *
  */
bool RainbruRPG::Network::Ident::xmlServerList::refresh(){
  GlobalURI gu;
  filename=gu.getXmlAdress("servers.xml");

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

/** Get the list of servers
  *
  * It creates a new instance of tServerList and returns it.
  *
  * \return The server list or NULL if an error occured
  *
  */
RainbruRPG::Network::Ident::tServerList* 
RainbruRPG::Network::Ident::xmlServerList::getServerList(){

  TiXmlNode* node;

  tServerList* pl= new tServerList();

  if (doc != NULL){
    TiXmlHandle docHandle( doc );
    TiXmlHandle sl_handle = docHandle.FirstChild( "ServerList" );

    TiXmlElement* child = sl_handle.FirstChild( "Server" ).Element();

    for( child; child; child=child->NextSiblingElement() ){

      ServerListItem *it=new ServerListItem();

      // Get the creation timestamp
      xmlTimestamp xts;
      it->setCreationDate(xts.getCTimeS("creation", child));
      it->setName(getXMLTextFromName(child, "Name"));
      it->setUniqueName(getXMLTextFromName(child, "UniqueName"));
      it->setDescription(getXMLTextFromName(child, "Desc"));
      it->setIpAddress(getXMLTextFromName(child, "Ip"));
      it->setUdpPort(getXMLTextFromName(child, "Port"));
      it->setFtpPort(getXMLTextFromName(child, "Ftp"));
      it->setTechNote(getXMLTextFromName(child, "TechNote"));
      it->setMaxClients(getXMLTextFromName(child, "MaxClients"));
      it->setActClients(getXMLTextFromName(child, "ActClients"));
      it->setType(getXMLTextFromName(child, "Type"));

      pl->push_back(it);
    }
    return pl;
  }
  else{
    return NULL;
  }
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
  std::string sName;  

  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){
      sName=(*iter)->getName();
      if (sName==n){
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
RainbruRPG::Network::Ident::ServerListItem* 
RainbruRPG::Network::Ident::xmlServerList::
getServerByName(const char* n){
  bool found=false;

  tServerList::const_iterator iter;
  tServerList* pl=this->getServerList();
  std::string sName;  
  
  if (pl){
    for (iter=pl->begin(); iter != pl->end(); iter++){
      sName=(*iter)->getName();
 
      // We have the good server
      if (sName==n){
	found=true;
	return (*iter);
      }
    }
  }

  if (!found)
    return NULL;
}

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

#include "xmlserverconf.h"

#include <globaluri.h>
#include <logger.h>
#include <stringconv.h>

/** The default constructor
  *
  * Loads the server.xml file into a TinyXml document structure.
  *
  */
RainbruRPG::Server::xmlServerConf::xmlServerConf(){
  LOGI("xmlServerConf created");

  correctlyLoaded=false;

  // Getting the absolute filename
  RainbruRPG::Network::GlobalURI gu;
  filename=gu.getUserDirFile("server.xml");

  /// Creating the TinyXml representation of the xml file
  doc=new TiXmlDocument( this->filename.c_str() );
  if (doc){
    bool ret=doc->LoadFile();
    if (ret){
      root =doc->RootElement();
      if (root){
	correctlyLoaded=true;
	LOGI("Server configuration file correctly loaded");
      }
      else{
	LOGW("Cannot get a valid root element");
	LOGCATS(" Error was :");
	LOGCATS(doc->ErrorDesc());
	LOGCAT();
      }
    }
    else{
      LOGW("Cannot load the xml document");
      LOGCATS(" Error was :");
      LOGCATS(doc->ErrorDesc());
      LOGCAT();
    }
  }
  else{
    LOGW("Cannot create a document from the given xml file");
  }
}

/** The destructor
  *
  */
RainbruRPG::Server::xmlServerConf::~xmlServerConf(){
  delete doc;
  doc=NULL;
  root=NULL;
}

/** Sets the loaded values to the given server configuration
  *
  * The given ServerConfiguration pointer \b must be valid.
  *
  * \param sc The ServerConfiguration structure pointer
  *
  * \return \c true if the operation successed
  *
  */
bool RainbruRPG::Server::xmlServerConf::load(ServerConfiguration* sc){
  LOGI("Getting saved server configuration :");

  LOGCATS("  name : '");
  LOGCATS( getServerName() );
  LOGCATS("'");
  LOGCAT();

  LOGCATS("  desc : '");
  LOGCATS( getServerDesc() );
  LOGCATS("'");
  LOGCAT();

  LOGCATS("  technote : '");
  LOGCATS( getTechNote() );
  LOGCATS("'");
  LOGCAT();

  LOGCATS("  Playmode : '");
  LOGCATB( getPlayMode() );
  LOGCATS("'");
  LOGCAT();

  LOGCATS("  Editmode : '");
  LOGCATB( getEditMode() );
  LOGCATS("'");
  LOGCAT();

  LOGCATS("  Floodmode : '");
  LOGCATB( getFloodMode() );
  LOGCATS("'");
  LOGCAT();

  LOGCATS("  Port : '");
  LOGCATI( getPort() );
  LOGCATS("'");
  LOGCAT();

  LOGCATS("  MaxClient : '");
  LOGCATI( getMaxClient() );
  LOGCATS("'");
  LOGCAT();

  sc->setName(getServerName());
  sc->setDesc(getServerDesc());
  sc->setTechNote(getTechNote());
  sc->setPlayMode(getPlayMode());
  sc->setEditMode(getEditMode());
  sc->setFloodMode(getFloodMode());
  sc->setPort(getPort());
  sc->setMaxClient(getMaxClient());
  sc->setIpAdress(getIpAdress());
}


/** Get the name of the server from the xml file
  *
  * \return The server name
  *
  */
const char* RainbruRPG::Server::xmlServerConf::getServerName(){
  TiXmlNode* childNode = root->FirstChild( "Name" );
  if (childNode){
    TiXmlElement* lu= childNode->ToElement();
    if (lu){
      return lu->GetText();
    }
    else{
      return "";
    }
  }
  else{
    return "";
  }
}

/** Get the description of the server from the xml file
  *
  * \return The server description
  *
  */
const char* RainbruRPG::Server::xmlServerConf::getServerDesc(){
  TiXmlNode* childNode = root->FirstChild( "Description" );
  if (childNode){
    TiXmlElement* lu= childNode->ToElement();
    if (lu){
      return lu->GetText();
    }
    else{
      return "";
    }
  }
  else{
    return "";
  }
}

/** Get the technical note of the server from the xml file
  *
  * \return The server technote
  *
  */
const char* RainbruRPG::Server::xmlServerConf::getTechNote(){
  TiXmlNode* childNode = root->FirstChild( "TechnicalNote" );
  if (childNode){
    TiXmlElement* lu= childNode->ToElement();
    // To prevent an empty TechnicalNote error
    if (lu->FirstChild()==NULL){
      return "";
    }
    if (lu){
      return lu->GetText();
    }
    else{
      return "";
    }
  }
  else{
    return "";
  }
}

/** A generic function to get the value of a server mode
  *
  * \param mode The mode you want
  *
  * \return The mode value
  *
  */
bool RainbruRPG::Server::xmlServerConf::getMode(const char* mode){
  TiXmlNode* childNode = root->FirstChild( "Modes" );
  if (childNode){
    TiXmlElement* lu= childNode->ToElement();
    if (lu){
      const char* val= lu->Attribute(mode);
      bool b=StringConv::getSingleton().ctob(val);
      return b;
    }
    else{
      return false;
    }
  }
  else{
    return false;
  }
}


/** Get the play mode of the server from the xml file
  *
  * \return The server play mode state
  *
  */
bool RainbruRPG::Server::xmlServerConf::getPlayMode(){
  return getMode("play");
}

/** Get the edit mode of the server from the xml file
  *
  * \return The server edit mode state
  *
  */
bool RainbruRPG::Server::xmlServerConf::getEditMode(){
  return getMode("editor");
}

/** Get the flood mode of the server from the xml file
  *
  * \return The server flood mode state
  *
  */
bool RainbruRPG::Server::xmlServerConf::getFloodMode(){
  return getMode("flood");
}

/** A generic function to get the value of a server's option
  *
  * \param opt The option's name you want
  *
  * \return The option value
  *
  */
const char* RainbruRPG::Server::xmlServerConf::getOption(const char* opt){
  TiXmlNode* childNode = root->FirstChild( "Options" );
  if (childNode){
    TiXmlElement* lu= childNode->ToElement();
    if (lu){
      return lu->Attribute(opt);
    }
    else{
      return "";
    }
  }
  else{
    return "";
  }
}

/** Get the port of the server from the xml file
  *
  * \return The server port
  *
  */
int RainbruRPG::Server::xmlServerConf::getPort(){
  return StringConv::getSingleton().ctoi(getOption("port"));
}

/** Get the maxClient of the server from the xml file
  *
  * \return The server maxClient
  *
  */
int RainbruRPG::Server::xmlServerConf::getMaxClient(){
  return StringConv::getSingleton().ctoi(getOption("maxClient"));
}

/** Save the ServerConfiguration in the TinyXml document
  *
  * The given ServerConfiguration pointer \b must be valid.
  *
  * \param sc The ServerConfiguration structure pointer
  *
  * \return \c true if the operation successed
  *
  */
bool RainbruRPG::Server::xmlServerConf::save(ServerConfiguration* sc){
  LOGI("Saving server configuration");

  setServerName(sc->getName());
  setDescription(sc->getDesc());
  setTechNote(sc->getTechNote());
  setServerMode(sc->getPlayMode(), sc->getEditMode(), sc->getFloodMode());
  setServerOption(sc->getIpAdress(), sc->getPort(), sc->getMaxClient());

  bool success=doc->SaveFile(this->filename.c_str());
  if (!success){
    LOGW("An error occurs during server configuration saved");
  }
  else{
    LOGI("Server configuration correctly saved");
  }
}

/** Changes the server's name
  *
  * The xml document should be saved after this call.
  *
  * \param v The new server's name
  *
  */
void RainbruRPG::Server::xmlServerConf::setServerName(const std::string& v){
  TiXmlText nameNode(v.c_str());

  TiXmlNode* childNode = root->FirstChild( "Name" );
  if (childNode){
    childNode->Clear();
    childNode->InsertEndChild(nameNode);
  }

}

/** Changes the server's description
  *
  * The xml document should be saved after this call.
  *
  * \param v The new server's description
  *
  */
void RainbruRPG::Server::xmlServerConf::setDescription(const std::string& v){
  TiXmlText nameNode(v.c_str());

  TiXmlNode* childNode = root->FirstChild( "Description" );
  if (childNode){
    childNode->Clear();
    childNode->InsertEndChild(nameNode);
  }

}

/** Changes the server's technical note
  *
  * The xml document should be saved after this call.
  *
  * \param v The new server's technical note
  *
  */
void RainbruRPG::Server::xmlServerConf::setTechNote(const std::string& v){
  TiXmlText nameNode(v.c_str());

  TiXmlNode* childNode = root->FirstChild( "TechnicalNote" );
  if (childNode){
    childNode->Clear();
    childNode->InsertEndChild(nameNode);
  }
 
}

/** Set the server modes
  *
  * \param play The status of the play mode
  * \param edit The status of the edit mode
  * \param flood The status of the flood mode
  *
  */
void RainbruRPG::Server::xmlServerConf::
setServerMode(bool play, bool edit, bool flood){
  const char* txtPlay=StringConv::getSingleton().btoc(play);
  const char* txtEdit=StringConv::getSingleton().btoc(edit);
  const char* txtFlood=StringConv::getSingleton().btoc(flood);

  TiXmlElement* childNode = root->FirstChild( "Modes" )->ToElement();
  if (childNode){
    childNode->Clear();
    childNode->SetAttribute("play", txtPlay);
    childNode->SetAttribute("editor", txtEdit);
    childNode->SetAttribute("flood", txtFlood);
  }
}

/** Set the server options
  *
  * \param ip The IP adress of the server
  * \param port The port used by the server
  * \param maxClients The maxClient option
  *
  */
void RainbruRPG::Server::xmlServerConf::
setServerOption(const std::string& ip, int port, int maxClients){
  TiXmlElement* childNode = root->FirstChild( "Options" )->ToElement();
  if (childNode){
    childNode->Clear();
    childNode->SetAttribute("ip", ip.c_str());
    childNode->SetAttribute("port", port);
    childNode->SetAttribute("maxClient", maxClients);
 }

}

/** Get the IP adress
  *
  * \return The IP adress saved in the xml file
  *
  */
const char* RainbruRPG::Server::xmlServerConf::getIpAdress(){
  return getOption("ip");
}

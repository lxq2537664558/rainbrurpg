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

/** \file curlserveradd.cpp
  * Implements a class used to add a server in the server list
  *
  */

#include "CurlServerAdd.hpp"

/** The default contructor
  *
  */
RainbruRPG::Network::Ident::CurlServerAdd::CurlServerAdd()
                                          :CurlSubmitForm(){

  GlobalURI g;

  xml=new xmlServerList();
  this->filename=g.getAdminAdress("addserver.php");

  // Setting the posted data key values
  postedData.addKey("name");
  postedData.addKey("uniqueName");
  postedData.addKey("type");
  postedData.addKey("ip");
  postedData.addKey("port");
  postedData.addKey("ftp");
  postedData.addKey("timestamp");
  postedData.addKey("maxClients");
  postedData.addKey("desc");

}

/** The default destructor 
  *
  */
RainbruRPG::Network::Ident::CurlServerAdd::~CurlServerAdd(){
  xml->~xmlServerList();
  xml=NULL;
}

/** Test the posted data before submit the added server
  *
  * It tests the postedData values. The most relevant error must
  * be tested last.
  *
  * \return \c true if the operation is successfull, \c false if it failed
  */
bool RainbruRPG::Network::Ident::CurlServerAdd::controlBefore(){
  bool ret=true;

  const char* name=postedData.getValue("name");
  const char* ip=postedData.getValue("ip");
  const char* port=postedData.getValue("port");
  const char* cli=postedData.getValue("maxClients");
  const char* errmsg;

  // The port adress is empty
  if (strlen(port)==0){
    errmsg=_("The new server's listening port is empty");
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
  }

  // The IP adress is empty
  if (strlen(ip)==0){
    errmsg=_("The new server's IP address is empty");
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
  }

  // The name is empty
  if (strlen(name)==0){
    errmsg=_("The new server's name is empty");
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
  }

  postedData.setTimestamp("timestamp");

  return ret;
}

/** Controls if the operation was correctly done
  *
  * It compares if the added server is in the administration site. By
  * using xmlServerList to get the server list.
  *
  * \return \c true if the accound was correctly added
  *
  */
bool RainbruRPG::Network::Ident::CurlServerAdd::controlAfter(){
  bool ret=true;
 
  /*  // Get the values
  const char* name=postedData.getValue("name");
  const char* pwd=postedData.getValue("pwd");
  const char* mail=postedData.getValue("mail");

  tServerListItem *it=xml->getServer(name);
  const char* itname= it->name;
  const char* itpwd= it->password;
  const char* itmail= it->mail;
  // control Name
  if ((strlen(name)==0)||(strlen(itname)==0)){
    LOGW("One of the name is empty, controlAfter failed");
    ret=false;

  }
  else{
    if (strcmp(name, itname)==0){
      LOGI("The name is the same");
    }
    else{
      LOGW("The name is not the same");
      ret=false;
    }
  */

  return ret;
}

/** Set the server name key value
  *
  * \param c The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::setName(const char*c){
  postedData.setValue("name", c);

}

/** Set the server IP address key value
  *
  * \param c The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::setIpAddress(const char*c){
  postedData.setValue("ip", c);

}

/** Set the server port key value
  *
  * \param c The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::setPort(const char*c){
  postedData.setValue("port", c);

}

/** Set the server maxClients key value
  *
  * \param c The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::setMaxClients(const char*c){
  postedData.setValue("maxClients", c);

}

/** Set the server description key value
  *
  * \param c The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::setDescription(const char*c){
  postedData.setValue("desc", c);

}

/** Set the server technical note key value
  *
  * \param c The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::setTechNote(const char*c){
  setCustomPost("techNote", c);
}

/** Set the server name key value
  *
  * \param s The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::
setName(const std::string& s){
  postedData.setValue("name", s);
}

/** Set the server IP address key value
  *
  * \param s The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::
setIpAddress(const std::string& s){
  postedData.setValue("ip", s);

}

/** Set the server UDP port key value
  *
  * \param s The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::
setPort(const std::string& s){
  postedData.setValue("port", s);
}

/** Set the server max clients key value
  *
  * \param s The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::
setMaxClients(const std::string& s){
  postedData.setValue("maxClients", s);

}

/** Set the server description key value
  *
  * \param s The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::
setDescription(const std::string& s){
  postedData.setValue("desc", s);

}

/** Set the server technical note key value
  *
  * \param s The new value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::
setTechNote(const std::string& s){
  setCustomPost("techNote", s.c_str());

}

/** Get the server name
  *
  * \return The server name
  *
  */
const char* RainbruRPG::Network::Ident::CurlServerAdd::getName(){
  return postedData.getValue("name");
}

/** Get the server IP adress
  *
  * \return The server IP adress
  *
  */
const char* RainbruRPG::Network::Ident::CurlServerAdd::getIpAddress(){
  return postedData.getValue("ip");
}

/** Get the server UDP port
  *
  * \return The server port
  *
  */
const char* RainbruRPG::Network::Ident::CurlServerAdd::getPort(){
  return postedData.getValue("port");
}

/** Get the server maxClients
  *
  * \return The server maxClients
  *
  */
const char* RainbruRPG::Network::Ident::CurlServerAdd::getMaxClients(){
  return postedData.getValue("maxClients");
}

/** Get the server description
  *
  * \return The server description
  *
  */
const char* RainbruRPG::Network::Ident::CurlServerAdd::getDescription(){
  return postedData.getValue("desc");
}

/** Get the server technical note
  *
  * \return The server technical note
  *
  */
const char* RainbruRPG::Network::Ident::CurlServerAdd::getTechNote(){
  return postedData.getValue("techNote");
}

/** Change the FTP control channel port
  *
  * \param c The new key value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::setFtpPort(const char* c){
  postedData.setValue("ftp", c);
}

/** Change the FTP control channel port
  *
  * \param s The new key value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::
setFtpPort(const std::string& s){
  postedData.setValue("ftp", s);
}

/** Get the server's FTP control channel port
  *
  * \return The server's FTP control channel port
  *
  */
const char* RainbruRPG::Network::Ident::CurlServerAdd::getFtpPort(){
  return postedData.getValue("ftp");
}

/** Change the Unique Name of the server
  *
  * \param s The new key value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::
setUniqueName(const std::string& s){
  postedData.setValue("uniqueName", s);
}

/** Change the Type of the server
  *
  * \param s The new key value
  *
  */
void RainbruRPG::Network::Ident::CurlServerAdd::
setType(const std::string& s){
  postedData.setValue("type", s);
}

/** Get the value of the \c uniqueName key
  *
  * \return The content of the \c uniqueName key
  *
  */
std::string RainbruRPG::Network::Ident::CurlServerAdd::
getUniqueName(){
  std::string s;
  s=postedData.getValue("uniqueName");
  return s;
}

/** Get the value of the \c type key
  *
  * \return The content of the \c type key
  *
  */
std::string RainbruRPG::Network::Ident::CurlServerAdd::
getType(){
  std::string s(postedData.getValue("type"));
  return s;
}

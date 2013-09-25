/*
 *  Copyright 2006-2013 Jerome PASQUIER
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
/** \file curlservermodifclients.cpp
  * Implements a class to modify connected clients number of a server
  *
  */
#include "CurlServerModifClients.hpp"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::CurlServerModifClients::CurlServerModifClients()
                                                   :CurlSubmitForm(){

  GlobalURI g;

  xml=new xmlServerList();
  this->filename=g.getAdminAdress("changeserveract.php");

  // Setting the posted data key values
  postedData.addKey("name");
  postedData.addKey("actClients");

}

/** The destructor
  *
  */
RainbruRPG::Network::Ident::CurlServerModifClients::~CurlServerModifClients(){

}

/** Sets the name of the server
  *
  * Changes the server's name you want to modify the actual connected clients 
  * number.
  *
  * \param c The new server's name
  *
  */
void RainbruRPG::Network::Ident::CurlServerModifClients::
setName(const char* c){
  postedData.setValue("name", c);

}

/** Sets the name of the server
  *
  * Changes the server's name you want to modify the actual connected clients 
  * number.
  *
  * \param s The new server's name
  *
  */
void RainbruRPG::Network::Ident::CurlServerModifClients::
setName(const std::string& s){
  postedData.setValue("name", s);

}

/** Sets the actually connected client number
  *
  * If the given client number is negative, it will be set to 0.
  * \ref RainbruRPG::Core::StringConv "StringConv" is used to convert 
  * the integer agrument into an std::string.
  *
  * \param i The client number
  *
  */
void RainbruRPG::Network::Ident::CurlServerModifClients::setActClients(int i){

  if (i<0) i=0;

  std::string s=StringConv::getSingleton().itos(i);
  postedData.setValue("actClients", s);
}

/** The controlBefore implementation
  *
  * \return \c true if the controls passed
  *
  */
bool RainbruRPG::Network::Ident::CurlServerModifClients::controlBefore(){
  return true;
}

/** The controlAfter implementation
  *
  * \return \c true if the controls passed
  *
  */
bool RainbruRPG::Network::Ident::CurlServerModifClients::controlAfter(){
  return true;
}

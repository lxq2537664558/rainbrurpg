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

/** \file curlserverdelete.cpp
  * Implements a class used to delete a server in the server list
  *
  */

#include "curlserverdelete.h"

/** The default contructor
  *
  */
RainbruRPG::Network::Ident::CurlServerDelete::CurlServerDelete()
                                             :CurlSubmitForm(){

  GlobalURI g;

  this->filename=g.getAdminAdress("deleteserver.php");

  // Setting the posted data key values
  postedData.addKey("name");

}

/** The destructor
  *
  */
RainbruRPG::Network::Ident::CurlServerDelete::~CurlServerDelete(){

}


/** Change the name of the server to delete
  *
  * \param c The new serverName
  *
  */
void RainbruRPG::Network::Ident::CurlServerDelete::setName(const char* c){
  postedData.setValue("name", c);

}

/** The default contructor
  *
  * \param s The new serverName
  *
  */
void RainbruRPG::Network::Ident::CurlServerDelete::
setName(const std::string& s){
  postedData.setValue("name", s);

}

/** Test the posted data before submit the deleted server
  *
  * It tests the postedData values. The most relevant error must
  * be tested last.
  *
  * \return \c true if the operation is successfull, \c false if it failed
  */
bool RainbruRPG::Network::Ident::CurlServerDelete::controlBefore(){
  bool ret=true;

  const char* name=postedData.getValue("name");
  const char* errmsg;

  // The name is empty
  if (strlen(name)==0){
    errmsg="The new server's name is empty";
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
  }

  return ret;
}

/** Test if the server was correctly deleted
  *
  * It tests the postedData values. The most relevant error must
  * be tested last.
  *
  * \return \c true if the operation is successfull, \c false if it failed
  */
bool RainbruRPG::Network::Ident::CurlServerDelete::controlAfter(){
  bool ret=true;

  return ret;

}

/** Get the server name
  *
  * \return The name of the server
  *
  */
const char* RainbruRPG::Network::Ident::CurlServerDelete::getName(){
  return postedData.getValue("name");
}

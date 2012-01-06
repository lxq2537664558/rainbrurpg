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

/** \file curlaccounttoggleblacklist.cpp
  * Implements the submition of an account toggle blacklist request
  *
  */
#include "curlaccounttoggleblacklist.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::CurlAccountToggleBlacklist::
CurlAccountToggleBlacklist()
  : CurlSubmitForm(){

  GlobalURI g;

  xml=new xmlAccountList();
  this->filename=g.getAdminAdress("toggleblacklist.php");
  // Setting the posted data key values
  postedData.addKey("name");
}

/** The destructor
  *
  */
RainbruRPG::Network::Ident::CurlAccountToggleBlacklist::
~CurlAccountToggleBlacklist(){

  xml->~xmlAccountList();
  xml=NULL;

}

/** Change the name of the account to be toggle-blacklisted
  *
  * \param c The account's name
  *
  */
void RainbruRPG::Network::Ident::CurlAccountToggleBlacklist::
setName(const char* c){
  this->setPostedData("name", c);

}

/** The controlBefore implementation
  *
  * \return \c true if the operation is successfull
  *
  * \sa CurlSubmitForm
  *
  */
bool RainbruRPG::Network::Ident::CurlAccountToggleBlacklist::controlBefore(){
  return true;
}

/** The controlAfter implementation
  *
  * \return \c true if the operation is successfull
  *
  * \sa CurlSubmitForm
  *
  */
bool RainbruRPG::Network::Ident::CurlAccountToggleBlacklist::controlAfter(){
  return true;

}

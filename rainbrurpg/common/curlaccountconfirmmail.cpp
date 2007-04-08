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

#include "curlaccountconfirmmail.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ident::CurlAccountConfirmMail::CurlAccountConfirmMail()
  : CurlSubmitForm(){

  GlobalURI g;

  xml=new xmlAccountList();
  this->filename=g.getAdminAdress("mailconfirm.php");
  // Setting the posted data key values
  postedData.addKey("name");
  postedData.addKey("confirmation");
}

/** The destructor
  *
  */
RainbruRPG::Network::Ident::CurlAccountConfirmMail::~CurlAccountConfirmMail(){
  xml->~xmlAccountList();
  xml=NULL;

}

/** Change the name of the account to be mail-confirmed
  *
  * \param c The account's name
  *
  */
void RainbruRPG::Network::Ident::CurlAccountConfirmMail::
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
bool RainbruRPG::Network::Ident::CurlAccountConfirmMail::controlBefore(){
  postedData.setTimestamp("confirmation");

  return true;
}

/** The controlAfter implementation
  *
  * \return \c true if the operation is successfull
  *
  * \sa CurlSubmitForm
  *
  */
bool RainbruRPG::Network::Ident::CurlAccountConfirmMail::controlAfter(){
  return true;

}

/** Get the name 
  *
  * \return the name of the account to confirm mail
  *
  */
const char* RainbruRPG::Network::Ident::CurlAccountConfirmMail::getName(){
  return postedData.getValue("name");

}

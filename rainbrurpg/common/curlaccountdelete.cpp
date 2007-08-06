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

#include "curlaccountdelete.h"

#include "globaluri.h"
#include "hashpassword.h"
#include "xmlaccountlist.h"

/** The default constructor 
  *
  */
RainbruRPG::Network::Ident::CurlAccountDelete::CurlAccountDelete()
                                          :CurlSubmitForm(){

  GlobalURI g;

  xml=new xmlAccountList();
  this->filename=g.getAdminAdress("deleteplayer.php");;
  // Setting the posted data key values
  postedData.addKey("name");

}


/** The default destructor 
  *
  */
RainbruRPG::Network::Ident::CurlAccountDelete::~CurlAccountDelete(){
  xml->~xmlAccountList();
  xml=NULL;
}

/** Test the posted data before submit the deleted player
  *
  * It tests if the name is not empty and if an account with this name exists
  *
  * \return \c true if the form can be submitted
  */
bool RainbruRPG::Network::Ident::CurlAccountDelete::controlBefore(){
  bool ret=true;

  const char* name=postedData.getValue("name");
  const char* errmsg;

  // The name is empty
  if (strlen(name)==0){
    errmsg="The player's name is empty";
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
  }



  // The player does not exists
  if (!xml->isAccountExisting(name)){
    errmsg="The player does not exists";
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);

    ret=false;

  }

  return ret;
}

/** Controls if the account was correctly deleted
  *
  * \return \c true if the account was deleted
  *
  */
bool RainbruRPG::Network::Ident::CurlAccountDelete::controlAfter(){
  xml->refresh();
  bool ret=true;
  const char* errmsg;

  // Get the values
  const char* name=postedData.getValue("name");

  tAccountListItem *it=xml->getAccount(name);

  if (it){
    errmsg="The player exists";
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
  }


  return ret;
}

/** Set the account's name
  *
  * \param c The name
  *
  */
void RainbruRPG::Network::Ident::CurlAccountDelete::setName(const char* c){
  this->setPostedData("name", c);

}

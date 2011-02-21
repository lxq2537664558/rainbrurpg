/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file curlaccountadd.cpp
  * Implements the account addition
  *
  */

#include "curlaccountadd.h"

#include "xmlaccountlist.h"
#include "hashpassword.h"
#include "globaluri.h"

/** The default contructor
  *
  */
RainbruRPG::Network::Ident::CurlAccountAdd::CurlAccountAdd()
                                          :CurlSubmitForm(){

  response=CAA_UNDEFINED;

  GlobalURI g;

  xml=new xmlAccountList();
  this->filename=g.getAdminAdress("addplayer.php");
  // Setting the posted data key values
  postedData.addKey("name");
  postedData.addKey("pwd");
  postedData.addKey("timestamp");
  postedData.addKey("mail");

}

/** The default destructor 
  *
  */
RainbruRPG::Network::Ident::CurlAccountAdd::~CurlAccountAdd(){
  xml->~xmlAccountList();
  xml=NULL;
}

/** Test the posted data before submit the added player
  *
  * The most relevant error must be tested last.
  *
  * \return \c true if the operation is successfull, \c false if it failed
  */
bool RainbruRPG::Network::Ident::CurlAccountAdd::controlBefore(){
  bool ret=true;

  const char* name=postedData.getValue("name");
  const char* pwd=postedData.getValue("pwd");
  const char* mail=postedData.getValue("mail");
  const char* errmsg;

  // The . sign
  const char* dotSign=strchr(mail, '.');
  if (dotSign==NULL){
    errmsg=_("The email adress does not contain the 'dot' sign");
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
    response=CAA_MAIL_SIGN_DOT;
  }

  // The @ sign
  const char* atSign=strchr(mail, '@');
  if (atSign==NULL){
    errmsg=_("The email adress does not contain the 'at' sign");
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
    response=CAA_MAIL_SIGN_AT;
  }

  // The mail is empty
  if (strlen(mail)==0){
    errmsg=_("Cannot add a player with empty email adress");
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
    response=CAA_EMPTY_MAIL;
  }

  // The mail already in use
  if (xml->isMailExisting(mail)){
    errmsg=_("This mail adress is already in use");
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
    response=CAA_MAIL_INUSE;
  }

  // The player already exists
  if (xml->isAccountExisting(name)){
    errmsg=_("The player already exists");
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);

    ret=false;
    response=CAA_EXISTS;
  }

  // The password is empty
  if (strlen(pwd)==0){
    errmsg=_("Cannot add a player with empty password");
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
    response=CAA_EMPTY_PWD;
  }

  // The name is empty
  if (strlen(name)==0){
    errmsg=_("The new player's name is empty");
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
    response=CAA_EMPTY_NAME;
  }

  postedData.setTimestamp("timestamp");

  if (ret){
    response=CAA_SUCCESS;
  }

  return ret;
}

/** Controls if the operation was correctly done
  *
  * \return \c true if the accound was correctly added
  *
  */
bool RainbruRPG::Network::Ident::CurlAccountAdd::controlAfter(){
  xml->refresh();
  bool ret=true;
 
  // Get the values
  const char* name=postedData.getValue("name");
  const char* pwd=postedData.getValue("pwd");
  const char* mail=postedData.getValue("mail");

  tAccountListItem *it=xml->getAccount(name);
  if (it){
    const char* itname= it->name;
    const char* itpwd= it->password;
    const char* itmail= it->mail;
    
    // control Name
    if ((strlen(name)==0)||(strlen(itname)==0)){
      LOGW(_("One of the name is empty, controlAfter failed"));
      ret=false;
      
    }
    else{
      if (strcmp(name, itname)==0){
	LOGI(_("The name is the same"));
      }
      else{
	LOGW(_("The name is not the same"));
	ret=false;
	response=CAA_UNKNOWN;
      }
      
      // control Password
      
      HashPassword hp;
      bool retpwd=hp.compare(pwd, itpwd);
      if (retpwd){
	LOGI(_("The password is the same"));
      }
      else{
	LOGW(_("The password is not the same"));
	LOGW(pwd);
	LOGW(itpwd);
	
	ret=false;
	response=CAA_UNKNOWN;
      }
      
      // control Mail
      if (strcmp(mail, itmail)==0){
	LOGI(_("The mail adress is the same"));
      }
      else{
	LOGW(_("The mail adress is not the same"));
	ret=false;
	response=CAA_UNKNOWN;
      }
    }
  }
  else{
    // it==NULL, an error occured
    ret=false;
  }

  return ret;
}

/** Set the account's name
  *
  * \param c The name
  *
  */
void RainbruRPG::Network::Ident::CurlAccountAdd::setName(const char* c){
  this->setPostedData("name", c);
}

/** Set the account's password
  *
  * The password is set in its clear form. This function will itself
  * create the hashsum. It may be the user's entered password.
  *
  * \param c The password
  *
  */
void RainbruRPG::Network::Ident::CurlAccountAdd::setPassword(const char* c){
  this->setPostedPwd("pwd", c);
}

/** Set the account's mail address
  *
  * \param c The mail adress
  *
  */
void RainbruRPG::Network::Ident::CurlAccountAdd::setMail(const char* c){
  this->setPostedData("mail", c);
}

/** Get the current response
  *
  * \return The response
  *
  */
RainbruRPG::Network::Ident::tCurlAccountAddReturn 
RainbruRPG::Network::Ident::CurlAccountAdd::
getResponse(){
  return this->response;
}

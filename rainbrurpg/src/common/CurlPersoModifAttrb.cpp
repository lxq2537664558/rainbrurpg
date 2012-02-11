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

/** \file curlpersomodifattrb.cpp
  * Implements how to submit an attribute modification
  *
  */
#include "CurlPersoModifAttrb.hpp"

/** The default constructor 
  *
  */
RainbruRPG::Network::CurlPersoModifAttrb::CurlPersoModifAttrb()
                                          :CurlSubmitForm(){

  GlobalURI g;

  xml=new xmlPersoList();
  this->filename=g.getAdminAdress("modifpersoattrb.php");
  LOGI(this->filename.c_str());
  // Setting the posted data key values
  postedData.addKey("id");
  postedData.addKey("cat");
}

/** The default destructor
  *  
  */
RainbruRPG::Network::CurlPersoModifAttrb::~CurlPersoModifAttrb(){
  xml->~xmlPersoList();
  xml=NULL;
}

/** Test the posted data before submit the added player
  *
  * \return \c true if all the test are successfull
  *
  */
bool RainbruRPG::Network::CurlPersoModifAttrb::controlBefore(){
  bool ret=true;

  //  const char* name=postedData.getValue("name");
  //  const char* pwd=postedData.getValue("id");
  //  const char* errmsg;

  // The . sign
  /* char* dotSign=strchr(mail, '.');
  if (dotSign==NULL){
    errmsg="The email adress does not contain the 'dot' sign";
    setCustomErrorMessage(errmsg);
    LOGW(errmsg);
    ret=false;
  }
  */

  return ret;
}

/** Test the operation result
  *
  * \return \c true if all the test are successfull
  *
  */
bool RainbruRPG::Network::CurlPersoModifAttrb::controlAfter(){
  /*  xml->refresh();
  bool ret=true;
 
  // Get the values
  const char* name=postedData.getValue("name");
  const char* pwd=postedData.getValue("pwd");
  const char* mail=postedData.getValue("mail");

  tPlayerListItem *it=xml->getPlayer(name);
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
      LOGI(_("The name is the same"));
    }
    else{
      LOGW(_("The name is not the same"));
      ret=false;
    }

  // control Password

    HashPassword hp;
    bool retpwd=hp.compare(pwd, itpwd);
    if (retpwd){
      LOGI(_("The password is the same"));
    }
    else{
      LOGW(_("The password is not the same"));
      
      ret=false;
    }

    // control Mail
    if (strcmp(mail, itmail)==0){
      LOGI(_("The mail adress is the same"));
    }
    else{
      LOGW(_("The mail adress is not the same"));
      ret=false;
    }
  }


  return ret;
  */
  return true;
}

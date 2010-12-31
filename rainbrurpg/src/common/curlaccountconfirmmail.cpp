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

/** \file curlaccountconfirmmail.cpp
  * Implements the confirmation of a account's mail address
  *
  */

#include "curlaccountconfirmmail.h"

#include "xmlaccountlist.h"
#include "globaluri.h"

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

  // Confirmation Id sent in the account creation confirmation mail
  postedData.addKey("id");
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
  * This automatically set the confirmId used in confirmation mail.
  *
  * \param c The account's name
  *
  */
void RainbruRPG::Network::Ident::CurlAccountConfirmMail::
setName(const std::string& c){
  this->setPostedData("name", c.c_str());

  // Get the confirmId value
  RainbruRPG::Gui::tAccountListItem* it=xml->getAccount(c.c_str());
  if (it){
    std::string val=it->validationId;
    this->setPostedData("id", val.c_str());

    GTS_LIT(err);
    // TRANSLATORS: The first parameter is the account name, the second
    // is the validationId used in the confirmation mail in string format.
    sprintf(err, _("ValidationId for account '%s' is %s"), c.c_str(), 
	    val.c_str());
    LOGI(err);
  }
  else{
    GTS_LIT(err);
    // TRANSLATORS: The parameter is the name of a account.
    sprintf(err, _("Cannot get the account with the name '%s'"), c.c_str());
    LOGE(err);
  }
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
  bool ret=true;

  const char* accountName=this->getName();

  // Testing if the mail address was confirmed
  xml->refresh();
  RainbruRPG::Gui::tAccountListItem* it=xml->getAccount(accountName);
  if (it){
    std::string conf(it->confirm);

    GTS_LIT(err);
    // TRANSLATORS: The parameter should be a date if the account
    // was confirmed.
    sprintf(err, _("Mail's confirm date is %s"), it->confirm.c_str());
    LOGI(err);

    // If tAccountListItem.confirm is empty, the mail was not confirmed
    if (conf.size()==0){
      ret=false;
      // TRANSLATORS: controlAfter() is the name of a function.
      // Do not translate it.
      LOGE(_("controlAfter() : confirm timestamp is empty"));
    }
  }
  else{
    ret=false;
    // TRANSLATORS: controlAfter() is the name of a function.
    // Do not translate it.
    LOGE(_("controlAfter() : account not found"));

  }

  return ret;}

/** Get the name 
  *
  * \return the name of the account to confirm mail
  *
  */
const char* RainbruRPG::Network::Ident::CurlAccountConfirmMail::getName(){
  return postedData.getValue("name");

}

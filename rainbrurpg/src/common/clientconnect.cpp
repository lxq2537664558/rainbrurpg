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

/** \file clientconnect.cpp
  * Implements the client connection ability
  *
  */

#include "clientconnect.h"

using namespace RainbruRPG::Gui;

/** A default constructor
  *
  * It sets the default value of response to CCR_UNKNOWN_ERROR.
  *
  */
RainbruRPG::Network::Ident::ClientConnect::ClientConnect(){
  response=CCR_UNKNOWN_ERROR;	
}


/** Try the connection of this user user with the given password
  *
  * \param user The account name of the user
  * \param pwd The password of the user
  */
RainbruRPG::Network::Ident::ClientConnect::ClientConnect(const char* user, 
							 const char* pwd){

  this->response=connect(user, pwd);

}


/** Get the last connection response
  *
  * \return The response in a tClientConnectReturn way
  */
RainbruRPG::Network::Ident::tClientConnectReturn 
RainbruRPG::Network::Ident::ClientConnect::getResponse(){
  return response;
}

/** Try the connection of this user user with the given password
  *
  * The order of testing is CCR_INEXISTANT_USER, CCR_EMAIL_NOT_VALIDATED, 
  * CCR_BLACKLIST, CCR_WRONG_PWD.
  *
  * \param user The account name of the user
  * \param pwd The password of the user
  *
  * \return The connection status
  *
  * \sa tClientConnectReturn
  *
  */
RainbruRPG::Network::Ident::tClientConnectReturn
RainbruRPG::Network::Ident::ClientConnect::
connect(const char* user, const char* pwd){

  tClientConnectReturn ret;

  xmlAccountList xml;

  // Test if this user exists
  bool userExist=xml.isAccountExisting(user);
  if (!userExist){
    ret=CCR_INEXISTANT_USER;
  }
  else{
    RainbruRPG::Gui::tAccountListItem* player=xml.getAccount(user);

    LOGCATS(_("Account blacklist status : "));
    LOGCATB(player->blacklist);
    LOGCAT();


    // Test the email confirmation status
    if (player->confirm.empty()){
      ret=CCR_EMAIL_NOT_VALIDATED;
    }
    else{

      // Test the blacklist status
      if(player->blacklist){
	ret=CCR_BLACKLIST;
      }
      else{
	// Test the password
	HashPassword hp;
	string hash=hp.encryptString(pwd);
	bool conn=hp.compare(player->password, hash.c_str());
	if (conn){
	  ret=CCR_SUCCESS;
	}
	else{
	  ret=CCR_WRONG_PWD;
	}
      }
    }
  }

  return ret;
}

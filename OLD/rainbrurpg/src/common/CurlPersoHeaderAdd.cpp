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

/** \file curlpersoheaderadd.cpp
  * Implements the  'add perso header' request
  *
  */
#include "CurlPersoHeaderAdd.hpp"

/** The default constructor
  *
  * It sets the admin adress to addperso.php and create 3 posted data keys :
  * player, id, timestamp.
  *
  */
RainbruRPG::Network::CurlPersoHeaderAdd::CurlPersoHeaderAdd()
                                          :CurlSubmitForm(){

  this->persoName="";

  GlobalURI g;

  xml=new xmlPersoList();
  this->filename=g.getAdminAdress("addperso.php");
  LOGI(this->filename.c_str());
  // Setting the posted data key values
  postedData.addKey("player");
  postedData.addKey("id");
  postedData.addKey("timestamp");
}

/** The default destructor
  *
  *
  */
RainbruRPG::Network::CurlPersoHeaderAdd::~CurlPersoHeaderAdd(){
  xml->~xmlPersoList();
  xml=NULL;
}

/** Test the posted data before submit the added player
  *
  * \return \c true if the control was successfull, otherwise false.
  */
bool RainbruRPG::Network::CurlPersoHeaderAdd::controlBefore(){
  bool ret=true;

  postedData.setTimestamp("timestamp");
  const char* id=xml->getNextId();
  this->setPostedData ("id", id);

  return ret;
}

/** Performs some test after the form was submited
  *
  * \return \c true if the control was successfull, otherwise false.
  */
bool RainbruRPG::Network::CurlPersoHeaderAdd::controlAfter(){
  return true;
}

/** Sets the player name that will be posted
  *
  * It is the name of the perso (character) that will be deleted.
  *
  * \param name The perso name
  *
  */
void RainbruRPG::Network::CurlPersoHeaderAdd::setName(const std::string& name){
  this->persoName=name;
  postedData.setValue("player", name);
}

/** Get the player name that will be posted
  *
  * It is the name of the perso (character) that will be deleted.
  *
  * \return The perso name
  *
  */
const std::string& RainbruRPG::Network::CurlPersoHeaderAdd::getName(void){
  return this->persoName;
}

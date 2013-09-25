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

/** \file curlpersoheaderdelete.cpp
  * Implements the 'delete perso header' request
  *
  */

#include "CurlPersoHeaderDelete.hpp"

/** The default constructor
  *
  * It sets the admin adress to addperso.php and create 3 posted data keys :
  * player, id, timestamp.
  *
  */
RainbruRPG::Network::CurlPersoHeaderDelete::CurlPersoHeaderDelete()
                                          :CurlSubmitForm(){

  persoName="";

  GlobalURI g;

  xml=new xmlPersoList();
  this->filename=g.getAdminAdress("deleteperso.php");
  LOGI(this->filename.c_str());
  // Setting the posted data key values
  postedData.addKey("player");
}

/** The default destructor
  *
  *
  */
RainbruRPG::Network::CurlPersoHeaderDelete::~CurlPersoHeaderDelete(){
  xml->~xmlPersoList();
  xml=NULL;
}

/** Test the posted data before submit the added player
  *
  * \return \c true if the control was successfull, otherwise false.
  */
bool RainbruRPG::Network::CurlPersoHeaderDelete::controlBefore(){
  bool ret=true;


  return ret;
}

/** Performs some test after the form was submited
  *
  * \return \c true if the control was successfull, otherwise false.
  */
bool RainbruRPG::Network::CurlPersoHeaderDelete::controlAfter(){

  return true;
}

/** Sets the player name that will be posted
  *
  * It is the name of the perso (character) that will be deleted.
  *
  * \param name The perso name
  *
  */
void RainbruRPG::Network::CurlPersoHeaderDelete::
setName(const std::string& name){
  postedData.setValue("player", name);
}

/** Get the player name that will be posted
  *
  * It is the name of the perso (character) that will be deleted.
  *
  * \return The perso name
  *
  */
const std::string& RainbruRPG::Network::CurlPersoHeaderDelete::getName(void){
  return this->persoName;
}

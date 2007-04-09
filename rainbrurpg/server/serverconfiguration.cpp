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

#include "serverconfiguration.h"

/** The default constructor 
  *
  */
RainbruRPG::Server::ServerConfiguration::ServerConfiguration(){
  name="Unnamed server";
  description="";
  techNote="";
  ipAdress="";
  playMode=false;
  editMode=false;
  floodMode=false;
  port=1234;
  maxClient=20;
}

/** Change the name of this server
  *
  * \param n The new name
  *
  */
void RainbruRPG::Server::ServerConfiguration::setName(const std::string& n){
  name=n;
}

/** Change the description
  *
  * \param d The new description
  *
  */
void RainbruRPG::Server::ServerConfiguration::setDesc(const std::string& d){
  description=d;
}

/** Change the technical note
  *
  * \param t The new technical note
  *
  */
void RainbruRPG::Server::ServerConfiguration::
setTechNote(const std::string& t){
  techNote=t;
}

/** Is this server accept the play mode ?
  *
  * \param b The new play mode value
  *
  */
void RainbruRPG::Server::ServerConfiguration::setPlayMode(bool b){
  playMode=b;
}

/** Is this server accept the edit mode ?
  *
  * \param b the new editMode value
  *
  */
void RainbruRPG::Server::ServerConfiguration::setEditMode(bool b){
  editMode=b;
}

/** Is this server accept the flood mode ?
  *
  * \param b The new floodMode value
  *
  */
void RainbruRPG::Server::ServerConfiguration::setFloodMode(bool b){
  floodMode=b;
}

/** Set the port of this server
  *
  * \param i The new port
  *
  */
void RainbruRPG::Server::ServerConfiguration::setPort(int i){
  port=i;
}

/** Set the maximum clients accepted
  *
  * \param i The new clients number
  *
  */
void RainbruRPG::Server::ServerConfiguration::setMaxClient(int i){
  maxClient=i;
}

/** Get the server's name
  *
  * \return The name
  *
  */
const std::string& RainbruRPG::Server::ServerConfiguration::getName()const{
  return name;
}

/** Get the server description
  *
  * \return The description
  *
  */
const std::string& RainbruRPG::Server::ServerConfiguration::getDesc()const{
  return description;
}

/** Get the technical note
  *
  * \return The technical note
  *
  */
const std::string& RainbruRPG::Server::ServerConfiguration::getTechNote()const{
  return techNote;
}

/** Get the play mode status
  *
  * \return The playMode status
  *
  */
bool RainbruRPG::Server::ServerConfiguration::getPlayMode(){
  return playMode;
}

/** Get the edit mode status
  *
  * \return The editMode status
  *
  */
bool RainbruRPG::Server::ServerConfiguration::getEditMode(){
  return editMode;
}

/** Get the flood mode status
  *
  * \return The floodMode status
  *
  */
bool RainbruRPG::Server::ServerConfiguration::getFloodMode(){
  return floodMode;
}

/** Get the port used by this server
  *
  * \return The port this server use
  *
  */
int RainbruRPG::Server::ServerConfiguration::getPort(){
  return port;
}

/** Get the maximum number of clients accepted
  *
  * \return The maxClient value
  *
  */
int RainbruRPG::Server::ServerConfiguration::getMaxClient(){
  return maxClient;
}

/** Set the Ip adress of the server
  *
  * \param s The ip adress
  *
  */
void RainbruRPG::Server::ServerConfiguration::
setIpAdress(const std::string& s){
  ipAdress=s;
}

/** Get the ip adress
  *
  * \return ipAdress;
  *
  */
const std::string& RainbruRPG::Server::ServerConfiguration::getIpAdress()const{
  return ipAdress;
}
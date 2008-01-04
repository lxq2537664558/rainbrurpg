/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

#include "serverlistitem.h"

#include "stringconv.h"

/** The default constructor
  *
  * It initialize type to SERVER_TYPE_INITIAL_VALUE (a define macro) and
  * maxClients and actClients to 0.
  *
  */
RainbruRPG::Network::Ident::ServerListItem::ServerListItem(){
  this->type=SERVER_TYPE_INITIAL_VALUE;     
  this->maxClients=0;
  this->actClients=0;
}

/** The destructor
  *
  */
RainbruRPG::Network::Ident::ServerListItem::~ServerListItem(){

}

/** Change the creation date
  *
  * This date should come from the admin site XML file. It is in the 
  * C date/time format.
  *
  * \param date The date comming from the XML file
  *
  * \sa getCreationDate(), creation (member).
  *
  */
void RainbruRPG::Network::Ident::ServerListItem::
setCreationDate(const std::string& date){
  this->creation=date;
}

/** Change the name of this server list item
  *
  * This name comes from the admin site XML file. It should not
  * be empty.
  *
  * \param n The name from comming from the XML file
  *
  * \sa getName(), name (member).
  *
  */
void RainbruRPG::Network::Ident::ServerListItem::
setName(const std::string& n){
  this->name=n;
}

/** Change the uniqueName of this server list item
  *
  * This name comes from the admin site XML site. Please see the 
  * \ref RainbruRPG::Server::UniqueName "UniqueName" class documentation
  * for more informations on unique name.
  *
  * \param n The unique name from comming from the XML file
  *
  * \sa \ref RainbruRPG::Server::UniqueName "UniqueName" (class),
  *     getUniqueName(), uniqueName (member).
  *
  */
void RainbruRPG::Network::Ident::ServerListItem::
setUniqueName(const std::string& n){
  this->uniqueName=n;
}

/** Change the description of this server
  *
  * This value comes from the admin site XML site.
  *
  * \param d The description test
  *
  * \sa getDescription(), description (member).
  *
  */
void RainbruRPG::Network::Ident::ServerListItem::
setDescription(const std::string& d){
  this->description=d;
}

/** Change the IP address of this server
  *
  * This value comes from the admin site XML site. It is a text
  * in the format X.Y.Z.W where each number can be between 0 and 255.
  * No tests are performed here to control if it is valid.
  * 
  * \param ip The new IP address
  *
  * \sa getIpAddress(), ipAddress (member).
  *
  */
void RainbruRPG::Network::Ident::ServerListItem::
setIpAddress(const std::string& ip){
  this->ipAddress=ip;
}

/** Change the UDP port
  *
  * This value comes from the admin site XML site. The UDP port is used
  * for in-game, action based connections.
  * 
  * \param udp The new UDP port
  *
  * \sa getUdpPort(), udpPort (member).
  *
  */
void RainbruRPG::Network::Ident::ServerListItem::
setUdpPort(const std::string& udp){
  this->udpPort=StringConv::getSingleton().stoi(udp);
}

/** Change the FTP control channel port
  *
  * This value comes from the admin site XML site. The FTP control channel
  * is used to contact the Server's FTP server. A FTP server opens two
  * ports : the control channel where you send commands (STOR, RETR...)
  * and a data channel where files are transfered.
  * 
  * \param ftp The new FTP control channel
  *
  * \sa getFtpPort(), ftpPort (member).
  *
  */
void RainbruRPG::Network::Ident::ServerListItem::
setFtpPort(const std::string& ftp){
  this->ftpPort=StringConv::getSingleton().stoi(ftp);
}

/** Set the technical note of this server
  *
  * This value comes from the admin site XML site. This text can be empty.
  * If it is, it will not be shown on the client screen.
  *
  * \param tn The new technical note
  *
  * \sa getTechNote(), techNote (member).
  *
  */
void RainbruRPG::Network::Ident::ServerListItem::
setTechNote(const std::string& tn){
  this->techNote=tn;
}

/** Change the maximum allowed clients for this server
  *
  * If this number of client is reached, no more client will be
  * accepted.
  *
  * \param mc The new maxClients value.
  *
  * \sa getMaxClientsStr(), getOccupationStr().
  *
  */
void RainbruRPG::Network::Ident::ServerListItem::
setMaxClients(const std::string& mc){
  this->maxClients=StringConv::getSingleton().stoi(mc);
}

/** Change the number of clients actually connected on this server
  *
  * This value comes from the Admin website.
  *
  * \param ac The actClients value
  *
  * \sa getActClientsStr(), getOccupationStr().
  *
  */
void RainbruRPG::Network::Ident::ServerListItem::
setActClients(const std::string& ac){
  this->actClients=StringConv::getSingleton().stoi(ac);
}

/** Change the server's type
  *
  * \param t The type
  *
  * \sa type, getTypeStr().
  *
  */
void RainbruRPG::Network::Ident::ServerListItem::
setType(const std::string& t){
  this->type=StringConv::getSingleton().stoi(t);
}

/** Get the name of this server list item
  *
  * This name comes from the admin site XML file. It should not
  * be empty.
  *
  * \return The name from comming from the XML file
  *
  * \sa setName(), name (member).
  *
  */
const std::string& RainbruRPG::Network::Ident::ServerListItem::
getName(){
  return this->name;
}

/** Return the maximum allowed clients for this server in text format
  *
  * If this number of client is reached, no more client will be
  * accepted.
  *
  * \return The maxClients value.
  *
  * \sa setMaxClients(), getOccupationStr(), maxClients (member).
  *
  */
std::string RainbruRPG::Network::Ident::ServerListItem::getMaxClientsStr(){
  return StringConv::getSingleton().itos(this->maxClients);
}

/** Return the number of clients actually connected on this server
  *
  * This value comes from the Admin website.
  *
  * \return The actClients value in text format.
  *
  * \sa setActClients(), getOccupationStr(), actClients (member).
  *
  */
std::string RainbruRPG::Network::Ident::ServerListItem::getActClientsStr(){
  return StringConv::getSingleton().itos(this->actClients);
}

/** Get the server's type
  *
  * \return The type
  *
  * \sa type, getTypeStr().
  *
  */
unsigned int RainbruRPG::Network::Ident::ServerListItem::getType(){
  return this->type;
}

/** Returns a string that describe the current type
  *
  * It returns a string as follow :
  * - The type number
  * - in parenthesys, the type in string format
  *
  * Example : <pre>1 (Fantasy)</pre> or <pre>2 (Contemporary)</pre>
  *
  * \return The type in string format
  *
  * \sa type (member), setType(), getType().
  *
  */
std::string RainbruRPG::Network::Ident::ServerListItem::getTypeStr(){
  std::string itemTypeText;
  switch (this->type){
  case 1:
    itemTypeText="1 (Fantasy)";
    break;
  case 2:
    itemTypeText="2 (Contemporary)";
    break;
  case 3:
    itemTypeText="3 (Futuristic)";
    break;
  case 4:
    itemTypeText="4 (Post-apocalyptic)";
    break;
  default:
    itemTypeText="ERROR";
    break;
  }

  return itemTypeText;
}

/** Get the occupation of this server in string format
  *
  * If the maxClients value is 20 and actClients is 15, it will
  * return \c 15/20.
  *
  * \return The occupation string
  *
  * \sa getActClientsStr(),getMaxClientsStr().
  *
  */
std::string RainbruRPG::Network::Ident::ServerListItem::getOccupationStr(){
  std::string occ;
  occ=this->getActClientsStr();
  occ+="/";
  occ+=this->getMaxClientsStr();
  return occ;
}

/** Get the IP address
  *
  * \return the IP address in the form \e x.y.z.w 
  *
  * \sa setIpAddress(), ipAddress (member).
  *
  */
std::string RainbruRPG::Network::Ident::ServerListItem::getIpAddress(){
  return this->ipAddress;
}

/** Returns the creation date/time
  *
  * \return The creation date/time as a C format string
  *
  * \sa setCreationDate(), creation (member)
  *
  */
const std::string& RainbruRPG::Network::Ident::ServerListItem::
getCreationDate(){
  return this->creation;
}

/** Gets the uniqueName of this server list item
  *
  * This name comes from the admin site XML site. Please see the 
  * \ref RainbruRPG::Server::UniqueName "UniqueName" class documentation
  * for more informations on unique name.
  *
  * \return The unique name from comming from the XML file
  *
  * \sa \ref RainbruRPG::Server::UniqueName "UniqueName", setUniqueName,
  *     uniqueName (member).
  *
  */
const std::string& RainbruRPG::Network::Ident::ServerListItem::
getUniqueName(){
  return this->uniqueName;
}

/** Get the number of clients actually connected on this server
  *
  * This value comes from the Admin website.
  *
  * \return The actClients value
  *
  * \sa getActClientsStr(), getOccupationStr(), actClients (member).
  *
  */
unsigned int RainbruRPG::Network::Ident::ServerListItem::getActClients(){
  return this->actClients;
}

/** Get the maximum allowed clients for this server
  *
  * If this number of client is reached, no more client will be
  * accepted.
  *
  * \return The new maxClients value.
  *
  * \sa getMaxClientsStr(), getOccupationStr(), maxClients (member).
  *
  */
unsigned int RainbruRPG::Network::Ident::ServerListItem::getMaxClients(){
  return this->maxClients;
}

/** Get the description of this server
  *
  * This value comes from the admin site XML site.
  *
  * \return The description test
  *
  * \sa setDescription(), description (member).
  *
  */
const std::string& RainbruRPG::Network::Ident::ServerListItem::
getDescription(){
  return this->description;
}

/** Get the technical note of this server
  *
  * This value comes from the admin site XML site. This text can be empty.
  * If it is, it will not be shown on the client screen.
  *
  * \return The new technical note
  *
  * \sa setTechNote(), techNote (member).
  *
  */
const std::string& RainbruRPG::Network::Ident::ServerListItem::getTechNote(){
  return this->techNote;
}

/** Get the UDP port
  *
  * This value comes from the admin site XML site. The UDP port is used
  * for in-game, action based connections.
  * 
  * \return The UDP port
  *
  * \sa setUdpPort(), getUdpPortStr(), udpPort (member).
  *
  */
int RainbruRPG::Network::Ident::ServerListItem::getUdpPort(){
  return this->udpPort;
}

/** Get the FTP control channel port
  *
  * This value comes from the admin site XML site. The FTP control channel
  * is used to contact the Server's FTP server. A FTP server opens two
  * ports : the control channel where you send commands (STOR, RETR...)
  * and a data channel where files are transfered.
  * 
  * \return ftp The FTP control channel
  *
  * \sa setFtpPort(), getFtpPortStr(), ftpPort (member).
  *
  */
int RainbruRPG::Network::Ident::ServerListItem::getFtpPort(){
  return this->ftpPort;
}

/** Get the UDP port in string format
  *
  * This value comes from the admin site XML site. The UDP port is used
  * for in-game, action based connections.
  * 
  * \return The UDP port in string format port
  *
  * \sa setUdpPort(), getUdpPortStr(), udpPort (member).
  *
  */
std::string RainbruRPG::Network::Ident::ServerListItem::getUdpPortStr(){
  return StringConv::getSingleton().itos(this->getUdpPort());
}

/** Get the FTP control channel port in string format
  *
  * This value comes from the admin site XML site. The FTP control channel
  * is used to contact the Server's FTP server. A FTP server opens two
  * ports : the control channel where you send commands (STOR, RETR...)
  * and a data channel where files are transfered.
  * 
  * \return ftp The FTP control channel port in string format
  *
  * \sa setFtpPort(), getFtpPort(), ftpPort (member).
  *
  */
std::string RainbruRPG::Network::Ident::ServerListItem::getFtpPortStr(){
  return StringConv::getSingleton().itos(this->getFtpPort());
}

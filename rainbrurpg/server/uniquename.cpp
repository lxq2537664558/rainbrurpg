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

#include "uniquename.h"

#include <logger.h>

/** Get the unique name of this server
  *
  * \return A std::string that contains the name or \c "" if not found
  *
  */
std::string RainbruRPG::Server::UniqueName::getUniqueName(void){
  std::string svr="svr";
  std::string mac=getMacAddress("eth0");
  svr+=mac;

  if (mac==""){
    LOGE("Cannot found mac address for eth0");
    return "";
  }
  else{
    LOGCATS("Server's unique name is ");
    LOGCATS(svr.c_str());
    LOGCAT();
    return svr;
  }
}

/** Get the MAC address of a given network interface
  *
  * \param itName The network interface you want the MAC address for
  *
  * \return A std::string that contains the MAC address or \c "" if not found
  *
  */
std::string RainbruRPG::Server::UniqueName::
getMacAddress(const std::string& itName){

  int descSock;
  struct sockaddr_in *sa;
  struct ifreq devea;
  char macBuffer[12];
  bool found=false;

  LOGI("Searching eth0 network interface");
  struct if_nameindex *nameindex = if_nameindex();
  if(nameindex == NULL){
    LOGE("Cannot get nerwork interface list");
  }

  int i = 0;
  while(1){
    // If there is no more interface, it exit the while 
    if(nameindex[i].if_name == NULL) break;
    // Copying card name in the devea structure
    strcpy(devea.ifr_name, nameindex[i++].if_name);
    // We open a socket for each card
    descSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (descSock < 0){
      perror("socket ");
      // We can free() the pointer allocated by if_nameindex
      if_freenameindex(nameindex);
    }
    
    if (strcmp(devea.ifr_name, itName.c_str())==0){
      // We get the MAC address
      if (ioctl(descSock,SIOCGIFHWADDR, &devea) < 0){
	LOGE("Cannot get the MAC address");
      }
      else{
	// Wa set the MAC address in a buffer
	sprintf(macBuffer, "%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X",
		(devea.ifr_hwaddr.sa_data[0]&0xFF),
		(devea.ifr_hwaddr.sa_data[1]&0xFF),
		(devea.ifr_hwaddr.sa_data[2]&0xFF),
		(devea.ifr_hwaddr.sa_data[3]&0xFF),
		(devea.ifr_hwaddr.sa_data[4]&0xFF),
		(devea.ifr_hwaddr.sa_data[5]&0xFF));
	found=true;
      }
      
      // Close the socket
      close(descSock);
    }
  }
  if(i == 0){
    LOGW("No network interface was found");
  }

  //Relache le pointeur dynamiquement alloue par if_nameindex
  if_freenameindex(nameindex);

  std::string ret(macBuffer);

  if (found){	
    return ret;
  }
  else{
    return "";
  }
}

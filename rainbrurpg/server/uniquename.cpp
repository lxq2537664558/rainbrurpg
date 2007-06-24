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

#include "uniquename.h"

#include <logger.h>

std::string RainbruRPG::Server::UniqueName::getUniqueName(void){
  getMacAddress();
}

std::string RainbruRPG::Server::UniqueName::getMacAddress(void){
  int descSock;
  struct sockaddr_in *sa;
  struct ifreq devea;

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
    //Affichage de celui-ci
    printf("%s\n", devea.ifr_name);
    //on ouvre un socket pour chacune des cartes que l'on closera après
    descSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (descSock < 0){
      perror("socket ");
      //On relache le pointeur dynamiquement alloue par if_nameindex
      if_freenameindex(nameindex);
      //      return errno;
    }
    
    //Récupération de la MAC adresse
    printf("\tMAC\t:\t");
    if (ioctl(descSock,SIOCGIFHWADDR, &devea) < 0)
      printf("ERROR\n");
    else{
      //Affichage de la mac adresse
      printf("%2.2X%2.2X%2.2X%2.2X%2.2X%2.2X\n\n",
	     (devea.ifr_hwaddr.sa_data[0]&0xFF),
	     (devea.ifr_hwaddr.sa_data[1]&0xFF),
	     (devea.ifr_hwaddr.sa_data[2]&0xFF),
	     (devea.ifr_hwaddr.sa_data[3]&0xFF),
	     (devea.ifr_hwaddr.sa_data[4]&0xFF),
	     (devea.ifr_hwaddr.sa_data[5]&0xFF));
    }
    
    //Ferme le socket pour passer au prochain
    close(descSock);
  }
  if(i == 0)//petit affichage pour le fun :D
    printf("Aucune carte disponible !!!\n");
  
  //Relache le pointeur dynamiquement alloue par if_nameindex
  if_freenameindex(nameindex);

}

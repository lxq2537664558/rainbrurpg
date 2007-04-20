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



#include "transfervisual.h"

/** The default constructor
  *
  */
RainbruRPG::Network::Ftp::TransferVisual::TransferVisual(){

}

/** The destructor
  *
  */
RainbruRPG::Network::Ftp::TransferVisual::~TransferVisual(){

}

/** Change the Ip adress of the host
  *
  * \param s The new IP adresss
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setIp(const QString& s){
  this->ip=s;
}

/** Return the Ip
  *
  * \return The Ip adress of the host
  *
  */
const QString& RainbruRPG::Network::Ftp::TransferVisual::getIp()const{
  return this->ip;
}

/** Set the file to be downloaded
  *
  * \param file The filename
  * \param path The absolute path containing the file (without the 
  *        ending slash)
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setFilename(const QString& file, const QString& path){
  this->filename=path;
  this->filename+="/";
  this->filename+=file;
}

/** Gets the absolute filename of the file
  *
  * \return The filename
  *
  */
const QString& RainbruRPG::Network::Ftp::TransferVisual::getFilename()const{
  return this->filename;
}

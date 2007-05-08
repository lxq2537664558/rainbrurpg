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

/** Change the transfer sense
  *
  * If the transfer is comming in, the server receive it, otherwise
  * the server send it.
  *
  * \param b Is the server receiving the file.
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setCommingIn(bool b){
  commingIn=b;
}

/** Set the download rate (Bytes/second)
  *
  * \param d The download rate
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setRate(double d){
  rate=d;
}

/** Set the file size in bytes
  *
  * \param i The file size
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setFileSize(int i){
  filesize=i;
}

/** Set the total downloaded bytes
  *
  * \param i The number of downloaded bytes
  *
  */
void RainbruRPG::Network::Ftp::TransferVisual::setDownloaded(int i){
  downloaded=i;
}

/** Get the transfer sense
  *
  * If the transfer is comming in, the server receive it, otherwise
  * the server send it.
  *
  * \return \c true if the server receiving the file or \c false if
  *         the file is sent.
  *
  */
bool RainbruRPG::Network::Ftp::TransferVisual::getCommingIn(){
  return commingIn;
}

/** Get the download rate (Bytes/second)
  *
  * \return The download rate
  *
  */
double RainbruRPG::Network::Ftp::TransferVisual::getRate(){
  return rate;
}

/** Get the file size in bytes
  *
  * \return The file size
  *
  */
int RainbruRPG::Network::Ftp::TransferVisual::getFileSize(){
  return filesize;
}

/** Get the total downloaded bytes
  *
  * \return The number of downloaded bytes
  *
  */
int RainbruRPG::Network::Ftp::TransferVisual::getDownloaded(){
  return downloaded;
}

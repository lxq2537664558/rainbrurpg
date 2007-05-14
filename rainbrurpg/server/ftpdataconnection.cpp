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

#include "ftpdataconnection.h"

/** Default constructor
  *
  */
RainbruRPG::Network::Ftp::FtpDataConnection::FtpDataConnection(){
  command=FTC_NONE;
  clientIp="";
  clientPort="";
}

/** Constructor
  *
  * \param ip The client IP address
  * \param port The client port
  * \param c The transfer command
  *
  */
RainbruRPG::Network::Ftp::FtpDataConnection::
FtpDataConnection(const QString& ip, const QString& port, tTransferCommand c){
  command=c;
  clientIp=ip;
  clientPort=port;
}

/** Destructor
  *
  */
RainbruRPG::Network::Ftp::FtpDataConnection::~FtpDataConnection(){

}

/** Is the connection is the same
  *
  * \param ip The IP address to test
  * \param port The port to test
  *
  * \return \c true if IP/port are the same
  *
  */
bool RainbruRPG::Network::Ftp::FtpDataConnection::
isThisConnection(const QString& ip, const QString& port){

  if (ip==clientIp && port==clientPort){
    return true;
  }
  else{
    return false;
  }
}

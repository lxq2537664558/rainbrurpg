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

#include "ftpclient.h"

/** The default constructor
  *
  */
RainbruRPG::Network::FtpClient::FtpClient(){

}

/** The destructor
  *
  */
RainbruRPG::Network::FtpClient::~FtpClient(){

}

/** Try to open a connection in the given host
  *
  * \param ip The ip adress of the host
  * \param port The port the host should listen
  *
  * \return \c true if the connection is successfull, \c false if an
  *         error occured
  *
  */
bool RainbruRPG::Network::FtpClient::
connectToHost(const std::string& ip, int port){

}

/** Send a string through the control channel
  *
  * The user should not use this function. It should use commandLIST 
  * and otrhers instead.
  *
  */
void RainbruRPG::Network::FtpClient::sendString(const std::string& s){

}

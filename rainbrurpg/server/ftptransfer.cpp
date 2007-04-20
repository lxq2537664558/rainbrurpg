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


#include "ftptransfer.h"

/** The constructor
  *
  * \param port The listening port
  *
  */
RainbruRPG::Network::Ftp::FtpTransfer::FtpTransfer(quint16 port) 
  :QThread() {
  this->port=port;
  currentDirectory="/home/mouse";

  descriptor=1;
  server=new QTcpServer();

}

/** The destructor
  *
  */
RainbruRPG::Network::Ftp::FtpTransfer::~FtpTransfer(){

}

/** Runs the thread
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::run (){
  QString s2;
  s2.setNum(port);
  QString s="Transfer channel now listening for new connections on port ";
  s+=s2;

  server->listen( QHostAddress::Any, port );
  emit(log(s));

}

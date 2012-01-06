/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file serverthread.cpp
  * Implements a thread that contains a Enet server
  *
  */

#include "serverthread.h"

#include <logger.h>

/** The default constructor
  *
  */
RainbruRPG::Server::ServerThread::ServerThread(){
  server=new EnetServer();

  // Simply redirect signals
  connect(server, SIGNAL(clientConnected(const ENetAddress &)),
	  this  , SIGNAL(clientConnected(const ENetAddress &)));

  connect(server, SIGNAL(packetReceived(const tReceivedPacket&)),
	  this  , SIGNAL(packetReceived(const tReceivedPacket&)));

}

/** The destructor
  *
  */
RainbruRPG::Server::ServerThread::~ServerThread(){
  delete server;
  server=NULL;
}

/** Change the server port
  *
  * \param i The new server's port
  *
  */
void RainbruRPG::Server::ServerThread::setPort(int i){
  server->setPort(i);
}

/** Change the server maxClient
  *
  * \param i The new server's maxClient value
  *
  */
void RainbruRPG::Server::ServerThread::setMaxClient(int i){
  server->setMaxClient(i);

}

/** Creates the server
  *
  */
void RainbruRPG::Server::ServerThread::createServer(){
  server->createServer();

}

/** Run the server
  *
  */
void RainbruRPG::Server::ServerThread::run(){
  while(true){
   server->eventLoop();
  }
}

/** Cleanup the server
  *
  */
void RainbruRPG::Server::ServerThread::cleanupServer(){
  server->cleanupServer();
}

/** Get the EnetServer instance
  *
  * \return The server instance currently used
  *
  */
EnetServer* RainbruRPG::Server::ServerThread::getServer(){
  return server;
}

/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file virtualserver.h
  * Declares a virtual server
  *
  * This file is used to define  some macro used to create a
  * virtual  server. This  informations are  shared by some
  * files  and  to  avoid  multiple definitions.  There  are
  * defined once, in this file.
  *
  * Modifications :
  * - 27 aug 2008 : Single file documentation
  * - 18 may 2007 : Basic implementation
  *
  */

#ifndef _VIRTUAL_SERVER_H_
#define _VIRTUAL_SERVER_H_

/** A name used to test the inexistance of a client
  *
  * I hope this server never exist but it will be created to test
  * some other responses.
  *
  */
#define SERVER_NAME "InexistantServerName_IHOPE"

/** The IP address of the inexistant server */
#define SERVER_IP "127.0.0.1"
/** The listening port of the inexistant server */
#define SERVER_PORT "50002"
/** The maxClients values of the inexistant server */
#define SERVER_MAX_CLIENTS "20"
/** The description of the inexistant server */
#define SERVER_DESC "Server description"
/** The technical note of the inexistant server */
#define SERVER_TECH_NOTE "Server technical note"

#endif // _VIRTUAL_SERVER_H_

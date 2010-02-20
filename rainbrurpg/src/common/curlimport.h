/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file curlimport.h
  * Import curl header with hack for win32
  *
  * Modifications :
  * - 04 oct 2008 : Starting implementation
  *
  */

#ifndef _CURL_IMPORT_H_
#define _CURL_IMPORT_H_

/*#ifdef __WIN32__
#  define _WS2TCPIP_H
#  define _WINSOCK2_H
#  define _WINSOCK_H
#  define _SYS_SELECT_H
#endif // __WIN32__
*/
#include <curl/curl.h>


#endif // _CURL_IMPORT_H_

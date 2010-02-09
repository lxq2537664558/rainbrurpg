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

/** \file uniquename.h
  * Declares a class used to get a unique server name
  *
  * Modifications :
  * - 05 sep 2008 : Single file documentation
  * - 24 jun 2007 : Starting implementation
  *
  */

#ifndef _UNIQUE_NAME_H_
#define _UNIQUE_NAME_H_

#include <string>

#include <sys/ioctl.h> // for ioctl
#include <net/if.h>    // for ifreq
#include <string.h>    // for strcpy
#include <unistd.h>    // for close
#include <arpa/inet.h> // for inet_ntoa
#include <stdio.h>     // for printf
#include <errno.h>     // for errno


using namespace std;

namespace RainbruRPG{
  namespace Server{

    /** A class used to get a unique server name
      *
      * The server need a unique name used when a client download files from 
      * it. The unique name is used as directory name.
      *
      * The unique name start with \c svr and is followed by the MAC address
      * of \c eth0 if this network interface if found.
      *
      */
    class UniqueName{
    public:
      static std::string getUniqueName(void);

    private:
      static std::string getMacAddress(const std::string&);

    };

  }
}

#endif // _UNIQUE_NAME_H_


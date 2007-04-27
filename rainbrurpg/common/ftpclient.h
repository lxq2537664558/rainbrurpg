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

/* Modifications :
 * - 27 apr 2007 : Starting implementation
 *
 */

#ifndef _FTP_CLIENT_H_
#define _FTP_CLIENT_H_

#include <string>

#include <gnet.h>

using namespace std;

namespace RainbruRPG {
  namespace Network{

    /** A class that implements the FTP protocol for client-side using
      *
      * This class is based on the GNet library (http://www.gnetlibrary.org/)
      * as a result, <b>before using it</b> you should call the \c gnet_init() 
      * function.  This function is found in the \c gnet.h header.
      *
      * It implements both the control and the data channel.
      *
      */
    class FtpClient{
    public:
      FtpClient();
      ~FtpClient();

      bool connectToHost(std::string, int );


    };

  }
}

#endif // _FTP_CLIENT_H_



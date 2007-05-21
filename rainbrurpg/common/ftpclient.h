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
 * - 21 may 2007 : Multi-thread implementation started
 * - 27 apr 2007 : Starting implementation
 *
 */

#ifndef _FTP_CLIENT_H_
#define _FTP_CLIENT_H_

#include <string>
#include <vector>
#include <iostream>

#include <gnet.h>
#include <glib.h>
#include <sigc++/sigc++.h>

#include "ftpdef.h"
#include "boost/filesystem/operations.hpp"
#include "boost/filesystem/fstream.hpp"

using namespace std;

namespace RainbruRPG {
  namespace Network{

    /** A class that implements the FTP protocol for client-side using
      *
      * This class is based on the GNet library (http://www.gnetlibrary.org/)
      * as a result, <b>before using it</b> you should call the \c gnet_init() 
      * function.  This function is found in the \c gnet.h header.
      *
      * It implements both the control and the data channel. You should call
      * connectToHost() with the control channel host port (L). The host
      * should listen in the data channel port L-1.
      *
      */
    class FtpClient{
    public:
      /** Defines a signal returning void with an integer parameter */
      typedef sigc::signal<void, int> tVoidIntSignal;

      FtpClient();
      ~FtpClient();

      bool connectToHost(const std::string&, int );
      bool openDataChannel();
      bool closeDataChannel();
      void toggleTransferMode();

      std::string commandLIST();
      std::string commandPWD();
      std::string commandSYST();
      std::string waitControlResponse();
      std::string commandBINARY();
      std::string commandASCII();
      std::string commandSTOR(const std::string&);
      std::string commandRETR(const std::string&);

      /** A signal emitted when bytes are read
        *
	* An integer parameter represents the number of bytes read.
	*
	*/
      tVoidIntSignal sigBytesRead;

      /** A signal emitted when bytes are written
        *
	* An integer parameter represents the number of bytes written.
	*
	*/
      tVoidIntSignal sigBytesWritten;

      void STOR_ThreadedFunction();

    private:
      void sendString(const std::string&);
      std::string readDataChannel();

      /** The host IP adress */
      std::string hostIp;
      /** The host port for control channel */
      int hostPort;

      /** The control channel socket */
      GTcpSocket* controlSock;
      /** The data channel socket */
      GTcpSocket* dataSock;

      /** Is the control channel connected ? */
      bool controlChannelConnected;

      /** Are we in FTT_BINARY or FTT_ASCII ? */
      tTransferType transferType;
      /** The name of the file to transfer */
      std::string transferFilename;

      /** The value returned in a thread */
      std::string returnValue;
    };
  }
}

#endif // _FTP_CLIENT_H_



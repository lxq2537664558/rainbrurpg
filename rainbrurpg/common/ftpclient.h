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

/** \file ftpclient.h
  * Declares a FTP client
  *
  * Modifications :
  * - 31 mar 2009 : Now using gettext
  * - 11 mar 2008 : Adds some function for unit tests implementation
  * - 08 jul 2007 : 
  *      - \ref RainbruRPG::Network::FtpClient::commandRETR "commandRETR" uses 
  *        \ref RainbruRPG::Network::GlobalURI::getDownloadFile()
  *        "GlobalURI::getDownloadFile()".
  *      - A \ref RainbruRPG::Network::FtpClient::sigTransferError 
  *        "sigTransferError" signal
  * - 30 jun 2007 : 
  *      - Add \ref RainbruRPG::Network::FtpClient::uniqueName "uniqueName"
  *        (member)
  *      - std::string return type become const std::string&
  * - 07 jun 2007 : A \ref RainbruRPG::Network::FtpClient::sigTransferTerminated 
  *                 "sigTransferTerminated" signal
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
#include "globaluri.h"

#include "rainbrudef.h" // For the gettext stuff

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
      * \warning Please read the connectToHost() documentation about the 
      * unique name parameter before using this class.
      *
      * \sa \ref Server::UniqueName "UniqueName" (class)
      *
      */
    class FtpClient{
    public:
      /** Defines a signal returning void with an integer parameter */
      typedef sigc::signal<void, int> tVoidIntSignal;
      /** Defines a signal returning void with none arguments */
      typedef sigc::signal<void> tVoidSignal;
      /** Defines a signal returning void with a tTransferError parameter */
      typedef sigc::signal<void, tTransferError> tVoidErrSignal;

      FtpClient();
      ~FtpClient();

      bool connectToHost(const std::string&, int, const std::string&);
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
      const std::string& commandRETR(const std::string&);

      int getFilesize(const std::string&);

      bool isControlChannelConnected(void);
      bool isDataChannelConnected(void);
      const std::string& getHostIp(void) const;
      const std::string& getHostUniqueName(void) const;
      int getHostPort(void) const;
      tTransferType getTransferType(void);

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

      /** A signal emitted when transfer is terminated
        *
	*/
      tVoidSignal sigTransferTerminated;

      /** A signal emitted when a FSIZE command is received
        *
	* An integer parameter represents the file's size. This function
	* is used when a RETR command is requested.
	*
	*/
      tVoidIntSignal sigFileSizeReceived;

      /** A signal emitted when an error occured
        * 
	* The errors are defined by the 
	* \ref RainbruRPG::Network::tTransferError "tTransferError" 
	* enum in ftpdef.h.
	*
	*/
      tVoidErrSignal sigTransferError;

      void STOR_ThreadedFunction();
      void RETR_ThreadedFunction();

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
      /** Is the data channel connected ? */
      bool dataChannelConnected;

      /** Are we in FTT_BINARY or FTT_ASCII ? */
      tTransferType transferType;
      /** The name of the file to transfer */
      std::string transferFilename;

      /** The value returned in a thread */
      std::string returnValue;
      /** The next filesize to get (RETR) */
      int nextFilesize;
      /** The total of received bytes */
      int totalBytesReceived;

      /** The server's UniqueName used to retrieve files 
        *
	* The downloaded files could come from many different server and 
	* the same filename can occur. The files coming from a given server
	* are set in a single directory called <code> 
	* $HOME/.RainbruRPG/download/$UNIQUE_NAME</code>. So we need 
	* the server's unique name to create this directory name.
	*
	*/
      std::string uniqueName;
    };
  }
}

#endif // _FTP_CLIENT_H_



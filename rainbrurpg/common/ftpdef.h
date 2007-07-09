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
 * - 05 may 2007 : Starting implementation
 *
 */

#ifndef _FTP_COMMON_DEFINITIONS_H_
#define _FTP_COMMON_DEFINITIONS_H_

/* 
 * The types defined in this file are used by both common/ftpclient and
 * server/ftptransfer. But it cannot be common/ftpclient.h because the
 * server is not compile with gnet/glib dependencies.
 *
 */
namespace RainbruRPG {
  namespace Network{

    /** All command that need a Transfer Channel
     *
     */
    typedef enum tTransferCommand{
      FTC_NONE,     // NOOP command
      FTC_LIST,     // The command is a LIST command
      FTC_RETR,     // The retrieve command
      FTC_STOR,     // The STORE command
    };
    
    /** An enumeration describing the FTP transfer mode
     *
     * The default is FTM_PASSIVE.
     *
     */
    typedef enum tTransferMode{
      FTM_ACTIVE,  //!< Active server mode
      FTM_PASSIVE, //!< Passive server mode
    };
    
    /** An enumeration describing the FTP transfer type
     *
     * It defines howx a file is transfered.
     *
     * The default is FTT_ASCII.
     *
     */
    typedef enum tTransferType { 
      FTT_BINARY, //!< The file is opened in binary mode
      FTT_ASCII,  //!< The file is opened in ascii mode
    };

    /** Defines the errors that can occur during a file transfer
      *
      */
    typedef enum tTransferError {
      FTE_OPEN_FILE_ERROR,         //!< Cannot create the requested file
      FTE_OPEN_DATA_CHANNEL_ERROR, //!< Cannot open data channel
    };

  }
}

#endif // _FTP_COMMON_DEFINITIONS_H_

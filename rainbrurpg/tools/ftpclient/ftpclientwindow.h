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
 * - 07 jun 2007 : A transferTerminated slot
 * - 25 apr 2007 : Starting implementation
 * - 25 apr 2007 : Starting implementation
 */ 
#ifndef NET_FLOODER_WINDOW_H
#define NET_FLOODER_WINDOW_H

#include <fox-1.6/fx.h>
#include <sigc++/sigc++.h>

#include <gnet.h>
#include <logger.h>
#include <ftpclient.h>

/** A define macro used to indent the help messages */
#define HELP_INDENT "            "
/** The GUI update interval */
#define UPDATE_INTERVAL 500

using namespace RainbruRPG::Network;

namespace RainbruRPG{
  namespace Gui{

    /** The ftpClient main window
      *
      * It is a simple FTP client used to test the FTP client-side functions
      * implementation. The \c PORT command is not implemented.
      *
      * \sa FtpClient
      * 
      */
    class FtpClientWindow : public FX::FXMainWindow, public sigc::trackable {
      FXDECLARE(FtpClientWindow)
	
    public:
      FtpClientWindow(FXApp *); 
      virtual ~FtpClientWindow(); 

      virtual void create();
      
      /** The enumeration defining the Fox selectors, used in event 
        * mechanism
	*/
      enum{
	/** Not Yet Implemented Identifier */
	ID_NYI=FXMainWindow::ID_LAST,
	/** A new command was entered */
	ID_NEW_CMD,
	/** A new command was entered */
	ID_HELP,
	/** The connect button identifier */
	ID_CONN,
	/** Setting the new value to  FXMainWindow::ID_LAST*/
        ID_LAST,
	/** The progressbar update identifier */
	ID_UPDT
      };
 
      long onNotYetImplemented(FXObject* ,FXSelector,void*);
      long treatNewCommand(FXObject* ,FXSelector,void*);
      long onConnect(FXObject* ,FXSelector,void*);
      long onHelp(FXObject* ,FXSelector,void*);
      long onUpdateTransfer(FXObject* ,FXSelector,void*);

      void slotBytesWritten(int);
      void slotTransferTerminated();
      void slotFileSizeReceived(int);

    private:
      void logMessage(FXString);
      void showHelpCommand(FXString, FXString);
      void showHelpUser();
      void showHelpPass();
      void showHelpPasv();
      void showHelpPwd();
      void showHelpList();
      void showHelpSyst();
      void showHelpBinary();
      void showHelpAscii();
      void showHelpStore();
      void showHelpRetrieve();

      void scrollDown();
      FXString filesizeToString(int);

      /** Required or Undefined references */
      FtpClientWindow(){};
      /** Required or Undefined references */
      FtpClientWindow(const FtpClientWindow&);
      /** Required or Undefined references */
      FtpClientWindow &operator=(const FtpClientWindow&);

      /** The file menu item */
      FXMenuPane*filemenu;
      /** The widget where we treat commands */
      FXText* fxText;
      /** The command text field */
      FXTextField* fxTextField;

      /** The etxt field used to enter the host IP adress */
      FXTextField* tfHostIp;
      /** The etxt field used to enter the host port */
      FXTextField* tfHostPort;

      /** The FtpClient instance used to send FTP commands */
      FtpClient* ftpClient;
      /** The progressbar of the current transfer */
      FXProgressBar* labTrPb;

      /** The total of already downloaded bytes */
      int downloadedBytes;

      /** The label that contain the transfered filename */
      FXLabel* labTransName;
      /** The label that contain the transfer orientation */
      FXLabel* labTransOrie;
      /** The label that contain the transfered file size */
      FXLabel* labTransSize;

      /** Set it to true to reset transfer visual */
      bool resetTransfer;

    }; 
  }
}

#endif// NET_FLOODER_WINDOW_H




/*
 *  Copyright 2006-2008 Jerome PASQUIER
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
 * - 10 jul 2007 : Using GlobalURI for RETR file info
 * - 18 apr 2007 : Starting implementation
 */

#ifndef _FTP_CONTROL_H_
#define _FTP_CONTROL_H_

#include <QThread>
#include <QDataStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include <xmlaccountlist.h>
#include <globaluri.h>
#include <iostream>


using namespace std;
using namespace RainbruRPG::Network;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG{
  namespace Network{
    namespace Ftp{

      /** An implementation of the Control Channel using by the FTP protocol
        *
	*/
      class FtpControl : public QThread {
	Q_OBJECT
	  public:
	FtpControl(quint16);
	~FtpControl();
	
	virtual void run ();
	
      signals:
	/** A signal used to log a message */
	void log(const QString&);
	/** A PORT command was received with this port */
	void transferListeningPort(const QString&, int);
	/** A signal emitted when a LIST command occured */
	void commandLIST();
	/** A signal emitted when a PASS command occured */
	void commandPASV();
	/** A signal emitted when a file is retrieved */
	void commandRETR(const QString&);
	/** A signal emitted when a file is sent */
	void commandSTOR(const QString&);
	/** A signal emitted when BINARY transfer type is on */
	void switchToBinaryType();
	/** A signal emitted when ASCII transfer type is on */
	void switchToAsciiType();
	/** Add a transfer visual
	  *
	  * \param ip The IP address of the connected client
	  * \param port The port of the connected client
	  * \param filename The filename to transfer
	  * \param commingIn Is the file sent by the client ?
	  * \param filesize The received file's size 
	  *
	  */
	void addTransferVisual(const QString& ip,const QString& port, 
			       const QString& filename, bool commingIn, 
			       int filesize);

      public slots:
	void transferComplete(const QString&);
        void startTransferFile(const QString&, qint64);
        void waitTransferFile(const QString&);
	void switchToActiveMode();
	void switchToPassiveMode();

      private slots:
	void newConnection();
	void readSocket();
	bool isFileExisting(const QString&);

      private:
	/** The port used to listen the control channel */
	quint16 port;
	/** The TCP server listening FTP commands */
	QTcpServer* server;
	/** A test wuth socket descriptor */
	int descriptor;
	/** A socket instance */
	QTcpSocket* socket1;
	/** The current FTP directory */
	QString currentDirectory;

	/** Account list used in user log in verification */
	xmlAccountList accountList;
	/** The next file size in bytes */
	int nextFilesize;
	/** Next filename of the file to store */
	QString nextStoredFile;
      };
    }
  }
}

#endif //_FTP_CONTROL_H_

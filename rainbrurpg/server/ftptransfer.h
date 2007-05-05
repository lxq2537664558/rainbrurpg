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
 * - 01 may 2007 : PASSIVE mode implementation
 * - 22 apr 2007 : LIST command imlementation
 * - 20 apr 2007 : Starting implementation
 */

#ifndef _FTP_TRANSFER_H_
#define _FTP_TRANSFER_H_

#include <QThread>
#include <QDataStream>
#include <QTextStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDir>
#include <QDateTime>
#include <QFile>

#include <iostream>

#include <ftpdef.h>

#define MAX_READ_LENGTH 1024

using namespace std;

namespace RainbruRPG{
  namespace Network{
    namespace Ftp{



      /** An implementation of the Transfer Channel using by the FTP protocol
        *
	* \sa FtpServer
	*
	*/
      class FtpTransfer : public QThread {
	Q_OBJECT
	  public:
	FtpTransfer(quint16);
	~FtpTransfer();
	
	virtual void run ();
	
      signals:
	/** A signal used to log messages */
	void log(const QString&);
	/** A signal emited when the transfer is complete */
	void transferComplete();
	/** A signal emitted when a transfer starts */
        void startTransferFile(const QString&, qint64);
	/** A signal emitted when we wait the transfer to starts */
        void waitTransferFile(const QString&);
	/** A signal emitted when the server switch to active mode */
	void switchToActiveMode();
	/** A signal emitted when the server switch to passive mode */
	void switchToPassiveMode();

      public slots:
	void changeHost(const QString&, int);
	void commandLIST();
	void commandPASV();
	void commandRETR(const QString&);
	void commandSTOR(const QString&);
	void switchToBinaryType();
	void switchToAsciiType();

      private slots:
	void newConnection();
	void error ( QAbstractSocket::SocketError socketError );

      private:
	void lsResult();
	void writeBytes(QTcpSocket*);

	QString fileSizeToString(qint64);
	QString filePermissions(bool,bool,bool);

	bool waitForActiveConnection(QTcpSocket*);
	bool waitForPassiveConnection(QTcpSocket*);

	bool waitForConnection(QTcpSocket*);

	/** The listening port used in passive mode */
	quint16 port;
	/** The TCP server instance */
	QTcpServer* server;
	/** A socket descriptor */
	int descriptor;
	/** A socket instance */
	QTcpSocket* socket1;
	/** The current working directory */
	QString currentDirectory;

	/** The host adress used in active mode */
	QString hostAdress;
	/** The host port used in active mode */
	int hostPort;

	/** The data of the packet that will be sent */
	QString packetData;

	/** The current transfer mode */
	tTransferMode transferMode;
	/** The current transfer type */
	tTransferType transferType;
	/** The command to execute on the next data channel opened */
	tTransferCommand nextCommand;
      };

    }
  }
}
#endif //_FTP_TRANSFER_H_

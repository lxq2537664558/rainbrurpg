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
 * - 22 apr 2007 : LIST command imlementation
 * - 20 apr 2007 : Starting implementation
 */

#ifndef _FTP_TRANSFER_H_
#define _FTP_TRANSFER_H_

#include <QThread>
#include <QDataStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDir>
#include <QDateTime>
#include <QFile>


#include <iostream>

#define MAX_READ_LENGTH 1024

using namespace std;

namespace RainbruRPG{
  namespace Network{
    namespace Ftp{

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
	/* A signal emitted when a transfer starts */
        void startTransferFile(const QString&, qint64);

      public slots:
	void changeHost(const QString&, int);
	void commandLIST();
	void commandPASV();
	void commandRETR(const QString&);

      private slots:
	void newConnection();
	void error ( QAbstractSocket::SocketError socketError );

      private:
	void lsResult();
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
      };

    }
  }
}
#endif //_FTP_TRANSFER_H_

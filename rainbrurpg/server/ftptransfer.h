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

#include <iostream>

using namespace std;

namespace RainbruRPG{
  namespace Network{
    namespace Ftp{

      typedef enum tTransferMode{
	FTM_ACTIVE,
	FTM_PASSIVE,
      };

      typedef enum tTransferType { 
	FTT_BINARY, 
	FTT_ASCII,
      };

      /** An implementation of the Transfer Channel using by the FTP protocol
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
	void transferComplete();

      public slots:
	void changeHost(const QString&, int);
	void commandLIST();

      private slots:
	void newConnection();
        void sendPacket();
	void packetSent();
	void error ( QAbstractSocket::SocketError socketError );

      private:
	void lsResult();

	QString filePermissions(bool,bool,bool);

	/** The listening port */
	quint16 port;
	/** The TCP server instance */
	QTcpServer* server;
	/** A socket descriptor */
	int descriptor;
	/** A socket instance */
	QTcpSocket* socket1;
	/** The current working directory */
	QString currentDirectory;

	QString hostAdress;
	int hostPort;

	QString packetData;

	tTransferMode transferMode;
	tTransferType transferType;
      };

    }
  }
}
#endif //_FTP_TRANSFER_H_

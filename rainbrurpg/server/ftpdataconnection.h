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
 * - 14 may 2007 : Starting implementation
 */

#ifndef _FTP_DATA_CONNECTION_H_
#define _FTP_DATA_CONNECTION_H_

#include <QObject>
#include <QFile>
#include <QtNetwork/QTcpSocket>

#include <ftpdef.h>
#include <logger.h>

#include "transfervisual.h"

namespace RainbruRPG{
  namespace Network{
    namespace Ftp{

      /** Stores the informations about a FTP data channel connection
        *
	* 
	*
	*/
      class FtpDataConnection : public QObject{
	Q_OBJECT
      public:
	FtpDataConnection(const QString&, const QString&, tTransferCommand);
	FtpDataConnection();
	virtual ~FtpDataConnection();

	bool isThisConnection(const QString&, const QString&, const QString&);
	bool isThisConnection(const QString&);
	void setTransferVisual(TransferVisual*);
	void setCommand(tTransferCommand);
	void setTransferType(tTransferType);
	void setFilename(const QString&);
	void setSocket(QTcpSocket*);
	void setCurrentDirectory(const QString&);
	void setIp(const QString&);
	void setPort(const QString&);

	void commandSTOR(const QString&);
	void computeRate();

      private slots:
	void readyRead();
	void readyWrite();

      private:
	/** The Transfer visual associated with this connection */
	TransferVisual* transferVisual;
	/** The connected client IP address */
	QString clientIp;
	/** The connected client port */
	QString clientPort;
	/** Defines the command type */
	tTransferCommand command;
	/** The file used to write/read the current transfered file */
	QFile* currentFile;
	/** The socket associated with this connection */
	QTcpSocket* socket;
	/** Set the filename of the file */
	QString filename;
	/** The current transfer type */
	tTransferType transferType;
	/** The current directory */
	QString currentDirectory;
      };
    }
  }
}
#endif // _FTP_DATA_CONNECTION_H_
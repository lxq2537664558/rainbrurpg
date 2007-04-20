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
 * - 18 apr 2007 : Starting implementation
 */

#ifndef _FTP_CONTROL_H_
#define _FTP_CONTROL_H_

#include <QThread>
#include <QDataStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include <iostream>

using namespace std;

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
	
      private slots:
	void newConnection();
	void readSocket();
	
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
      };
    }
  }
}

#endif //_FTP_CONTROL_H_

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
 * - 20 apr 2007 : Starting implementation
 */

#ifndef FTP_SERVER_H_
#define FTP_SERVER_H_

#include <iostream>
#include <QtGui/QWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QtGui>
#include <QtGui/QTreeWidget>
#include <ftpdef.h>

#include "ftpcontrol.h"
#include "ftptransfer.h"
#include "transfervisual.h"

using namespace std;

namespace RainbruRPG{
  namespace Network{
    namespace Ftp{

      /** An implementation of a threaded FTP server based on FTC0959
        *
	* It is a widget implementing the FTP protocol. It internally uses
	* two QThreads : FtpControl and FtpTransfer.
	*
	* The default listening port for the control channel is 50002.
	*
	* Is you're running GNU/Linux, the shell command  
	* <code>netstat -tulpn</code> can be usefull. It tells you which 
	* port are listened be the server.
	* 
	*/
      class FtpServer : public QWidget{
	Q_OBJECT
	  public:
	FtpServer(QWidget* parent=0, quint16 port=50002);
	~FtpServer();
	

      signals:
	/** A signal sent to tell we start to store a file
	  *
	  * This signal comes from FtpTransfer and is sent to MainWindow.
	  * It tells the user seeing QuanrantineList that the given filename
	  * is not totally transfered.
	  *
	  * \param filename The filename of the STOR file
	  *
	  * \sa transferComplete(const QString&);
	  *
	  */
	void storeFile(const QString& filename);
	/** Should be used to tell QuarantineList that the transfer is finished
	  *
	  * When a STOR file transfer is finished, this signal is emitted 
	  * to tell QuarantineListe that the transfer is finished.
	  * It does not work for QuarantneList but is used in another
	  * mechanisms.
	  *
	  * \param filename The filename of the STOR file
	  *
	  * \sa storeFile(const QString&);
	  *
	  */
	void transferComplete(const QString& filename);

     public slots:
       void log(const QString&);
       void addTransfer(TransferVisual*);
	
       TransferVisual* addTransferVisual(const QString& ip, 
					 const QString& port, 
					 const QString& filename, 
					 bool commingIn, int);

	void updateTransferVisual(const QString& , int);



      private:
	/** The widget used to log messages */
	QTextEdit* textEdit;
	/** The control channel */
	FtpControl* control;
	/** The data channel */
	FtpTransfer* transfer;
	/** The tree showing current downloads */
	Q3ListView* tree;
      };
      
    }
  }
}
#endif // FTP_SERVER_H_

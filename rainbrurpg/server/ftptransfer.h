
#ifndef _FTP_TRANSFER_H_
#define _FTP_TRANSFER_H_

#include <QThread>
#include <QDataStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include <iostream>

using namespace std;

namespace RainbruRPG{
  namespace Network{
    namespace Ftp{

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
	void log(const QString&);
	
      private:
	quint16 port;
	QTcpServer* server;
	int descriptor;
	QTcpSocket* socket1;
	QString currentDirectory;
      };

    }
  }
}
#endif //_FTP_TRANSFER_H_

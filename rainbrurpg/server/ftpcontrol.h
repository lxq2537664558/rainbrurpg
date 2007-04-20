
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
	void log(const QString&);
	
	private slots:
	  void newConnection();
	void readSocket();
	
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

#endif //_FTP_CONTROL_H_

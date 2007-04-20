#ifndef FTP_SERVER_H_
#define FTP_SERVER_H_

#include <iostream>
#include <QtGui/QWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QtGui>
#include <QtGui/QTreeWidget>


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
	FtpServer(quint16 port=50002);
	~FtpServer();
	
	public slots:
	  void log(const QString&);
	void addTransfer(TransferVisual*);
	
      private:
	
	QTextEdit* textEdit;
	FtpControl* control;
	FtpTransfer* transfer;
	QTreeWidget* tree;
      };
      
    }
  }
}
#endif // FTP_SERVER_H_

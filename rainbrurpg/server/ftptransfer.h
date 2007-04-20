

#include <QThread>
#include <QDataStream>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

#include <iostream>

using namespace std;

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

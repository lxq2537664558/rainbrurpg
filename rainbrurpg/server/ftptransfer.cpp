
#include "ftptransfer.h"

FtpTransfer::FtpTransfer(quint16 port) 
  :QThread() {
  this->port=port;
  currentDirectory="/home/mouse";

  descriptor=1;
  server=new QTcpServer();

}

FtpTransfer::~FtpTransfer(){


}

void FtpTransfer::run (){
  QString s2;
  s2.setNum(port);
  QString s="Transfer channel now listening for new connections on port ";
  s+=s2;

  server->listen( QHostAddress::Any, port );
  emit(log(s));

}

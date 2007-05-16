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

#include "ftpdataconnection.h"

/** Default constructor
  *
  */
RainbruRPG::Network::Ftp::FtpDataConnection::FtpDataConnection(){
  command=FTC_NONE;
  transferType=FTT_ASCII;

  clientIp="";
  clientPort="";

  transferVisual=NULL;
  socket=NULL;
}

/** Constructor
  *
  * \param ip The client IP address
  * \param port The client port
  * \param c The transfer command
  *
  */
RainbruRPG::Network::Ftp::FtpDataConnection::
FtpDataConnection(const QString& ip, const QString& port, tTransferCommand c){
  command=c;
  transferType=FTT_ASCII;

  clientIp=ip;
  clientPort=port;

  transferVisual=NULL;
  socket=NULL;
}

/** Destructor
  *
  */
RainbruRPG::Network::Ftp::FtpDataConnection::~FtpDataConnection(){

}

/** Set the transfer visual
  *
  * \param tv The TransferVisual to change
  *
  */
void RainbruRPG::Network::Ftp::FtpDataConnection::
setTransferVisual(TransferVisual* tv){
  transferVisual=tv;
}

/** Change the transfer command
  *
  * \param tc The command type
  *
  */
void RainbruRPG::Network::Ftp::FtpDataConnection::
setCommand(tTransferCommand tc){
  command=tc;
}

/** The readyWrite slot
  *
  * It is connected to the readyWrite() signal of the socket.
  *
  */
void RainbruRPG::Network::Ftp::FtpDataConnection::readyWrite(){

}

/** Change the filename
  *
  * \param s The new filename
  *
  */
void RainbruRPG::Network::Ftp::FtpDataConnection::
setFilename(const QString& s){
  this->filename=s;
}

/** Change the transfer type
  *
  * \param tt The new transfer type
  *
  */
void RainbruRPG::Network::Ftp::FtpDataConnection::
setTransferType(tTransferType tt){
  this->transferType=tt;
}

/** Execute a STOR command
  *
  * \param fn The filename
  *
  */
void RainbruRPG::Network::Ftp::FtpDataConnection::
commandSTOR(const QString& fn){
  this->filename=fn;
  command=FTC_STOR;

  // Do the file already exist ?
  QDir a(currentDirectory);
  if (a.exists(filename)){
    LOGI("The file already exist");
    a.remove(filename);
  }

  currentFile=new QFile(a.filePath(filename));
  QIODevice::OpenMode om;

  // We are in Binary mode
  if (transferType==FTT_BINARY){
    om=QIODevice::WriteOnly|QIODevice::Append;
  }
  // We are in ASCII mode
  else if (transferType==FTT_ASCII){
    om=QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append;
  }

  bool b=currentFile->open(om);
}

/** The readyRead slot
  *
  * It is connected to the readyRead() signal of the socket.
  *
  */
void RainbruRPG::Network::Ftp::FtpDataConnection::readyRead(){
  switch(command){
  case FTC_STOR:
    QByteArray ba=socket->readAll();
    int rep=currentFile->write(ba);
    if (rep==-1){
      LOGE("An error occured during STOR file writing");
      LOGCATS("ErrorString :");
      LOGCATS(currentFile->errorString().toLatin1());
      LOGCAT();
      break;
    }
    else{
      if (transferVisual==NULL){
	LOGW("Cannot update transferVisual");
      }
      else{
	transferVisual->addBytes(rep);
      }
    }
    break;
  }
}

/** Set the socket
  *
  * \param s The socket
  *
  */
void RainbruRPG::Network::Ftp::FtpDataConnection::setSocket(QTcpSocket* s){
  this->socket=s;
  connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

/** Change the current directory
  *
  * \param s The current directory value
  *
  */
void RainbruRPG::Network::Ftp::FtpDataConnection::
setCurrentDirectory(const QString& s){
  this->currentDirectory=s;
}

/** Is the connection the same
  *
  * \param ip The IP address to test
  *
  * \return \c true if IP are the same
  *
  */
bool RainbruRPG::Network::Ftp::FtpDataConnection::
isThisConnection(const QString& ip){
  if (ip==clientIp){
    return true;
  }
  else{
    return false;
  }
}

/** Change the client IP address
  *
  * \param ip The client IP address
  *
  */
void RainbruRPG::Network::Ftp::FtpDataConnection::setIp(const QString& ip){
  this->clientIp=ip;
}

/** Change the client port
  *
  * \param p The client port
  *
  */
void RainbruRPG::Network::Ftp::FtpDataConnection::setPort(const QString& p){
  this->clientPort=p;
}

/** Is the connection the same
  *
  * If clientPort is empty, the port given in parameter is set.
  *
  * \param ip The IP address to test
  * \param port The port to test
  *
  * \return \c true if IP/port are the same
  *
  */
bool RainbruRPG::Network::Ftp::FtpDataConnection::
isThisConnection(const QString& ip, const QString& port, 
		 const QString& filename){

  LOGI("isThisConnection(2string) called");
  LOGCATS("  matched IP=");
  LOGCATS(ip.toLatin1());
  LOGCATS(" port=");
  LOGCATS(port.toLatin1());
  LOGCATS(" filename=");
  LOGCATS(filename.toLatin1());
  LOGCAT();
  LOGCATS("  local IP=");
  LOGCATS(clientIp.toLatin1());
  LOGCATS(" port=");
  LOGCATS(clientPort.toLatin1());
  LOGCATS(" filename=");
  LOGCATS(this->filename.toLatin1());
  LOGCAT();

  if (ip==clientIp && this->filename==filename){
    if (clientPort.isEmpty()){
      LOGI("First call, setting port");
      clientPort=port;
      return true;
    }
    else{
      if (clientPort==port){
	LOGI("Already called, connection is the same");
	return true;
      }
      else{
	LOGI("Already called, connection is not the same");
	return false;
      }
    }
  }
  else{
    return false;
  }
}


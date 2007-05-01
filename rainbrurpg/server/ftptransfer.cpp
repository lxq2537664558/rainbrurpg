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

#include "ftptransfer.h"

#include <logger.h>

/** The constructor
  *
  * \param port The listening port
  *
  */
RainbruRPG::Network::Ftp::FtpTransfer::FtpTransfer(quint16 port) 
  :QThread() {

  transferMode=FTM_ACTIVE;
  transferType=FTT_ASCII;

  this->port=port;
  currentDirectory="/home/mouse/servertest/";
  QDir::setCurrent(currentDirectory);
  descriptor=1;
  server=new QTcpServer();
  server->listen( QHostAddress::Any, port );

  //  connect(server, SIGNAL(newConnection()), SLOT(newConnection()));

}

/** The destructor
  *
  */
RainbruRPG::Network::Ftp::FtpTransfer::~FtpTransfer(){

}

/** Runs the thread
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::run (){
}

/** A new connection was requested
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::newConnection(){
  emit(log( "A new connection is requested on transfer channel" ));
  LOGI("A new connection is requested on transfer channel" );

  QTcpSocket *tcpSocket=server->nextPendingConnection();

  descriptor=tcpSocket->socketDescriptor();
  LOGCATS("Socket descriptor is ");
  LOGCATI( descriptor );
  LOGCAT();
  
  QString s="essai.txt\naze.lf\r\n";
  //  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readSocket()));
  socket1=tcpSocket;

  tcpSocket->write(s.toLatin1());

}

/** Change the host configuration if a PORT command occured
  *
  * \param host The host IP adress
  * \param port The host port
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::
changeHost(const QString& host,int port){

  QString s2;
  s2.setNum(port);
  QString s="Transfer channel now on ";
  s+=host;
  hostAdress=host;
  s+=":";
  s+=s2;
  hostPort=port;


  this->port=port;
  server->listen( QHostAddress::Any, port );

  //  server->listen( QHostAddress(host), port );
  emit(log(s));

}


/** A slot called is an error occured in the current socket
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::
error ( QAbstractSocket::SocketError socketError ){
  const char* msg;

  LOGE( "A socket error occured ");


  if (socketError==QAbstractSocket::ConnectionRefusedError){
    msg="0 - The connection was refused by the peer (or timed out)";
    LOGCATS("error message : " );
    LOGCATS( msg );
    LOGCAT();
  }
  else if (socketError==QAbstractSocket::RemoteHostClosedError){
    msg="1 - The remote host closed the connection";
    LOGCATS("error message : " );
    LOGCATS( msg );
    LOGCAT();
  }
  else if (socketError==QAbstractSocket::HostNotFoundError){
    msg="2 - The host adress was not found";
    LOGCATS("error message : " );
    LOGCATS( msg );
    LOGCAT();
  }
  else{
    LOGCATS("error code : " );
    LOGCATI(socketError);
    LOGCAT();

  }
}

/** Creates the \c ls command result 
  *
  * It creates it in the packetData string.
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::lsResult(){
  LOGI("LIST command result :");
  unsigned int childs=1;
  packetData="";

  QDir dir(currentDirectory );
  dir.setFilter(QDir::Dirs| QDir::Files| QDir::NoSymLinks);
  dir.setSorting(QDir::Name);

  QFileInfoList list = dir.entryInfoList();

  LOGCATS("Sending ");
  LOGCATI(list.size());
  LOGCATS(" files.");
  LOGCAT();

  for (int i = 0; i < list.size(); ++i) {
    QFileInfo fileInfo = list.at(i);

    // ====== User permissions
    // Diretory ?
    if (fileInfo.isDir()){
      packetData+="d";

      QDir dir2(fileInfo.absoluteFilePath());
      childs=dir2.count();

    }
    else{
      packetData+="-";
      childs=1;
    }

    packetData+=filePermissions(fileInfo.isReadable(),fileInfo.isWritable(),
				fileInfo.isExecutable());

    packetData+=filePermissions(fileInfo.permission(QFile::ReadGroup),
				fileInfo.permission(QFile::WriteGroup),
				fileInfo.permission(QFile::ExeGroup));

    packetData+=filePermissions(fileInfo.permission(QFile::ReadOther),
				fileInfo.permission(QFile::WriteOther),
				fileInfo.permission(QFile::ExeOther));

    // Child number
    QString sChild;
    sChild.setNum(childs);
    sChild=sChild.rightJustified(5);
    packetData+=sChild;

    // Owner and group names
    packetData+=' ';
    QString sOwner=fileInfo.owner();
    sOwner=sOwner.leftJustified(9);
    packetData+=sOwner;
    QString sGroup=fileInfo.group();
    sGroup=sGroup.leftJustified(9);
    packetData+=sGroup;

    // File size
    qint64 size=fileInfo.size();

    QString sSize=fileSizeToString(size);
    sSize=sSize.rightJustified(8);
    packetData+=sSize;

    // Last modified time
    packetData+=" ";
    QDateTime dt=fileInfo.lastModified();
    packetData+=dt.toString("yyyy-MM-dd hh:mm");

    // File name and EOL
    packetData+=" ";
    packetData+=fileInfo.fileName();
    packetData+="\r\n";
  }
}

/** Get a human-readable string from a file size
  *
  * It try to wotks lithe the <code>ls -lh</code> command of an 
  * unix-like system.
  *
  * \param s The file size
  *
  * \return The result string
  *
  */
QString RainbruRPG::Network::Ftp::FtpTransfer::fileSizeToString(qint64 s){
  QString ret;
  double d;


  if (s<1000){
    return ret.setNum(s);
  }
  else if (s>999 && s<1000000){
    d=(double)s/1000;
    ret.setNum(d, 'f', 2);
    ret+= "K";
    return ret;
  }
  else{
    d=(double)s/1000000;
    ret.setNum(d, 'f', 2);
    ret+= "M";
    return ret;

  }
}

/** Create a string defining the given access permissions
  *
  * \param r The read permission
  * \param w The write permission
  * \param x The execution permission
  *
  * \return A string representing the given permissions
  *
  */
QString RainbruRPG::Network::Ftp::FtpTransfer::
filePermissions(bool r,bool w,bool x){
  QString s="";
  if (r) s+="r";
  else   s+="-";

  if (w) s+="w";
  else   s+="-";

  if (x) s+="x";
  else   s+="-";
  return s;
}

/** Send the packet for the LS command
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::commandLIST(){
  // The socket::write returned value
  int rep;

  QTcpSocket sock;
  if (waitForConnection(&sock)){
    lsResult();
    emit(log("Sending LS result"));

    // If we are in ACTIVE mode, we can use the socket
    // returned by waitForConnection() else, we should
    // use the TCP server.
    if (transferMode==FTM_ACTIVE){
      rep=sock.write(packetData.toLatin1());
    }
    else{
      rep=server->nextPendingConnection()->write(packetData.toLatin1());
    }


    if (rep==-1){
      LOGE("An error occured during LIST command");
    }
    LOGI("Waiting for writing bytes");

    if (sock.waitForBytesWritten(3000)){
      emit(log("Transfer channel closed"));
      emit(transferComplete());
      sock.disconnectFromHost();
      LOGI( "LIST command complete");

    }
  }
}

/** Wait for an active connection
  *
  * \param sock The socket used
  *
  * \return \c true if the connection is successfull, \c false if an
  *         error occured
  *
  */
bool RainbruRPG::Network::Ftp::FtpTransfer::
waitForActiveConnection(QTcpSocket* sock){

  if (sock->state()==QAbstractSocket::ConnectedState){
    sock->disconnectFromHost();
  }

  bool b=sock->setSocketDescriptor(++descriptor, 
				  QAbstractSocket::UnconnectedState);

  if (b){
    LOGI("Socket descriptor accepted");
  }
  else{
    LOGW( "Socket descriptor refused");
  }

  sock->connectToHost(hostAdress, hostPort );
  connect (sock, SIGNAL(error ( QAbstractSocket::SocketError )),
	   this, SLOT(error ( QAbstractSocket::SocketError )));


  LOGI("Waiting for connection");
  if (sock->waitForConnected(3000)){
    LOGI( "Connection opened");
    return true;
  }
  else{
    LOGI( "Waiting for writing bytes" );
    LOGW(sock->errorString().toLatin1());

    return false;
  }
}

/** Wait for a passive connection
  *
  * \param sock The socket used
  *
  * \return \c true if the connection is successfull, \c false if an
  *         error occured
  *
  */
bool RainbruRPG::Network::Ftp::FtpTransfer::
waitForPassiveConnection(QTcpSocket* sock){
  LOGI("WaitForPassiveConnection called");
  bool timeOut;
  bool success=server->waitForNewConnection(3000, &timeOut);
  if (success){
    LOGI("Passive connection happened");
    return true;
  }
  else{
    LOGE("Passive connection failed");
  }
  return false;
}

/** A PASV command received
  *
  * The PASV command is used to switch the server mode between
  * Active and Passive modes.
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::commandPASV(){
  if (transferMode==FTM_PASSIVE){
    transferMode=FTM_ACTIVE;
  }
  else{
    transferMode=FTM_PASSIVE;
  }

  QString s("Switching to ");
  if (transferMode==FTM_PASSIVE){
    s+="PASSIVE";
  }
  else{
    s+="ACTIVE";
  }
  s+=" mode";
  emit(log(s));
}

/** Wait for an active or passive connection
  *
  * \param sock The socket used
  *
  * \return \c true if the connection is successfull, \c false if an
  *         error occured
  *
  */
bool RainbruRPG::Network::Ftp::FtpTransfer::
waitForConnection(QTcpSocket* sock){
  if (transferMode==FTM_PASSIVE){
    return waitForPassiveConnection(sock);
  }
  else{
    return waitForActiveConnection(sock);
  }
}

/** A file is requested by the host
  *
  * \param filename The filename
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::
commandRETR(const QString& filename){
  LOGI("Sending file...");
  QString s("Sending file ");
  s+=filename;
  emit(log(s));

  const char* aze=filename.toLatin1();
  const char* aze2=QDir::currentPath().toLatin1();
  LOGCATS("Opening file '");
  LOGCATS(aze);
  LOGCATS("' in ");
  LOGCATS(aze2);
  LOGCAT();

  QDir a(currentDirectory);
  QFile f(a.filePath(filename));
  QIODevice::OpenMode om;

  // We are in Binary mode
  if (transferType==FTT_BINARY){
    om=QIODevice::ReadOnly;
  }
  // We are in ASCII mode
  else if (transferType==FTT_ASCII){
    om=QIODevice::ReadOnly|QIODevice::Text;
  }


  if(f.open(om)){
    
    QTcpSocket sock;
    if (waitForConnection(&sock)){
      emit(startTransferFile(filename, f.size()));
      int rep=0;
      
      while (!f.atEnd()){
	rep=sock.write(f.read(MAX_READ_LENGTH));
	if (rep==-1){
	  LOGE("An error occured during RETR command");
	  break;
	}
	else{
	  LOGCATS("Writing ");
	  LOGCATI(rep);
	  LOGCATS(" bytes");
	  LOGCAT();
	  
	  sock.waitForBytesWritten(3000);
	}
      }
      
      // Transfer complete
      emit(log("Transfer channel closed"));
      emit(transferComplete());
      sock.disconnectFromHost();
      LOGI("Transfer complete");
      f.close();

    }
  }
  else{
    emit(log("An error occured during opening file :"));
    QFile::FileError fe=f.error();

    QString feText;
    if (fe==QFile::OpenError){
      feText=("5 The file could not be opened.");
    }
    else{
      feText.setNum(fe);
    }
    emit(log(feText));
  }
}

/** Switch to the Binary transfer type
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::switchToBinaryType(){
  emit(log("Transfer type set to BINARY"));
  transferType=FTT_BINARY;
}

/** Switch to the Ascii transfer type
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::switchToAsciiType(){
  emit(log("Transfer type set to ASCII"));
  transferType=FTT_ASCII;
}

/** A file is sent by the host
  *
  * \param filename The filename to create
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::
commandSTOR(const QString& filename){
  LOGI("Executing STOR command");
  QString s("Receiving file ");
  s+=filename;
  emit(log(s));

  QDir a(currentDirectory);
  if (a.exists(filename)){
    LOGI("The file already exist");
    a.remove(filename);
  }

  QFile f(a.filePath(filename));
    
  QIODevice::OpenMode om;

  // We are in Binary mode
  if (transferType==FTT_BINARY){
    om=QIODevice::WriteOnly|QIODevice::Append;
  }
  // We are in ASCII mode
  else if (transferType==FTT_ASCII){
    om=QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append;
  }

  if(f.open(om)){
      
    QTcpSocket sock;
    if (waitForConnection(&sock)){
      emit(waitTransferFile(filename));
      int rep=0;
	
      while(sock.state()==QAbstractSocket::ConnectedState&&(rep!=-1)){
	LOGI("waitForReadyRead called");
	sock.waitForReadyRead(30000);
	LOGI("reading packet...");
	QByteArray ba=sock.readAll();
	LOGI("Packet read");

	rep=f.write(ba);
	if (rep==-1){
	  LOGE("An error occured during STOR file writing");
	  LOGCATS("ErrorString :");
	  LOGCATS(f.errorString().toLatin1());
	  break;
	}
	else{
	  LOGCATS("Writing ");
	  LOGCATI(rep);
	  LOGCATS(" bytes");
	  LOGCAT();
	}
      }
      
      // Transfer complete
      emit(log("Transfer channel closed"));
      emit(transferComplete());
      sock.disconnectFromHost();
      LOGI("Transfer complete");
      f.close();
      
    }
  }
  else{
    emit(log("An error occured during opening file :"));
    QFile::FileError fe=f.error();
    
    QString feText;
    if (fe==QFile::OpenError){
      feText=("5 The file could not be opened.");
    }
    else{
      feText.setNum(fe);
    }
    emit(log(feText));
  }
}


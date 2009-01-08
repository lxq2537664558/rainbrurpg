/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file ftptransfer.cpp
  * Implements the transfer channel of the FTP server
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
  nextCommand=FTC_NONE;
  transferMode=FTM_PASSIVE;
  transferType=FTT_ASCII;

  this->port=port;
  currentDirectory="/home/mouse/servertest/";
  QDir::setCurrent(currentDirectory);
  descriptor=1;
  server=new QTcpServer();
  //  bool succ=server->listen( QHostAddress::Any, port );
  bool succ=server->listen( QHostAddress::Any, port );
  succ=server->listen( QHostAddress::Any, port+1 );
  if (succ){
    LOGCATS("Now listening in port ");
    LOGCATI(port);
    LOGCAT();
  }
  else{
    LOGE("Cannot listen on the given port");
    LOGCATS("Listening port ");
    LOGCATI(port);
    LOGCATS(" Error string ");
    LOGCATS(server->errorString().toLatin1());

    LOGCAT();

  }

  timer=new QTimer();
  connect(timer, SIGNAL(timeout()), this, SLOT(update()));
  timer->start(500);

  connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

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
  * Prionts a message according to the given error instance.
  *
  * \param socketError the error that occured in the socket
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
  packetData="";
  unsigned int childs=1;

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
    packetData+="\n";
  }
  LOGI("PacketData done. LIST result can be sent");
  int i=  packetData.size();
  LOGCATS("PacketData lenght :");
  LOGCATI(i);
  LOGCAT();
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

  if (socket1!=NULL){
    return true;
  }
  else{
    return false;
  }
}

/** A PASV command received
  *
  * The PASV command is used to switch the server mode between
  * Active and Passive modes.
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::commandPASV(){
  /*  if (transferMode==FTM_PASSIVE){
    transferMode=FTM_ACTIVE;
  }
  else{
    transferMode=FTM_PASSIVE;
  }

  QString s("Switching to ");
  if (transferMode==FTM_PASSIVE){
    s+="PASSIVE";
    emit(switchToPassiveMode());
  }
  else{
    s+="ACTIVE";
    emit(switchToActiveMode());
  }
  s+=" mode";
  */
  emit(switchToPassiveMode());
  QString s("PASV command deactivated");
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
  * This function is called when the client retirieve a file. The file
  * is sent to the client from the \c uploaded directory.
  *
  * \param filename The filename without path
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::
commandRETR(const QString& filename){
  LOGI("Sending file...");
  QString s("Sending file ");
  s+=filename;
  emit(log(s));
  LOGI(s.toLatin1());
  nextCommand=FTC_RETR;

  // Get the absolute filename
  GlobalURI gu;
  std::string stdFilename(filename.toLatin1());
  std::string fullFileName=gu.getUploadFile(stdFilename);
  nextFilename=filename;
  nextOnlyFilename=filename;

  LOGCATS("Opening file '");
  LOGCATS(fullFileName.c_str());
  LOGCAT();

  QFile f(fullFileName.c_str());
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
      emit(transferComplete(filename));
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


/** Send the packet for the LS command
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::commandLIST(){
  // The socket::write returned value
  int rep;

  nextCommand=FTC_LIST;

  QTcpSocket* sock;
  if (waitForConnection(sock)){
    lsResult();
    emit(log("Sending LS result"));

    // If we are in ACTIVE mode, we can use the socket
    // returned by waitForConnection() else, the packetData content
    // is write in the newConnection() function
    if (transferMode==FTM_ACTIVE){
      rep=sock->write(packetData.toLatin1());

      if (rep==-1){
	LOGE("An error occured during LIST command");
      }

      LOGI("Waiting for writing bytes");
      
      writeBytes(sock);
      LOGI( "LIST command complete");
    }
  }
}

/** Waits for the queued bytes to be wrote and close the channel
  *
  * \param s The socket to flush and close
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::writeBytes(QTcpSocket* s){
  if (s->waitForBytesWritten(3000)){
    emit(transferComplete(nextOnlyFilename));
    s->disconnectFromHost();
    emit(log("Transfer channel closed"));
  }
  else{
    LOGE("An error occured during waitForBytesWritten execution");
  }
}

/** A file is sent by the host
  *
  * \param filename The filename to create
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::
commandSTOR(const QString& filename){
  LOGI("Executing STOR command");
  nextCommand=FTC_STOR;

  std::string strFilename(filename.toLatin1());
  GlobalURI gu;
  std::string strNnextFilename=gu.getQuarantineFile(strFilename);
  nextFilename=strNnextFilename.c_str();
  nextOnlyFilename=filename;

  QTcpSocket* sock;
  waitForConnection(sock);
}

/** Set the TransferVisual to a FtpDataConnection
  *
  * The FtpDataConnection update the TransferVisual. It must
  * contains a pointer to the right FtpDataConnection.
  *
  * \param ip The ip of the FtpDataConection
  * \param port The port of the FtpDataConection
  * \param tv The transfer visual object
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::
registerVisual(const QString& ip, const QString& port, TransferVisual* tv){
  tConnectionList::const_iterator iter;

  LOGI("FtpDataConnection creation");
  FtpDataConnection* fdc=new FtpDataConnection();
  connectionList.push_back(fdc);
  fdc->setTransferType(transferType);
  fdc->setIp(ip);
  fdc->setFilename(tv->getAbsoluteFilename());
  fdc->setCurrentDirectory(currentDirectory);
  fdc->setTransferVisual(tv);
}

/** A new connection was requested
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::newConnection(){
  emit(log( "A new connection is requested on transfer channel" ));
  LOGI("A new connection is requested on transfer channel" );
  socket1=server->nextPendingConnection();
  QString filename, s;

  descriptor=socket1->socketDescriptor();
  LOGCATS("Socket descriptor is ");
  LOGCATI( descriptor );
  LOGCAT();

  switch(nextCommand){
  case FTC_NONE:
    LOGW("New connection has no pending command...CLOSED");
    break;
  case FTC_LIST:
    lsResult();
    emit(log("Sending LS result"));
    socket1->write(packetData.toLatin1());
    writeBytes(socket1);
    LOGI( "LIST command complete");
    break;
  case FTC_STOR:
    s="Receiving file ";
    s+=nextOnlyFilename;
    emit(storeFile(nextOnlyFilename));
    emit(log(s));
    break;
  case FTC_RETR:
    LOGI("RETR not yet implemented");
    break;
  }

  //Setting the socket to the FtpDataConnection
  LOGI("registerVisual called");
  LOGCATS("connectionList size : ");
  LOGCATI(connectionList.size());
  LOGCAT();

  QString pport=QString::number(socket1->peerPort());

  bool found=false;

  tConnectionList::const_iterator iter;
  for (iter=connectionList.begin(); iter!=connectionList.end(); iter++){
    if ((*iter)->isThisConnection(socket1->peerAddress().toString(), 
				  pport, nextOnlyFilename)){

      LOGI("Socket correctly added to the FtpDataConnection");
      (*iter)->setSocket(socket1);
      found=true;

      // Setting the command
      if (nextCommand==FTC_STOR){
	(*iter)->commandSTOR(nextFilename);
      }
      else if (nextCommand==FTC_RETR){
	(*iter)->commandRETR(nextFilename);
      }
    }
  }

  // FtpDataConnection not found
  if (!found){
    LOGW("FtpDataConnection not found");
    LOGCATS("Address : ");
    LOGCATS(socket1->peerAddress().toString().toLatin1());
    LOGCATS(" pport : ");
    LOGCATS(pport.toLatin1());
    LOGCATS(" nextFilename : ");
    LOGCATS(nextFilename.toLatin1());
    LOGCAT();
  }
}

/** Updates periodically the FtpDataConnection::computeRate() value
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::update(){
  tConnectionList::const_iterator iter;
  for (iter=connectionList.begin(); iter!=connectionList.end(); iter++){
    (*iter)->computeRate();
  }
}

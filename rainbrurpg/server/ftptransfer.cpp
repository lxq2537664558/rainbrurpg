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

/** The constructor
  *
  * \param port The listening port
  *
  */
RainbruRPG::Network::Ftp::FtpTransfer::FtpTransfer(quint16 port) 
  :QThread() {

  transferMode=FTM_PASSIVE;
  transferType=FTT_ASCII;

  this->port=port;
  currentDirectory="/home/mouse/programmation/rainbrurpg/";

  descriptor=1;
  server=new QTcpServer();

  connect(server, SIGNAL(newConnection()), SLOT(newConnection()));

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

  QTcpSocket *tcpSocket=server->nextPendingConnection();

  descriptor=tcpSocket->socketDescriptor();
  cout << "Socket descriptor is "<< descriptor << endl;
  
  QString s="essai.txt\naze.lf\r\n";
  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readSocket()));
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

  //  server->listen( QHostAddress(host), port );
  emit(log(s));

}

/** Send the packet for the LS command
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::commandLIST(){
  emit(log("Sending LS result"));

  QTcpSocket sock;

  if (sock.state()==QAbstractSocket::ConnectedState){
    sock.disconnectFromHost();
  }

  bool b=sock.setSocketDescriptor(++descriptor, 
				  QAbstractSocket::UnconnectedState, 
				  QIODevice::WriteOnly);

  if (b){
    cout << "Socket descriptor accepted" << endl;
  }
  else{
    cout << "Socket descriptor refused" << endl;

  }

  sock.connectToHost(hostAdress, hostPort );
  connect (&sock, SIGNAL(error ( QAbstractSocket::SocketError )),
	   this, SLOT(error ( QAbstractSocket::SocketError )));


    cout << "Waiting for connection" << endl;
  if (sock.waitForConnected(3000)){
    cout << "Connection opened" << endl;
    lsResult();
    int rep=sock.write(packetData.toLatin1());
    if (rep==-1){
      cout << "AN ERROR OCCURED" << endl;
    }
    cout << "Waiting for writing bytes" << endl;

    if (sock.waitForBytesWritten(3000)){
      emit(log("Transfer channel closed"));
      emit(transferComplete());
      sock.disconnectFromHost();
      cout << "Transfer complete" << endl;

    }
  }
  else{
    cout << "Waiting for writing bytes" << endl;
    qDebug(sock.errorString().toLatin1());
  }

  qDebug(sock.peerName().toLatin1()); 
}

/** A slot called is an error occured in the current socket
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::
error ( QAbstractSocket::SocketError socketError ){
  cout << "AN ERROR OCCURED" << endl;
}

/** Creates the \c ls command result 
  *
  * It creates it in the packetData string.
  *
  */
void RainbruRPG::Network::Ftp::FtpTransfer::lsResult(){
  unsigned int childs=1;
  packetData="";

  QDir dir(currentDirectory );
  dir.setFilter(QDir::Dirs| QDir::Files| QDir::NoSymLinks);
  dir.setSorting(QDir::Name);

  QFileInfoList list = dir.entryInfoList();

  cout << "Sending "<<list.size()<< "files ? " << endl;
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

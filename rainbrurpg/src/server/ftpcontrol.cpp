/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file ftpcontrol.cpp
  * Implements the FTP control channel
  *
  */

#include "ftpcontrol.h"

#include <QStringList>
#include <QFileInfo>

/** The constructor
  *
  * \param port The port the TCP server will listen for new connections
  *
  */
RainbruRPG::Network::Ftp::FtpControl::FtpControl(quint16 port)
:QThread(){
  this->port=port;
  currentDirectory="/home/mouse";

  descriptor=1;
  nextFilesize=0;

  server=new QTcpServer();


  connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
}

/** The destructor
  *
  */
RainbruRPG::Network::Ftp::FtpControl::~FtpControl(){
  delete server;
}

/** Run the thread
  *
  */
void RainbruRPG::Network::Ftp::FtpControl::run(){
  QString s2;
  s2.setNum(port);
  QString s="Control channel now listening for new connections on port ";
  s+=s2;

  server->listen( QHostAddress::Any, port );
  emit(log(s));
}

/** A new connection was requested
  *
  */
void RainbruRPG::Network::Ftp::FtpControl::newConnection(){
  emit(log( "A new connection is requested on control channel" ));

  QTcpSocket *tcpSocket=server->nextPendingConnection();

  descriptor=tcpSocket->socketDescriptor();
  cout << "Socket descriptor is "<< descriptor << endl;
  
  QString s="220 Connection ready. Waiting commands\r\n";
  //  tcpSocket->setSocketDescriptor(descriptor);

  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readSocket()));
  socket1=tcpSocket;

  tcpSocket->write(s.toLatin1());
}

/** Read a comming socket
  *
  */
void RainbruRPG::Network::Ftp::FtpControl::readSocket(){
  QTcpSocket *tcpSocket = socket1;
  QString pport=QString::number(tcpSocket->peerPort());

  if (tcpSocket){
    int ba=tcpSocket->bytesAvailable();
    if (ba>0){
      QDataStream in;
      in.setVersion(QDataStream::Qt_4_0);
      in.setDevice(tcpSocket);

      char *c;
      c=(char*)malloc(ba*sizeof(char));
      int res=in.readRawData( c, ba );

      // Contains the originally received command (not uppercase)
      QString read(const_cast<const char*>(c));

      // Contains the command in uppercase
      QString s;
      s=read;
      s=read.toUpper();
      s=s.trimmed();

      // The supposed first command
      if (s=="SYST"){
	emit(log("SYST command received"));
	tcpSocket->write("215 RainbruRPG FTP server\r\n");
      }
      else{
	// Truncate and trim the QString due to a bug
	s.truncate(ba-2);
	s=s.trimmed();

	if (s=="QUIT"){
	  emit(log("QUIT command received"));
	  tcpSocket->write("221 Goodbye.\r\n");
	}
	else if (s=="SYST"){
	  emit(log("SYST command received"));
	  tcpSocket->write("215 RainbruRPG FTP server\r\n");
	}
	else if (s.contains("USER")){
	  emit(log("USER command received"));
	  tcpSocket->write("331 Enter password\r\n");

	}
	else if (s.contains("PASS")){
	  emit(log("PASS command received"));
	  tcpSocket->write("230 User logged in.\r\n");
	}
	else if (s.contains("PWD")){
	  emit(log("PWD command received"));
	  QString tmp="257 \"";
	  tmp+=currentDirectory;
	  tmp+="\" is current directory\r\n";
	  tcpSocket->write(tmp.toLatin1());

	}
	else if (s.contains("PASV")){
	  emit(log("PASV command received"));
	  emit(commandPASV());

	}
	else if (s.contains("LIST")){
	  emit(log("LS command received"));
	  tcpSocket->write("150 Opening ASCII mode.\r\n");
	  emit(commandLIST());
	}
	else if (s.contains("PORT")){
	  emit(log("PORT command received"));
	  // Find the port number
	  QStringList list1 = s.split(",");
	  QString p1=list1.at(4);
	  QString p2=list1.at(5);

	  QString p11=QString::number(p1.toInt(), 16);
	  QString p21=QString::number(p2.toInt(), 16);
	  p11=p11.rightJustified(2, '0');
	  p21=p21.rightJustified(2, '0');


	  QString hex=p11;
	  hex+=p21;
	  qDebug(p11.toLatin1());
	  qDebug(p21.toLatin1());
	  qDebug(hex.toLatin1());

	  bool ok;
	  int i=hex.toInt(&ok, 16);

	  // Find the IP adress
	  QString h1=list1.at(0);
	  QString h2=h1.right(h1.length()-4);
	  h2+=".";
	  h2+=list1.at(1);
	  h2+=".";
	  h2+=list1.at(2);
	  h2+=".";
	  h2+=list1.at(3);

	  qDebug(h2.toLatin1());
	  cout << "new port : " << i << endl;
	  emit(transferListeningPort(h2,i));
	  tcpSocket->write("200 Port command succeeded.\r\n");

	}
	else if (s.contains("RETR")){
	  read.replace(QString("\n"), QString(" "));
	  QStringList list1 = read.split(" ", QString::SkipEmptyParts);
	  QString h1=list1.at(1);
	  h1=h1.simplified();
	  QString l("Requesting file ");
	  l+=h1;

	  // Uses uploaded/ file
	  GlobalURI gu;
	  std::string strFilename(h1.toLatin1());
	  std::string strUploadFile=gu.getUploadFile(strFilename);
	  QString qstrH1(strUploadFile.c_str());
	  QFileInfo fi(qstrH1);
	  if (!fi.exists()){
	    LOGW("RETR file does not exist");
	    LOGCATS("Filename : ");
	    LOGCATS(strUploadFile.c_str());
	    LOGCAT();
	  }
	  else{
	    int filesize=fi.size();
	  
	    QString s("FSIZE ");
	    QString s2;
	    s2.setNum(filesize);
	    s+=s2;
	    s+="\r\n";
	    tcpSocket->write(s.toLatin1());
	    
	    emit(log(l));
	    emit(addTransferVisual(tcpSocket->peerAddress().toString(),pport, 
				   h1, false, filesize));

	    emit(commandRETR(h1));
	  }

	}
	else if (s.contains("STOR")){
	  read.replace(QString("\n"), QString(" "));
	  QStringList list1 = read.split(" ", QString::SkipEmptyParts);
	  QString h1=list1.at(1);
	  h1=h1.simplified();
	  QString l("Requesting file ");
	  l+=h1;
	  if (!isFileExisting(h1)){
	    nextStoredFile=h1;
	    emit(log(l));
	    tcpSocket->write("200 waiting FSIZE command.\r\n");
	  }
	  else{
	    tcpSocket->write("553 File already exists on server.\r\n");
	  }
	}
	else if (s.contains("TYPE I")){
	  emit(switchToBinaryType());
	  tcpSocket->write("200 Type set to BINARY.\r\n");
	}
	else if (s.contains("TYPE A")){
	  emit(switchToAsciiType());
	  tcpSocket->write("200 Type set to ASCII.\r\n");
	}
	else if(s.contains("FSIZE")){
	  QStringList list1 = read.split(" ", QString::SkipEmptyParts);
	  QString h1=list1.at(1);

	  int chopValue=2;
	  bool convertSuccess=false;
	  // To remove extra characters

	  while(!convertSuccess){
	    h1.chop(chopValue);
	    h1=h1.simplified();
	    nextFilesize=h1.toInt(&convertSuccess);
	    chopValue=1;
	  }

	  emit(addTransferVisual(tcpSocket->peerAddress().toString(), pport, 
				 nextStoredFile, true, nextFilesize));

	  tcpSocket->write("200 Data channel ready.\r\n");
	  emit(commandSTOR(nextStoredFile));
	}
	else{
	  cout << "New packet received (unknown command)"<< endl;
	  cout << "  Packet lenght : " << ba << endl;
	  cout << "  Contains : " << c << endl;
	  tcpSocket->write("502 Command not implemented.\r\n");
	  
	}
      }
    }
  }
}

/** A slot called when a transfer is complete
  *
  */
void RainbruRPG::Network::Ftp::FtpControl::transferComplete(const QString&){
  log("Transfer complete");
  socket1->write("226 Transfer complete.\r\n");
}

/** A slot called when a transfer start
  *
  * \param filename The file name
  * \param filesize The file size
  *
  */
void RainbruRPG::Network::Ftp::FtpControl::startTransferFile(const QString& filename, qint64 filesize){
  QString s2;
  s2.setNum(filesize);

  QString s("150 Opening ASCII mode data connection for ");
  s+=filename;
  s+=" (";
  s+=s2;
  s+=" bytes)\r\n";

  socket1->write(s.toLatin1());

}

/** A slot called when the transfer channel is waiting for the given file
  *
  * \param fn The filename of the file we are waiting
  *
  */
void RainbruRPG::Network::Ftp::FtpControl::waitTransferFile(const QString& fn){
  cout << "waitTransferFile called" << endl;

  QString s("150 Opening ASCII mode data connection for ");
  s+=fn;
  s+="\r\n";

  socket1->write(s.toLatin1());
  socket1->flush();
}

/** Send a message to the client telling the server is in active mode
  *
  */
void RainbruRPG::Network::Ftp::FtpControl::switchToActiveMode(){
  //  socket1->write("227 Server now in Active mode.\r\n");
  socket1->write("227 PASV command deactivated.\r\n");
}

/** Send a message to the client telling the server is in passive mode
  *
  */
void RainbruRPG::Network::Ftp::FtpControl::switchToPassiveMode(){
  //  socket1->write("227 Server now in Passive mode.\r\n");
  socket1->write("227 PASV command deactivated.\r\n");
}

/** Is this file already exists on server
  *
  * The given filename is tested in the \c upload and the \c quarantine
  * directories. It is used when receiving a STOR command from the client.
  * As we cannot save 2 files with the same name, we cannot accept to store
  * a file if its name is already in use.
  *
  * \param fn The filename to test (without path)
  *
  * \return \c true if a name called \e fn already exists in \c upload or 
  *         \c quarantine
  *
  */
bool RainbruRPG::Network::Ftp::FtpControl::isFileExisting(const QString& fn){
  std::string strFn(fn.toLatin1());

  GlobalURI gu;
  std::string strUpload=gu.getUploadFile(strFn);
  std::string strQuaran=gu.getQuarantineFile(strFn);

  QString qsUpload(strUpload.c_str());
  QString qsQuaran(strQuaran.c_str());

  QFile fUpload(qsUpload);
  QFile fQuaran(qsQuaran);

  // Testing for upload/ directory
  bool bUpload=fUpload.exists();

  // Testing for quarantine/ directory
  bool bQuaran=fQuaran.exists();

  if (bUpload){
    return true;
  }
  else if (bQuaran){
    return true;
  }
  else{
    return false;
  }
}
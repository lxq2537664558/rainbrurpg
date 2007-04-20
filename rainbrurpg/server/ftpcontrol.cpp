
#include "ftpcontrol.h"

/** An implementation of the Control Channel using by the FTP protocol
  *
  */
FtpControl::FtpControl(quint16 port)
:QThread(){
  this->port=port;
  currentDirectory="/home/mouse";

  descriptor=1;
  server=new QTcpServer();


  connect(server, SIGNAL(newConnection()), SLOT(newConnection()));
}

FtpControl::~FtpControl(){
  delete server;
}

void FtpControl::run(){
  QString s2;
  s2.setNum(port);
  QString s="Control channel now listening for new connections on port ";
  s+=s2;

  server->listen( QHostAddress::Any, port );
  emit(log(s));
}

void FtpControl::newConnection(){
  emit(log( "A new connection is requested" ));

  QTcpSocket *tcpSocket=server->nextPendingConnection();

  descriptor=tcpSocket->socketDescriptor();
  cout << "Socket descriptor is "<< descriptor << endl;
  
  QString s="220 Connection ready. Waiting commands\r\n";
  //  tcpSocket->setSocketDescriptor(descriptor);

  connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readSocket()));
  socket1=tcpSocket;

  tcpSocket->write(s.toLatin1());
  tcpSocket->flush();
}

void FtpControl::readSocket(){
  QTcpSocket *tcpSocket = socket1;
  if (tcpSocket){
    int ba=tcpSocket->bytesAvailable();
    if (ba>0){
      QDataStream in;
      in.setVersion(QDataStream::Qt_4_0);
      in.setDevice(tcpSocket);

      //      QString s;
      //      in >> s;
      //      qDebug(s.toLatin1());  

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

      qDebug ("Command received :");
      qDebug (s.toLatin1());


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
	  //	  tcpSocket->write("230 Session opened\r\n");
	  QString tmp="257 \"";
	  tmp+=currentDirectory;
	  tmp+="\" is current directory\r\n";
	  tcpSocket->write(tmp.toLatin1());

	}
	else if (s.contains("PASV")){
	  emit(log("PASV command received"));
	  //	  tcpSocket->write("230 Session opened\r\n");
	  tcpSocket->write("Using binary mode to transfer files.");

	}
	else{
	  //	std::string s20(s.toLatin1());
	  cout << "New packet received (unknown command)"<< endl;
	  cout << "  Packet lenght : " << ba << endl;
	  //	cout << "  String lenght : " << s.size() << endl;
	  cout << "  Contains : " << c << endl;
	  
	}
      }
    }
  }
}

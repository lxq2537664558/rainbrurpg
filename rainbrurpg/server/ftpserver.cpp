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

#include "ftpserver.h"

/** The constructor
  *
  * \param port The port used to connect to the Protocol Interpreter
  *
  */
RainbruRPG::Network::Ftp::FtpServer::FtpServer(quint16 port)
  : QWidget(){

  setWindowTitle("RainbruRPG FTP server");
  setMinimumWidth(550);
  QVBoxLayout *mainLayout = new QVBoxLayout;

  // Control widgets
  QLabel* lab1=new QLabel(tr("Control :"), this);
  mainLayout->addWidget(lab1);
  textEdit=new QTextEdit(this);
  mainLayout->addWidget(textEdit);
  setLayout(mainLayout);

  // Transfert widgets
  QLabel* lab2=new QLabel(tr("Transfert :"), this);
  mainLayout->addWidget(lab2);
  tree=new Q3ListView(this);
  tree->addColumn("Ip", 120);
  tree->addColumn("Filename", 160);
  tree->addColumn("In/Out");
  tree->addColumn("Rate", 70);
  tree->addColumn("Size", 100);
  tree->addColumn("Progress", 200);
  mainLayout->addWidget(tree);



  control=new FtpControl(50002);
  connect(control, SIGNAL(log(const QString&)), this, 
	  SLOT(log(const QString&)));
  control->run();

  transfer=new FtpTransfer(50001);
  connect(transfer, SIGNAL(log(const QString&)), this, 
	  SLOT(log(const QString&)));
  transfer->run();

  connect(control, SIGNAL(transferListeningPort(const QString&,int)), 
	  transfer, SLOT(changeHost(const QString&,int)));

  // Commands connections
  connect(control, SIGNAL(commandLIST()), 
	  transfer, SLOT(commandLIST()));

  connect(control, SIGNAL(commandPASV()), 
	  transfer, SLOT(commandPASV()));

  connect(control, SIGNAL(commandRETR(const QString&)), 
	  transfer, SLOT(commandRETR(const QString&)));

  connect(control, SIGNAL(commandSTOR(const QString&)), 
	  transfer, SLOT(commandSTOR(const QString&)));

  // Transfer type switching
  connect(control, SIGNAL(switchToBinaryType()), 
	  transfer, SLOT(switchToBinaryType()));
  connect(control, SIGNAL(switchToAsciiType()), 
	  transfer, SLOT(switchToAsciiType()));

  // Transfer mode switching
  connect(transfer, SIGNAL(switchToActiveMode()), 
	  control, SLOT(switchToActiveMode()));

  connect(transfer, SIGNAL(switchToPassiveMode()), 
	  control, SLOT(switchToPassiveMode()));


  // transfer control
  connect(transfer, SIGNAL(startTransferFile(const QString&, qint64)), 
	  control, SLOT(startTransferFile(const QString&, qint64)));

  connect(transfer, SIGNAL(waitTransferFile(const QString&)), 
	  control, SLOT(waitTransferFile(const QString&)));

  connect(transfer, SIGNAL(transferComplete()), 
	  control, SLOT(transferComplete()));

  // Transfer visual management
 connect(control,SIGNAL(addTransferVisual(const QString&,const QString&,bool, int)),
	  this, SLOT(addTransferVisual(const QString&, const QString&, bool, int)));

 connect(transfer, SIGNAL(updateTransferVisual(const QString& , int)),
	 this, SLOT(updateTransferVisual(const QString& , int)));

  TransferVisual* tv=new TransferVisual(tree);
  tv->setIp("255.255.255.255");
  tv->setFilename("essai.txt", "home/aze");
  tv->setFileSize(453200);
  tv->setDownloaded(4388);
  addTransfer(tv);


}

/** The destructor
  *
  */
RainbruRPG::Network::Ftp::FtpServer::~FtpServer(){
  control->quit();
  delete control;
  transfer->quit();
  delete transfer;
  delete tree;
}

/** Log a message in the textEdit
  *
  * \param s The string to append
  *
  */
void RainbruRPG::Network::Ftp::FtpServer::log(const QString&s){
  textEdit->append(s);
}

/** Adds a transfer
  *
  * \param tv The transfer to add
  *
  */
void RainbruRPG::Network::Ftp::FtpServer::addTransfer(TransferVisual* tv){
  tree->insertItem(tv);
}


void RainbruRPG::Network::Ftp::FtpServer::
addTransferVisual(const QString& ip, const QString& filename, 
		  bool commingIn, int filesize){

  TransferVisual* tv2=new TransferVisual(tree);
  tv2->setIp(ip);
  tv2->setFilename(filename, "");
  tv2->setFileSize(filesize);
  tv2->setCommingIn(commingIn);
  addTransfer(tv2);

}

void RainbruRPG::Network::Ftp::FtpServer::
updateTransferVisual(const QString& ip, int bytes){
  Q3ListViewItem* it=tree->findItem(ip,0);
  if(it==NULL){
    LOGW("Cannot update TransferVisual");
  }
  else{
    TransferVisual* tv=dynamic_cast<TransferVisual*>(it);
    if (tv!=NULL){
      tv->addBytes(bytes);
    }
  }
}

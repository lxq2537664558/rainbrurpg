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
  tree->addColumn("Ip");
  tree->addColumn("Filename");
  tree->addColumn("In/Out");
  tree->addColumn("Rate");
  tree->addColumn("Progress", 150);
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


  TransferVisual* tv=new TransferVisual(tree);
  tv->setIp("123.23.12.123");
  tv->setFilename("essai.txt", "home/aze");
  addTransfer(tv);

  TransferVisual* tv2=new TransferVisual(tree);
  tv2->setIp("192.168.0.1");
  tv2->setFilename("azezertar.gz", "home/aze");
  tv2->setCommingIn(false);
  addTransfer(tv2);

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

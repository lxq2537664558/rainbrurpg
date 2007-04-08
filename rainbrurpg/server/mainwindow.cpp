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

#include "mainwindow.h"

#include "xmlserverconf.h"
#include "helpviewer.h"

#include <logger.h>

#include <QTextEdit>
#include <QDockWidget>
#include <QMenu>
#include <QWorkspace>

/** The default constructor
  *
  * \param fileName A string
  * \param parent The parent widget
  *
  */
RainbruRPG::Server::MainServerWindow::
MainServerWindow(const QString &fileName, QWidget *parent)
		  : QMainWindow(parent)
{
  LOGI("Creating MainWindow");
  clientList=NULL;
  running=false;
  server=new ServerThread();

  // Registrering metatype (needed for signal/slot argumenst)
  qRegisterMetaType<ENetAddress>("ENetAddress");
  qRegisterMetaType<tReceivedPacket>("tReceivedPacket");

  workspace=new QWorkspace();
  setCentralWidget(workspace);

  //Server Log
  serverLog=new ServerLog();
  workspace->addWindow(serverLog);
  serverLog->hide();


  setupActions();

  // Setting up status bar
  statusbar=new QStatusBar(this);
  setStatusBar(statusbar);

  stateLab=new QLabel("Started : No");
  clientsLab=new QLabel("Clients : 0");

  statusbar->showMessage("Ready");
  statusbar->addPermanentWidget(stateLab, 0);
  statusbar->addPermanentWidget(clientsLab, 0);

  // Loading the server configuration
  serverConfig=new ServerConfiguration();
  xmlServerConf xsc;
  xsc.load(serverConfig);

  connect(server, SIGNAL(clientConnected(const ENetAddress &)),
	  this, SLOT(clientConnected(const ENetAddress &)));
  connect(server, SIGNAL(packetReceived(const tReceivedPacket&)),
	  this, SLOT(packetReceived(const tReceivedPacket&)));

  LOGI("MainWindow created");
}

/** The default destructor
  *
  */
RainbruRPG::Server::MainServerWindow::~MainServerWindow(){
  delete workspace;
  delete serverConfig;
  delete stopAct;
  delete runAct;
  delete server;
  delete serverLog;

  if (clientList){
    delete clientList;
  }
}

/** Creates the Qt actions 
  *
  */
void RainbruRPG::Server::MainServerWindow::setupActions(){

  // The Server/Configuration Action
  QAction* confAct = new QAction(tr("&Configuration"), this);
  confAct->setShortcut(tr("Ctrl+C"));
  confAct->setStatusTip(tr("Server's configuration dialog"));

  // The Server/Technote Action
  QAction* techAct = new QAction(tr("&Technical note"), this);
  techAct->setShortcut(tr("Ctrl+T"));
  techAct->setStatusTip(tr("Change the Server's technical note"));


  // The Server/Run Action
  runAct = new QAction(QIcon(":/images/start.png"), tr("&Run"), this);
  runAct->setShortcut(tr("Ctrl+R"));
  runAct->setStatusTip(tr("Runs the server"));

  // The Server/Stop Action
  stopAct = new QAction(QIcon(":/images/stop.png"), 
				 tr("&Stop"), this);
  stopAct->setShortcut(tr("Ctrl+S"));
  stopAct->setStatusTip(tr("Stops the server"));
  stopAct->setEnabled(false);

  // The Server/Exit Action
  QAction* exitAct = new QAction(tr("&Exit"), this);
  exitAct->setShortcut(tr("Ctrl+E"));
  exitAct->setStatusTip(tr("Exit"));


  // The Manage/clients Action
  QAction* clientsAct = new QAction(tr("&Clients"), this);
  clientsAct->setShortcut(tr("Ctrl+I"));
  clientsAct->setStatusTip(tr("Manages the connected clients"));

  // The Manage/log Action
  QAction* logAct = new QAction(tr("&Log"), this);
  logAct->setShortcut(tr("Ctrl+L"));
  logAct->setStatusTip(tr("Manages the server's log"));



  // The Help/about action
  QAction* aboutAct = new QAction(tr("&About"), this);
  aboutAct->setShortcut(tr("Ctrl+A"));
  aboutAct->setStatusTip(tr("About RainbruRPG server"));

  // The Help/index action
  QAction* indexAct = new QAction(tr("&Index"), this);
  indexAct->setShortcut(tr("Ctrl+I"));
  indexAct->setStatusTip(tr("Shows the manual index"));

  // The menus
  QMenu* serverMenu = menuBar()->addMenu(tr("&Server"));
  serverMenu->addAction(confAct);
  serverMenu->addAction(techAct);
  serverMenu->addSeparator();
  serverMenu->addAction(runAct);
  serverMenu->addAction(stopAct);
  serverMenu->addSeparator();
  serverMenu->addAction(exitAct);

  QMenu* manageMenu = menuBar()->addMenu(tr("&Manage"));
  manageMenu->addAction(clientsAct);
  manageMenu->addAction(logAct);


  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
  helpMenu->addAction(indexAct);


  // The tool bar
  QToolBar* toolBar=this->addToolBar("toolbar");
  toolBar->insertAction( 0, runAct );
  toolBar->insertAction( 0, stopAct );

  connect(confAct, SIGNAL(triggered()), this, SLOT(showConfigDialog()));
  connect(techAct, SIGNAL(triggered()), this, SLOT(showTechNoteDialog()));
  connect(indexAct, SIGNAL(triggered()), this, SLOT(showHelpDialog()));
  connect(indexAct, SIGNAL(triggered()), this, SLOT(showHelpDialog()));
  connect(runAct, SIGNAL(triggered()), this, SLOT(startServer()));

  connect(clientsAct, SIGNAL(triggered()), this, SLOT(manageClients()));
  connect(logAct, SIGNAL(triggered()), this, SLOT(showLog()));

  connect(stopAct, SIGNAL(triggered()), this, SLOT(stopServer()));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

}

/** Shows the server configuration dialog
  *
  */
void RainbruRPG::Server::MainServerWindow::showConfigDialog(){
  LOGI("Showing configuration dialog");
  ConfigDialog cd(serverConfig, this);
  cd.exec();

  // Saving the server configuration
  xmlServerConf xsc;
  xsc.save(serverConfig);
}

/** Shows the server's technical note dialog
  *
  */
void RainbruRPG::Server::MainServerWindow::showTechNoteDialog(){
  LOGI("Showing tech note dialog");
  TechNoteDialog tnd(serverConfig, this);
  tnd.exec();

  // Saving the server configuration
  xmlServerConf xsc;
  xsc.save(serverConfig);

}

/** Show the help viewer
  *
  */
void RainbruRPG::Server::MainServerWindow::showHelpDialog(){
  ServerHelpViewer shv;
  shv.exec();
}

/** The slot that start the server
  *
  */
void RainbruRPG::Server::MainServerWindow::startServer(){
  LOGI("Starting server");
  if (!running){
    if (registerServer()){
      runAct->setEnabled(false);
      stopAct->setEnabled(true);
      stateLab->setText("Started : Yes");
      running=true;

      // Serverlog 
      QString msg="Server started";
      serverLog->addMessage(SLL_INFORMATIVE, msg);

      // Init enetHost
      server->setPort(serverConfig->getPort());
      server->setMaxClient(serverConfig->getMaxClient());
      server->createServer();
      server->start();
     }
  }
}

/** The slot used to stop the server
  *
  */
void RainbruRPG::Server::MainServerWindow::stopServer(){
  if (running){
    if (unregisterServer()){
      stateLab->setText("Started : No");
      runAct->setEnabled(true);
      stopAct->setEnabled(false);
      LOGI("Server correctly shutdown");
      running=false;
      server->terminate();
      server->cleanupServer();
      QString msg="Server stopped";
      serverLog->addMessage(SLL_INFORMATIVE, msg);
    }
  }
}

/** The last exit signal
  *
  * No interaction can be done here. I simply removing the server from
  * the admin site if it still running.
  *
  */
void RainbruRPG::Server::MainServerWindow::exitRequested(){
  LOGI("Exit requested");
  stopServer();
}

/** Register the server to the admin site
  *
  * \return \c true if the operation was successfull, \c false
  *         if the registration failed
  *
  */
bool RainbruRPG::Server::MainServerWindow::registerServer(){
  LOGI("Registering server");
  bool ret=true;

  std::string txtPort=StringConv::getSingleton().itos(serverConfig->getPort());
  std::string txtMC=StringConv::getSingleton()
    .itos(serverConfig->getMaxClient());

  CurlServerAdd csa;
  csa.setName(serverConfig->getName());
  csa.setIpAddress(serverConfig->getIpAdress());
  csa.setPort(txtPort);
  csa.setMaxClients(txtMC);
  csa.setDescription(serverConfig->getDesc());
  csa.setTechNote(serverConfig->getTechNote());

  bool resp=csa.perform();
  if (!resp){
    LOGW("Failed to register server");
    LOGCATS("Error message : ");
    LOGCATS(csa.getCustomErrorMessage());
    LOGCAT();
    QMessageBox::critical ( this, "An error occured", 
	"An error occured during server registration", "OK" );
    ret=false;
  }

  return ret;
}

/** Unregister the server to the admin site
  *
  * \return \c true if the operation was successfull, \c false
  *         if the unregistration failed
  *
  */
bool RainbruRPG::Server::MainServerWindow::unregisterServer(){
  LOGI("Unregistering server");

  bool ret=true;

  CurlServerDelete csd;
  csd.setName(serverConfig->getName());

  bool resp=csd.perform();
  if (!resp){
    LOGW("Failed to register server");
    LOGCATS("Error message : ");
    LOGCATS(csd.getCustomErrorMessage());
    LOGCAT();
    QMessageBox::critical ( this, "An error occured", 
	"An error occured during server unregistration", "OK" );
    ret=false;
  }

  return ret;
}

/** Start the event loop on the EnetEvent
  *
  */
void RainbruRPG::Server::MainServerWindow::manageClients(){
  LOGI("manageClients called");

  if (!clientList){
    clientList=new ClientList();
  }
  workspace->addWindow(clientList);
  clientList->show();
}

/** A slot called when a client try to connect 
  *
  * The identification isn't done yet.
  *
  */
void RainbruRPG::Server::MainServerWindow::
clientConnected(const ENetAddress &){
  LOGI("A client is connected");
  //  QString msg="A client is requesting a connection.";
  //  serverLog->addMessage(SLL_INFORMATIVE, msg);
}

/** A network packet is received
  *
  * \param e The received packet
  *
  */
void RainbruRPG::Server::MainServerWindow::
packetReceived(const tReceivedPacket& e){
  LOGI("A packet was received");
  LOGCATS("Packet length : ");
  LOGCATI(e.dataLength);

  std::string c((const char*)e.data);
  LOGCATS(" Packet data : ");
  LOGCATS(c.c_str());

  // Try to get the NetBasePacket id
  NetPacketBase npb;
  npb.setData(e.data, e.dataLength);
  tNetPacketIdentifier i=npb.getIdentifier();
  LOGCATS(" Packet type : ");
  LOGCATS(npb.typeToString(i));
  LOGCAT();

  if (i==NPI_GEN_IDENT){
    npIdentification npi;
    npi.setData(e.data, e.dataLength);
    npi.netDeserialize();

    tNetworkClientType clientType=npi.getClientType();
    const char* typeString=npi.clientTypeToString(clientType);
    LOGCATS("Client type :");
    LOGCATS(typeString);
    LOGCAT();

    QString msg="A ";
    msg+=typeString;
    msg+=" client is requesting a connection :";

    tServerLogLevel msgType;

    // Prepare the connection response
    bool clientAccepted=isClientAccepted(clientType);

    npConnectionResponse ncr;

    if (clientAccepted){
      msg+=" Accepted";
      msgType=SLL_INFORMATIVE;
      ncr.setResponse(NCR_ACCEPTED);
    }
    else{
      msg+=" Refused";
      msgType=SLL_WARNING;
      ncr.setResponse(NCR_REFUSED);
    }

    // Creates the clientList if it doesn't exist
    if (!clientList){
      clientList=new ClientList();
    }
    clientList->addClient(e.host, e.port, clientType, clientAccepted);
    serverLog->addMessage(msgType, msg);

    server->getServer()->sendPacket(e.peer, &ncr);
  }
}

/** Is the given client type is accepted
  *
  * \param t The client type to test
  *
  * \return \c true if the given type is accepted, \c false if refused
  *
  */
bool RainbruRPG::Server::MainServerWindow::
isClientAccepted(tNetworkClientType t){
  bool ret=false;

  if (t==NCT_FLOODER){
    ret=serverConfig->getFloodMode();
  }
  else if (t==NCT_EDITOR){
    ret=serverConfig->getEditMode();

  }
  else if (t==NCT_GAME){
    ret=serverConfig->getPlayMode();

  }

  return ret;
}

/** Show the log window
  *
  */
void RainbruRPG::Server::MainServerWindow::showLog(){
  serverLog->show();

}

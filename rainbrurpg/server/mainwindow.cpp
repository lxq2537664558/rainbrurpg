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

/** \file server/mainwindow.cpp
  * Implements the server's main window
  *
  */

#include "mainwindow.h"

#include "xmlserverconf.h"
#include "helpviewer.h"

#include <logger.h>
#include <npflooder0004.h>

#include <QTextEdit>
#include <QDockWidget>
#include <QMenu>
#include <QWorkspace>

// Database needs
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>

/** The default constructor
  *
  * \param fileName A string
  * \param parent The parent widget
  *
  */
RainbruRPG::Server::MainServerWindow::
MainServerWindow(const QString &fileName, QWidget *parent)
  : QMainWindow(parent),
    quarantDir(NULL)
{
  LOGI("Creating MainWindow");
  setWindowTitle(fileName);

  // Does not change the following name
  // it is used in the notifier system
  setAccessibleName("MainServerWindow");

  clientList=NULL;
  objectList=NULL;
  quarantineList=NULL;
  running   =false;
  alert     =false;
  quaranActFirstImage=true;

  numQuarantFiles=0;

  server=new ServerThread();

  // Registrering metatype (needed for signal/slot arguments)
  qRegisterMetaType<ENetAddress>("ENetAddress");
  qRegisterMetaType<tReceivedPacket>("tReceivedPacket");

  workspace=new QWorkspace();
  setCentralWidget(workspace);

  // FtpServer
  ftpServer=new FtpServer(this);


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

  // Init database
  QSqlDatabase db= QSqlDatabase::addDatabase("QPSQL", "rainbru");
  db.setHostName(serverConfig->getHostName().c_str());
  db.setDatabaseName(serverConfig->getDatabaseName().c_str());
  db.setUserName(serverConfig->getUserName().c_str());
  db.setPassword(serverConfig->getPassword().c_str());
  bool ok = db.open();
  
  if (ok){
    LOGI("Connection to database successfull");
    serverLog->addMessage (SLL_INFORMATIVE, 
      tr("Connection to database successfull"));
  }
  else{
    LOGE("Connection to database failed");
    QMessageBox::critical ( this, tr("Database connection error"), 
      tr("An error occured during the database connection. Please "
	 "change the server's configuration and restart the server."));

    serverLog->addMessage (SLL_ERROR, 
      tr("Database connection failed : you MUST restart server."));

    QSqlError err=db.lastError();
    LOGW("Connection to db failed");
    LOGCATS("Connection error : ");
    LOGCATS(err.text().toLatin1());
    LOGCAT();
    stopServer();
  }

  // Manage notifier
  GlobalURI globalURI;
  std::string s(globalURI.getQuarantineFile(""));
  QString qs(s.c_str());
  quarantDir=new QDir(qs);
  quarantDir->setFilter(QDir::Files);

  quarantIco1=QIcon(":/images/quarantine1.png");
  quarantIco2=QIcon(":/images/quarantine2.png");

  // System tray icon
  systemTrayIcon=new QSystemTrayIcon( quarantIco1, this );
  systemTrayIcon->setVisible(true);

  // Quarantine filelist
  quarantineList =new QuarantineList();

  connect(quarantineList, SIGNAL(filesRemoved(int)), this, 
	  SLOT(filesRemoved(int)));

  connect(ftpServer, SIGNAL(storeFile(const QString&)), 
	  quarantineList, SLOT(storeFile(const QString&)));

  connect(ftpServer, SIGNAL(transferComplete(const QString&)), 
	  quarantineList, SLOT(transferComplete(const QString&)));


  connect(server, SIGNAL(clientConnected(const ENetAddress &)),
	  this, SLOT(clientConnected(const ENetAddress &)));

  connect(server, SIGNAL(packetReceived(const tReceivedPacket&)),
	  this, SLOT(packetReceived(const tReceivedPacket&)));

  connect(systemTrayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
	  this,SLOT(systemTrayActivated(QSystemTrayIcon::ActivationReason)));

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
  delete quarantDir;
  delete systemTrayIcon;

  if (clientList){
    delete clientList;
  }

  if (objectList){
    delete objectList;
  }

  if (quarantineList){
    delete quarantineList;
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

  // The Manage/objects Action
  QAction* objAct = new QAction(tr("&Objects"), this);
  objAct->setShortcut(tr("Ctrl+O"));
  objAct->setStatusTip(tr("Manages the objects"));

  // The Manage/FTP server Action
  QAction* ftpAct = new QAction(tr("&FTP Server"), this);
  ftpAct->setShortcut(tr("Ctrl+F"));
  ftpAct->setStatusTip(tr("Manages the FTP server"));

  // The Manage/Quarantine Action
  quaranAct = new QAction(tr("&Quarantine"), this);
  quaranAct->setIcon(quarantIco2);
  quaranAct->setShortcut(tr("Ctrl+Q"));
  quaranAct->setStatusTip(tr("Manages the files in quarantine"));



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
  manageMenu->addAction(objAct);
  manageMenu->addAction(ftpAct);
  manageMenu->addAction(quaranAct);


  QMenu* helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);
  helpMenu->addAction(indexAct);


  // The tool bar
  QToolBar* toolBar=this->addToolBar("toolbar");
  toolBar->insertAction( 0, runAct );
  toolBar->insertAction( 0, stopAct );
  toolBar->addSeparator();
  toolBar->insertAction( 0, quaranAct );


  connect(confAct, SIGNAL(triggered()), this, SLOT(showConfigDialog()));
  connect(techAct, SIGNAL(triggered()), this, SLOT(showTechNoteDialog()));
  connect(indexAct, SIGNAL(triggered()), this, SLOT(showHelpDialog()));
  connect(indexAct, SIGNAL(triggered()), this, SLOT(showHelpDialog()));
  connect(runAct, SIGNAL(triggered()), this, SLOT(startServer()));

  connect(clientsAct, SIGNAL(triggered()), this, SLOT(manageClients()));
  connect(logAct, SIGNAL(triggered()), this, SLOT(showLog()));
  connect(objAct, SIGNAL(triggered()), this, SLOT(manageObjects()));
  connect(ftpAct, SIGNAL(triggered()), this, SLOT(manageFtp()));
  connect(quaranAct, SIGNAL(triggered()), this, SLOT(manageQuarantine()));

  connect(stopAct, SIGNAL(triggered()), this, SLOT(stopServer()));
  connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

  QTimer *quarantineNotifierTimer = new QTimer(this);
  connect(quarantineNotifierTimer, SIGNAL(timeout()), 
	  this, SLOT(quarantineNotifier()));

  quarantineNotifierTimer->start(700);

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
  HelpViewer shv;
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
  std::string txtFtp=StringConv::getSingleton()
    .itos(serverConfig->getFtpPort());
  std::string txtMC=StringConv::getSingleton()
    .itos(serverConfig->getMaxClient());
  std::string txtType=StringConv::getSingleton().itos(serverConfig->getType());

  CurlServerAdd csa;
  csa.setName(serverConfig->getName());
  csa.setIpAddress(serverConfig->getIpAdress());
  csa.setPort(txtPort);
  csa.setFtpPort(txtFtp);
  csa.setMaxClients(txtMC);
  csa.setDescription(serverConfig->getDesc());
  csa.setTechNote(serverConfig->getTechNote());

  csa.setType(txtType);
  csa.setUniqueName(serverConfig->getUniqueName());

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
  else if (i==NPI_FLOOD_0004){
    LOGI("A netflooder paquet with 4 bytes long was received");
    npFlooder0004 np4(0);
    np4.setData(e.data, e.dataLength);
    np4.netDeserialize();
    np4.netSerialize();

    server->getServer()->sendPacket(e.peer, &np4);


  }
}

/** Is the given client type accepted ?
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

/** Shows the log window
  *
  */
void RainbruRPG::Server::MainServerWindow::showLog(){
  serverLog->show();

}

/** Shows the object managing widget
  *
  */
void RainbruRPG::Server::MainServerWindow::manageObjects(){
  LOGI("manageObjects called");

  if (!objectList){
   objectList =new ObjectList();
  }
  workspace->addWindow(objectList);
  objectList->show();
  
}

/** Shows the FTP server widget
  *
  */
void RainbruRPG::Server::MainServerWindow::manageFtp(){
  workspace->addWindow(ftpServer);
  ftpServer->move(0,0);
  ftpServer->show();

}

/** Shows the Quarantine file list widget
  *
  * The QuarantineList instance is created in the MainServerWindow constructor
  * (MainServerWindow::MainServerWindow).
  *
  */
void RainbruRPG::Server::MainServerWindow::manageQuarantine(){
  workspace->addWindow(quarantineList);
  quarantineList->show();
}

/** Visualy notify the user that some files are waiting for approval
  *
  * It first refreshes the \ref MainServerWindow::quarantDir 
  * "quarantDir" QDir object. If new files
  * are detected (by comparing \c quarantDir->count() and 
  * \ref MainServerWindow::numQuarantFiles "numQuarantFiles"
  * it launch a visual (SystemTrayIcon) and audio (beep()) alert. 
  * quarantine is also refreshed if it exist.
  *
  * \note This is a slot, regularly called by a Qt timer.
  *
  */
void RainbruRPG::Server::MainServerWindow::quarantineNotifier(){
  LOGI("quarantineNotifier called");
  uint i;
  /* v0.0.5-193 : Fix a segfault when database connection failed
   * For some reason, the postgres plugin for Qt is no longer
   * available. It could cause a devalidation of the quarantDir
   * pointer that causes a segfault on the server startup.
   *
   */
  if (quarantDir != NULL){
    quarantDir->refresh();
    i=quarantDir->count();
  }
  else{
    const char* m="quarantineNotifier call failed.";
    LOGE(m);
    serverLog->addMessage (SLL_ERROR, m);
    return;
  }

  // If new files are arrived, alert
  if (i!=numQuarantFiles ){ 
    LOGI("A new file arrived");
    numQuarantFiles=i;

    if (quarantineList){
      quarantineList->refresh();

      if (!quarantineList->isVisible()){
	alert=true;
      }
    }

    QApplication::alert(this);
    QApplication::beep();
    systemTrayIcon->showMessage("RainbruRPG Server's quarantine",
	"Some files in quarantine are waiting for approval. Please go to "
	"the manage/quarantine menu of the server to approve or refuse it.",
	QSystemTrayIcon::Warning);
  }

  // If an alert was declared
  if (alert){
    if (quaranActFirstImage){
      quaranAct->setIcon(quarantIco2);
      quaranActFirstImage=false;
    }
    else{
      quaranAct->setIcon(quarantIco1);
      quaranActFirstImage=true;
    }
  }
}

/** A slot called when focus changed
  *
  * \param old The widget that lost focus
  * \param now The widget that have the focus
  *
  */
void RainbruRPG::Server::MainServerWindow::
focusChanged(QWidget* old, QWidget* now){
  if (quarantineList && quarantineList->isVisible()){
    alert=false;

    if (!quaranActFirstImage){
      quaranAct->setIcon(quarantIco1);
      quaranActFirstImage=true;
    }
  }
  else{
    statusBar()->showMessage(tr("Some files in quarantine are waiting "
      "for approval."), 10000);

  }
}

/** A slot called when the SystemTrayIcon is clicked
  *
  * It intends to show this window if the SystemTrayIcon is mouse-clicked.
  * But, at least on Gnome, it appears that it work only if we are on
  * the same workspace (aka virtual desktop).
  *
  * \param reason The event type
  *
  * \todo make it work on all workspace
  *
  */
void RainbruRPG::Server::MainServerWindow::
systemTrayActivated(QSystemTrayIcon::ActivationReason reason){
  switch(reason){
  case QSystemTrayIcon::Trigger:

    if (alert){
      LOGI("SystemTrayActivated called : showing main window");

      this->showMinimized();
      this->raise();
      this->setVisible(true);
      this->activateWindow();
      this->showMaximized();
      break;
    }
  }
}

/** A slot called when a file is removed from the QuarantineList
  *
  * It is important to count the removed files for the notification
  * system.
  *
  * \param i The number of removed files
  *
  * \sa \ref RainbruRPG::Gui::QuarantineList::filesRemoved()
  *          "QuarantineList::filesRemoved(int)"
  *
  */
void RainbruRPG::Server::MainServerWindow::filesRemoved(int i){
  numQuarantFiles-=i;
}

/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file configdialog.cpp
  * Iplements the server configuration dialog
  *
  */

#include <Logger.hpp>

#include "configdialog.h"

#include <QTabWidget>

/** The server configuration dialog constructor
  *
  * The defaults values are DEFAULT_SERVER_PORT for the port and 
  * DEFAULT_MAX_CLIENTS for the max client.
  *
  * \param sc The ServerConfiguration the values will be saved in
  * \param parent The parent QWidget
  *
  */
RainbruRPG::Server::ConfigDialog::
ConfigDialog(ServerConfiguration* sc, QWidget* parent)
  : QDialog(parent)
{
  this->setMinimumWidth(400);
  this->setMinimumHeight(300);
  this->setWindowTitle(tr("Server configuration"));
  this->serverConfig=sc;

  // The root layout
  QVBoxLayout *vb1=new QVBoxLayout(this);
  // The tab widget
  QTabWidget *tabWidget=new QTabWidget(this);
  vb1->addWidget(tabWidget);

  // First tab
  QWidget* page1=new QWidget();
    // The server name
    QVBoxLayout *page1vb1=new QVBoxLayout();
    page1->setLayout(page1vb1);
    QHBoxLayout *nameLayout=new QHBoxLayout();
    page1vb1->addLayout(nameLayout);
    QLabel* nameLabel=new QLabel(tr("Server name"),page1);
    leName=new QLineEdit(this);
    leName->setToolTip(tr("The server public name"));
    nameLayout->addWidget(nameLabel);
    nameLayout->addWidget(leName);

    // The server's unique name
    QHBoxLayout *uNameLayout=new QHBoxLayout();
    page1vb1->addLayout(uNameLayout);
    QLabel* uNameLabel=new QLabel(tr("Unique name"),page1);
    uName=new QLabel("",page1);
    uName->setAlignment(Qt::AlignLeft);
    uNameLayout->addWidget(uNameLabel);
    uNameLayout->addWidget(uName);

    // The server description
    QLabel* descLabel=new QLabel(tr("Server description :"),this);
    page1vb1->addWidget(descLabel);
    teDesc=new QTextEdit(this);
    teDesc->setToolTip(tr("The server's multiline description"));
    page1vb1->addWidget(teDesc);
    // Adding tab
    tabWidget->addTab(page1, "Identification");

    // The server's type
    QLabel* typeLabel=new QLabel(tr("Server's type :"),this);
    page1vb1->addWidget(typeLabel);
    QLabel* typeLabel2=new QLabel(
	    tr("If some users are already playing in your server, you "
	       "should not change the server's type because they could "
	       "not play anymore."),this);

    typeLabel2->setWordWrap(true);
    page1vb1->addWidget(typeLabel2);
    QHBoxLayout *typeLayout=new QHBoxLayout();
    page1vb1->addLayout(typeLayout);
    typeButtonsGroup=new QButtonGroup();
    QGroupBox* typeButtons=new QGroupBox(tr("Type"));
      typeLayout->addWidget(typeButtons);
      QRadioButton* radio1=new QRadioButton(tr("Fantasy"), typeButtons);
      QRadioButton* radio2=new QRadioButton(tr("Contemporary"), typeButtons);
      QRadioButton* radio3=new QRadioButton(tr("Futuristic"), typeButtons);
      QRadioButton* radio4=new QRadioButton(tr("Post-apocalyptic"), 
					    typeButtons);

      typeButtonsGroup->addButton(radio1);
      typeButtonsGroup->addButton(radio2);
      typeButtonsGroup->addButton(radio3);
      typeButtonsGroup->addButton(radio4);

      typeButtonsGroup->setId(radio1, 1);
      typeButtonsGroup->setId(radio2, 2);
      typeButtonsGroup->setId(radio3, 3);
      typeButtonsGroup->setId(radio4, 4);


      QVBoxLayout *vbox = new QVBoxLayout;
        vbox->addWidget(radio1);
        vbox->addWidget(radio2);
        vbox->addWidget(radio3);
        vbox->addWidget(radio4);
        vbox->addStretch(1);
        typeButtons->setLayout(vbox);

    QGroupBox* typeDesc=new QGroupBox(tr("Description"));
      typeLayout->addWidget(typeDesc);
      labTypeDescription=new QLabel(tr("No type selected"));
      labTypeDescription->setAlignment(Qt::AlignLeft|Qt::AlignTop);
      labTypeDescription->setWordWrap(true);
      QVBoxLayout *vbox2 = new QVBoxLayout;
        vbox2->addWidget(labTypeDescription);
        typeDesc->setLayout(vbox2);
	typeDesc->setFixedWidth(250);

  // Second page
  QWidget* page2=new QWidget();
    QVBoxLayout *page2vb1=new QVBoxLayout();
    page2->setLayout(page2vb1);
    // The group boxes
    QHBoxLayout *boxesLayout=new QHBoxLayout();
      page2vb1->addLayout(boxesLayout);
      QGroupBox* modeGroup=new QGroupBox(tr("Server modes"), this);
      QGroupBox* optsGroup=new QGroupBox(tr("Server options"), this);
      boxesLayout->addWidget(modeGroup);
      boxesLayout->addWidget(optsGroup);
      // Server's modes
      QVBoxLayout *vbModes=new QVBoxLayout();
      modeGroup->setLayout(vbModes);
      cbPlay=new QCheckBox(tr("Player"), this);
      cbPlay->setToolTip(tr("This server accepts client "
			    "connections for playing"));
      vbModes->addWidget(cbPlay);
      cbEdit=new QCheckBox(tr("Editor"), this);
      cbEdit->setToolTip(tr("This server accepts editor connections"));
      vbModes->addWidget(cbEdit);
      cbFlood=new QCheckBox(tr("Flooder"), this);
      cbFlood->setToolTip(tr("This server accepts netflooder connections"));
      vbModes->addWidget(cbFlood);
      vbModes->addStretch(1);

      // Server's options
      QGridLayout *glOpts=new QGridLayout();
      optsGroup->setLayout(glOpts);
      QLabel* labIp=new QLabel(tr("IP adress"), this);
      glOpts->addWidget(labIp, 0, 0);
      leIp=new QLineEdit(this);
      glOpts->addWidget(leIp, 0, 1);
      leIp->setToolTip(tr("The IP adress to access this server"));
      // UDP port
      QLabel* labPort=new QLabel(tr("UDP Port"), this);
      glOpts->addWidget(labPort, 1, 0);
      sbPort=new QSpinBox(this);
      sbPort->setToolTip(tr("The listening UDP port"));
      sbPort->setMaximum(0xFFFF);
      sbPort->setValue(DEFAULT_SERVER_PORT);
      glOpts->addWidget(sbPort, 1, 1);
      // FTP port
      QLabel* labFtpPort=new QLabel(tr("FTP Port"), this);
      glOpts->addWidget(labFtpPort, 2, 0);
      sbFtpPort=new QSpinBox(this);
      sbFtpPort->setToolTip(tr("The FTP control channel port"));
      sbFtpPort->setMaximum(0xFFFF);
      sbFtpPort->setValue(DEFAULT_SERVER_PORT);
      glOpts->addWidget(sbFtpPort, 2, 1);
      // Max client
      QLabel* labCli=new QLabel(tr("Max client"), this);
      glOpts->addWidget(labCli, 3, 0);
      sbCli=new QSpinBox(this);
      sbCli->setToolTip(tr("The maximum number of accepted clients"));
      sbCli->setMaximum(0xFFFF);
      sbCli->setValue(DEFAULT_MAX_CLIENTS);
      glOpts->addWidget(sbCli, 3, 1);
      glOpts->setRowStretch( 4, 1);
    // Adding tab
    tabWidget->addTab(page2, "Network");

  // Second page
  QWidget* page3=new QWidget();
    QVBoxLayout *page3vb1=new QVBoxLayout();
    page3->setLayout(page3vb1);
    // Database connection
    QGroupBox* dbGroup=new QGroupBox(tr("Database connection"), this);
    page3vb1->addWidget(dbGroup);
    QGridLayout *dbOpts=new QGridLayout();
    dbGroup->setLayout(dbOpts);
      // HostName
      QLabel* labDbHost=new QLabel(tr("HostName"));
      dbOpts->addWidget(labDbHost, 0, 0);
      leDbHost=new QLineEdit("localhost", this);
      dbOpts->addWidget(leDbHost, 0, 1);
      // Database name
      QLabel* labDbName=new QLabel(tr("Database name"));
      dbOpts->addWidget(labDbName, 1, 0);
      leDbName=new QLineEdit("rainbrurpg", this);
      dbOpts->addWidget(leDbName, 1, 1);
      // Role name
      QLabel* labDbRole=new QLabel(tr("Role name"));
      dbOpts->addWidget(labDbRole, 2, 0);
      leDbRole=new QLineEdit("rainbrurpg", this);
      dbOpts->addWidget(leDbRole, 2, 1);
      // Password
      QLabel* labDbPwd=new QLabel(tr("Password"));
      dbOpts->addWidget(labDbPwd, 3, 0);
      leDbPwd=new QLineEdit("", this);
      leDbPwd->setEchoMode(QLineEdit::Password);
      dbOpts->addWidget(leDbPwd, 3, 1);

      dbOpts->setRowStretch( 4, 1);
    // Adding tab
    tabWidget->addTab(page3, "Database");



  // TechNote info
  showTechNote=new QLabel(this);
  showTechNote->setToolTip(tr("Is the technical note contains text"));
  vb1->addWidget(showTechNote);
  // The dialog's button
  QHBoxLayout *buttonLayout=new QHBoxLayout();
  vb1->addLayout(buttonLayout);
  buttonLayout->addStretch(100);
  QPushButton *btnOk=new QPushButton(tr("OK"), this );
  buttonLayout->addWidget(btnOk);


  // Connections
  connect (btnOk, SIGNAL(clicked()), this, SLOT(controls()));
  connect(teDesc, SIGNAL(textChanged()), this, SLOT(descriptionChanged()));
  connect(leName, SIGNAL(textChanged(const QString&)), this, 
	  SLOT(nameChanged()));
  connect(cbPlay, SIGNAL(stateChanged(int)), this, SLOT(playModeChanged(int)));
  connect(cbEdit, SIGNAL(stateChanged(int)), this, SLOT(editModeChanged(int)));
  connect(cbFlood, SIGNAL(stateChanged(int)), this, 
	  SLOT(floodModeChanged(int)));
  connect(sbPort, SIGNAL(valueChanged(int)), this, SLOT(portChanged(int)));
  connect(sbFtpPort, SIGNAL(valueChanged(int)), this, 
	  SLOT(ftpPortChanged(int)));
  connect(sbCli, SIGNAL(valueChanged(int)), this, SLOT(maxClientChanged(int)));
  connect(leIp, SIGNAL(textChanged(const QString&)), this, 
	  SLOT(ipAddressChanged(const QString&)));

  connect(typeButtonsGroup, SIGNAL(buttonClicked(int)), this, 
	  SLOT(serverTypeChanged(int)));

  // database related connections
  connect(leDbHost, SIGNAL(textChanged(const QString&)), this, 
	  SLOT(hostNameChanged(const QString&)));
  connect(leDbName, SIGNAL(textChanged(const QString&)), this, 
	  SLOT(dbNameChanged(const QString&)));
  connect(leDbRole, SIGNAL(textChanged(const QString&)), this, 
	  SLOT(UserNameChanged(const QString&)));
  connect(leDbPwd, SIGNAL(textChanged(const QString&)), this, 
	  SLOT(passwordChanged(const QString&)));

  initValues();
}

/** The destructor
  *
  */
RainbruRPG::Server::ConfigDialog::~ConfigDialog(){
  delete leName;
  delete teDesc;
  delete cbPlay;
  delete cbEdit;
  delete cbFlood;
  delete sbPort;
  delete sbFtpPort;
  delete sbCli;
  delete showTechNote;
  delete leIp;
  delete labTypeDescription;
  delete typeButtonsGroup;
  delete uName;

  // Database line edit widgets
  delete leDbHost;
  delete leDbName;
  delete leDbRole;
  delete leDbPwd;

}

/** Initialize the dialog's values
  *
  * The values used for initialization are taken from the ServerConfiguration
  * instance passed as parameter of the constructor of this dialog.
  *
  */
void RainbruRPG::Server::ConfigDialog::initValues(){
  LOGI("Setting initial values");
  leName->setText(serverConfig->getName().c_str());
  teDesc->setText(serverConfig->getDesc().c_str());
  cbPlay->setChecked(serverConfig->getPlayMode());
  cbEdit->setChecked(serverConfig->getEditMode());
  cbFlood->setChecked(serverConfig->getFloodMode());
  sbPort->setValue(serverConfig->getPort());
  sbFtpPort->setValue(serverConfig->getFtpPort());
  sbCli->setValue(serverConfig->getMaxClient());
  leIp->setText(serverConfig->getIpAdress().c_str());

  QString t(tr("Showing technical note : "));
  QString tn(serverConfig->getTechNote().c_str());

  if (tn.isEmpty()){
    t.append(tr("No"));
  }
  else{
    t.append(tr("Yes"));
  }

  showTechNote->setText(t);

  // Database values
  leDbHost->setText(serverConfig->getHostName().c_str());
  leDbName->setText(serverConfig->getDatabaseName().c_str());
  leDbRole->setText(serverConfig->getUserName().c_str());
  leDbPwd->setText(serverConfig->getPassword().c_str());

  // Server's type
  int type=serverConfig->getType();
  QAbstractButton* btn=typeButtonsGroup->button(type);
  btn->setChecked(true);
  // Calling the clicked slot to show the description at startup
  serverTypeChanged(type);

  // Unique name
  uName->setText(serverConfig->getUniqueName().c_str());
}
/** A slot used when the server's description changed
  *
  */
void RainbruRPG::Server::ConfigDialog::descriptionChanged(){
  std::string temp(teDesc->toPlainText().toLatin1());
  serverConfig->setDesc(temp);
}

/** A slot used when the server's name changed
  *
  */
void RainbruRPG::Server::ConfigDialog::nameChanged(){
  std::string temp(leName->text().toLatin1());
  serverConfig->setName(temp);
}

/** A slot used when the server's playMode changed
  *
  * \param i The new state of the play mode combobox
  *
  */
void RainbruRPG::Server::ConfigDialog::playModeChanged(int i){
  if (i==Qt::Checked){
    serverConfig->setPlayMode(true);
  }
  else{
    serverConfig->setPlayMode(false);
  }
}

/** A slot used when the server's editMode changed
  *
  * \param i The new state of the edit mode combobox
  *
  */
void RainbruRPG::Server::ConfigDialog::editModeChanged(int i){
  if (i==Qt::Checked){
    serverConfig->setEditMode(true);
  }
  else{
    serverConfig->setEditMode(false);
  }
}

/** A slot used when the server's floodMode changed
  *
  * \param i The new state of the flood mode combobox
  *
  */
void RainbruRPG::Server::ConfigDialog::floodModeChanged(int i){
  if (i==Qt::Checked){
    serverConfig->setFloodMode(true);
  }
  else{
    serverConfig->setFloodMode(false);
  }
}

/** A slot used when the server's UDP port changed
  *
  * \param i The new value of the UDP port spin box
  *
  */
void RainbruRPG::Server::ConfigDialog::portChanged(int i){
  serverConfig->setPort(i);
}

/** A slot used when the server's maxClientMode changed
  *
  * \param i The new value of the maxClient spin box
  *
  */
void RainbruRPG::Server::ConfigDialog::maxClientChanged(int i){
  serverConfig->setMaxClient(i);

}

/** Makes some control before accept the dialog
  *
  */
void RainbruRPG::Server::ConfigDialog::controls(){
  LOGI("Controlling configuration values");

  bool acc=true;

  std::string s=serverConfig->getName();

  // Testing if the name is empty
  if (s.empty()){
    acc=false;
    QMessageBox::warning ( this, tr("Configuration error"), 
	tr("The server's name cannot be empty."), QMessageBox::Ok );
  }

  if (acc){
    accept();
  }
}

/** The slot called if the IP address change
  *
  * \param t The new IP address
  *
  */
void RainbruRPG::Server::ConfigDialog::ipAddressChanged(const QString& t){
  std::string temp(t.toLatin1());
  serverConfig->setIpAdress(temp);
}

/** The slot called if the hostname change
  *
  * \param t The new value
  *
  */
void RainbruRPG::Server::ConfigDialog::hostNameChanged(const QString& t){
  std::string temp(t.toLatin1());
  serverConfig->setHostName (temp);
}

/** The slot called if the database name change
  *
  * \param t The new value
  *
  */
void RainbruRPG::Server::ConfigDialog::dbNameChanged(const QString& t){
  std::string temp(t.toLatin1());
  serverConfig->setDatabaseName (temp);

}

/** The slot called if the username change
  *
  * \param t The new value
  *
  */
void RainbruRPG::Server::ConfigDialog::UserNameChanged(const QString& t){
  std::string temp(t.toLatin1());
  serverConfig->setUserName (temp);

}

/** The slot called if the password change
  *
  * \param t The new value
  *
  */
void RainbruRPG::Server::ConfigDialog::passwordChanged(const QString& t){
  std::string temp(t.toLatin1());
  serverConfig->setPassword (temp);

}

/** A slot used when the server's FTP port changed
  *
  * \param i The new value of the FTP port spin box
  *
  */
void RainbruRPG::Server::ConfigDialog::ftpPortChanged(int i){
  serverConfig->setFtpPort(i);

}

/** The slot called when the server's type change
  *
  * It change the labTypeDescription QLabel content to show a short
  * description of the selected type.
  *
  * \param i The new type index
  *
  */
void RainbruRPG::Server::ConfigDialog::serverTypeChanged(int i){
  LOGI("Server type changed");
  LOGCATS("New type is ");
  LOGCATI(i);
  LOGCAT();

  QString s;

  switch (i){
  case 1:
    s="The game is situated at medieval time, in a world where the magic "
      "is important.";
    serverConfig->setType(1);
    break;

  case 2:
    s="The game is played in our current time.";
    serverConfig->setType(2);
    break;

  case 3:
    s="The game is based on a distant era whith advanced technologies.";
    serverConfig->setType(3);
    break;

  case 4:
    s="The player is in a rebuilding world, recently devastated by an "
      "apocalypse.";
    serverConfig->setType(4);
    break;

  default:
    s="No type selected";
  }

  labTypeDescription->setText(s);
}

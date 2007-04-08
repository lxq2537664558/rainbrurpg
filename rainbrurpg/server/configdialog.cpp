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

#include <logger.h>

#include "configdialog.h"

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

  // The server name
  QHBoxLayout *nameLayout=new QHBoxLayout();
  vb1->addLayout(nameLayout);
  QLabel* nameLabel=new QLabel(tr("Server name"),this);
  leName=new QLineEdit(this);
  leName->setToolTip(tr("The server public name"));
  nameLayout->addWidget(nameLabel);
  nameLayout->addWidget(leName);

  // The server description
  QLabel* descLabel=new QLabel(tr("Server description :"),this);
  vb1->addWidget(descLabel);
  teDesc=new QTextEdit(this);
  teDesc->setToolTip(tr("The server's multiline description"));
  vb1->addWidget(teDesc);

  // TechNote info
  showTechNote=new QLabel(this);
  showTechNote->setToolTip(tr("Is the technical note contains text"));
  vb1->addWidget(showTechNote);


  // The group boxes
  QHBoxLayout *boxesLayout=new QHBoxLayout();
  vb1->addLayout(boxesLayout);
  QGroupBox* modeGroup=new QGroupBox(tr("Server modes"), this);
  QGroupBox* optsGroup=new QGroupBox(tr("Server options"), this);
  boxesLayout->addWidget(modeGroup);
  boxesLayout->addWidget(optsGroup);

  // Server's modes
  QVBoxLayout *vbModes=new QVBoxLayout();
  modeGroup->setLayout(vbModes);
  cbPlay=new QCheckBox(tr("Player"), this);
  cbPlay->setToolTip(tr("This server accepts client connections for playing"));
  vbModes->addWidget(cbPlay);
  cbEdit=new QCheckBox(tr("Editor"), this);
  cbEdit->setToolTip(tr("This server accepts editor connections"));
  vbModes->addWidget(cbEdit);
  cbFlood=new QCheckBox(tr("Flooder"), this);
  cbFlood->setToolTip(tr("This server accepts netflooder connections"));
  vbModes->addWidget(cbFlood);

  // Server's options
  QGridLayout *glOpts=new QGridLayout();
  optsGroup->setLayout(glOpts);
  QLabel* labIp=new QLabel(tr("IP adress"), this);
  glOpts->addWidget(labIp, 0, 0);
  leIp=new QLineEdit(this);
  glOpts->addWidget(leIp, 0, 1);
  leIp->setToolTip(tr("The IP adress to access this server"));
  QLabel* labPort=new QLabel(tr("Port"), this);
  glOpts->addWidget(labPort, 1, 0);
  sbPort=new QSpinBox(this);
  sbPort->setToolTip(tr("The listening port"));
  sbPort->setMaximum(0xFFFF);
  sbPort->setValue(DEFAULT_SERVER_PORT);
  glOpts->addWidget(sbPort, 1, 1);
  QLabel* labCli=new QLabel(tr("Max client"), this);
  glOpts->addWidget(labCli, 2, 0);
  sbCli=new QSpinBox(this);
  sbCli->setToolTip(tr("The maximum number of accepted clients"));
  sbCli->setMaximum(0xFFFF);
  sbCli->setValue(DEFAULT_MAX_CLIENTS);
  glOpts->addWidget(sbCli, 2, 1);


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
  connect(sbCli, SIGNAL(valueChanged(int)), this, SLOT(maxClientChanged(int)));
  connect(leIp, SIGNAL(textChanged(const QString&)), this, 
	  SLOT(ipAddressChanged(const QString&)));



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
  delete sbCli;
  delete showTechNote;
  delete leIp;
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

/** A slot used when the server's portMode changed
  *
  * \param i The new value of the port spin box
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

/** The slot called id the IP address change
  *
  * \param t The new IP address
  *
  */
void RainbruRPG::Server::ConfigDialog::ipAddressChanged(const QString& t){
  std::string temp(t.toLatin1());
  serverConfig->setIpAdress(temp);
}

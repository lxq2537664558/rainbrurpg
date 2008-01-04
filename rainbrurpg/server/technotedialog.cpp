/*
 *  Copyright 2006-2008 Jerome PASQUIER
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

#include "technotedialog.h"

/** The server configuration dialog constructor
  *
  * The defaults values are DEFAULT_SERVER_PORT for the port and 
  * DEFAULT_MAX_CLIENTS for the max client.
  *
  * \param sc The ServerConfiguration the technote will be saved in
  * \param parent The parent QWidget
  *
  */
RainbruRPG::Server::TechNoteDialog::
TechNoteDialog(ServerConfiguration* sc, QWidget* parent)
  : QDialog(parent)
{
  this->setMinimumWidth(400);
  this->setMinimumHeight(300);
  this->setWindowTitle(tr("Server configuration"));
  this->serverConfig=sc;

  // The root layout
  QVBoxLayout *vb1=new QVBoxLayout(this);

  // The help label
  QLabel* helpLabel=new QLabel(
    tr("Every server can have a technical note. This is a multiline text "
       "that is shown in the client screen at the connection. It is intended "
       "to show technical informations.\n\n If You let this field empty, "
       "no text will popup at the connection to this server."),this);
  helpLabel->setWordWrap(true);
  vb1->addWidget(helpLabel);

  // The server description
  QLabel* descLabel=new QLabel(tr("Server technical note :"),this);
  vb1->addWidget(descLabel);
  teTechNote=new QTextEdit(this);
  teTechNote->setToolTip(tr("The server's multiline technical note"));
  vb1->addWidget(teTechNote);

  // The dialog's button
  QHBoxLayout *buttonLayout=new QHBoxLayout();
  vb1->addLayout(buttonLayout);
  buttonLayout->addStretch(100);
  QPushButton *btnOk=new QPushButton(tr("OK"), this );
  buttonLayout->addWidget(btnOk);

  // Connections
  connect(btnOk, SIGNAL(clicked()), this, SLOT(accept()));
  connect(teTechNote, SIGNAL(textChanged()), this, SLOT(techNoteChanged()));

  initValues();
}

/** The destructor
  *
  */
RainbruRPG::Server::TechNoteDialog::~TechNoteDialog(){
  delete teTechNote;
}

/** Initialize the technical value
  *
  */
void RainbruRPG::Server::TechNoteDialog::initValues(void){
  teTechNote->setText(serverConfig->getTechNote().c_str());
}

/** A slot called if the technote changes
  *
  */
void RainbruRPG::Server::TechNoteDialog::techNoteChanged(){
  std::string temp(teTechNote->toPlainText().toLatin1());
  serverConfig->setTechNote(temp);
}

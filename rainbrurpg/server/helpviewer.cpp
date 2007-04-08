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

#include "helpviewer.h"
#include "../config.h"

/** The server's help viewer constructor
  *
  * \param parent The parent widget
  *
  */
RainbruRPG::Server::ServerHelpViewer::ServerHelpViewer(QWidget* parent) 
  :QDialog(parent)
{
  home= USER_INSTALL_PREFIX "/share/doc/RainbruRPG/index.html";

  this->setMinimumWidth(600);
  this->setMinimumHeight(400);
  this->setWindowTitle(tr("Server's help viewer"));

  QVBoxLayout* vb1=new QVBoxLayout(this);
  QTextBrowser* tb=new QTextBrowser(this);
  vb1->addWidget(tb);

  tb->setSource(home);

  // The dialog's button
  QHBoxLayout *buttonLayout=new QHBoxLayout();
  vb1->addLayout(buttonLayout);
  buttonLayout->addStretch(100);
  QPushButton *btnOk=new QPushButton(tr("OK"), this );
  buttonLayout->addWidget(btnOk);

  connect(btnOk, SIGNAL(clicked()), this, SLOT(accept()) );
}

/** The destructor
  *
  */
RainbruRPG::Server::ServerHelpViewer::~ServerHelpViewer(){

}

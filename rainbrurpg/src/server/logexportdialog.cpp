/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file logexportdialog.cpp
  * Implements a class to help user to export log content
  *
  */

#include "logexportdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QTextEdit>
#include <QFileDialog>
#include <QDir>

/** The default constructor
  *
  * \param parent The parent widget
  *
  */
RainbruRPG::Server::LogExportDialog::LogExportDialog(QWidget* parent)
  :QDialog(parent)
{
  setWindowTitle(tr("Log Exporter dialog"));
  setMinimumSize(600, 300);

  // The main layout
  QVBoxLayout* vb1=new QVBoxLayout();
  this->setLayout(vb1);

  // The filename label
  QLabel* lblFilename=new QLabel(tr("Log filename"), this);
  vb1->addWidget(lblFilename);

  // ****************************************
  // The filename layout
  QHBoxLayout* hb1=new QHBoxLayout();
  vb1->addLayout(hb1);

  // The filename line edit
  leFilename=new QLineEdit( this);
  hb1->addWidget(leFilename);

  // The change filename  button
  QPushButton* btnChange=new QPushButton(tr("Change"), this);
  hb1->addWidget(btnChange);

  // ****************************************
  // The preview label layout
  QHBoxLayout* hb2=new QHBoxLayout();
  vb1->addLayout(hb2);

  //The preview Label
  QLabel* labPreview=new QLabel(tr("Preview"), this);
  hb2->addWidget(labPreview);
  // A space between the Preview label and Refresh button
  hb2->addStretch(1);
  // The Refresh button
  QPushButton* btnRefresh=new QPushButton(tr("Refresh"), this);
  hb2->addWidget(btnRefresh);

  //The preview TextEdit
  QTextEdit* tePreview=new QTextEdit();
  vb1->addWidget(tePreview);

  // ****************************************
  // The buttons layout
  QHBoxLayout* hbb=new QHBoxLayout();
  vb1->addLayout(hbb);

  // The Cancel button
  QPushButton* btnCancel=new QPushButton(tr("Cancel"), this);
  hbb->addWidget(btnCancel);

  // A space between the OK and Cancel buttons
  hbb->addStretch(1);

  // The OK button
  QPushButton* btnOk=new QPushButton(tr("OK"), this);
  hbb->addWidget(btnOk);

  // Connections
  connect( btnOk, SIGNAL(clicked()), this, SLOT(accept()) );
  connect( btnCancel, SIGNAL(clicked()), this, SLOT(reject()) );
  connect( btnChange, SIGNAL(clicked()), this, SLOT(changeFilename()) );

  // Other initializations
  initFilename();
}

/** The destructor
  *
  */
RainbruRPG::Server::LogExportDialog::~LogExportDialog(){

}

/** The Change button slot
  *
  */
void RainbruRPG::Server::LogExportDialog::changeFilename(){
  QString s=QFileDialog::getSaveFileName();
  leFilename->setText(s);
  filename=s;
}

/** Creates a filename based on the current directory and set it to the
  * filename LineEdit
  *
  */
void RainbruRPG::Server::LogExportDialog::initFilename(){
  QDir dir;
  QString s=dir.absoluteFilePath("server.export.log");
  leFilename->setText(s);
  filename=s;
}

/** Returns the chosen filename
  *
  * \return the text of leFilename
  *
  */
const QString& RainbruRPG::Server::LogExportDialog::getFilename(){
  return filename;
}

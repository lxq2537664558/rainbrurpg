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

#include "quarantinelist.h"

/** The default constructor
  *
  * \param parent The parent widget
  *
  */
RainbruRPG::Gui::QuarantineList::QuarantineList(QWidget* parent) 
  :QWidget(parent){

  setWindowTitle(tr("Quarantine"));
  setMinimumSize(500, 150);

 // The main layout
  QVBoxLayout* vb1=new QVBoxLayout();
  this->setLayout(vb1);

  // The tool bar
  QToolBar* toolBar=new QToolBar(this);
  toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);

  QAction *previewAct=new QAction(tr("Preview"), toolBar);
  QAction *approveAct=new QAction(tr("Approve"), toolBar);
  QAction *deleteAct=new QAction(tr("Delete"), toolBar);

  previewAct->setEnabled(false);
  approveAct->setEnabled(false);
  deleteAct->setEnabled(false);

  toolBar->addAction(previewAct);
  toolBar->addAction(approveAct);
  toolBar->addAction(deleteAct);
  vb1->addWidget(toolBar);

  // The list widget
  tree=new QTreeWidget();
  tree->setSortingEnabled(true);
  QStringList header;
  header << tr("Filename") << tr("Size") << tr("Usage") << tr("Type");
  tree->setColumnCount(4);
  tree->setHeaderLabels(header);
  vb1->addWidget(tree);

  // Feeding table
  GlobalURI gu;
  std::string s(gu.getQuarantineFile(""));
  QString qs(s.c_str());
  QDir dir(qs);
  int i=dir.count();

  LOGCATS("Files in directory : ");
  LOGCATI(i);
  LOGCAT();

  QFileInfoList list=dir.entryInfoList();

  for (int i = 0; i < list.size(); ++i) {
    addFile(list.at(i));
  }
}

/** the default destructor
  *
  */
RainbruRPG::Gui::QuarantineList::~QuarantineList(){
  delete tree;
}

void RainbruRPG::Gui::QuarantineList::addFile(QFileInfo fi){

  if (fi.isFile()){
    // adding it to the list
    QTreeWidgetItem *it= new QTreeWidgetItem(tree);
    it->setText(0,fi.fileName() );
    it->setText(1,fileSizeToString(fi.size()) );
   
    tree->addTopLevelItem( it );
  }
}

/** Get the filesize in text format
  *
  * \return A human-readable form of the filesize 
  *
  */
QString RainbruRPG::Gui::QuarantineList::fileSizeToString(qint64 filesize){
  QString s;

  float fs;

  int mo=1024*1024;

  if (filesize>mo){
    fs=filesize/mo;
    s+=QString::number(fs, 'f', 2);
    s+=" Mb";
  }
  else if (filesize>1024){
    fs=filesize/1024;
    s+=QString::number(fs, 'f', 2);
    s+=" kb";
  }
  else{
    s+=QString::number(filesize);
    s+=" b";
  }

  return s;
}

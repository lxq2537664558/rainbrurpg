/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file quarantinelist.cpp
  * Implements a widget showing files in quarantine
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
  //  toolBar->setToolButtonStyle(Qt::ToolButtonTextOnly);

  previewAct=new QAction(QIcon(":/images/preview.png"),
			 tr("Preview"), toolBar);
  approveAct=new QAction(QIcon(":/images/accept.png"),
			 tr("Approve"), toolBar);
  deleteAct=new QAction(QIcon(":/images/refuse.png"),
			tr("Delete"), toolBar);
  QAction* refreshAct=new QAction(tr("Refresh"), toolBar);

  QAction* helpAct=new QAction(tr("Help"), toolBar);

  previewAct->setEnabled(false);
  approveAct->setEnabled(false);
  deleteAct->setEnabled(false);

  toolBar->addAction(previewAct);
  toolBar->addAction(approveAct);
  toolBar->addAction(deleteAct);
  toolBar->addSeparator();
  toolBar->addAction(refreshAct);
  toolBar->addSeparator();
  toolBar->addAction(helpAct);

  vb1->addWidget(toolBar);

  labStillInTransfer=new 
    QLabel("At least one file is still in transfer, it's size and its type "
	   "could be wrong. You can click the refresh button to update "
	   "informations and look at FTP server (Ctrl+F) to see if the "
	   "transfer is finished.");
  labStillInTransfer->setVisible(false);
  labStillInTransfer->setWordWrap(true);
  vb1->addWidget(labStillInTransfer);

  // The list widget
  tree=new QTreeWidget();
  tree->setSortingEnabled(true);
  tree->setSelectionMode(QAbstractItemView::ExtendedSelection);
  QStringList header;
  header << tr("Filename") << tr("Size") << tr("Usage") << tr("Type");
  tree->setColumnCount(4);
  tree->setHeaderLabels(header);
  vb1->addWidget(tree);

  refresh();


  connect(tree, SIGNAL(itemSelectionChanged()), this,
	  SLOT(treeSelectionChanged()));

  connect(tree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),
	  this, SLOT(treeDoubleClicked(QTreeWidgetItem*,int)));

  connect(previewAct, SIGNAL(triggered()), this, SLOT(filePreview()));
  connect(approveAct, SIGNAL(triggered()), this, SLOT(fileAccept()));
  connect(deleteAct,  SIGNAL(triggered()), this, SLOT(fileRefused()));
  connect(refreshAct, SIGNAL(triggered()), this, SLOT(refresh()));
  connect(helpAct,    SIGNAL(triggered()), this, SLOT(showHelp()));

}

/** the default destructor
  *
  */
RainbruRPG::Gui::QuarantineList::~QuarantineList(){
  delete tree;

  delete previewAct;
  delete approveAct;
  delete deleteAct;

  delete labStillInTransfer;
}

/** Adds a file to the tree widget
  *
  * \param fi A QFileInfo object pointing the file to add
  *
  */
void RainbruRPG::Gui::QuarantineList::addFile(QFileInfo fi){
  LOGI("Addfile called");
  QBrush red(QColor(250,0,0));
  QBrush orange(QColor(0, 0, 240));
  QBrush green(QColor(0,250,0));

  bool fileInTransfer;

  if (fi.isFile()){

    // Is this file is in storedFile list
    QRegExp rexp(fi.fileName());
    
    if (storedFiles.indexOf(rexp)==-1){
      LOGI("The file is NOT being stored");
      LOGCATS("filename=");
      LOGCATS(fi.fileName().toLatin1());
      LOGCAT();

      LOGCATS("storedFiles=");
      LOGCATS(storedFiles.join(";").toLatin1());
      LOGCAT();

      fileInTransfer=false;
    }
    else{
      LOGI("The file is being stored");
      fileInTransfer=true;
      labStillInTransfer->setVisible(true);

    }

    // adding it to the list
    QTreeWidgetItem *it= new QTreeWidgetItem(tree);
    it->setText(0,fi.fileName() );
    it->setText(1,fileSizeToString(fi.size()) );
   
    // Get the mime-type
    FileTypeGuesser ftg;
    std::string stdFn(fi.absoluteFilePath().toLatin1());
    std::string strMime=ftg.getMimeType(stdFn);
    it->setText(2,strMime.c_str() );

    tQuarantineFileStatus status=ftg.getFileStatus(stdFn);
    std::string strStatus;
    switch(status){
      case QFS_ACCEPTED:
	strStatus="Accepted";
	it->setForeground ( 0, green);
	it->setForeground ( 1, green);
	it->setForeground ( 2, green);
	it->setForeground ( 3, green);
	break;
      case QFS_REFUSED:
	strStatus="Refused";
	it->setForeground ( 0, red);
	it->setForeground ( 1, red);
	it->setForeground ( 2, red);
	it->setForeground ( 3, red);
	break;
      case QFS_UNKNOWN:
	strStatus="Unknown";
	it->setForeground ( 0, orange);
	it->setForeground ( 1, orange);
	it->setForeground ( 2, orange);
	it->setForeground ( 3, orange);
	break;
      case QFS_WRONGEXT:
	strStatus="Wrong extension";
	it->setForeground ( 0, orange);
	it->setForeground ( 1, orange);
	it->setForeground ( 2, orange);
	it->setForeground ( 3, orange);
	break;
      case QFS_TESTEDEXT:
	strStatus="Tested but unlisted extension";
	break;
    default:
	strStatus="ERROR";
	it->setForeground ( 0, red);
	it->setForeground ( 1, red);
	it->setForeground ( 2, red);
	it->setForeground ( 3, red);
    }

    it->setText(3,strStatus.c_str() );

    //    if (fileInTransfer){
    //      it->setText(3,"Still in transfer...");
    //    }

    tree->addTopLevelItem( it );
  }
}

/** Get the filesize in text format
  *
  * \param filesize The file size in bytes
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

/** Refresh the file list
  *
  * Feeds the table with the files in quarantine.
  *
  */
void RainbruRPG::Gui::QuarantineList::refresh(){
  tree->clear();
  // Feeding table
  GlobalURI gu;
  std::string s(gu.getQuarantineFile(""));
  QString qs(s.c_str());
  QDir dir(qs);
  int i=dir.count();

  QFileInfoList list=dir.entryInfoList();

  for (int i = 0; i < list.size(); i++) {
    addFile(list.at(i));
  }
}

/** The slot called when the tree's selection changed
  *
  * Here wa enabled or disable some actions.
  *
  */
void RainbruRPG::Gui::QuarantineList::treeSelectionChanged(){
  QList<QTreeWidgetItem*> list=tree->selectedItems();
  int i=list.size();

  if (i==0){
    // disabled menus
    previewAct->setEnabled(false);
    approveAct->setEnabled(false);
    deleteAct->setEnabled(false);
  }
  else if(i==1){
    // enabled menus
    previewAct->setEnabled(true);
    approveAct->setEnabled(true);
    deleteAct->setEnabled(true);
  }
  else{
    // enabled all menus but preview
    previewAct->setEnabled(false);
    approveAct->setEnabled(true);
    deleteAct->setEnabled(true);

  }
}

/** Implements a context menu
  *
  * An implementation of a Qt protected function that provides a context
  * menu.
  *
  * \param event The context menu event
  *
  */
void RainbruRPG::Gui::QuarantineList::
contextMenuEvent(QContextMenuEvent* event){
  QMenu menu(this);
  menu.addAction(previewAct);
  menu.addAction(approveAct);
  menu.addAction(deleteAct);
  menu.exec(event->globalPos());

}

/** The slot called when user accept some files
  *
  * Several files can be accepted in the same time. The selected files 
  * are moved to the \c upload directory.
  *
  */
void RainbruRPG::Gui::QuarantineList::fileAccept(){
  LOGI("fileAccept called");


   QList<QTreeWidgetItem*> list=tree->selectedItems();
   GlobalURI gu;

   while (!list.isEmpty()){
     QString filename=list.first()->text(0);
     std::string s(filename.toLatin1());
     std::string oldPath=gu.getQuarantineFile(s);
     std::string newPath=gu.getUploadFile(s);
     QString qOldPath(oldPath.c_str());
     QString qNewPath(newPath.c_str());
     QFile f(qOldPath);
     bool success=f.copy(qNewPath);

     if (success){
       bool success2=f.remove();

       if (success2){
	 delete list.takeFirst();
	 emit(filesRemoved(1));
       }
       else{
	 list.takeFirst();
       }
     }
     else{
       list.takeFirst();
     }
   }
}

/** The slot called when user refused some files
  *
  * Several files can be refused in the same time. The selected files
  * are definitively removed from the hard drive.
  *
  */
void RainbruRPG::Gui::QuarantineList::fileRefused(){
   LOGI("fileRefused called");

   QList<QTreeWidgetItem*> list=tree->selectedItems();
   GlobalURI gu;

   while (!list.isEmpty()){
     QString filename=list.first()->text(0);
     std::string s(filename.toLatin1());
     std::string path=gu.getQuarantineFile(s);
     QString qPath(path.c_str());
     QFile f(qPath);
     bool success=f.remove();

     if (success){
       delete list.takeFirst();
       emit(filesRemoved(1));
     }
     else{
       list.takeFirst();
     }
   }
 }

/** Open the help dialog
  *
  * This slot is connected to the help action.
  *
  */
void RainbruRPG::Gui::QuarantineList::showHelp(){
  HelpViewer hv("Server-quarant", this);
  hv.exec();

}

/** A slot called when a file is comming from FTP
  *
  * This slot is connected to signal in FtpTransfer telling a
  * file is being stored.
  *
  */
void RainbruRPG::Gui::QuarantineList::
storeFile(const QString& filename){
  LOGI("storeFile slot called");
  LOGCATS("filename is ");
  LOGCATS(filename.toLatin1());
  LOGCAT();

  storedFiles.append(filename);
}

/** A slot called when a STOR file transfer is finished
  *
  * It does not work actuallt.
  *
  * \param filename The filename of the STOR file
  *
  */
void RainbruRPG::Gui::QuarantineList::
transferComplete(const QString& filename){
  LOGI("QuarantineList::transferComplete called");

  if (!filename.isEmpty()){
    LOGI("storeFile slot called");
    LOGCATS("filename is ");
    LOGCATS(filename.toLatin1());
    LOGCAT();
    int i=storedFiles.removeAll(filename);
    
    if (i==0){
      LOGW("Cannot remove stored filename");
    }
  }
  else{
    LOGI("filename.isEmpty()==true");
  }
}

/** The slot called when user run a preview in a file
  *
  * It is the only action that can be used only in one file.
  *
  */
void RainbruRPG::Gui::QuarantineList::filePreview(){
  LOGI("filePreview called");

   QList<QTreeWidgetItem*> list=tree->selectedItems();
   GlobalURI gu;

   QString filename=list.first()->text(0);
   std::string s(filename.toLatin1());
   std::string strPath=gu.getQuarantineFile(s);
   QString path(strPath.c_str());

   FilePreview fp(path, this);
   fp.exec();
}

/** The TreeWidget was double clicked
  *
  * It opens the file preview.
  *
  * \param it The clicked item
  *
  * \param column An unused parameter
  *
  */
void RainbruRPG::Gui::QuarantineList::
treeDoubleClicked(QTreeWidgetItem* it, int column){
   GlobalURI gu;
   QString filename=it->text(0);
   std::string s(filename.toLatin1());
   std::string strPath=gu.getQuarantineFile(s);
   QString path(strPath.c_str());

   FilePreview fp(path, this);
   fp.exec();
}
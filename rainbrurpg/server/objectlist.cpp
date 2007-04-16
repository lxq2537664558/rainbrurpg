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

#include "objectlist.h"

#include <logger.h>

RainbruRPG::Gui::ObjectList::ObjectList(QWidget* parent) 
  :QWidget(parent) {

  setWindowTitle("Objects list");

  // The main layout
  QVBoxLayout* vb1=new QVBoxLayout();
  this->setLayout(vb1);

  QTabWidget* tab=new QTabWidget(this);
  vb1->addWidget(tab);
  
  // ObjectMesh widget
  QWidget* meshes=new QWidget(this);
  QVBoxLayout* vbMeshes=new QVBoxLayout();
  meshes->setLayout(vbMeshes);

    // The meshTree
    meshTree=new QTreeWidget(this);
    meshTree->setSortingEnabled(true);
    QStringList header;
    header << tr("Ip") << tr("Port") << tr("Type") << tr("Status") 
	   << tr("Try");
    meshTree->setColumnCount(5);
    meshTree->setHeaderLabels(header);
    vbMeshes->addWidget(meshTree);

  tab->addTab(meshTree, "Meshes");

  feed();
}

RainbruRPG::Gui::ObjectList::~ObjectList(){
  delete meshTree;
}

void RainbruRPG::Gui::ObjectList::feed(){
  QSqlDatabase db=QSqlDatabase::database ( "rainbru" );
  QSqlQuery q=db.exec("select * from objectpos");
  QSqlRecord rec = q.record();

  if (q.isActive()){
    qDebug() << "Number of columns: " << rec.count();
  }
  else{
    QMessageBox::critical ( this, tr("Database query error"), 
      tr("An error occured during SQL query execution. Please "
	 "verify you have GRANTed the role you are using."));

    LOGW("An error occured during SQL query execution");
    LOGCATS("DbMessage :");
    LOGCATS(db.lastError().text().toLatin1());
    LOGCAT();
    LOGCATS("QueryMessage :");
    LOGCATS(q.lastError().text().toLatin1());
    LOGCAT();
  }

  while (q.next())
    qDebug() << q.value(1).toString(); // output all names

  // It is a new client, adding it to the list
  /*  QTreeWidgetItem *it= new QTreeWidgetItem(tree);
  it->setText(0,ipText );
  it->setText(1, portText);
  it->setText(2, typeText);
  it->setText(3, statusText);
  if (!accepted){
    it->setTextColor(3, r);
  }
  it->setText(4, "1");
  
  meshTree->addTopLevelItem( it );
  */
}

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

/** \file staticmeshdialog.cpp
  * Implements a class displaying informations on an ObjectMesh
  *
  */

#include "staticmeshdialog.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStringList>

#include "meshviewerstats.h"

/** The default constructor
  * 
  * \param meshName The name of the object
  * \param parent A possible parent 
  *
  */
RainbruRPG::Editor::StaticMeshDialog::
StaticMeshDialog(const char* meshName, QWidget* parent)
  :QDialog(parent)

{
  LOGI("Opening a static mesh dialog");
  LOGCATS("Mesh name :");
  LOGCATS(meshName);
  LOGCAT();

  xol=new xmlObjectList();
  mesh=xol->getObjectMeshByName(meshName);


  setWindowTitle( tr("Object properties") );
  this->meshName=meshName;

  QVBoxLayout* layout=new QVBoxLayout(this);
  this->setLayout(layout);

  QHBoxLayout* hlayout=new QHBoxLayout(this);
  layout->addLayout(hlayout);

  // TabWidget
  QTabWidget* toolTab = new QTabWidget();
  //  toolTab->setMinimumSize(243, 350);
  hlayout->addWidget(toolTab);

  infoPanel(toolTab);
  positionsPanel(toolTab);

  // Viewer
  QVBoxLayout* mvLayout=new QVBoxLayout(this);
  hlayout->addLayout(mvLayout);

  meshViewer=new MeshViewer(this);
  meshViewer->addMesh(mesh->getMeshFile());
  mvLayout->addWidget(meshViewer);

  MeshViewerStats* mvs=new MeshViewerStats();
  mvLayout->addWidget(mvs);

  // OK Button
  QPushButton *pb=new QPushButton( tr("OK"), this);
  pb->setDefault(true);
  pb->setMaximumWidth( 100 );
  layout->addWidget(pb);

  QObject::connect(meshViewer, SIGNAL(updateFpsCount(int)),
		   mvs, SLOT(setFps(int)));
  QObject::connect(meshViewer, SIGNAL(updateTriCount(int)),
		   mvs, SLOT(setTri(int)));

  QObject::connect(pb, SIGNAL(clicked()), SLOT(accept()));


  LOGI("Static mesh dialog created");

}

/** The destructor
  *
  */
RainbruRPG::Editor::StaticMeshDialog::~StaticMeshDialog(){
  delete meshViewer;
  meshViewer=NULL;

  delete xol;
  xol=NULL;

  mesh=NULL;
}

/** Creates the information panel
  *
  * \param parent The QTabWidget used for the creation of the tab
  *
  */
void RainbruRPG::Editor::StaticMeshDialog::infoPanel(QTabWidget* parent){

  QWidget* infoTab=new QWidget();
  parent->addTab(infoTab, tr("Infos") );

  // name
  QGridLayout* grid=new QGridLayout(infoTab);
  QLabel* nameLabel=new QLabel(tr("Nom"), infoTab);
  grid->addWidget(nameLabel, 0, 0);
  QLabel* nameLabel2=new QLabel(mesh->getName().c_str(), infoTab);
  grid->addWidget(nameLabel2, 0, 10);

  // Type
  QLabel* typeLabel=new QLabel(tr("Type"), infoTab);
  grid->addWidget(typeLabel, 1, 0);
  QLabel* typeLabel2=new QLabel("static", infoTab);
  grid->addWidget(typeLabel2, 1, 10);

  // Meshfile
  // Type
  QLabel* fileLabel=new QLabel(tr("Filename"), infoTab);
  grid->addWidget(fileLabel, 2, 0);
  QLabel* fileLabel2=new QLabel(mesh->getMeshFile(), infoTab);
  grid->addWidget(fileLabel2, 2, 10);



}

/** Creates the position list tab
  *
  * \param parent The QTabWidget used for the creation of the tab
  *
  */
void RainbruRPG::Editor::StaticMeshDialog::positionsPanel(QTabWidget* parent){
  QWidget* posTab=new QWidget();
  parent->addTab(posTab, tr("Positions") );

  QHBoxLayout* hlayout=new QHBoxLayout(posTab);
  posTab->setLayout(hlayout);

  QTreeWidget* tree=new QTreeWidget(posTab);
  hlayout->addWidget(tree);

  QStringList header;
  header << tr("Name") << "x" << "y" << "z" << "rw" << "rx" << "ry" << "rz";

  tree->setColumnCount(7);
  tree->setHeaderLabels(header);

}

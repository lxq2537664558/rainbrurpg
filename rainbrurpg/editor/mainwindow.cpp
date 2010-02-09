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

/** \file editor/mainwindow.cpp
  * Implements the editor's main window
  *
  */

#include "mainwindow.h"

#include <QtGui/QDockWidget>

#include "tabenvironment.h"

/** The default constructor
  *
  * \param fileName A string
  * \param parent The parent widget
  *
  */
RainbruRPG::Editor::EditorMainWindow::EditorMainWindow(const QString &fileName, QWidget *parent)
		  : QMainWindow(parent)
{
  LOGI("Creating MainWindow");
  QFileInfo fileInfo(fileName);

  tabWidget=new QTabWidget(this);
  scriptEditor = new ScriptEditor();

  //Ogre View
  ogreView = new OgreView(tabWidget);
  ogreView->setFocusPolicy(Qt::ClickFocus);
  ogreView->setMinimumSize(105, 355);
  ///////////////////

  //tool tab
  toolTab = new QTabWidget();
  toolTab->setMinimumSize(243, 350);
  //  toolTab->setTabShape(QTabWidget::Triangular);

  objTab=new ObjectsTab();
  toolTab->addTab(objTab, QIcon(":/images/object.png"), "Objects" );

  TabEnvironment *tabEnv=new TabEnvironment();
  toolTab->addTab(tabEnv, "Environment" );
  ///////////////////

  //Ogre Log
  ogreLog = new QTextEdit;
  ogreLog->setReadOnly(true);
  ogreLog->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  ogreLog->setMinimumSize(100, 73);
  ogreLog->insertPlainText(ogreView->getLog().c_str());
  connect(ogreLog, SIGNAL(textChanged()), this, SLOT(scrollLog()));
  
  QDockWidget *propDock = new QDockWidget("Tools");
  propDock->setWidget(toolTab);
  propDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
  addDockWidget(Qt::LeftDockWidgetArea, propDock);
  
  QDockWidget *logDock = new QDockWidget("Log");
  logDock->setWidget(ogreLog);
  logDock->setAllowedAreas(Qt::TopDockWidgetArea | Qt::BottomDockWidgetArea);
  addDockWidget(Qt::BottomDockWidgetArea, logDock);
  
  // Init to white the diffuse and specular colors 
  // (NOTE: the initialisation takes effect on the "LightWindow")
  diffuseLightColor.setRgba(qRgba(255, 255, 255, 255));
  specularLightColor.setRgba(qRgba(255, 255, 255, 255));
  // This is our first light created by hand in LightWindow, 
  // so we've to put in the "blacklist" of names
  listName.push_back("Main Light");
  
  createActions();
  createMenus();
  createToolBars();
  
  QStatusBar(this);
  
  startTimer(50);
  
  setWindowTitle(fileName);
  setWindowIcon(QIcon(":/images/ogre.png"));
  setGeometry(50, 50, 1024, 768);
  
  tabWidget->addTab(ogreView, QIcon(":/images/3d.png"), "3D view");

  setCentralWidget(tabWidget);
  LOGI("MainWindow created");
}

/** The default destructor
  *
  */
RainbruRPG::Editor::EditorMainWindow::~EditorMainWindow(){
  delete objTab;
  delete scriptEditor;

  objTab=NULL;
}

/** Scrolls the log
  *
  * Always shows the last log.
  *
  */
void RainbruRPG::Editor::EditorMainWindow::scrollLog(){
	ogreLog->verticalScrollBar()
	  ->setValue( ogreLog->verticalScrollBar()->maximum() );
};

/** Shows the about dialog
  *
  */
void RainbruRPG::Editor::EditorMainWindow::about(){
  QString ogreVersion = QString::number(OGRE_VERSION_MAJOR) + "." 
    + QString::number(OGRE_VERSION_MINOR) + "." 
    + QString::number(OGRE_VERSION_PATCH);
  QMessageBox::about(this, tr("About Show Mesh"),
	tr("Show Mesh %1\n").arg("1.1") +
	tr("Copyright (C) 2006 Quentin Bereau\n\n") +
	tr("Licensed under the GPLv2\n") +
	tr("Using Ogre %1 and Qt %2\n\n").arg(ogreVersion).arg(qVersion()) +
	tr("Developers:\n") +
	tr("Quentin Bereau <scratattack@users.sourceforge.net>\n") +
	tr("John Eric Martin <cpuwhiz105@users.sourceforge.net>"));
}

/** Setup of the actions
  *
  */
void RainbruRPG::Editor::EditorMainWindow::createActions(){
  addObjAct = new QAction(QIcon(":/images/object.png"), tr("&Add Object"), this);
  addObjAct->setShortcut(tr("Ctrl+O"));
  addObjAct->setStatusTip(tr("Add Object"));
  connect(addObjAct, SIGNAL(triggered()), this, SLOT(addObj()));
  
  addLightAct = new QAction(QIcon(":/images/light.png"), tr("Add &Light"), this);
  addLightAct->setShortcut(tr("Ctrl+L"));
  addLightAct->setStatusTip(tr("Add Light"));
  connect(addLightAct, SIGNAL(triggered()), this, SLOT(addLight()));
  
  quitAct = new QAction(tr("&Quit"), this);
  quitAct->setShortcut(tr("Ctrl+Q"));
  quitAct->setStatusTip(tr("Quit the application"));
  connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));
  
  scriptAct = new QAction(tr("&Set Script Path"), this);
  scriptAct->setStatusTip(tr("Set Script Path"));
  connect(scriptAct, SIGNAL(triggered()), this, SLOT(setScriptPath()));
  
  textureAct = new QAction(tr("&Set Texture Path"), this);
  textureAct->setStatusTip(tr("Set Texture Path"));
  connect(textureAct, SIGNAL(triggered()), this, SLOT(setTexturePath()));
  
  aboutAct = new QAction(tr("&About"), this);
  aboutAct->setShortcut(tr("Ctrl+A"));
  aboutAct->setStatusTip(tr("About"));
  connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

}

/** Populates the menus
  *
  */
void RainbruRPG::Editor::EditorMainWindow::createMenus(){
  // The script editor action
  QAction* scriptEditorAct = new QAction(tr("&ScriptEditor"), this);
  scriptEditorAct->setShortcut(tr("Ctrl+E"));
  scriptEditorAct->setStatusTip(tr("Open the script editor"));
  connect(scriptEditorAct, SIGNAL(triggered()), this, 
	  SLOT(showScriptEditor()));

  fileMenu = menuBar()->addMenu(tr("&File"));
  //fileMenu->addAction(newAct);
  fileMenu->addAction(addObjAct);
  fileMenu->addAction(addLightAct);
  fileMenu->addSeparator();
  fileMenu->addAction(quitAct);
  
  editMenu = menuBar()->addMenu(tr("&Edit"));
  editMenu->addAction(scriptEditorAct);

  matMenu = editMenu->addMenu(tr("&Materials Properties"));
  matMenu->addAction(scriptAct);
  matMenu->addAction(textureAct);
  

  helpMenu = menuBar()->addMenu(tr("&Help"));
  helpMenu->addAction(aboutAct);

}

/** Creates toolbars
  *
  */
void RainbruRPG::Editor::EditorMainWindow::createToolBars(){
  fileToolBar = addToolBar(tr("File"));
  fileToolBar->addAction(addObjAct);
  fileToolBar->addAction(addLightAct);
}

/** The TimeEvent callback
  *
  * \param evt The event
  *
  */
void RainbruRPG::Editor::EditorMainWindow::timerEvent(QTimerEvent* evt){
  Q_UNUSED(evt);
  statusBar()->clearMessage();
  
  QString fullMsg;
  fullMsg += "FPS : ";
  
  QString nbFPS;
  nbFPS.setNum(ogreView->getFPS());
  fullMsg += nbFPS;
  
  fullMsg += "     ";
  fullMsg += "Triangles : ";
  
  QString nbTriangles;
  nbTriangles.setNum(ogreView->getTriangles());
  fullMsg += nbTriangles;
  
  //POSITION
  fullMsg += "     ";
  fullMsg += "Position : ";
  
  QString camX;
  camX.setNum(ogreView->getPosCamera().x);
  fullMsg += camX;
  fullMsg += ", ";
  
  QString camY;
  camY.setNum(ogreView->getPosCamera().y);
  fullMsg += camY;
  fullMsg += ", ";
  
  QString camZ;
  camZ.setNum(ogreView->getPosCamera().z);
  fullMsg += camZ;
  
  //DIRECTION
  fullMsg += "     ";
  fullMsg += "Direction : ";
  
  QString dirX;
  dirX.setNum(ogreView->getDirCamera().x);
  fullMsg += dirX;
  fullMsg += ", ";
  
  QString dirY;
  dirY.setNum(ogreView->getDirCamera().y);
  fullMsg += dirY;
  fullMsg += ", ";
  
  QString dirZ;
  dirZ.setNum(ogreView->getDirCamera().z);
  fullMsg += dirZ;
  
  statusBar()->showMessage(fullMsg);//Update stats
}

/** The resize event
  *
  * \param evt The Qt event
  *
  */
void RainbruRPG::Editor::EditorMainWindow::resizeEvent(QResizeEvent* evt){
  Q_UNUSED(evt);
}

/** Shows the script editor
  *
  */
void RainbruRPG::Editor::EditorMainWindow::showScriptEditor(){
  int i=tabWidget->addTab(scriptEditor,QIcon(":images/script.png"),
			  "unnamed.lua");

  tabWidget->setCurrentIndex(i);
}

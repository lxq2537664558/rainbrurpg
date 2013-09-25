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

#include "objectstab.h"

#include <QVBoxLayout>

#include "selectionmanager.h"
#include "posordialog.h"

/** The default constructor
  *
  * \param parentWidget The parent widget
  *
  */
RainbruRPG::Editor::ObjectsTab::ObjectsTab(QWidget *parentWidget)
               : QWidget(parentWidget){

  LOGI("Creating ObjectsTab");

  isNodeHighLighted=false;
  highLightNode=NULL;
  highLightEntity=NULL;

  QVBoxLayout* layout=new QVBoxLayout(this);
  this->setLayout(layout);

  objTree=new QTreeWidget();
  layout->addWidget(objTree);

  setupTreeView();

  QObject::connect(objTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem* , int)),
		   SLOT(objectTreeClicked( QTreeWidgetItem *, int )));

  LOGI("ObjectsTab created");
}

/** The default destructor
  *
  */
RainbruRPG::Editor::ObjectsTab::~ObjectsTab(){
  objTree->~QTreeWidget();
  objTree=NULL;

  highLightNode=NULL;
  highLightEntity=NULL;
}

/** Setup the object tree view 
  *
  * This QTreeView is used to store the list of objects.
  *
  */
void RainbruRPG::Editor::ObjectsTab::setupTreeView(){

  QStringList header;
  header << tr("Name") << tr("Filename/Pos") << tr("Count/Rot");

  objTree->setColumnCount(3);
  objTree->setHeaderLabels(header);

  xmlObjectList xol;
  ObjectMeshList* meshList=xol.getMeshList();

  ObjectMeshList::const_iterator iter;
  for (iter=meshList->begin(); iter != meshList->end(); iter++){
    addObjectMesh((*iter));
    
  }
}

/** Adds an ObjectMesh in the TreeView
  *
  * \param om The ObjectMesh to add
  *
  */
void RainbruRPG::Editor::ObjectsTab::addObjectMesh(ObjectMesh* om){
  std::string name=om->getName();
  const char* meshFile=om->getMeshFile();

  ObjectPosList opl=om->getPosList();
  int count=opl.size();
  QString txtCount;
  txtCount.setNum(count);

  QTreeWidgetItem *item=new QTreeWidgetItem();
  item->setText(0, name.c_str());
  item->setText(1, meshFile);
  item->setText(2, txtCount);

  QString toolTip=tr("Left double-click to open a dialog");
  item->setToolTip(0, toolTip);
  item->setToolTip(1, toolTip);
  item->setToolTip(2, toolTip);

  objTree->addTopLevelItem( item );

  ObjectPosList::const_iterator iter;
  for (iter=opl.begin(); iter != opl.end(); iter++){
    addObjectMeshChilds((*iter), item);
    
  }

}

/** Adds an ObhectPos in the tree view
  *
  * It creates a nested tree view item to the parent ObejctMesh.
  *
  * \param op The ObjectPos to be added
  * \param parent The parent tree widget item
  *
  */
void RainbruRPG::Editor::ObjectsTab::
addObjectMeshChilds(ObjectPos op, QTreeWidgetItem* parent)
{

  QString temp;

  std::string name(op.getName());

  QString pos;

  // Makes the position string
  temp.setNum(op.getPosX());
  pos +=temp;
  pos +=",";

  temp.clear();
  temp.setNum(op.getPosY());
  pos +=temp;
  pos +=",";

  temp.clear();
  temp.setNum(op.getPosZ());
  pos +=temp;

  // Makes the rotation string
  QString rot;

  temp.clear();
  temp.setNum(op.getRotW());
  rot +=temp;
  rot +=",";

  temp.clear();
  temp.setNum(op.getRotX());
  rot +=temp;
  rot +=",";

  temp.clear();
  temp.setNum(op.getRotY());
  rot +=temp;
  rot +=",";

  temp.clear();
  temp.setNum(op.getRotZ());
  rot +=temp;

  QTreeWidgetItem *item=new QTreeWidgetItem(parent);
  item->setText(0, name.c_str());
  item->setText(1, pos);
  item->setText(2, rot);

  QString toolTip=tr("Left double-click to go to this object");
  item->setToolTip(0, toolTip);
  item->setToolTip(1, toolTip);
  item->setToolTip(2, toolTip);

}

/** The double click slot of the TreeView
  *
  * To test the type of object we clicked, I use the 
  * QTreeWidget::indexOfTopLevelItem function. It it returns -1, the given
  * item is not a top-level one, so it is an ObjectPos.
  *
  * \param it The treeview item receiving the mouse event
  * \param col The column receiving the mouse event
  *
  */
void RainbruRPG::Editor::ObjectsTab::
objectTreeClicked( QTreeWidgetItem * it, int col)
{

  LOGI("The treeView was clicked");
  int i=objTree->indexOfTopLevelItem(it);
  const char* name=it->text(0).toLatin1();

  if (i==-1){
    LOGI("An ObjectPos was clicked");
    //    lookAtObject(it);
    selectObject(it->text(0));
    PosorDialog pod;
    pod.setPosName(it->text(0));
    pod.exec();
  }
  else{
    LOGI("An ObjectMesh was clicked");
    LOGCATS("ObjectMesh name : ");
    LOGCATS(name);
    LOGCAT();

    StaticMeshDialog smd(name);
    int res=smd.exec();
  }
}

/** Look at an ObjectPos
  *
  * Called from objectTreeClicked().
  *
  * \param it The item double-clicked
  *
  */
void RainbruRPG::Editor::ObjectsTab::lookAtObject(QTreeWidgetItem* it){
  QString posText=it->text(1);
  QString xTxt=posText.section(',', 0, 0);
  QString yTxt=posText.section(',', 1, 1);
  QString zTxt=posText.section(',', 2, 2);

  LOGI("Getting position of the object :");
  LOGCATS("X=");
  LOGCATS(xTxt.toLatin1());
  LOGCATS(" Y=");
  LOGCATS(yTxt.toLatin1());
  LOGCATS(" Z=");
  LOGCATS(zTxt.toLatin1());
  LOGCAT();

  // The lookAt position
  float lx, ly, lz;
  lx=xTxt.toFloat();
  ly=yTxt.toFloat();
  lz=zTxt.toFloat();

  // The camera position
  float cx, cy, cz;
  cx=lx-1.0f;
  cy=ly;
  cz=lz;

  // Real is a float
  Ogre::Camera* cam=Ogre::Root::getSingleton()
    .getSceneManager("MainEditorView")
    ->getCamera("MainEditorCam");

  cam->setPosition (cx, cy, cz);
  cam->lookAt (lx, ly, lz);
}

/** Set the BoundingBox of the named entity to true to highlight it
  *
  * \param name The name of the entity
  *
  */
void RainbruRPG::Editor::ObjectsTab::selectObject(const QString& name){
  LOGI("ObjectsTab::setBoundingBox called");


  Ogre::SceneManager* sm=Ogre::Root::getSingleton()
    .getSceneManager("MainEditorView");

  //  const char* n=name.toLatin1();
  //  const char* n=name.toAscii();
  std::string n=std::string(name.toAscii());
  LOGCATS("Entity name : '");
  LOGCATS(n.c_str());
  LOGCATS("'");
  LOGCAT();

  Ogre::String s=n;
  SelectionManager::getSingleton().selectNewObject(s);
}

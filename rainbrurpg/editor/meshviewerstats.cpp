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

#include "meshviewerstats.h"

#include <QHBoxLayout>
#include <QVBoxLayout>

#include <logger.h>

/** The default constructor
  *
  * \param parent The QWidget parent (default to 0)
  *
  */
RainbruRPG::Editor::MeshViewerStats::MeshViewerStats(QWidget* parent)
  :QWidget(parent){

  QVBoxLayout* vl=new QVBoxLayout(this);
  this->setLayout(vl);


  // FPS and Tri
  QHBoxLayout* layout=new QHBoxLayout(this);
  vl->addLayout(layout);

  QLabel* l1=new QLabel(tr("FPS :"), this);
  layout->addWidget(l1);

  labFps=new QLabel("0", this);
  layout->addWidget(labFps);

  QLabel* l2=new QLabel(tr("Tri :"), this);
  layout->addWidget(l2);

  labTri=new QLabel("0", this);
  layout->addWidget(labTri);

  // Pos and rot
  QHBoxLayout* layout2=new QHBoxLayout(this);
  vl->addLayout(layout2);

  QLabel* l3=new QLabel(tr("Pos :"), this);
  layout2->addWidget(l3);

  labPos=new QLabel("0", this);
  layout2->addWidget(labPos);

  QLabel* l4=new QLabel(tr("Rot :"), this);
  layout2->addWidget(l4);

  labRot=new QLabel("0", this);
  layout2->addWidget(labRot);


  setMaximumHeight(60);

  mSceneManager=Ogre::Root::getSingleton().getSceneManager("MeshViewerView");
  mCamera=mSceneManager->getCamera("MeshViewerCam");

}
 
/** The default destructor
  *
  */
RainbruRPG::Editor::MeshViewerStats::~MeshViewerStats(){
  delete labPos;
  delete labRot;
  delete labFps;
  delete labTri;

  labPos=NULL;
  labRot=NULL;
  labFps=NULL;
  labTri=NULL;
}

/** Changes the FPS count 
  *
  * This slot is designed to be connected to the MeshViewer::updateFpsCount()
  * signal.
  *
  * \param fps The number of frame per second
  *
  */
void RainbruRPG::Editor::MeshViewerStats::setFps(int fps){
  labFps->setNum( fps );
  updateCamStats();
}

/** Changes the triangle count 
  *
  * This slot is designed to be connected to the MeshViewer::updateTriCount()
  * signal.
  *
  * \param tri The number of triangle
  *
  */
void RainbruRPG::Editor::MeshViewerStats::setTri(int tri){
  labTri->setNum(tri);
}

/** Update the camera statistics
  *
  * As this is not a slot, this method must be called either in setFps
  * or setTri.
  *
  */
void RainbruRPG::Editor::MeshViewerStats::updateCamStats(){
  Ogre::Vector3 posVec= mCamera->getPosition();
  Ogre::Vector3 dirVec= mCamera->getDirection();

  QString pos=vectorToString(posVec);
  QString dir=vectorToString(dirVec);

  labPos->setText(pos.toAscii());
  labRot->setText(dir.toAscii());
}

/** Converts an Ogre Vector3 to a QString
  *
  * This function is used to print the camera position and orientation.
  * The values are shown with the 9.99format. They are troncated if needed
  *
  * \param v The Ogre vector to convert
  *
  * \return The resulted QString
  *
  */
QString RainbruRPG::Editor::MeshViewerStats::
vectorToString(const Ogre::Vector3& v){
  QString x,y,z;
  x.setNum(v.x, 'f', 2);
  y.setNum(v.y, 'f', 2);
  z.setNum(v.z, 'f', 2);

  QString vts="";
  vts+=x;
  vts+=",";
  vts+=y;
  vts+=",";
  vts+=z;
  return vts;
}

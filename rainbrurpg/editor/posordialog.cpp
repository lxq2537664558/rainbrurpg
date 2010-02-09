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

/** \file posordialog.cpp
  * Implements a dialog to change position and orientation of a mesh
  *
  */

#include "posordialog.h"

#include <xmlobjectlist.h>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QSizePolicy>
#include <QPushButton>

/** The default destructor
  *
  * \param parent The parent widget
  *
  */
RainbruRPG::Editor::PosorDialog::PosorDialog(QWidget* parent)
                                :QDialog(parent)

{
  setWindowTitle( tr("ObjectPos properties") );

  // The root layout
  QVBoxLayout* root=new QVBoxLayout(this);
  this->setLayout(root);

  // The header (object name) layout
  QHBoxLayout* header=new QHBoxLayout(this);
  root->addLayout( header );

  // The name label
  QLabel* nameLabel=new QLabel("Instance name :", this);
  header->addWidget( nameLabel );
  lblObjectName=new QLabel("[Not set]", this);
  header->addWidget( lblObjectName );
  header->addStretch( 200 );

  // Creates the posor
  QWidget* posorParent=new QWidget();
  QSizePolicy qsp=QSizePolicy();
  qsp.setVerticalPolicy(QSizePolicy::Expanding);
  qsp.setHorizontalPolicy(QSizePolicy::Expanding);
  qsp.setVerticalStretch(1);

  posorParent->setSizePolicy(qsp);

  QHBoxLayout* pl=new QHBoxLayout();
  posorParent->setLayout(pl);
  root->addWidget(posorParent);
  createPosorWidget(posorParent);

  // The OK button
  QPushButton* pbOk=new QPushButton(tr("OK"), this);
  pbOk->setDefault(true);
  pbOk->setMaximumWidth( 100 );
  root->addWidget( pbOk );

  // Signals connections
  QObject::connect(pbOk, SIGNAL(clicked()), SLOT(accept()));

}

/** Change the name of the ObjectPos to modify
  *
  * An ObjectPos can only be retrieve if we know its type (The name of
  * ObjectMesh).
  *
  * \param meshName The name of the ObjectMesh
  * \param posName The name of the ObjectPos
  *
  */
void RainbruRPG::Editor::PosorDialog::
setPosName(const QString& meshName, const QString& posName){

  std::string stdMeshName(meshName.toLatin1());
  std::string stdPosName(posName.toLatin1());

  xmlObjectList xol;
  ObjectMesh *mesh=xol.getObjectMeshByName(stdMeshName);
  //  ObjectPos* pos=new ObjectPos(mesh->getPosByName(stdPosName));
  ObjectPos pos;
  pos=mesh->getPosByName(stdPosName);

  lblObjectName->setText(posName);

  posX->setValue(pos.getPosX());
  posY->setValue(pos.getPosY());
  posZ->setValue(pos.getPosZ());

  spRotW->setValue(pos.getRotW());
  spRotX->setValue(pos.getRotX());
  spRotY->setValue(pos.getRotY());
  spRotZ->setValue(pos.getRotZ());

  cout << "X ="<< pos.getPosX() << endl;
  cout << "Y ="<< pos.getPosY() << endl;
  cout << "rw="<< pos.getRotW() << endl;
  cout << "rx="<< pos.getRotX() << endl;
  cout << "ry="<< pos.getRotY() << endl;
  cout << "rz="<< pos.getRotZ() << endl;
}

/** Creates the Position and Orientation groups
  *
  * \param parent The parent widget (this)
  *
  */
void RainbruRPG::Editor::PosorDialog::createPosorWidget(QWidget* parent){
  // Position group
  QGroupBox* posGroup=new QGroupBox(tr("Position"), parent);
  parent->layout()->addWidget(posGroup);
  QGridLayout* posGroupLayout=new QGridLayout(posGroup);
  posGroup->setLayout(posGroupLayout);

  // X position
  QLabel* labX=new QLabel(tr("x"), posGroup);
  posGroupLayout->addWidget(labX, 0, 0);

  posX=new QDoubleSpinBox(posGroup);
  posX->setMaximum(10000);
  posGroupLayout->addWidget(posX, 0, 1);

  // Y position
  QLabel* labY=new QLabel(tr("y"), posGroup);
  posGroupLayout->addWidget(labY, 1, 0);

  posY=new QDoubleSpinBox(posGroup);
  posY->setMaximum(10000);
  posGroupLayout->addWidget(posY, 1, 1);

  // Z position
  QLabel* labZ=new QLabel(tr("z"), posGroup);
  posGroupLayout->addWidget(labZ, 2, 0);

  posZ=new QDoubleSpinBox(posGroup);
  posZ->setMaximum(10000);
  posGroupLayout->addWidget(posZ, 2, 1);


  // Orientation group
  QGroupBox* orGroup=new QGroupBox(tr("Orientation"), parent);
  parent->layout()->addWidget(orGroup);
  QGridLayout* rotGroupLayout=new QGridLayout(orGroup);
  orGroup->setLayout(rotGroupLayout);

  // W rotation
  QLabel* rotW=new QLabel(tr("W"), orGroup);
  rotGroupLayout->addWidget(rotW, 0, 0);

  spRotW=new QDoubleSpinBox(orGroup);
  spRotW->setMaximum(10000);
  rotGroupLayout->addWidget(spRotW, 0, 1);

  // X rotation
  QLabel* rotX=new QLabel(tr("X"), orGroup);
  rotGroupLayout->addWidget(rotX, 1, 0);

  spRotX=new QDoubleSpinBox(orGroup);
  spRotX->setMaximum(10000);
  rotGroupLayout->addWidget(spRotX, 1, 1);

  // Y rotation
  QLabel* rotY=new QLabel(tr("Y"), orGroup);
  rotGroupLayout->addWidget(rotY, 2, 0);

  spRotY=new QDoubleSpinBox(orGroup);
  spRotY->setMaximum(10000);
  rotGroupLayout->addWidget(spRotY, 2, 1);

  // Z rotation
  QLabel* rotZ=new QLabel(tr("Z"), orGroup);
  rotGroupLayout->addWidget(rotZ, 3, 0);

  spRotZ=new QDoubleSpinBox(orGroup);
  spRotZ->setMaximum(10000);
  rotGroupLayout->addWidget(spRotZ, 3, 1);

}

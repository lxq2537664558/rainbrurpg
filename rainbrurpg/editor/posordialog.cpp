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

#include "posordialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QSizePolicy>

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
  QLabel* lblObjectName=new QLabel("[Not set]", this);
  header->addWidget( lblObjectName );
  header->addStretch( 200 );

  // Cretaes the posor
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
}

/** Change the name of the ObjectPos to modify
  *
  * \param name The name of the ObjectPos
  *
  */
void RainbruRPG::Editor::PosorDialog::setPosName(const QString &name){

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

  // Orientation group
  QGroupBox* orGroup=new QGroupBox(tr("Orientation"), parent);
  parent->layout()->addWidget(orGroup);
}

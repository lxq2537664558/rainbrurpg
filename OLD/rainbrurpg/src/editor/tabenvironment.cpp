/*
 *  Copyright 2006-2013 Jerome PASQUIER
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

/** \file tabenvironment.cpp
  * Implements the environment parameters tab
  *
  */

#include "tabenvironment.h"

#include "QVBoxLayout"

/** The default constructor
  *
  * \param parent The parent widget
  *
  */
RainbruRPG::Editor::TabEnvironment::TabEnvironment(QWidget *parent)
               : QWidget(parent){

  QVBoxLayout* layout=new QVBoxLayout(this);
  this->setLayout(layout);

  toolBox=new QToolBox(this);
  QWidget* fogPage=new QWidget(this);
  QWidget* ambientPage=new QWidget(this);
  toolBox->addItem(fogPage, "Fog");
  toolBox->addItem(ambientPage, "Ambient");

  layout->addWidget(toolBox);
}

/** The destructor
  *
  */
RainbruRPG::Editor::TabEnvironment::~TabEnvironment(){

}
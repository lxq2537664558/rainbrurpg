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

#ifndef POSOR_DIALOG_H
#define POSOR_DIALOG_H

#include <QDialog>
#include <QWidget>
#include <QLabel>
#include <QDoubleSpinBox>

#include "objectpos.h"

using namespace RainbruRPG::Core;

namespace RainbruRPG{
  namespace Editor{
    /** A dialog to change position and orientation of a mesh
      *
      * This dialog can modify an ObjectPos instance. The selection in the
      * OgreView is not managed, it must already be done, 
      * with SelectionManager is the easiest way.
      *
      * There is two ways to open this dialog :
      * - in the ObjectsTab if you make a double click in an object position;
      * - in the OgreView if you make a double click on an mesh
      *
      * \sa StaticMeshDialog, OgreView, ObjectsTab, ObjectPos, SelectionManager
      */
    class PosorDialog : public QDialog{
      Q_OBJECT
    public:
      PosorDialog(QWidget* parent=0);
      void setPosName(const QString &, const QString &);

    private:
      void createPosorWidget(QWidget*);
      /** The ObjectPos to be modified */
      ObjectPos* objectPos;
      /** A label containing the ObjectPos name */
      QLabel* lblObjectName;

      /** The spin box containing the x-axis position */
      QDoubleSpinBox* posX;
      /** The spin box containing the y-axis position */
      QDoubleSpinBox* posY;
      /** The spin box containing the z-axis position */
      QDoubleSpinBox* posZ;

      /** The spin box containing the w-axis rotation */
      QDoubleSpinBox* spRotW;
      /** The spin box containing the x-axis rotation */
      QDoubleSpinBox* spRotX;
      /** The spin box containing the y-axis rotation */
      QDoubleSpinBox* spRotY;
      /** The spin box containing the z-axis rotation */
      QDoubleSpinBox* spRotZ;

    };
  }
}

#endif // POSOR_DIALOG_H

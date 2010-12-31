/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file staticmeshdialog.h
  * Declares a class displaying informations on an ObjectMesh
  *
  * Modifications :
  * - 13 aug 2008 : Single file documentation
  *
  */

#ifndef STAIC_MESH_DIALOG_H
#define STAIC_MESH_DIALOG_H

#include <QWidget>
#include <QDialog>
#include <QTabWidget>

#include <xmlobjectlist.h>
#include <objectmesh.h>

#include "meshviewer.h"

using namespace RainbruRPG::Core;

namespace RainbruRPG {
  namespace Editor{

    /** A class displaying informations on an ObjectMesh
      *
      */
    class StaticMeshDialog : public QDialog{
    public:
      StaticMeshDialog(const char*, QWidget * parent = 0);
      ~StaticMeshDialog();

    private:
      void infoPanel(QTabWidget*);
      void positionsPanel(QTabWidget*);


      /** The name of the mesh used */
      const char* meshName;
      /** An Ogre window for mesh viewing */
      MeshViewer* meshViewer;
      /** The interface to the object list */
      xmlObjectList* xol;
      /** The ObjectMesh this dialog is open for*/
      ObjectMesh* mesh;
    };
  }
}

#endif // STAIC_MESH_DIALOG_H

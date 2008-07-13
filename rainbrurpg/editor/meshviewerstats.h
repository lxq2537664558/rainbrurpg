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

#ifndef MESH_VIEWER_STATS_H
#define MESH_VIEWER_STATS_H

#include <QWidget>
#include <QLabel>

#include <ogreimport.h>

namespace RainbruRPG{
  namespace Editor{

    /** A Qt widget than can be 'linked' to a MeshViewer to draw 
      * some statistics
      *
      */
    class MeshViewerStats : public QWidget{
      Q_OBJECT
    public:
      MeshViewerStats(QWidget* parent=0);
      ~MeshViewerStats();

    public slots:
      void setFps(int);
      void setTri(int);
      void updateCamStats();

    private:
      QString vectorToString(const Ogre::Vector3&);

      /** The Ogre scene manager */
      Ogre::SceneManager* mSceneManager;
      /** The Ogre camera */
      Ogre::Camera* mCamera;

      /** The FPS label */
      QLabel* labFps;
      /** The triangle count label */
      QLabel* labTri;
      /** The camera position label */
      QLabel* labPos;
      /** The camera rotation label */
      QLabel* labRot;
    };
  }
}

#endif // MESH_VIEWER_STATS_H

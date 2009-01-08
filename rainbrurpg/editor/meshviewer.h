/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file meshviewer.h
  * Declares a class used to view a single mesh
  *
  * Modifications :
  * - 13 aug 2008 : Single file documentation
  *
  */

#ifndef MESH_VIEWER_H
#define MESH_VIEWER_H


#include <ogreimport.h>
#if (OGRE_PLATFORM  == OGRE_PLATFORM_WIN32)
#include <windows.h>
#endif

#include <QWidget>


namespace RainbruRPG {
  namespace Editor{

    /** A class used to view a single mesh (ie. in a dialog)
      *
      * To allow multiple MeshViewer instance, The scene manager
      * is created once in OgreViewer.
      *
      * The scenemanager is of type 'DefaultSceneManager' and its name is
      * 'MeshViewerView'. The Ogre camera is called 'MeshViewerCam'.
      *
      */
    class MeshViewer : public QWidget{
      Q_OBJECT
    public:
      MeshViewer(QWidget* parent=0);
      ~MeshViewer();

      void addMesh(const char*);

    signals:
      /** Update the fps value */
      void updateFpsCount(int);
      /** Update the triangle count */
      void updateTriCount(int);


    protected:
      void setupView();
      void update();

      void resizeEvent(QResizeEvent* evt);
      void timerEvent(QTimerEvent* evt);
      void paintEvent(QPaintEvent* evt);


    private:
      void updateStats();

      /** The Ogre render window */
      Ogre::RenderWindow* mRenderWindow;
      /** The Ogre scene manager */
      Ogre::SceneManager* mSceneManager;
      /** The Ogre camera */
      Ogre::Camera* mCamera;
      /** The Ogre viewport */
      Ogre::Viewport* mVp;
    };
  }
}

#endif // MESH_VIEWER_H

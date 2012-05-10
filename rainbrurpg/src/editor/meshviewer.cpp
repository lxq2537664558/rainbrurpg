/*
 *  Copyright 2006-2012 Jerome PASQUIER
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

/** \file meshviewer.cpp
  * Implements a class used to view a single mesh
  *
  */

#include "meshviewer.h"

#include <Logger.hpp>

#if !defined(Q_WS_WIN)
#include <QX11Info>
#endif

using namespace Ogre;

/** The default constructor
  *
  * \param parent The parent Widget
  *
  */
RainbruRPG::Editor::MeshViewer::MeshViewer(QWidget* parent)
  :QWidget(parent){
  setMinimumSize(150, 150);

  mRenderWindow=NULL;
  mSceneManager=Ogre::Root::getSingleton().getSceneManager("MeshViewerView");
  mCamera=mSceneManager->getCamera("MeshViewerCam");

  mCamera->setPosition(Vector3(100,100,0));
  mCamera->lookAt(Vector3(1.0f, 1.0f, 1.0f));


}

/** The default destructor
  *
  */
RainbruRPG::Editor::MeshViewer::~MeshViewer(){

}

/** Setup the Ogre render window and the viewport
  *
  */
void RainbruRPG::Editor::MeshViewer::setupView(){
  if(mRenderWindow)
    return;

  NameValuePairList params;

#if !defined(Q_WS_WIN)
  QWidget *q_parent = dynamic_cast <QWidget *> (parent());
  QX11Info xInfo = x11Info();

  params["parentWindowHandle"] = Ogre::StringConverter::
    toString ((unsigned long)xInfo.display()) +
    ":" + Ogre::StringConverter::toString ((unsigned int)xInfo.screen()) +
    ":" + Ogre::StringConverter::toString ((unsigned long)q_parent->winId());

#else
  params["externalWindowHandle"] = Ogre::StringConverter::
    toString((size_t)(HWND)winId());
#endif

  LOGI("Creating MeshViewer render window");
  LOGCATS("width='");
  LOGCATI(width());
  LOGCATS("' height='");
  LOGCATI(height());
  LOGCATS("'");
  LOGCAT();

  mRenderWindow = Ogre::Root::getSingleton()
    .createRenderWindow("MeshView", width(), height(), true, &params);


  // Setup the Camera, viewport...
  LOGI("Creating MeshViewer viewport");
  mVp=mRenderWindow->addViewport(mCamera);
  mVp->setBackgroundColour(ColourValue(0.2f, 0.2f, 0.2f, 1));

#if !defined(Q_WS_WIN) // Linux
  WId window_id;
  mRenderWindow->getCustomAttribute("GLXWINDOW", &window_id);
  
  // Take over the ogre created window.
  QWidget::create(window_id);
  
  LOGI("Repositionning MeshViewer render window");
  LOGCATS("x='");
  LOGCATI(x());
  LOGCATS("' y='");
  LOGCATI(y());
  LOGCATS("'");
  LOGCAT();
  mRenderWindow->reposition(x(),y());
#endif

  startTimer(5);

}

/** The Qt resize event
  *
  * \param evt The Qt ResizeEvent
  *
  */
void RainbruRPG::Editor::MeshViewer::resizeEvent(QResizeEvent* evt){
  Q_UNUSED(evt);
  setupView();

  if (mRenderWindow != NULL){
#if !defined(Q_WS_WIN) // Linux
    mRenderWindow->resize (width(), height());
#endif
    mRenderWindow->windowMovedOrResized();
    mCamera->setAspectRatio(Ogre::Real(mVp->getActualWidth()) 
			    / Ogre::Real(mVp->getActualHeight()));
  }

}

/** The Qt timer event
  *
  * \param evt The Qt TimerEvent
  *
  */
void RainbruRPG::Editor::MeshViewer::timerEvent(QTimerEvent* evt){
  Q_UNUSED(evt);
  update();
  //  updateAnim();
}

/** The Qt paint event
  *
  * \param evt The Qt PaintEvent
  *
  */
void RainbruRPG::Editor::MeshViewer::paintEvent(QPaintEvent* evt){
  Q_UNUSED(evt);
  if(mRenderWindow == NULL)
    setupView();
  
  update();
}

/** Updates the view
  *
  * Do not call \c mRenderWindow->update(), \c mVp->update() in this method, 
  * it causes the keyboard to be grab, the computer crashes.
  *
  */
void RainbruRPG::Editor::MeshViewer::update(){
  if(mRenderWindow != NULL){
    Ogre::Root::getSingleton()._fireFrameStarted();
    mRenderWindow->update();

    updateStats();
    Ogre::Root::getSingleton()._fireFrameEnded();
  }
}

/** Adds a mesh named name
  *
  * \param name The filename of the mesh
  *
  */
void RainbruRPG::Editor::MeshViewer::addMesh(const char* name){
  if (!mRenderWindow)
    setupView();

  LOGI("Adding a mesh");
  LOGCATS("Mesh filename :");
  LOGCATS(name);
  LOGCAT();

  // Mesh
  Ogre::Entity *ent = mSceneManager->createEntity( "Essai", name );
  ent->setCastShadows( true );
  Ogre::SceneNode* sn=mSceneManager->getRootSceneNode()
    ->createChildSceneNode( Vector3( 0, 0, 0 ) );

  //  sn->setOrientation(rw, rx, ry, rz);
  sn->attachObject( ent );

  mCamera->setPosition(Vector3(800,200,1200));
  //  mCamera->lookAt( 0.0f ,0.0f ,0.0f );
}

/** Updates the statistics
  *
  * Updates the FPS and triangles values
  *
  */
void RainbruRPG::Editor::MeshViewer::updateStats(){
  try{
    const RenderTarget::FrameStats& stats = mRenderWindow->getStatistics();
    int FPS = (int)stats.lastFPS;
    int triangles = stats.triangleCount;

    emit updateFpsCount(FPS);
    emit updateTriCount(triangles);
  }
  catch(...){}
}

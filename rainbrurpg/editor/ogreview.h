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

#ifndef __OgreView_h__
#define __OgreView_h__

#include <QWidget>
#include <QMouseEvent>
#include <QMessageBox>
#include <QRgb>
#include <QColor>
#include <QString>

#include <ogreimport.h>
#if (OGRE_PLATFORM  == OGRE_PLATFORM_WIN32)
#include <windows.h>
#endif

#include "loglistener.h"
#include "selectioncycle.h"

using namespace RainbruRPG::Editor;

/** A Ogre3D renderer embedded in a QWidget
  *
  * This code is based on the Quentin Bereau's Show Mesh 
  *
  */
class OgreView : public QWidget{
  Q_OBJECT

public:
  OgreView(QWidget* parent = 0);
  ~OgreView();
  
  Ogre::Entity* getMainEnt();
  
  /// Not yet documented
  void addObject(Ogre::String);
  
  //-->Fog
  void setFog(int);
  void setFogColor(QColor);
  QColor getFogColor();
  
  //-->Background
  void setBackgroundColor(QColor);
  QColor getBackgroundColor();
  
  //-->Shadow
  void setShadow(int);
  
  //-->Light
  void setAmbientLight(QColor);
  QColor getAmbientLight();
  void setDiffuseColor(QColor);
  QColor getDiffuseColor();
  void setSpecularColor(QColor);
  QColor getSpecularColor();
  /// Not yet documented
  void createPointLight(Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String);//name, xPos, yPos, zPos, diffuse color, specular color
  /// Not yet documented
  void createDirectionalLight(Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String);//name, xDir, yDir, zDir, diffuse color, specular color
  /// Not yet documented
  void createSpotlight(Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String);

  /// Not yet documented
  void updatePointLight(Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String);

  /// Not yet documented
  void updateDirectionalLight(Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String);

  /// Not yet documented
  void updateSpotlight(Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String, Ogre::String);
  /// Not yet documented
  void deleteLight(Ogre::String);//name
  
  //-->Display
  void setRenderDetail(int);
  void setLOD(int);
  void setBoundingBoxes(int);
  void setSkeleton(int);
  
  //-->Material
  void updateMaterial();
  
  //-->Animation
  void setAnimationState(Ogre::String);
  void setAnimLoop(bool);
  void setAnimEnabled(bool);
  
  //Log
  Ogre::String getLog();
  ///////////////////
  
  //Stats
  float getFPS();
  float getTriangles();
  Ogre::Vector3 getPosCamera();
  Ogre::Vector3 getDirCamera();
  ///////
  
  //Entity
  /** The main Ogre entity */
  Ogre::Entity* mainEnt;
  /** The main entity animation state */
  Ogre::AnimationState* mainEntAnim;
  ////////
  
 protected:
  void setupView();
  
  void update();
  void updateAnim();
  void setupResources();
  void updateStats();
  
  void resizeEvent(QResizeEvent* evt);
  void timerEvent(QTimerEvent* evt);
  void paintEvent(QPaintEvent* evt);
  
  void dragEnterEvent(QDragEnterEvent* evt);
  void dropEvent(QDropEvent* evt);
  
  void keyPressEvent(QKeyEvent* evt);
  void keyReleaseEvent(QKeyEvent* evt);
  void mousePressEvent(QMouseEvent* evt);
  void mouseReleaseEvent(QMouseEvent* evt);
  void mouseMoveEvent(QMouseEvent* evt);
  void wheelEvent(QWheelEvent* evt);
  
  void selectObject(QMouseEvent*);

  //Setup
  /** The Ogre render window */
  Ogre::RenderWindow* mRenderWindow;
  /** The Ogre scene manager */
  Ogre::SceneManager* mSceneMgr;
  /** The Ogre camera */
  Ogre::Camera* mCamera;
  /** The Ogre viewport */
  Ogre::Viewport* mVp;
  /** The Ogre root object */
  Ogre::Root* mRoot;
  ///////
  
  //Deplacement
  /** The direction of the camera */
  Ogre::Vector3 mDirection;
  /** The rotation value */
  Ogre::Real mRotate;
  /** The move value */
  Ogre::Real mMove;
  /** Defining if the camera is moving */
  bool isMoving;
  /** The position of the mousePressed event */
  QPoint mousePressPos;
  /** The position of the mouse */
  QPoint mousePos;
  /** A value used for tha View */
  float angleX;
  /** A value used for tha View */
  float angleY;
  /** A value used for tha View */
  float rotX;
  /** A value used for tha View */
  float rotY;
  ////////////
  
  //Entity
  /** The Ogre main Scene node */
  Ogre::SceneNode* mainNode;
  /** An internally used Ogre entity */
  Ogre::SubEntity* mainSubEnt;
  ////////
  
  //Base Plane
  //Ogre::MovablePlane* mPlane;
  /** An internally used Ogre entity */
  Ogre::Plane* mPlane;
  /** An internally used Ogre entity */
  Ogre::Entity* plane;
  /** An internally used Ogre entity */
  Ogre::SceneNode* planeNode;
  ////////////
  
  //Light
  /** The light diffuse color */
  Ogre::ColourValue lightDiffuseColor;
  /** The light specular color */
  Ogre::ColourValue lightSpecularColor;
  /** The light ambient color */
  Ogre::ColourValue ambientLightColor;
  /** The old light ambient color */
  QColor ambientOldColor;
  /** The old light diffuse color */
  QColor diffuseOldColor;
  /** The old light specular color */
  QColor specularOldColor;
  ///////
  
  //Fog
  /** The fog color */
  Ogre::ColourValue fogColor;
  /** The last selected fog color */
  QColor fogOldColor;
  /** The background color */
  Ogre::ColourValue backgroundColor;
  /** The last selected background color */
  QColor backgroundOldColor;
  /////
  
  //Ogre Stats
  /** The frame per second statistic */
  int FPS;
  /** The triangle number */
  int triangles;
  /** The last log message */
  Ogre::String oldMsgLog;
  ////////////
  
  /** A list of Ogre entity */
  QList<Ogre::Entity*> entities;
  /** A custom log listener */
  myLogListener* mLogListener;
  
  /** Is the left mouse button pressed */
  bool mouseLeftPressed;
  /** Is the right mouse button pressed */
  bool mouseRightPressed;
  /** Is the middle mouse button pressed */
  bool mouseMiddleBtn;
  /** An internally used Ogre entity */
  bool isLoopOn;
  /** An internally used Ogre entity */
  bool isAnimEnabled;
  /** An Ogre timer used to manage mouse events */
  Ogre::Timer* mouseTimer;
  /** The max millisecond number to consider a mouse click */
  int msClickTime;
  /** The main view scene query */
  Ogre::RaySceneQuery *mRaySceneQuery;
  /** The SelectionCycle used with the mouse click */
  SelectionCycle* selectionCycle;
};

#endif // __OgreView_h__

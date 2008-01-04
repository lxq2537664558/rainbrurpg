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

#include "ogreview.h"
#include "mainwindow.h"

#include <environmentsetup.h>
#include <highlightlistener.h>

#include "selectionmanager.h"
#include "globaluri.h"

using namespace Ogre;

#if !defined(Q_WS_WIN)
#include <QX11Info>
#endif

/** The default constructor
  *
  * \param parent The parent widget
  *
  */
OgreView::OgreView(QWidget* parent) : 
  QWidget(parent),
  mRenderWindow(NULL),
  mainEntAnim(NULL),
  mainSubEnt(NULL),
  mSceneMgr(NULL),
  mainNode(NULL),
  mainEnt(NULL),
  mVp(NULL)
{
  LOGI("Creating OgreView");
  mouseLeftPressed = false;
  mouseRightPressed = false;
  mouseMiddleBtn = false;
  isMoving = false;
  isLoopOn = false;
  isAnimEnabled = false;
  
  selectionCycle=new SelectionCycle();

  mDirection = Vector3::ZERO;
  mMove = 5;
  mRotate = 0.0005;
  mousePos = QPoint(0, 0);
  mousePressPos = QPoint(0, 0);
  angleX = 0.0; // Added these because the display started spinning
  angleY = 0.0; // when I upgraded to Qt4.2, they were left undefined.
  rotX = 0.0;
  rotY = 0.0;
  
  FPS = 0;
  triangles = 0;
  
  oldMsgLog = "";
  
  fogColor.setAsRGBA(qRgba(0, 0, 0, 1));
  backgroundColor.setAsRGBA(qRgba(0, 0, 0, 1));
  backgroundOldColor.setRgba(qRgba(0, 0, 0, 1));
  lightDiffuseColor.setAsRGBA(qRgba(0, 0, 0, 1));
  lightSpecularColor.setAsRGBA(qRgba(0, 0, 0, 1));
  ambientLightColor.setAsRGBA(qRgba(0, 0, 0, 1));
  
  setAcceptDrops(true);
  setupResources();
  // Creates a timer to get interval between mouse press/release events
  mouseTimer=new Timer();
  LOGI("OgreView created");
  msClickTime=200;
}

/** The default destructor
  *
  */
OgreView::~OgreView(){
  delete mouseTimer;
  mouseTimer=NULL;

  delete selectionCycle;
  selectionCycle=NULL;

  if(mRenderWindow != NULL){
    delete mRenderWindow;
    mRenderWindow = NULL;
  }
  if(mSceneMgr != NULL){
    delete mSceneMgr;
    mSceneMgr = NULL;
  }
  if(mVp != NULL){
    delete mVp;
    mVp = NULL;
  }
  if(mRoot != NULL){
    delete mRoot;
    mRoot = NULL;
  }
}

/** Setup the resources according to resources.cfg
  *
  */
void OgreView::setupResources(){
  LOGI("Setting OgreView ressources");

  // Setting up Ogre::Root
  RainbruRPG::Network::GlobalURI gu;
  std::string plugFN=gu.getShareFile("config/plugins.cfg");
  std::string ogreFN=gu.getUserDirFile("ogre.cfg");
  mRoot = new Ogre::Root(plugFN.c_str(), ogreFN.c_str(), "ogre.log");

  mLogListener = new myLogListener();
  Log* defaultLog=LogManager::getSingleton().getDefaultLog();
  defaultLog->addListener(mLogListener);
  
  std::string resCfg=gu.getShareFile("config/resources.cfg");

  ConfigFile cf;
  cf.load(resCfg);
  
  ConfigFile::SectionIterator seci = cf.getSectionIterator();
  String secName, typeName, archName, shareArchName;
  while(seci.hasMoreElements())	{
    secName = seci.peekNextKey();
    ConfigFile::SettingsMultiMap* settings = seci.getNext();
    ConfigFile::SettingsMultiMap::iterator i;
    for(i=settings->begin(); i!=settings->end(); ++i){
      typeName = i->first;
      archName = i->second;
      shareArchName= gu.getShareFile(archName);

      // Logging
      LOGCATS("secName :");
      LOGCATS(secName.c_str());
      LOGCATS(" typeName :");
      LOGCATS(typeName.c_str());
      LOGCATS(" archName :");
      LOGCATS(shareArchName.c_str());
      LOGCAT();

      ResourceGroupManager::getSingleton()
	.addResourceLocation(shareArchName, typeName, secName);
    }
  }
  
  mRoot->restoreConfig();
  LOGI("Initialise Ogre Root");
  mRoot->initialise(false);
  LOGI("OgreView ressources loadded");
}

/** Setup the view
  *
  */
void OgreView::setupView(){
    if(mRenderWindow)
        return;

    NameValuePairList params;

#if !defined(Q_WS_WIN)
    QWidget *q_parent = dynamic_cast <QWidget *> (parent());
    QX11Info xInfo = x11Info();

    params["parentWindowHandle"] = Ogre::StringConverter::toString ((unsigned long)xInfo.display()) +
        ":" + Ogre::StringConverter::toString ((unsigned int)xInfo.screen()) +
        ":" + Ogre::StringConverter::toString ((unsigned long)q_parent->winId());

#else
	params["externalWindowHandle"] = Ogre::StringConverter::toString((size_t)(HWND)winId());
#endif

    mRenderWindow = mRoot->createRenderWindow("View", width(), height(), true, &params);

    // Do not change the name of the scenemanager or the 
    // camera because it is used to move the camera later
    EnvironmentSetup es( mRenderWindow, "MainEditorView", "MainEditorCam");
    mSceneMgr=es.getSceneManager();
    mCamera=es.getCamera();
    mVp=es.getViewPort();

    SelectionManager::getSingleton().init(mSceneMgr, mCamera);

    mRaySceneQuery=mSceneMgr->createRayQuery(Ray());
    mRaySceneQuery->setSortByDistance( true );

    mSceneMgr->addRenderQueueListener(new HighlightQueueListener());

    // Scene manager used by the MeshViewer
    Ogre::SceneManager* sm2=Ogre::Root::getSingleton()
      .createSceneManager("DefaultSceneManager", "MeshViewerView");
    sm2->setAmbientLight(ColourValue(1.0f, 1.0f, 1.0f, 1.0f));

    Ogre::Camera* cam2=sm2->createCamera("MeshViewerCam");


    // Creates MeshViewer SceneManager
    //    Ogre::SceneManager* sm2= Ogre::Root::getSingleton()
    //      .createSceneManager("DefaultSceneManager", "MeshViewerView");
    //   Ogre::Camera* cam2= sm2->createCamera("MeshViewerCam");

   /*    mSceneMgr = mRoot->createSceneManager("PagingLandScapeSceneManager",
					  "MainEditorView");

    mSceneMgr->setWorldGeometry( "paginglandscape2.cfg" );
    mCamera = mSceneMgr->createCamera("MainEditorCam");

    mCamera->setPosition(Vector3(800,200,1200));
    mCamera->lookAt(Vector3(0,0,0));

    mVp = mRenderWindow->addViewport(mCamera);
    mVp->setBackgroundColour(ColourValue(0.58, 0.65, 0.76, 1));

    ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	createLight();

	TextureManager::getSingleton().setDefaultNumMipmaps(5);
	MaterialManager::getSingleton().setDefaultTextureFiltering(Ogre::TFO_ANISOTROPIC);
    MaterialManager::getSingleton().setDefaultAnisotropy(2);

    mCamera->setAspectRatio(Real(mVp->getActualWidth()) / Real(mVp->getActualHeight()));

    */
#if !defined(Q_WS_WIN) // Linux
    WId window_id;
    mRenderWindow->getCustomAttribute("GLXWINDOW", &window_id);

    // Take over the ogre created window.
    QWidget::create(window_id);

    mRenderWindow->reposition(x(),y());
#endif

    startTimer(5);
};

/** The Qt provided paintEvent
  *
  * \param evt The paint event
  *
  */
void OgreView::paintEvent(QPaintEvent *evt){
  Q_UNUSED(evt);
  if(mRenderWindow == NULL)
    setupView();
  
  update();
}

/** The Qt provided timer event
  *
  * \param evt The timer event
  *
  */
void OgreView::timerEvent(QTimerEvent* evt){
  Q_UNUSED(evt);
  update();
  updateAnim();
}

/** Updates the view
  *
  */
void OgreView::update(){
  if(mRenderWindow != NULL){
    mRoot->_fireFrameStarted();
    mRenderWindow->update();
    
    mCamera->moveRelative(mDirection);
    mCamera->yaw(Radian(angleX));
    mCamera->pitch(Radian(angleY));
    
    updateStats();
    mRoot->_fireFrameEnded();
  }
}

/** Updates the animation
  *
  */
void OgreView::updateAnim(){
  if(mainEntAnim != NULL)
    mainEntAnim->addTime(mRenderWindow->getBestFPS()/100000);
}

/** Returns the main entity
  *
  * \return The main Ogre entity
  *
  */
Ogre::Entity* OgreView::getMainEnt(){
  if(mainEnt != NULL)
    return mainEnt;
  else
    return 0;
}

/** Gets the FPS
  *
  * \return The number of frame per seconds 
  *
  */
float OgreView::getFPS(){
  return FPS;
}

/** Gets the number of diplayed triangles
  *
  * \return The number of triangles
  *
  */
float OgreView::getTriangles(){
  return triangles;
}

/** Gets the camera position
  *
  * \return The position of the camera
  *
  */
Vector3 OgreView::getPosCamera(){
  return mCamera->getPosition();
}

/** Get the camera's orientation
  *
  * \return The orientation of the camera
  *
  */
Vector3 OgreView::getDirCamera(){
  return mCamera->getDirection();
}

/** Updates the statistics
  *
  * Updates the FPS and triangles values
  *
  */
void OgreView::updateStats(){
  try{
    const RenderTarget::FrameStats& stats = mRenderWindow->getStatistics();
    FPS = (int)stats.lastFPS;
    triangles = stats.triangleCount;
  }
  catch(...){}
}

/** The Qt provided resize event
  *
  * \param evt The resize event
  *
  */
void OgreView::resizeEvent(QResizeEvent *evt){
  Q_UNUSED(evt);
  if (mRenderWindow != NULL){
#if !defined(Q_WS_WIN) // Linux
    mRenderWindow->resize (width(), height());
#endif
    mRenderWindow->windowMovedOrResized();
    mCamera->setAspectRatio(Ogre::Real(mVp->getActualWidth()) 
			    / Ogre::Real(mVp->getActualHeight()));
  }
}

/** The Qt provided keypress event
  *
  * \param evt The keypress event
  *
  */
void OgreView::keyPressEvent(QKeyEvent* evt){
  if(mainEnt != NULL && mainNode != NULL){
    switch(evt->key()){
    case Qt::Key_W:
    case Qt::Key_Up:
      rotX = -0.1;
      mainNode->pitch(Radian(rotX));
      break;
    case Qt::Key_S:
    case Qt::Key_Down:
      rotX = 0.1;
      mainNode->pitch(Radian(rotX));
      break;
    case Qt::Key_A:
    case Qt::Key_Left:
      rotY = -0.1;
      mainNode->yaw(Radian(rotY));
      break;
    case Qt::Key_D:
    case Qt::Key_Right:
      rotY = 0.1;
      mainNode->yaw(Radian(rotY));
      break;
    }
  }
}

/** The Qt provided keyrelease event
  *
  * \param evt The keyrelease event
  *
  */
void OgreView::keyReleaseEvent(QKeyEvent* evt){
  if(mainEnt != NULL && mainNode != NULL){
    switch(evt->key()){
    case Qt::Key_W:
    case Qt::Key_Up:
      rotX = 0.0;
      mainNode->pitch(Radian(rotX));
      break;
    case Qt::Key_S:
    case Qt::Key_Down:
      rotX = 0.0;
      mainNode->pitch(Radian(rotX));
      break;
    case Qt::Key_A:
    case Qt::Key_Left:
      rotY = 0.0;
      mainNode->yaw(Radian(rotY));
      break;
    case Qt::Key_D:
    case Qt::Key_Right:
      rotY = 0.0;
      mainNode->yaw(Radian(rotY));
      break;
    }
  }
}

/** The Qt provided mouse pressed event
  *
  * \param evt The mouse pressed event
  *
  */
void OgreView::mousePressEvent(QMouseEvent* evt){
  if(evt->button() == Qt::LeftButton)
    mouseLeftPressed = true;
  if(evt->button() == Qt::RightButton){
    mouseRightPressed = true;
    mousePos = evt->pos();
  }
  if(evt->button() == Qt::MidButton)
    mouseMiddleBtn = true;

  mouseTimer->reset();
}

/** The Qt provided mouse released event
  *
  * \param evt The mouse released event
  *
  */
void OgreView::mouseReleaseEvent(QMouseEvent* evt){
  Q_UNUSED(evt);
  mouseLeftPressed = false;
  mouseRightPressed = false;
  mouseMiddleBtn = false;

  int i=mouseTimer->getMilliseconds();
  LOGI("A button was released");
  LOGCATS("Time elapsed since last mouse press event :");
  LOGCATI(i);
  LOGCATS(" milliseconds");
  LOGCAT();

  if (i<msClickTime){
    LOGI("This is a mouse click");
    selectObject(evt);
  }

}

/** The Qt provided mouse moved event
  *
  * \param evt The mouse moved event
  *
  */
void OgreView::mouseMoveEvent(QMouseEvent* evt){
  float dirScale=4.0f;
  if(mouseMiddleBtn || mouseLeftPressed){
    QPoint currentPos = evt->pos();
    
    if(mousePos.x() < currentPos.x())
      mDirection.x = dirScale;
    else if(mousePos.x() > currentPos.x())
      mDirection.x = -dirScale;
    else
      mDirection.x = 0;
    
    if(mousePos.y() < currentPos.y())
      mDirection.y = -dirScale;
    else if(mousePos.y() > currentPos.y())
      mDirection.y = dirScale;
    else
      mDirection.y = 0;
    
    update();
    mousePos = currentPos;
    mDirection = Vector3::ZERO;
  }

  float moveScale=0.04f;
  if(mouseRightPressed){
    QPoint currentPos = evt->pos();
    
    if(mousePos.x() < currentPos.x())
      angleX = -moveScale;
    else if(mousePos.x() > currentPos.x())
      angleX = moveScale;
    else
      angleX = 0.00;
    
    if(mousePos.y() < currentPos.y())
      angleY = -moveScale;
    else if(mousePos.y() > currentPos.y())
      angleY = moveScale;
    else
      angleY = 0.00;
    
    update();
    mousePos = currentPos;
    angleX = 0.00;
    angleY = 0.00;
  }
  //if(mouseLeftPressed){
  //	QPoint currentPos = evt->pos();
  
  //	if(mousePos.x() < currentPos.x())
  //		mDirection.x = -0.01;
  //	else if(mousePos.x() > currentPos.x())
  //		mDirection.x = 0.01;
  //	else
  //		mDirection.x = 0;
  //
  //	update();
  //	mousePos = currentPos;
  //	mDirection = Vector3::ZERO;
  //}
  //if(mouseRightPressed){
  //       QPoint currentPos = evt->pos();
  
  //	if(mousePos.x() < currentPos.x())
  //		mDirection.x = -0.01;
  //	else if(mousePos.x() > currentPos.x())
  //		mDirection.x = 0.01;
  //	else
  //		mDirection.x = 0;
  
  //	if(mousePos.y() < currentPos.y())
  //		mDirection.y = -0.01;
  //	else if(mousePos.y() > currentPos.y())
  //		mDirection.y = 0.01;
  //	else
  //		mDirection.y = 0;
  
  //	mousePos = currentPos;
  //       update();
  //	mDirection = Vector3::ZERO;
  //}
}

/** The Qt provided mouse wheel event
  *
  * \param evt The mouse wheel event
  *
  */
void OgreView::wheelEvent(QWheelEvent* evt){
  mDirection.z = -evt->delta();
  update();
  mDirection.z = 0;
}

/** Adds an object
  *
  * \param name The mesh name (including the .mesh extension)
  *
  */
void OgreView::addObject(Ogre::String name){
  LOGI("Adding object :");
  LOGCATS("Object name :");
  LOGCATS(name.c_str());
  LOGCAT();
  //Update the name
  String meshName = name;
  meshName.substr(meshName.size()-5, 5);

  //Remove old object
  if(mainEnt != NULL){
    mSceneMgr->destroyEntity(mainEnt);
    mainEntAnim = 0;
  }
  if(mainNode != NULL)
    mSceneMgr->destroySceneNode(mainNode->getName());

  //Add New Object
  mainEnt = mSceneMgr->createEntity(meshName, name);
  mainNode = mSceneMgr->getRootSceneNode()
    ->createChildSceneNode(meshName+"node");

  mainNode->attachObject(mainEnt);
  mainNode->setPosition(Vector3(0, 0, 0));

  //Update the camera's pos to fit whith the object size
  mCamera->setPosition(mainNode->getPosition().x, 
		       mainNode->getPosition().y, 
		       mainNode->getPosition().z - 200);
  mCamera->lookAt(mainNode->getPosition());
  LOGI("Object correctly added");
}

/** Sets the fog type
  *
  * \param fogType The type of fog
  *
  */
void OgreView::setFog(int fogType){
  switch(fogType){
  case 0:
    mSceneMgr->setFog(FOG_NONE);
    break;
  case 1:
    mSceneMgr->setFog(FOG_LINEAR, fogColor, 0.0, 50, 500);
    break;
  case 2:
    mSceneMgr->setFog(FOG_EXP, fogColor, 0.005);
    break;
  case 3:
    mSceneMgr->setFog(FOG_EXP2, fogColor, 0.003);
    break;
  }
}

/** Sets the fog color
  *
  * \param color The new fog color
  *
  */
void OgreView::setFogColor(QColor color){
  fogOldColor = color;
  fogColor.setAsARGB(color.rgba());
  if(mSceneMgr->getFogMode() == FOG_LINEAR)
    mSceneMgr->setFog(FOG_LINEAR, fogColor, mSceneMgr->getFogDensity(), 
		      mSceneMgr->getFogStart(), mSceneMgr->getFogEnd());

  else if(mSceneMgr->getFogMode() == FOG_EXP)
    mSceneMgr->setFog(FOG_EXP, fogColor, mSceneMgr->getFogDensity());

  else if(mSceneMgr->getFogMode() == FOG_EXP2)
    mSceneMgr->setFog(FOG_EXP2, fogColor, mSceneMgr->getFogDensity());
}

/** Gets the fog color
  *
  * \return The fog color
  *
  */
QColor OgreView::getFogColor(){
  return fogOldColor;
}

/** Change the background color
  *
  * \param color The new background color
  *
  */
void OgreView::setBackgroundColor(QColor color){
  backgroundOldColor = color;
  backgroundColor.setAsARGB(color.rgba());
  mVp->setBackgroundColour(backgroundColor);
}

/** Gets the background color
  * 
  * \return The background color
  *
  */
QColor OgreView::getBackgroundColor(){
  return backgroundOldColor;
}

/** Sets the shadow technique
  *
  * \param shadowType The shadow type
  *
  */
void OgreView::setShadow(int shadowType){
  if(shadowType == 0)
    mSceneMgr->setShadowTechnique(SHADOWTYPE_NONE);
  else if(shadowType == 1)
    mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_MODULATIVE);
  else if(shadowType == 2)
    mSceneMgr->setShadowTechnique(SHADOWTYPE_STENCIL_ADDITIVE);
  else if(shadowType == 3)
    mSceneMgr->setShadowTechnique(SHADOWTYPE_TEXTURE_MODULATIVE);
}

/** Set the ambient light color
  *
  * \param color The new color
  *
  */
void OgreView::setAmbientLight(QColor color){
  mSceneMgr->setAmbientLight(ColourValue(color.redF(), color.greenF(), 
					 color.blueF(), color.alphaF()));

  ambientOldColor = color;
}

/** Get the ambient light color
  *
  * \return The color
  *
  */
QColor OgreView::getAmbientLight(){
  return ambientOldColor;
}

/** Set the diffuse color
  *
  * \param color The new color
  *
  */
void OgreView::setDiffuseColor(QColor color){
  diffuseOldColor = color;
}

/** Get the diffuse color
  *
  * \return The color
  *
  */
QColor OgreView::getDiffuseColor(){
  return diffuseOldColor;
}

/** Set the specular color
  *
  * \param color The new color
  *
  */
void OgreView::setSpecularColor(QColor color){
  specularOldColor = color;
}

/** Get the specular color
  *
  * \return The color
  *
  */
QColor OgreView::getSpecularColor(){
  return specularOldColor;
}

/** Creates a light
  *
  * \param name The name of the color
  * \param xPos The x position
  * \param yPos The y position
  * \param zPos The z position
  * \param diffuse The diffuse color
  * \param specular The specular color
  *
  */
void OgreView::createPointLight(Ogre::String name, Ogre::String xPos, 
	Ogre::String yPos, Ogre::String zPos, Ogre::String diffuse, 
	Ogre::String specular)
{

  Light* newLight = mSceneMgr->createLight(name);
  newLight->setPosition(StringConverter::parseReal(xPos), 
			StringConverter::parseReal(yPos), 
			StringConverter::parseReal(zPos));

  QColor diffuseColor(diffuse.c_str());
  QColor specularColor(specular.c_str());
  lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
  lightSpecularColor.setAsRGBA(specularColor.rgba());
  diffuseOldColor = diffuseColor;
  specularOldColor = specularColor;
  newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), 
			     diffuseColor.blueF());
  newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), 
			      specularColor.blueF());
}

/** Creates a directional light
  *
  * \param name The name of the color
  * \param xDir The x direction
  * \param yDir The y direction
  * \param zDir The z direction
  * \param diffuse The diffuse color
  * \param specular The specular color
  *
  */
void OgreView::createDirectionalLight(Ogre::String name, Ogre::String xDir, 
	Ogre::String yDir, Ogre::String zDir, Ogre::String diffuse, 
        Ogre::String specular)
{

  Light* newLight = mSceneMgr->createLight(name);
  newLight->setDirection(StringConverter::parseReal(xDir), 
			 StringConverter::parseReal(yDir), 
			 StringConverter::parseReal(zDir));

  QColor diffuseColor(diffuse.c_str());
  QColor specularColor(specular.c_str());
  lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
  lightSpecularColor.setAsRGBA(specularColor.rgba());
  diffuseOldColor = diffuseColor;
  specularOldColor = specularColor;
  newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), 
			     diffuseColor.blueF());

  newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), 
			      specularColor.blueF());
}

/** Creates a spot light
  *
  * \param name The name of the color
  * \param xPos The x position
  * \param yPos The y position
  * \param zPos The z position
  * \param xDir The x direction
  * \param yDir The y direction
  * \param zDir The z direction
  * \param diffuse The diffuse color
  * \param specular The specular color
  *
  */
void OgreView::createSpotlight(Ogre::String name, Ogre::String xPos, 
	Ogre::String yPos, Ogre::String zPos, Ogre::String xDir, 
	Ogre::String yDir, Ogre::String zDir, Ogre::String diffuse, 
        Ogre::String specular)
{

  Light* newLight = mSceneMgr->createLight(name);
  newLight->setPosition(StringConverter::parseReal(xPos), 
			StringConverter::parseReal(yPos), 
			StringConverter::parseReal(zPos));

  newLight->setDirection(StringConverter::parseReal(xDir), 
			 StringConverter::parseReal(yDir), 
			 StringConverter::parseReal(zDir));
  
  QColor diffuseColor(diffuse.c_str());
  QColor specularColor(specular.c_str());
  lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
  lightSpecularColor.setAsRGBA(specularColor.rgba());
  diffuseOldColor = diffuseColor;
  specularOldColor = specularColor;
  newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), 
			     diffuseColor.blueF());

  newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), 
			      specularColor.blueF());
}

/** Updates a point light
  *
  * \param oldName The old name of the light
  * \param name The name of the color
  * \param xPos The x position
  * \param yPos The y position
  * \param zPos The z position
  * \param diffuse The diffuse color
  * \param specular The specular color
  *
  */
void OgreView::updatePointLight(Ogre::String oldName, Ogre::String name, 
	Ogre::String xPos, Ogre::String yPos, Ogre::String zPos, 
	Ogre::String diffuse, Ogre::String specular)
{

  Light* newLight = NULL;

  //name has changed
  if(oldName != "none"){
    mSceneMgr->destroyLight(oldName);
    newLight = mSceneMgr->createLight(name);
  }
  else
    newLight = mSceneMgr->getLight(name);
  
  newLight->setPosition(StringConverter::parseReal(xPos), 
			StringConverter::parseReal(yPos), 
			StringConverter::parseReal(zPos));

  QColor diffuseColor(diffuse.c_str());
  QColor specularColor(specular.c_str());
  lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
  lightSpecularColor.setAsRGBA(specularColor.rgba());
  diffuseOldColor = diffuseColor;
  specularOldColor = specularColor;
  newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), 
			     diffuseColor.blueF());

  newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), 
			      specularColor.blueF());
}

/** Updates a direction light
  *
  * \param oldName The old name of the light
  * \param name The name of the color
  * \param xDir The x direction
  * \param yDir The y direction
  * \param zDir The z direction
  * \param diffuse The diffuse color
  * \param specular The specular color
  *
  */
void OgreView::updateDirectionalLight(Ogre::String oldName, Ogre::String name, 
      Ogre::String xDir, Ogre::String yDir, Ogre::String zDir, 
      Ogre::String diffuse, Ogre::String specular)
{

  Light* newLight = NULL;

  //name has changed
  if(oldName != "none"){
    mSceneMgr->destroyLight(oldName);
    newLight = mSceneMgr->createLight(name);
  }
  else
    newLight = mSceneMgr->getLight(name);
  
  newLight->setDirection(StringConverter::parseReal(xDir), StringConverter::parseReal(yDir), StringConverter::parseReal(zDir));
  
  QColor diffuseColor(diffuse.c_str());
  QColor specularColor(specular.c_str());
  lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
  lightSpecularColor.setAsRGBA(specularColor.rgba());
  diffuseOldColor = diffuseColor;
  specularOldColor = specularColor;
  newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
  newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

/** Updates a spot light
  *
  * \param oldName The old name of the light
  * \param name The name of the color
  * \param xPos The x position
  * \param yPos The y position
  * \param zPos The z position
  * \param xDir The x direction
  * \param yDir The y direction
  * \param zDir The z direction
  * \param diffuse The diffuse color
  * \param specular The specular color
  *
  */
void OgreView::updateSpotlight(Ogre::String oldName, Ogre::String name, 
       Ogre::String xPos, Ogre::String yPos, Ogre::String zPos, 
       Ogre::String xDir, Ogre::String yDir, Ogre::String zDir, 
       Ogre::String diffuse, Ogre::String specular)
{

  Light* newLight = NULL;
  if(oldName != "none"){//name has changed
    mSceneMgr->destroyLight(oldName);
    newLight = mSceneMgr->createLight(name);
  }
  else
    newLight = mSceneMgr->getLight(name);

  newLight->setPosition(StringConverter::parseReal(xPos), StringConverter::parseReal(yPos), StringConverter::parseReal(zPos));
  newLight->setDirection(StringConverter::parseReal(xDir), StringConverter::parseReal(yDir), StringConverter::parseReal(zDir));
  
  QColor diffuseColor(diffuse.c_str());
  QColor specularColor(specular.c_str());
  lightDiffuseColor.setAsRGBA(diffuseColor.rgba());
  lightSpecularColor.setAsRGBA(specularColor.rgba());
  diffuseOldColor = diffuseColor;
  specularOldColor = specularColor;
  newLight->setDiffuseColour(diffuseColor.redF(), diffuseColor.greenF(), diffuseColor.blueF());
  newLight->setSpecularColour(specularColor.redF(), specularColor.greenF(), specularColor.blueF());
}

/** Deletes a light
  *
  * \param name The name of the light
  *
  */
void OgreView::deleteLight(Ogre::String name){
  mSceneMgr->destroyLight(name);
}

/** Sets the render detail
  *
  * \param value The new detail
  *
  */
void OgreView::setRenderDetail(int value){
  switch(value){
  case 0:
    mCamera->setPolygonMode(PM_SOLID);
    break;
  case 1:
    mCamera->setPolygonMode(PM_WIREFRAME);
    break;
  case 2:
    mCamera->setPolygonMode(PM_POINTS);
    break;
  }
}

/** Changes the LOG (Level Of Detail
  *
  * \param value The new LOD value
  *
  */
void OgreView::setLOD(int value){
  mainEnt->setMeshLodBias(value);
}

/** Sets the showBoundingBox value
  *
  * \param value The new value
  *
  */
void OgreView::setBoundingBoxes(int value){
  if(value)
    mainNode->showBoundingBox(true);
  else
    mainNode->showBoundingBox(false);
}

/** Sets the setDisplaySkeleton value
  *
  * \param value The new value
  *
  */
void OgreView::setSkeleton(int value){
  if(value)
    mainEnt->setDisplaySkeleton(true);
  else
    mainEnt->setDisplaySkeleton(false);
}

/** Reloads the used materials
  *
  */
void OgreView::updateMaterial(){
  for(unsigned int i=0; i<mainEnt->getNumSubEntities(); ++i){
    mainSubEnt = mainEnt->getSubEntity(i);
    mainSubEnt->getMaterial()->reload();
  }
}

/** Change the animation state
  *
  * \param name The new state
  *
  */
void OgreView::setAnimationState(Ogre::String name){
  if(mainEntAnim != NULL){
    mainEntAnim->setLoop(false);
    mainEntAnim->setEnabled(false);
  }
  mainEntAnim = mainEnt->getAnimationState(name);
  mainEntAnim->setLoop(false);
  if(isLoopOn)
    mainEntAnim->setLoop(true);
  if(isAnimEnabled)
    mainEntAnim->setEnabled(true);
}

/** Sets the animation loop value
  *
  * \param enable The new value
  *
  */
void OgreView::setAnimLoop(bool enable){
  mainEntAnim->setLoop(enable);
  isLoopOn = enable;
}

/** Enable or disable the animation
  *
  * \param enable The new value
  *
  */
void OgreView::setAnimEnabled(bool enable){
  mainEntAnim->setEnabled(enable);
  isAnimEnabled = enable;
}

/** Gets the last Log
  *
  * \return The last log
  *
  */
String OgreView::getLog(){
  String msgLog(mLogListener->getMsg().toStdString() + '\n');

  //the message has been updated
  if(msgLog != oldMsgLog){
    return msgLog;
    ///////////////////////////////////////////////////////////
    // Why is this here? It never gets executed...
    ///////////////////////////////////////////////////////////
    //oldMsgLog = msgLog;
    //QMessageBox::warning(this, msgLog.c_str(), oldMsgLog.c_str());
  }
  else
    return "";
}

/** The drag and drop enter event
  *
  * \param evt The drag event
  *
  */
void OgreView::dragEnterEvent(QDragEnterEvent* evt){

#if defined(Q_WS_WIN)
  if(evt->mimeData()->hasUrls()){
    QRegExp fileMatcher("^/([A-Z]:/.*\\.mesh)$");
    if( fileMatcher.exactMatch(evt->mimeData()->urls().first().path()) )
      evt->acceptProposedAction();
  }
#else
  QRegExp fileMatcher("^file://(/.*\\.mesh)$");
  if( fileMatcher.exactMatch(evt->mimeData()->text()) )
    evt->acceptProposedAction();
#endif
};


/** The drop event
  *
  * \param evt The drop event
  *
  */
void OgreView::dropEvent(QDropEvent* evt)
{
#if defined(Q_WS_WIN)
    QRegExp fileMatcher("^/([A-Z]:/.*\\.mesh)$");
    if( fileMatcher.exactMatch(evt->mimeData()->urls().first().path()) )
    {
        QString meshName = fileMatcher.cap(1);
        meshName.replace("/", "\\");
#else
    QRegExp fileMatcher("^file://(/.*\\.mesh)$");
    if( fileMatcher.exactMatch(evt->mimeData()->text()) )
    {
        QString meshName = fileMatcher.cap(1);
#endif
	//		((MainWindow*)parentWidget())->loadObj(meshName);
        evt->acceptProposedAction();
    }
};

/** Called if a mouse click is done
  *
  * It uses Ogre RaySceneQuery and camera getCameraToViewportRay to 
  * know if we click on an Ogre Entity.
  *
  * \param evt The Qt mouse event
  *
  */
void OgreView::selectObject(QMouseEvent* evt){
  LOGI("OgreView::selectObject called");
  Ogre::Real x, y;
  x=(float)evt->x()/width();
  y=(float)evt->y()/height();

  Ogre::Ray mouseRay = mCamera
    ->getCameraToViewportRay( x, y );
  mRaySceneQuery->setRay( mouseRay );

  Ogre::RaySceneQueryResult &result = mRaySceneQuery->execute();

  Ogre::String selName=selectionCycle->getNextEntity(result);
  LOGCATS("Selected object name : ");
  LOGCATS(selName.c_str());
  LOGCAT();
  SelectionManager::getSingleton().selectNewObject(selName);

}

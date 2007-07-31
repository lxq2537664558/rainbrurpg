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

#include "gameengine.h"

#include <iostream>
#include <OGRE/OgreRenderSystem.h>
#include <OGRE/OgreIteratorWrappers.h>
#include <OGRE/OgreSceneManagerEnumerator.h>
#include <OGRE/OgreLogManager.h>

#include <CEGUI/CEGUIDefaultLogger.h>

#include <logger.h>
#include "gamestate.h"

#include "gsmainmenu.h"
#include "gslocaltest.h"
#include "gsconnection.h"
#include "gscreateaccount.h"
#include "gsserverlist.h"

#include "guimanager.h"
#include "guiframelistener.h"
#include "exampleframelistener.h"
#include "xmlobjectlist.h"
#include "globaluri.h"

using namespace RainbruRPG::Events;


/** A function used to know if the GameEngine is running.
  * 
  * \return the value of the m_running variable
  */
bool RainbruRPG::Core::GameEngine::running() {
  return m_running;
}

/** Initialize the GameEngine instance
  *
  * This method must be called once. It loads the options with a
  * XmlOptions class instance.
  *
  * It only initialize 3D engine. Each GameState initialize its
  * own parameters.
  */
void RainbruRPG::Core::GameEngine::init(){
  userName="";
  userPwd="";
  mInputMgr=NULL;
  actualState=ST_MAIN_MENU;

  initOgre();
  initCEGUI();
  initStates();
}

/** Set m_running to \c true telling GameEngine it can run
  *
  *
  * This call is needed as it sets m_running to true. If m_running is set
  * to false, run() does not enter in the main loop.
  *
  * \sa run(), m_running
  */
void RainbruRPG::Core::GameEngine::play() {
  m_running = true; 
}

/** Set m_running to false so the run method do nothing
  *
  * It can be called even before the init or run methods
  * The m_running value is tested by the GuiFrameListener for
  * earch frame and if the GameEngine is not still running,
  * it request the shutdown of the engine.
  */
void RainbruRPG::Core::GameEngine::quit() {
  LOGI("Exiting GameEngine ...");
  mInputMgr->removeAllListeners();
  m_running = false; 
}

/** Enter in the Ogre mainloop
  *
  * This call must follow a call to play() if you want to enter
  * in the mainloop.
  *
  * \sa play(), m_running
  */
void RainbruRPG::Core::GameEngine::run() {
  if (m_running){

     LOGI("Setting the GuiFrameListener");
    
    mFrameListener= new GuiFrameListener(mWindow, mCamera, mGUIRenderer);
    Ogre::Root::getSingleton().addFrameListener(mFrameListener);
    
    
    
    try {
      LOGI("starting rendering");
      Ogre::Root::getSingleton().startRendering();
    } 
    catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
      MessageBox( NULL, e.getFullDescription().c_str(), 
		  "An exception has occured!", 
		  MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
      std::string err= "An exception has occured: ";
      err+= e.getFullDescription().c_str();
      LOGE(err.c_str());
#endif
    }
  }

  LOGI("GameEngine::run ended");
}

/** Initialize all the states
  *
  *
  */
void RainbruRPG::Core::GameEngine::initStates() {
  LOGI("Initializing Game states...");

  GameState *gs1=new gsLocalTest();
  GameState *gs2=new gsConnection();
  GameState *gs3=new gsMainMenu();
  GameState *gs4=new gsCreateAccount();
  GameState *gs5=new gsServerList();

  states.push_back(gs1);
  states.push_back(gs2);
  states.push_back(gs3);
  states.push_back(gs4);
  states.push_back(gs5);

}

/** Set the current GameState to \c t
  *
  * \param t The GameState type to switch to
  */
void RainbruRPG::Core::GameEngine::changeState(tStateType t){
  if (m_running){

    switch (t){
    case ST_MAIN_MENU:
      LOGI("Switching to MainMenu Game...");
      break;
    case ST_LOCAL_TEST:
      LOGI("Switching to LocalTest...");
      break;
    case ST_MENU_CONNECT:
      LOGI("Switching to ConnectMenu Game...");
      break;
    case ST_CREATE_ACCOUNT:
      LOGI("Switching to CreateMenu...");
      break;
    case ST_SERVER_LIST:
      LOGI("Switching to ServerList...");
      break;
    default:
      LOGW("Unknown game state received");
    }


    if ((unsigned int)t>states.size()){
      LOGE("An error will occured : we are calling a non-inexisting "
	   "gamestate");
    }
    else{
      tGameStateType oldType=states[actualState]->getStateType();
      tGameStateType newType=states[t]->getStateType();
      if (oldType!=newType){
	if (oldType==GST_MENU){
	  if (newType==GST_GAME){
	    this->fromMenuToGame(states[actualState], states[t]);
	  }
	}
      }

      // Pause the actual state
      states[actualState]->pause();

      // Change the state
      actualState=t;
      // Init the new state or resume it if it
      // was already initialized
      if (states[actualState]->wasInit()){
	states[actualState]->resume();
      }
      else{
	states[actualState]->init();
      }

    }
  }
}



/** The Destrictor of the GameEngine destructor
  *
  *
  */
void RainbruRPG::Core::GameEngine::cleanup(){
  LOGI("Cleaning up GameEngine...");
  m_running=false;
  delete mInputMgr;
/*
  this->cleanStates();
  this->cleanIrrgui();

  delete erc;
  erc=NULL;
*/
}

/** delete all states and receivers in vectors
  *
  */
void RainbruRPG::Core::GameEngine::cleanStates(){
  LOGI("  Cleaning up GameStates...");
  // delete all states
  for (unsigned int indx = 0; indx < states.size(); indx++){
    states[indx]->cleanup();
    delete states[indx];
  } 

  actualState=-1;
  states.clear();
}

/** Shows the debugging console 
  *
  */
void RainbruRPG::Core::GameEngine::showConsole(){

}

/** Hides the debugging console 
  *
  */
void RainbruRPG::Core::GameEngine::hideConsole(){

}

/** Test if the given User can be connected
  *
  * The values are entered by the user in the gsConnection gamestate.
  * There are send to a \ref RainbruRPG::Network::Ident::ClientConnect
  * "ClientConnect" instance to test connection rights.
  *
  * \param user The userName
  * \param pwd The password hashsum of the given user
  *
  * \return \c true if the connection is accepted otherwise returns \c false.
  */
bool RainbruRPG::Core::GameEngine::connectUser(const char* user, 
					       const char* pwd ){
  LOGI("Trying to connect a user");

  ClientConnect cc(user, pwd);

  tClientConnectReturn ret=cc.getResponse();

  const char* errMsg;

  switch(ret){
  case CCR_INEXISTANT_USER: 
    errMsg="This user does not exist.\nPlease create an account";
    break;
  case CCR_WRONG_PWD:
    errMsg="Wrong password.";
    break;
  case CCR_EMAIL_NOT_VALIDATED:
    errMsg="Your email was not yet validated.";
     break;
  case CCR_BLACKLIST:
    errMsg="Your in blacklist.";
    break;
  case CCR_UNKNOWN_ERROR:
    errMsg="An unknown error occured.";
    break;
  case CCR_SUCCESS:
    errMsg="";
    break;
  }

  if (ret!=CCR_SUCCESS){
    LOGW("The login of this user failed");
    GuiManager::getSingleton()
      .showMessageBox("Connection failed", errMsg, 
		      states[actualState]->getRootWindowName());

    return false;

  }
  else{
    LOGI("The login is successfull");
    userName=user;
    userPwd=pwd;

    return true;
  }
}


/** Set the Ogre renderer
  *
  * \param rName A string representing the ogre renderer name
  *
  * \todo Use Root::getSingleton().getRenderSystemByName(rName) when available
  */
void RainbruRPG::Core::GameEngine::setRender(const char* rName){
  LOGI("Setting renderer :");
  LOGCATS("Renderer name :");
  LOGCATS(rName);
  LOGCAT();

  bool found=false;
  const char* name;

  // No Root::getSingleton().getRenderSystemByName(rName) function !
  Ogre::RenderSystemList::iterator listIt;
  Ogre::RenderSystem* item;

  Ogre::RenderSystemList* list=Ogre::Root::getSingleton().
    getAvailableRenderers();


  // Adds the render name to the hold browser
  for( listIt= list->begin(); listIt!= list->end(); listIt++){
    item=*listIt;
    name=item->getName().c_str();
    // We have the good Render system
    if (strcmp(name, rName)==0){
      found=true;
      Ogre::Root::getSingleton().setRenderSystem(item);
    }
  }

  if (!found){
    LOGE("No driver found");
  }
}

/** Get the Ogre render window
  *
  * The render window is created in the initOgre() function. If you
  * want a valid pointer, call this function after the initialization
  * of Ogre.
  *
  * \return The Ogre render window
  *
  */
Ogre::RenderWindow* RainbruRPG::Core::GameEngine::getRenderWindow(){
  return this->mWindow;
}

/** Inits the Ogre3D rendering engine
  *
  * The first step is to try a configuration restore. Then it create
  * the Ogre render window. The last step is to call chooseSceneManager(),
  * createCamera(), createViewports(). The last step is to create the 
  * Ogre overlay (debug and title).
  *
  */
void RainbruRPG::Core::GameEngine::initOgre(){
  if (!Ogre::Root::getSingleton().restoreConfig())
    LOGE("The Ogre configuration cannot be restored");

  bool  	defaultLog = true;
  bool  	debuggerOutput = false;
  bool  	suppressFileOutput = false;
  Ogre::Log* log=Ogre::LogManager::getSingleton()
    .createLog("Ogre.log", defaultLog, debuggerOutput, suppressFileOutput);

  Ogre::LogManager::getSingleton().setDefaultLog(log);

  log->setLogDetail(Ogre::LL_BOREME);


  // True for autocreate window
  Ogre::Root::getSingleton().initialise(false, "RainbruRPG blah");

  // It seems to avoid the 'GLX_icon.png not found' Exception
  // as the setupResources() and loadResources() functions are
  // called later
  GlobalURI gu;
  std::string dataPath=gu.getShareFile("data");
  Ogre::Root::getSingleton().addResourceLocation(dataPath, "FileSystem");


#ifdef RAINBRU_RPG_DEBUG
  bool fullscreen=false;
  int winWidth=640;
  int winHeight=480;
#else
  bool fullscreen=true;
  int winWidth=1024;
  int winHeight=768;
#endif // RAINBRU_RPG_DEBUG

  mWindow=Ogre::Root::getSingleton().getRenderSystem()
    ->createRenderWindow("RainbruRPG2", winWidth, winHeight, fullscreen);
  
  initOIS();

  if (!mWindow){
    LOGE("The Ogre::Root cannot be initalized");
  }

  // Added for Ogre v1.2 to avoid crashes due to uninitialized materials,
  // Techniques and passes
  MaterialManager::getSingleton().initialise();

  setupResources();
  loadResources();

  logSceneMgrList();
  chooseSceneManager();
  createCamera();
  createViewports();

  // Set default mipmap level (NB some APIs ignore this)
  TextureManager::getSingleton().setDefaultNumMipmaps(5);

#ifdef RAINBRU_RPG_DEBUG
  GuiManager::getSingleton().createNumDebugWindow(mWindow);
#endif

  GuiManager::getSingleton().createTitleOverlay(mWindow);
  
}

/** Init CEGUI
  *
  *
  *
  */
void RainbruRPG::Core::GameEngine::initCEGUI(){
  // Set up GUI system
  LOGI("Initializing CEGUI");

  // true for rendering CEGUI last, with false, CEGUI windows are not
  // over OGRE overlays (they are hidden)
  mGUIRenderer = new CEGUI::OgreCEGUIRenderer(mWindow, 
					      Ogre::RENDER_QUEUE_OVERLAY, 
					      true, 3000, mSceneMgr);

  mGUISystem = new CEGUI::System(mGUIRenderer, NULL, NULL, 
				 NULL, "", (CEGUI::utf8*)"cegui.log");

  CEGUI::SchemeManager::getSingleton().
    loadScheme((CEGUI::utf8*)"TaharezLook.scheme");
  CEGUI::SchemeManager::getSingleton().
    loadScheme((CEGUI::utf8*)"VanillaSkin.scheme");
  mGUISystem->setDefaultMouseCursor((CEGUI::utf8*)"TaharezLook", 
				    (CEGUI::utf8*)"MouseArrow");
  
  // load in a font.  The first font loaded automatically becomes 
  //the default font.
  CEGUI::FontManager::getSingleton()
    .createFont((CEGUI::utf8*)"fkp-16.font");
  CEGUI::FontManager::getSingleton()
    .createFont((CEGUI::utf8*)"iconified-20.font");

  CEGUI::MouseCursor::getSingleton().setImage("TaharezLook", 
					      "MouseMoveCursor");
     
}

/** Get the PagingLandScape2 scene manager
  *
  *
  */void RainbruRPG::Core::GameEngine::chooseSceneManager(){
  LOGI("chooseSceneManager");
  // Get the SceneManager, in this case a generic one
  mSceneMgr = Ogre::Root::getSingleton().
    createSceneManager("DefaultSceneManager" );

  // Set ambient light
  mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));
}

/** Create a generic Ogre camera
  *
  *
  */
void RainbruRPG::Core::GameEngine::createCamera(){
  LOGI("createCamera");

  // Create the camera
  mCamera = mSceneMgr->createCamera("PlayerCam");
  
  // Position it at 500 in Z direction
  //  mCamera->setPosition(Vector3(0,0,500));
  // Look back along -Z
  //  mCamera->lookAt(Vector3(0,0,-300));
  mCamera->setNearClipDistance(5);
}

/** Create a generic Ogre viewPort
  *
  *
  */
void RainbruRPG::Core::GameEngine::createViewports(){
  LOGI("createViewports");

  // Create one viewport, entire window
  if (mWindow){
    Viewport* vp = mWindow->addViewport(mCamera);
    vp->setBackgroundColour(ColourValue(0,0,0));
    
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
      Real(vp->getActualWidth()) / Real(vp->getActualHeight()));
  }
  else{
    LOGE("Invalid OgreWindow");
  }
}

/** Setup the needed ressources from a local file
  *
  * Using \ref RainbruRPG::Network::GlobalURI "GlobalURI", 
  * we get the \c config/resources.cfg file
  * in the share directory. Then, it goes through the sections 
  * of the ressource file and adds it
  * to the Ogre ResourceGroupManager.
  *
  */
void RainbruRPG::Core::GameEngine::setupResources(){
  LOGI("Setting up Resources");

  // Get the filename according to the installation prefix
  Network::GlobalURI gu;
  std::string resCfg=gu.getShareFile("config/resources.cfg");

  // Load resource paths from config file
  ConfigFile cf;
  cf.load(resCfg);
  
  // Go through all sections & settings in the file
  ConfigFile::SectionIterator seci = cf.getSectionIterator();
  
  String secName, typeName, archName, shareArchName;

  while (seci.hasMoreElements()){
    secName = seci.peekNextKey();
    ConfigFile::SettingsMultiMap *settings = seci.getNext();
    ConfigFile::SettingsMultiMap::iterator i;
    for (i = settings->begin(); i != settings->end(); ++i){
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

      ResourceGroupManager::getSingleton().
	addResourceLocation( shareArchName, typeName, secName);
    }
  }

  LOGI("All resources correctly setup");

}

/** Converts a mouse button event from Ogre to Cegui
  *
  * \param buttonID The Ogre button identifier
  *
  * \return The mouse button given as parameter in the CEGUI format
  */
CEGUI::MouseButton RainbruRPG::Core::GameEngine::
convertOgreButtonToCegui(int buttonID){
   switch (buttonID)   {
   case MouseEvent::BUTTON0_MASK:
       return CEGUI::LeftButton;
   case MouseEvent::BUTTON1_MASK:
       return CEGUI::RightButton;
   case MouseEvent::BUTTON2_MASK:
       return CEGUI::MiddleButton;
   case MouseEvent::BUTTON3_MASK:
       return CEGUI::X1Button;
   default:
       return CEGUI::LeftButton;
   }
}

/** Get the CEGUI System object
  *
  * \return The CEGUI System Object
  *
  */
CEGUI::System* RainbruRPG::Core::GameEngine::getCEGUISystem(){
  return mGUISystem;
}

/** Get the Ogre Root object
  *
  * \return The Ogre root object
  *
  */
Root* RainbruRPG::Core::GameEngine::getOgreRoot(){
  return this->mRoot;
}

/** Get the Ogre scene manager
  * 
  * \return The Ogre scene manager
  *
  */
SceneManager* RainbruRPG::Core::GameEngine::getOgreSceneMgr(){
  return this->mSceneMgr;
}

/** The frame ended event handler
  *
  * It simply calls the frameEnded function of the actual GameState
  *
  * \param evt The Ogre frame event
  *
  */ 
void RainbruRPG::Core::GameEngine::frameEnded(const FrameEvent& evt){
  states[actualState]->frameEnded(evt);
}

/** Logging the list of available Ogre scene manager
  *
  */
void RainbruRPG::Core::GameEngine::logSceneMgrList(){
  LOGI("Logging available scene manager");

  SceneManagerEnumerator::MetaDataIterator it = Ogre::Root::getSingleton()
    .getSceneManagerMetaDataIterator();


  while (it.hasMoreElements ()){
    const SceneManagerMetaData* metaData = it.getNext ();

    LOGCATS(metaData->typeName.c_str());
    LOGCAT();
  } 
}

/** Loads all ressources needed by Ogre
  *
  * It simply calls initialiseAllResourceGroups from the Ogre
  * ResourceGroupManager.
  *
 */
void RainbruRPG::Core::GameEngine::loadResources(void){
  LOGI("Loading all resources");

  // Get a vector of groups
  StringVector sv=ResourceGroupManager::getSingleton().getResourceGroups();
  unsigned int indx;
  for (indx = 0; indx < sv.size(); indx++){
    loadResourcesGroup(sv[indx]);
  }

  // Initialise, parse scripts etc
  //  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  LOGI("All resources loaded");
}

/** Load a named resource group
  *
  * \param groupName The name of the resource group to load
  *
  */
void RainbruRPG::Core::GameEngine::
loadResourcesGroup(const Ogre::String& groupName){
    LOGCATS("Loading resource group : ");
    LOGCATS(groupName.c_str());
    LOGCAT();

    Ogre::ResourceGroupManager::ResourceDeclarationList::iterator iter;

    Ogre::ResourceGroupManager::ResourceDeclarationList rdl=
      ResourceGroupManager::getSingleton()
      .getResourceDeclarationList(groupName);


    for (iter=rdl.begin(); iter != rdl.end(); iter++){
      LOGCATS("Loading ressource ");
      LOGCATS((*iter).resourceName.c_str());
      LOGCAT();
    }

    ResourceGroupManager::getSingleton().initialiseResourceGroup(groupName);
}

/**
  * It asks :
  * - The fadeOut of the CEGUI layout to the GuiManager
  * - destroy the current CEGUILayout
  */
void RainbruRPG::Core::GameEngine::
fromMenuToGame(GameState* from, GameState* to){
  LOGI("Switching from menuType to gameType");
  GuiManager::getSingleton().beginGuiFadeOut();

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }

  GuiManager::getSingleton().removeCurrentCEGUILayout();

  LOGI("Clearing Scene");
  mSceneMgr->clearScene();
  mWindow->removeAllViewports();
  mSceneMgr->destroyAllCameras();


  LOGI("Setting new scene manager");
  mSceneMgr = Ogre::Root::getSingleton().
    createSceneManager("PagingLandScapeSceneManager"); 

  //  mSceneMgr->setShadowTechnique(SHADOWTYPE_NONE);

  //  addMesh("Tree", "MyPineTree.mesh");

  createCamera();

  //mettre a jour la camera de mFrameListener
  GuiFrameListener* gfl=(GuiFrameListener*)mFrameListener;
  gfl->setCamera(mCamera);

  //BaseCameraViewpoint.x=-4098.0f
  //BaseCameraViewpoint.y=30644.0f
  //BaseCameraViewpoint.z=293.0f


      mCamera->setPosition(Vector3(800,200,1200));
  //     mCamera->setPosition(Vector3(-4098,30644,293));
  mCamera->lookAt(Vector3(0,0,0));

  createViewports();

  GuiManager::getSingleton().destroyTitleOverlay();

  ColourValue fadeColour( 0.9, 0.9, 0.9 );
  //mSceneMgr->setFog( FOG_LINEAR, fadeColour, 0.0, 350, 515 );
  //mWindow->getViewport(0)->setBackgroundColour( fadeColour );
  mSceneMgr->setFog( FOG_EXP, fadeColour, 0.0002 );
  mSceneMgr->setWorldGeometry( "paginglandscape2.cfg" );
  //  addMesh("Cube", "Cube.mesh");
  mSceneMgr->setSkyDome( true, "Examples/CloudySky", 5, 8 );

  // Loads object list
  xmlObjectList xol;

  LOGI("LocalTest environment successfully initialized");
}

/** The keypressed OIS callback
  *
  * \param evt The OIS event
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::GameEngine::keyPressed(const OIS::KeyEvent& evt){
  // ESC is quit
  OIS::KeyCode kc=evt.key;
  if (kc==OIS::KC_ESCAPE)
    this->quit();

  states[actualState]->keyPressed(evt);

  return true;
}

/** The keyReleased OIS callback implementation
  *
  * \param evt The OIS event
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::GameEngine::keyReleased(const OIS::KeyEvent& evt){
  states[actualState]->keyReleased(evt);
  return true;

}

/** The mouseMoved OIS callback implementation
  *
  * \param evt The OIS event
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::GameEngine::mouseMoved(const OIS::MouseEvent& evt){
  states[actualState]->mouseMoved(evt);
  return true;
}

/** The mousePressed OIS callback implementation
  *
  * \param evt The OIS event
  * \param id The OIS mouse button
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::GameEngine::
mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
  states[actualState]->mousePressed(evt, id);
  return true;

}

/** The mouseReleased OIS callback implementation
  *
  * \param evt The OIS event
  * \param id The OIS mouse button
  *
  * \return An OIS value
  *
  */
bool RainbruRPG::Core::GameEngine::
mouseReleased(const OIS::MouseEvent& evt, OIS::MouseButtonID id){
  states[actualState]->mouseReleased(evt, id);
  return true;

}

/** Initialize OIS
  *
  * caution : The Ogre RenderWindow must exist.
  *
  */
void RainbruRPG::Core::GameEngine::initOIS(){
  mInputMgr=InputManager::getSingletonPtr();
  mInputMgr->initialise(mWindow);
  mInputMgr->addKeyListener(this, "GameEngine");
  mInputMgr->addMouseListener(this, "GameEngine");

}

/** The frame started event handler
  *
  * It simply calls the frameStarted function of the actual GameState
  *
  * \param evt The Ogre frame event
  *
  */ 
void RainbruRPG::Core::GameEngine::frameStarted(const FrameEvent& evt){
  if (mInputMgr)
    mInputMgr->capture();

  states[actualState]->frameStarted(evt);
}

/** Gets the current camera
  *
  * \return The Ogre camera object
  *
  */
Camera* RainbruRPG::Core::GameEngine::getCamera(){
  return mCamera;
}

/** Get the OIS input manager
  *
  * Use this if you need a direct access to the currently used
  * InputManager instance. Even if InputManager is a singleton,
  * this function can be usefull.
  *
  * \sa mInputMgr, InputManager
  *
  */
InputManager* RainbruRPG::Core::GameEngine::getInputManager(){
  return mInputMgr;
}

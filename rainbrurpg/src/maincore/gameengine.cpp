/*
 *  Copyright 2006-2010 Jerome PASQUIER
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

/** \file gameengine.cpp
  * Implements the client game engine
  *
  */

#ifdef __WIN32__
#  include <windows.h>
#endif // __WIN32__

#include <assert.h>

#include "gamestate.h"

#include "gslocaltest.h"

#include "xmlobjectlist.h"
#include "globaluri.h"
#include "inputmanager.h"

#include "gameengine.h"

#include <logger.h>
#include <Brush.hpp>

#include <OgreGuiRenderQueueListener.hpp>

//using namespace RainbruRPG::Events; // Removed to avoid OgreGui deps

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
void RainbruRPG::Core::GameEngine::init(const GameEngineOptions& vOptions){
  userName="";
  userPwd="";
  mInputMgr=NULL;
  mSceneMgr=NULL;
  mViewport=NULL;
  mCamera=NULL;
  actualState=-1;
  mOptions = vOptions;

  initOgre();
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
  LOGI(_("Exiting GameEngine ..."));
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

    try {
      LOGI(_("starting rendering"));
      Ogre::Root::getSingleton().startRendering();
    } 
    catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32 
     MessageBox( NULL, e.getFullDescription().c_str(), 
		 _("An exception has occured!"), 
		 MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
     std::string err= _("An exception has occured: ");
     err+= e.getFullDescription().c_str();
     LOGE(err.c_str());
#endif
    }
  }

  LOGI(_("GameEngine::run ended"));
}

/** Set the current GameState to \c t
  *
  * \param vName The name of the GameState to switch to
  *
  */
void RainbruRPG::Core::GameEngine::changeState(const std::string& vName){
  if (m_running){
    size_t t = this->getGameStateIndexByName(vName);

    GTS_MID(msg); // A char* used to create parametered messages

    if (t == std::string::npos){
      // TRANSLATORS: The parameter is the name of a game state.
      sprintf(msg, _("Cannot find %s state"), vName.c_str());
      LOGE(msg);
    }
    else{
      // TRANSLATORS: The parameter is the name of a game state.
      sprintf(msg, _("Switching to %s state"), vName.c_str());
      LOGI(msg);
    }

    if ((unsigned int)t>states.size()){
      LOGE(_("An error will occur : we are calling a non-inexisting "
	     "gamestate"));
    }
    else{
      /* Avoid a SEGFAULT when setting the first game state */
      tGameStateType oldType;
      if (actualState != -1){
	oldType=states[actualState]->getStateType();
      }
      else{
	oldType = GST_UDEF;
      }
      tGameStateType newType=states[t]->getStateType();

      if (oldType==GST_UDEF && newType==GST_UDEF){
	LOGE(_("Both game states type are Undefined"));
      }

      if (oldType!=newType){
	if (oldType==GST_MENU){
	  if (newType==GST_GAME){
	    this->fromMenuToGame(states[actualState], states[t]);
	  }
	}
      }

       // Pause the actual state
      if (actualState != -1){
	states[actualState]->pause();
      }

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



/** The Destructor of the GameEngine
  *
  *
  */
void RainbruRPG::Core::GameEngine::cleanup(){
  LOGI(_("Cleaning up GameEngine..."));
  m_running=false;
  delete mInputMgr;

  /* Removed to avoid OgreGui dependencies
    mSceneMgr->removeRenderQueueListener(mRenderQueueListener);
  delete mRenderQueueListener;
  mRenderQueueListener=NULL;
  SkinManager::getSingleton().cleanup();
  */

/*
  this->cleanStates();
  this->cleanIrrgui();

  delete erc;
  erc=NULL;

*/

  delete mBrush;

  LOGI(_("GameEngine cleaned"));
}

/** delete all states and receivers in vectors
  *
  */
void RainbruRPG::Core::GameEngine::cleanStates(){
  LOGI(_("  Cleaning up GameStates..."));
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
  LOGI(_("Trying to connect a user"));

  ClientConnect cc(user, pwd);

  tClientConnectReturn ret=cc.getResponse();

  const char* errMsg;

  switch(ret){
  case CCR_INEXISTANT_USER: 
    errMsg=_("This user does not exist.\nPlease create an account");
    break;
  case CCR_WRONG_PWD:
    errMsg=_("Wrong password.");
    break;
  case CCR_EMAIL_NOT_VALIDATED:
    errMsg=_("Your email was not yet validated.");
     break;
  case CCR_BLACKLIST:
    errMsg=_("You are in blacklist.");
    break;
  case CCR_UNKNOWN_ERROR:
    errMsg=_("An unknown error occured.");
    break;
  case CCR_SUCCESS:
    errMsg="";
    break;
  }

  if (ret!=CCR_SUCCESS){
    LOGW(_("The login of this user failed"));
    /* Removed to avoid OgreGui dependencies
    GuiManager::getSingleton()
      .showMessageBox("Connection failed", errMsg);
    */
    return false;

  }
  else{
    LOGI(_("The login is successfull"));
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
  GTS_LIT(str);
  // TRANSLATORS: The parameter is a graphic renderer name.
  sprintf(str, _("Setting renderer '%s'"), rName);
  LOGI(str);

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
  this->mRoot = &Ogre::Root::getSingleton();

  // It seems to avoid the 'GLX_icon.png not found' Exception
  // as the setupResources() and loadResources() functions are
  // called later
  GlobalURI gu;
  std::string dataPath=GET_SHARE_FILE(gu, "data");
  Ogre::Root::getSingleton().addResourceLocation(dataPath, "FileSystem");


#ifdef RAINBRU_RPG_DEBUG
  int winWidth=640;
  int winHeight=480;
#else
  int winWidth=1024;
  int winHeight=768;
#endif // RAINBRU_RPG_DEBUG

  mWindow=Ogre::Root::getSingleton().getRenderSystem()
    ->createRenderWindow(CLIENT_WIN_CAPTION, winWidth, winHeight, mOptions.fullscreen);
  
  initOIS();

  if (!mWindow){
    LOGE(_("The Ogre::Root cannot be initalized"));
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

  // Create the Brush object
  mBrush = new Brush(mRoot->getRenderSystem(), mSceneMgr, 
		     mViewport, "GameEngine");
}

/** Get the PagingLandScape2 scene manager
  *
  *
  */
void RainbruRPG::Core::GameEngine::chooseSceneManager(){
  // Get the SceneManager, in this case a generic one
  mSceneMgr = Ogre::Root::getSingleton().
    createSceneManager("DefaultSceneManager", "DefaultSceneManager_Instance" );

  // Set ambient light
  mSceneMgr->setAmbientLight(ColourValue(0.5, 0.5, 0.5));


  mRenderQueueListener = new OgreGuiRenderQueueListener();
  mSceneMgr->addRenderQueueListener(mRenderQueueListener);
}

/** Create a generic Ogre camera
  *
  *
  */
void RainbruRPG::Core::GameEngine::createCamera(){
  // Create the camera

  if (mSceneMgr != NULL){
    mCamera = mSceneMgr->createCamera("PlayerCam");
  }
  else{
    LOGE(_("mSceneMgr is NULL"));
  }
  
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
  // Create one viewport, entire window
  if (mWindow){
    mViewport = mWindow->addViewport(mCamera);
    mViewport->setBackgroundColour(ColourValue(1.0f, 1.0f, 1.0f));
    
    // Alter the camera aspect ratio to match the viewport
    mCamera->setAspectRatio(
      Real(mViewport->getActualWidth()) / Real(mViewport->getActualHeight()));
    assert(mViewport && "Failed to create the Ogre viewport");
  }
  else{
    LOGE(_("Invalid OgreWindow"));
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
  // Get the filename according to the installation prefix
  Network::GlobalURI gu;
  std::string resCfg=GET_SHARE_FILE(gu,"config/resources.cfg");

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
      shareArchName= GET_SHARE_FILE(gu, archName);

      // Logging
      GTS_HUG(str);
      // TRANSLATORS: The parameters are ressource settings.
      sprintf(str, _("Loading ressource : secName='%s' typeName='%s' "
		     "archName='%s'"), 
	      secName.c_str(), typeName.c_str(), shareArchName.c_str());
      LOGI(str);

      ResourceGroupManager::getSingleton().
	addResourceLocation( shareArchName, typeName, secName);
    }
  }

  LOGI(_("All resources correctly setup"));

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
  LOGI(_("Logging available scene manager"));

  SceneManagerEnumerator::MetaDataIterator it = Ogre::Root::getSingleton()
    .getSceneManagerMetaDataIterator();

  GTS_MID(str);
  while (it.hasMoreElements ()){
    const SceneManagerMetaData* metaData = it.getNext ();
    // TRANSLATORS: The parameter is a scene manager name.
    sprintf(str, _("Scene manager '%s' found."), metaData->typeName.c_str());
    LOGI(str);
  } 
}

/** Loads all ressources needed by Ogre
  *
  * It simply calls initialiseAllResourceGroups from the Ogre
  * ResourceGroupManager.
  *
 */
void RainbruRPG::Core::GameEngine::loadResources(void){
  LOGI(_("Loading all resources"));

  // Get a vector of groups
  StringVector sv=ResourceGroupManager::getSingleton().getResourceGroups();
  unsigned int indx;
  for (indx = 0; indx < sv.size(); indx++){
    loadResourcesGroup(sv[indx]);
  }

  // Initialise, parse scripts etc
  //  ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
  LOGI(_("All resources loaded"));
}

/** Load a named resource group
  *
  * \param groupName The name of the resource group to load
  *
  */
void RainbruRPG::Core::GameEngine::
loadResourcesGroup(const Ogre::String& groupName){

  GTS_LIT(str);
  // TRANSLATORS: The parameter is a ressource group name
  sprintf(str, _("Loading resource group '%s'"), groupName.c_str());
  LOGI(str);

    Ogre::ResourceGroupManager::ResourceDeclarationList::iterator iter;

    Ogre::ResourceGroupManager::ResourceDeclarationList rdl=
      ResourceGroupManager::getSingleton()
      .getResourceDeclarationList(groupName);


    for (iter=rdl.begin(); iter != rdl.end(); iter++){
      // TRANSLATORS: The parameter is a ressource name
      sprintf(str, _("Loading ressource '%s'"), (*iter).resourceName.c_str());
      LOGI(str);
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
  LOGI(_("Switching from menuType to gameType"));
  /* Removed to avoid OgreGui dependencies
  GuiManager::getSingleton().beginGuiFadeOut();
  */

  // We must wait for the CEGUI fade end to prevent
  // SEGFAULT in access to CEGUI windows (getAlpha())
  /* Removed to avoid OgreGui dependencies
  while (GuiManager::getSingleton().isInGuiFadeOut()){
    Ogre::Root::getSingleton().renderOneFrame();
  }
  */
  LOGI(_("Clearing Scene"));
  mSceneMgr->clearScene();
  mWindow->removeAllViewports();
  mSceneMgr->destroyAllCameras();


  LOGI(_("Setting new scene manager"));
  mSceneMgr = Ogre::Root::getSingleton().
    createSceneManager("PagingLandScapeSceneManager"); 

  //  mSceneMgr->setShadowTechnique(SHADOWTYPE_NONE);

  //  addMesh("Tree", "MyPineTree.mesh");

  createCamera();

  // Updates the mFrameListener's camera
  /* Removed to avoid OgreGui dependencies
  GuiFrameListener* gfl=(GuiFrameListener*)mFrameListener;
  gfl->setCamera(mCamera);
  */
  //BaseCameraViewpoint.x=-4098.0f
  //BaseCameraViewpoint.y=30644.0f
  //BaseCameraViewpoint.z=293.0f


      mCamera->setPosition(Vector3(800,200,1200));
  //     mCamera->setPosition(Vector3(-4098,30644,293));
  mCamera->lookAt(Vector3(0,0,0));

  createViewports();

  /* Removed to avoid OgreGui dependencies
  GuiManager::getSingleton().destroyTitleOverlay();
  */
  ColourValue fadeColour( 0.9, 0.9, 0.9 );
  //mSceneMgr->setFog( FOG_LINEAR, fadeColour, 0.0, 350, 515 );
  //mWindow->getViewport(0)->setBackgroundColour( fadeColour );
  mSceneMgr->setFog( FOG_EXP, fadeColour, 0.0002 );
  mSceneMgr->setWorldGeometry( "paginglandscape2.cfg" );
  //  addMesh("Cube", "Cube.mesh");
  mSceneMgr->setSkyDome( true, "Examples/CloudySky", 5, 8 );

  // Loads object list
  xmlObjectList xol;

  LOGI(_("LocalTest environment successfully initialized"));
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

  /* v 0.0.5-160 : Mouse button bug fix
   *
   * It appears that this function is automatically called 
   * by InputManager/OIS each time we change from one 
   * GameSate to another. As the Gui fade in comes after
   * this bug, we use to test if the mouse pressed event
   * should be handled.
   *
   */
  /* Removed to avoid OgreGui dependencies
  if (!GuiManager::getSingleton().isInGuiFadeIn()){
  */
    states[actualState]->mousePressed(evt, id);
    /*
  }
  */
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
  mInputMgr=RainbruRPG::Core::InputManager::getSingletonPtr();
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
RainbruRPG::Core::InputManager* 
RainbruRPG::Core::GameEngine::getInputManager(){
  return mInputMgr;
}

/** Adds the given game state to the map
  *
  * \param gs The game state to be added
  *
  */
void RainbruRPG::Core::GameEngine::registerGameState(GameState* gs){
  LOGA( gs , "Adding a NULL GameState");
  states.push_back(gs);
}

/** Get the index of a named GameState
  *
  * \param vName The name of the searched game state
  *
  * \return The index of the gamestate in the \ref states vactor if found,
  *         otherwise, returns the \c std::string::npos value.
  *
  */
size_t RainbruRPG::Core::GameEngine::
getGameStateIndexByName(const std::string& vName){
  int i;

  for (i=0; i< states.size(); i++){
    if (states[i]->getName().compare(vName) == 0){
      return i;
    }
  }
  return std::string::npos;
}

/** Get the current Ogre viewport
  *
  */
Viewport* RainbruRPG::Core::GameEngine::getViewport(void) const
{
  return mViewport;
}

/** Calls draw() on the actual game state
  *
  * This function is called by \ref "OgreGui::OgreGuiRenderQueueListener::renderQueueEnded" 
  * "RenderQueueListener::renderQueueEnded".
  *
  */
void RainbruRPG::Core::GameEngine::draw()
{
  LOGI("GameEngine::draw called");
  // Should set GuiTransparency
  states[actualState]->draw(mBrush);
}

/** Changes the transparency of the GUI drawing
  *
  * \param vGuiTransparency The new alpha value
  *
  */
void RainbruRPG::Core::GameEngine::setGuiTransparency(float vGuiTransparency)
{
  mGuiTransparency = vGuiTransparency;
}

/** Get the transparency of the GUI drawing
  *
  * \return The alpha value
  *
  */
float RainbruRPG::Core::GameEngine::getGuiTransparency(void) const
{
  return mGuiTransparency;
}

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

#include "gameengine.h"

#include <iostream>

#include "logger.h"
#include "console.h"
#include "gamestate.h"
#include "gsgame.h"
#include "gsgameesc.h"
#include "gsconnection.h"
#include "gscreateaccount.h"
#include "gschangepassword.h"
#include "gsselectperso.h"
#include "gscreateperso.h"

#include "irrfontmanager.h"

/** A function used to know if the GameEngine is running.
  * 
  * \return the value of the m_running variable
  */
bool RainbruRPG::Core::GameEngine::running() {
  return m_running;
};

/** Get the Irrlicht device 
  *
  * \return the Irrlicht Device
  */
irr::IrrlichtDevice* RainbruRPG::Core::GameEngine::getIrrlichtDevice(){
  return this->irrDevice;
}

/** Get the Irrlicht driver type
  *
  * It can return a value of the irr::video::E_DRIVER_TYPE enumeration
  *
  * \return the Irrlicht driver type
  */
irr::video::E_DRIVER_TYPE RainbruRPG::Core::GameEngine::getDriverType(){
  return this->driverType;
}

/** Get the Irrlicht driver 
  *
  * \return the Irrlicht video driver
  */
irr::video::IVideoDriver* RainbruRPG::Core::GameEngine::getIrrlichtDriver(){
  return this->irrDriver;
}

/** Get the Irrlicht SceneManager 
  *
  * \return the Irrlicht SceneManager
  */
irr::scene::ISceneManager* RainbruRPG::Core::GameEngine::getIrrlichtSmgr(){
  return this->irrSmgr;
}

/** Initialize the GameEngine instance
  *
  * This method must be called once. It loads the options with a
  * XmlOptions class instance.
  *
  * It only initialize Irrlicht engine. Each GameState initialize its
  * own parameters.
  */
void RainbruRPG::Core::GameEngine::init(){

  userName="";
  userPwd="";

  if(m_running){
    LOGI("Initializing the GameEngine...");

    switch (this->driverType){
    case EDT_SOFTWARE:
      LOGI("Using SOFTWARE graphic driver");
      break;
      
    case EDT_SOFTWARE2:
      LOGI("Using SOFTWARE2 graphic driver");
      break;
      
    case EDT_DIRECT3D8:
      LOGI("Using DIRECT3D8 graphic driver");
      break;
      
    case EDT_OPENGL:
      LOGI("Using OPENGL graphic driver");
      break;

    case EDT_DIRECT3D9:
      LOGI("Using DIRECT3D9 graphic driver");
      break;
      
    case EDT_NULL:
      LOGW("GameEngine init with a EDT_NULL graphic driver");
      break;
      
    default:
      LOGE("GameEngine can't found the graphic driver type");
    }

    this->initIrrlicht();
    this->initIrrgui();
    this->initStates();

    RainbruRPG::Gui::GuiManager::getSingleton().init();
    RainbruRPG::Gui::GuiManager::getSingleton().createNumDebugWindow();

    RainbruRPG::Exception::Console::getSingleton().init();
    setGuiTransparency(190);
    //    RainbruRPG::Gui::GuiManager::getSingleton().createConsole();
  }
}

/** Set the graphic driver to use
  *
  * This method is called when clicking the Launcher Play button.
  * 
  * \param d the irr::video::E_DRIVER_TYPE enum value correspong o the
  *        selected graphic driver
  */
void RainbruRPG::Core::GameEngine::setDriverType( irr::video::E_DRIVER_TYPE d){
  this->driverType=d;
}

/** Initialization of Irrlicht 
  *
  */
void RainbruRPG::Core::GameEngine::initIrrlicht(){
  LOGI("Initialization of Irrlicht...");

  LOGI("  Creating Irrlicht device");

  // create device
  irrDevice = createDevice(this->driverType, 
			   core::dimension2d<s32>(640, 480));//, 16, false);
		
  if (irrDevice == 0)
    LOGE("Error occured while creating Irrlicht device");  


  LOGI("  Gets the Irrlicht Video driver");
  irrDriver = irrDevice->getVideoDriver();

  if (irrDriver==0)
    LOGE("Error occured while creating Irrlicht driver");  

  LOGI("  Gets the Irrlicht Scene Manager");
  irrSmgr = irrDevice->getSceneManager();

  if (irrSmgr==0)
    LOGE("Error occured while creating Irrlicht Scene manager");  
}


/** Set m_running to \c true telling GameEngine it can run
  *
  */
void RainbruRPG::Core::GameEngine::play() {
  m_running = true; 
}

/** Set m_running to false so the run method do nothing
  *
  * It can be called even before the init or run methods
  */
void RainbruRPG::Core::GameEngine::quit() {
 LOGI("Quitting GameEngine ...");
  m_running = false; 
}

/** A wrapper to the current GameState::run()
  *
  * I use actualState and states to call the run method
  */
void RainbruRPG::Core::GameEngine::run() {
  if (m_running)
    states[actualState]->run();
}

/** Initialize all the states and their events receivers
  *
  *
  */
void RainbruRPG::Core::GameEngine::initStates() {
  LOGI("Initializing Game states...");
    // INIT GAME STATES
    gsGame           *g =new gsGame();
    gsGameEsc        *g2=new gsGameEsc();
    gsConnection     *g3=new gsConnection();
    gsCreateAccount  *g4=new gsCreateAccount();
    gsChangePassword *g5=new gsChangePassword();
    gsSelectPerso    *g6=new gsSelectPerso();
    gsCreatePerso    *g7=new gsCreatePerso();

    states.push_back( g );
    states.push_back( g2 );
    states.push_back( g3 );
    states.push_back( g4 );
    states.push_back( g5 );
    states.push_back( g6 );
    states.push_back( g7 );


  LOGI("Initializing events receiver...");

    // INIT EVENT RECEIVER
    erGame           *e=new erGame();
    erGameEsc        *e2=new erGameEsc();
    erConnection     *e3=new erConnection();
    erCreateAccount  *e4=new erCreateAccount();
    erChangePassword *e5=new erChangePassword();
    erSelectPerso    *e6=new erSelectPerso();
    erCreatePerso    *e7=new erCreatePerso();

    receivers.push_back( e );
    receivers.push_back( e2 );
    receivers.push_back( e3 );
    receivers.push_back( e4 );
    receivers.push_back( e5 );
    receivers.push_back( e6 );
    receivers.push_back( e7 );

    erc= new erConsole();
}

/** Set the current GameState to \c t
  *
  * \param t The GameState type to switch to
  */
void RainbruRPG::Core::GameEngine::changeState(tStateType t){
  if (m_running){

    switch (t){
    case ST_GAME:
      LOGI("Switching to state Game...");
      break;

    case ST_GAME_ESC:
      LOGI("Switching to state Game Esc Menu...");
      break;

    case ST_CONNECT:
      LOGI("Switching to state Connection...");
      break;

    case ST_PERSO_LIST:
      LOGI("Switching to character selection state...");
      break;

    case ST_PERSO_CREATE:
      LOGI("Switching to character creation state...");
      break;


    default:
      LOGW("Unknown game state received");
    }

    if (t>states.size())
      LOGE("An error will occured : we are calling a non-inexisting "
	   "gamestate");

    if (states[actualState]->wasInit())
      states[actualState]->pause();

    actualState=t;

    if (!states[actualState]->wasInit())
      states[actualState]->init();

    states[actualState]->resume();

    irrDevice->setEventReceiver(receivers[actualState]);
    //    states[actualState]->run();
  }
}

/** Get the Irrlicht GUI environment
  *
  * The Irrlicht GUI environment must be accessible to add some widgets.
  *
  * \return The Irrlicht GUI environment
  */
irr::gui::IGUIEnvironment* RainbruRPG::Core::GameEngine::getIrrlichtGui(){
  return this->guiEnv;
}

/** Initialization of the Irrlicht build-in Gui system
  *
  */
void RainbruRPG::Core::GameEngine::initIrrgui(){
  guiEnv = irrDevice->getGUIEnvironment();

  IGUISkin* skin = guiEnv->getSkin();
  IGUIFont* font = guiEnv->getFont("../data/fonts/fonthaettenschweiler.bmp");
  if (font)
    skin->setFont(font);
  

  //  IrrFontManager::getSingleton().setGlobalFont( IFM_COURRIER, 10);
}

/** The Destrictor of the GameEngine destructor
  *
  *
  */
void RainbruRPG::Core::GameEngine::cleanup(){
  LOGI("Cleaning up GameEngine...");
  m_running=false;

  this->cleanStates();
  this->cleanIrrgui();

  delete erc;
  erc=NULL;
  /*  this->cleanIrrlicht();

  irrDevice=NULL;
  //  driverType=NULL;
  irrDriver=NULL;
  irrSmgr=NULL;
  guiEnv=NULL;*/
}

/// delete all states and receivers in vectors
void RainbruRPG::Core::GameEngine::cleanStates(){
  LOGI("  Cleaning up GameStates...");
  // delete all states
  for (int indx = 0; indx < states.size(); indx++){
    states[indx]->cleanup();
    delete states[indx];
  } 

  // delete all receivers
  for (int indx = 0; indx < receivers.size(); indx++){
    delete receivers[indx];
  } 

  actualState=-1;
  states.clear();
  receivers.clear();
}

/** Do nothing */
void RainbruRPG::Core::GameEngine::cleanIrrgui(){
  LOGI("  Cleaning up Irrlicht build-in GUI...");
}

/** Correctly close the Irrlicht engine */
void RainbruRPG::Core::GameEngine::cleanIrrlicht(){
  LOGI("  Cleaning up Irrlicht...");

  if (m_running)
    LOGW("Closing IrrlichtDevice while GameEngine running");

  if (irrDevice){
    //   irrDevice->closeDevice();
    //  irrDevice->drop();
  }
  else
    LOGW("Closing a NULL IrrlichtDevice");
}

/** Shows the debugging console */
void RainbruRPG::Core::GameEngine::showConsole(){
  lastState=actualState;
  Exception::Console::getSingleton().createConsole();


  irrDevice->setEventReceiver(erc);
}

/** Hides the debugging console 
  *
  */
void RainbruRPG::Core::GameEngine::hideConsole(){
  actualState=lastState;
  Exception::Console::getSingleton().hide();

  irrDevice->setEventReceiver(receivers[actualState]);
}

/** Test if the given User can be connected
  *
  * The values are entered by the user in the gsConnection gamestate.
  * There are send to a ClientConnect instance to test connection rights.
  *
  * \param user The userName
  * \param pwd The password hashsum of the given user
  *
  * \return \c true if the connection is accepted otherwise returns \c false.
  */
bool RainbruRPG::Core::GameEngine::connectUser(const wchar_t* user, 
					       const wchar_t* pwd ){
  LOGI("Trying to connect a user");

  std::wcout << pwd << endl;

  std::string sUser=StringConv::getSingleton().wtos(user);
  std::string sPwd=StringConv::getSingleton().wtos(pwd);
  ClientConnect cc(sUser.c_str(), sPwd.c_str());

  tClientConnectReturn ret=cc.getResponse();

  stringw errMsg;

  switch(ret){
  case CCR_INEXISTANT_USER: 
    errMsg=L"This user does not exist.\nPlease create an account";
    break;
  case CCR_WRONG_PWD:
    errMsg=L"Wrong password.";
    break;
  case CCR_EMAIL_NOT_VALIDATED:
    errMsg=L"Your email was not yet validated.";
     break;
  case CCR_BLACKLIST:
    errMsg=L"Your in blacklist.";
    break;
  case CCR_UNKNOWN_ERROR:
    errMsg=L"An unknown error occured.";
    break;
  }

  if (ret!=CCR_SUCCESS){
    guiEnv->addMessageBox (L"Connection failed", errMsg.c_str());
    return false;

  }
  else{
    userName=sUser.c_str();
    userPwd=sPwd.c_str();

    return true;
  }
}

/** Change the built-in Irrlivht GUI transparency
  *
  * Use getGuiTransparency(s32 pos) to get this value.
  *
  * \param pos A value beetween 0 and 255.
  */
void RainbruRPG::Core::GameEngine::setGuiTransparency(s32 pos){
  LOGI("Changing the GUI transparency");
  if (pos>0 & pos <255){
     if (guiEnv){
       for (s32 i=0; i<EGDC_COUNT ; ++i){
	 SColor col = guiEnv->getSkin()->getColor((EGUI_DEFAULT_COLOR)i);
	 col.setAlpha(pos);
	 guiEnv->getSkin()->setColor((EGUI_DEFAULT_COLOR)i, col);
       }
       this->guiTransparency=pos;
     }
     else{
       LOGW("Cannot set transparency, gui envirronment does not exist");
     }
  }
  else{
    LOGW("Cannot set transparency, argument out of range");
  }
}

/** Get the gui transparency value
  *
  * Use setGuiTransparency(s32 pos) to set this value.
  *
  * \return The gui transparency value.
  *
  */
s32 RainbruRPG::Core::GameEngine::getGuiTransparency(){
  return this->guiTransparency;
}

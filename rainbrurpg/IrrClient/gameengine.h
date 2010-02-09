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

#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <vector>
#include <string>
#include <singleton.h>
#include <irrlicht.h>
#include <stringconv.h>
#include <clientconnect.h>

#include "guimanager.h"

#include "xmloptions.h"

#include "gamestate.h"
#include "ergame.h"
#include "ergameesc.h"
#include "erconsole.h"
#include "erconnection.h"
#include "ercreateaccount.h"
#include "erchangepassword.h"
#include "erselectperso.h"
#include "ercreateperso.h"


// Forward declaration
// class GameState;
using namespace std;
using namespace irr;
using namespace video;
using namespace gui;
using namespace RainbruRPG::Events;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Core{

    /** The game states enumeration
      *
      * This enumeration is used when dealing with the GameEngine
      * state system. 
      */
    enum tStateType{
      ST_GAME           =0,  //!< The game state
      ST_GAME_ESC       =1,  //!< The ingame menu (Save, Load, Quit...)
      ST_CONNECT        =2,  //!< The connection game state
      ST_CREATE_ACCOUNT =3,  //!< The account creation gamestate
      ST_CHANGE_PWD     =4,  //!< The change password state
      ST_PERSO_LIST     =5,  //!< The character selection screen
      ST_PERSO_CREATE   =6,  //!< The character creation screen
      ST_INTRO          =7,  //!< Introduction of the game (a video...)
      ST_INTRO_MENU     =8   //!< The menu after the intro (Quit,Play...)
    };

    /** The game engine
      *
      * This singleton deals with some GameState and with options
      *
      * The options are stored in the \c data/saves/options.xml
      * file. They are read by an instance of the XmlOptions class,
      * created in the void init() method.
      *
      * To quit the application from the launcher, the quit button
      * callback calls GameEngine::quit() <em>before the call of
      * GameEngine::init() GameEngine::run()</em>. So the init and run
      * method do nothig.
      */
    class GameEngine : public Singleton<GameEngine>{
    public:
      GameEngine(){};

      void init();
      /// The singleton destructor
      void cleanup();
      void run();
      
      // Set state as actual gameState
      void changeState(tStateType);
      
      bool running();
      void play();
      void quit();  

      void setDriverType( irr::video::E_DRIVER_TYPE );

      void initIrrlicht();
      void initIrrgui();
      void initStates();

      void showConsole();
      void hideConsole();

      void cleanStates();
      void cleanIrrgui();
      void cleanIrrlicht();
      void setGuiTransparency(s32);
      s32 getGuiTransparency();

      bool connectUser(const wchar_t* , const wchar_t* );

      irr::IrrlichtDevice* getIrrlichtDevice();
      irr::video::E_DRIVER_TYPE getDriverType();
      irr::video::IVideoDriver* getIrrlichtDriver();
      irr::scene::ISceneManager* getIrrlichtSmgr();
      irr::gui::IGUIEnvironment* getIrrlichtGui();
    private:
      /** Unimplemented copy constructors 
        *
	* In a singleton the use of this methos must be forbidden.
	* 
	* \param obj A GameEngine
	*/
      GameEngine(const GameEngine& obj);

      /** Unimplemented assignment
        *
	* In a singleton the use of this method must be forbidden.
	* \param obj A GameEngine
	*/
      GameEngine& operator=(const GameEngine& obj);

      /** The stack of states
        *
	* All the GameStates the GameEngine can use are in this STL
	* vector. We know wich state we use with the actualState integer.
	*/
      vector<GameState*> states;

      /** The stack of Irrlicht event receiver
        *
	* All the GameStates the GameEngine can use have their own
	* event receiver. They are stored in this STL
	* vector. We know wich state we use with the actualState
	* integer, so we know wich receiver to use.
	*/
      vector<IEventReceiver*> receivers;

      /** The currenttly used Irrlicht event receiver */
      IEventReceiver* erc;

      /** The index of the in-use State
        *
	* We know wich state we use in the states vector with this integer.
	*/
      int actualState;

      /** The index of the last-use State
        *
	* We must know it if we show the console..
	*/
      int lastState;

      /** Tells the GameEngine if it runs
        *
	* The play() and quit() methods assign \c true and \c false to
	* this boolean.
	*/
      bool m_running;

      /** The userName the user entered */
      const char* userName;
      /** The passord hashsum */
      const char* userPwd;

      /// The Irrlicht Device
      irr::IrrlichtDevice *irrDevice;

      /// The Irrlicht driver type
      irr::video::E_DRIVER_TYPE driverType;

      /// The Irrlicht video driver
      irr::video::IVideoDriver* irrDriver;

      /// The Irrlicht scene manager
      irr::scene::ISceneManager* irrSmgr;

      /// The Irrlicht build-in Gui environment
      irr::gui::IGUIEnvironment* guiEnv;

      /** The last set gui transparency value.
        *
	* This value is set to 190 by default in the GameEngine::init()
	* method.
	*/
      s32 guiTransparency;
    };
  }
}
#endif // GAME_ENGINE

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

/* Modifications :
 * - 21 sep 2007 : Uses OgreGUI
 *
 */

#ifndef GAME_ENGINE
#define GAME_ENGINE

#include <vector>
#include <string>
#include <singleton.h>
#include <stringconv.h>
#include <clientconnect.h>

#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

// OGRE headers
#include <Ogre.h>
#include <OgreRoot.h>
#include <OgreSceneManagerEnumerator.h>

// OgreGUI headers
#include "bggui.h"

// Forward declaration
namespace RainbruRPG {
  namespace Core{
    class GameState;
    class InputManager;
  }
  namespace Network{
    class GlobalURI;
  }
  namespace OgreGui{
    class OgreGuiRenderQueueListener;
  }
}
// End of forward declaration

using namespace std;
using namespace Ogre;

//using namespace RainbruRPG::Events;
using namespace RainbruRPG::OgreGui;
using namespace RainbruRPG::Network;
using namespace RainbruRPG::Network::Ident;

namespace RainbruRPG {
  namespace Core{

    /** The game states enumeration
      *
      * This enumeration is used when dealing with the GameEngine
      * state system. 
      */
    enum tStateType{
      ST_LOCAL_TEST          =0x0000,  //!< The local test state
      ST_MENU_CONNECT        =0x0001,  //!< The connection menu
      ST_MAIN_MENU           =0x0002,  //!< The main menu state
      ST_CREATE_ACCOUNT      =0x0003,  //!< The create account state
      ST_SERVER_LIST         =0x0004,  //!< The server list menu state
    };

    /** The game engine
      *
      * This singleton deals with some GameState and with options
      *
      * The options are stored in the \c data/saves/options.xml
      * file. They are read by an instance of the XmlOptions class,
      * created in the void init() method.
      *
      * To run game, make sure you have called GameEngine::play() 
      * before calling GameEngine::run().
      *
      * To quit the application from the launcher, the quit button
      * callback does not call play(). m_running is not set to true
      * and when we call run(), we do not enter in the main loop.
      */
    class GameEngine : public Singleton<GameEngine>, OIS::MouseListener, 
      OIS::KeyListener{

    public:
      /** An empty default constructor */
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

      void initStates();
      void initOgre();
      void initOgreGui();
      void initOIS();

      void showConsole();
      void hideConsole();

      RenderWindow* getRenderWindow();

      void cleanStates();

      bool connectUser(const char* , const char* );
      void setRender(const char*);

      void frameStarted(const FrameEvent&);
      void frameEnded(const FrameEvent&);

      Root *getOgreRoot();
      SceneManager* getOgreSceneMgr();
      Camera* getCamera();

      virtual bool keyPressed(const OIS::KeyEvent&);
      virtual bool keyReleased(const OIS::KeyEvent&);
      virtual bool mouseMoved(const OIS::MouseEvent&);
      virtual bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
      virtual bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);

      RainbruRPG::Core::InputManager* getInputManager();
      BetaGUI::GUI* getOgreGui();
 
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

      void chooseSceneManager();
      void createCamera();
      void createViewports();
      void setupResources();
      void loadResources(void);
      void loadResourcesGroup(const Ogre::String&);
      void logSceneMgrList();

      void fromMenuToGame(GameState*, GameState*);
      /** The stack of states
        *
	* All the GameStates the GameEngine can use are in this STL
	* vector. We know wich state we use with the actualState integer.
	*/
      vector<GameState*> states;

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

      /** The Ogre::Root object */
      Root *mRoot;
      /** The Ogre camera */
      Camera* mCamera;
      /** The Ogre Scene manager */
      SceneManager* mSceneMgr;
      /** The Ogre main Window */
      RenderWindow* mWindow;
      /** The Ogre framelistener */
      FrameListener* mFrameListener;

      /** The input manager making OIS easy to use */
      RainbruRPG::Core::InputManager* mInputMgr;

      /** The OgreGUI manager instance */
      BetaGUI::GUI* mOgreGUI;

      /** The userName the user entered 
        *
	* This value is set only if the connection is accepted.
	*
	*/
      const char* userName;

      /** The passord hashsum 
        *
	* This value is set only if the connection is accepted.
	*
        */
      const char* userPwd;

      /** The render queue listener that draw the GUI */
      OgreGuiRenderQueueListener* mRenderQueueListener;

    };
  }
}
#endif // GAME_ENGINE

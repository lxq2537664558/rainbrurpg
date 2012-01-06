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

/** \file gameengine.h
  * Declares an Ogre frame listenerthe client game engine
  *
  * Modifications :
  * - 29 aug 2009 : Made messages transatable with gettext
  * - 01 fev 2009 : Adding assertions to test some pointers
  * - 31 oct 2008 : Adding mViewport member and accessor
  * - 29 oct 2008 : Defining and using GET_SHARE_FILE
  * - 16 oct 2008 : changeState() now takes a string parameter
  * - 15 oct 2008 : 
  *   - Avoid the use of OgreGui
  *   - Removed initStates()
  * - 14 aug 2008 : Single file documentation
  * - 21 sep 2007 : Uses OgreGUI
  *
  */

#ifndef GAME_ENGINE
#define GAME_ENGINE

// OGRE headers
#include <ogreimport.h>
#include <vector>
#include <string>
#include <singleton.h>
#include <stringconv.h>
#include <clientconnect.h>

#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <rainbrudef.h> // For the GNU gettext stuff

// Forward declarations
namespace RainbruRPG 
{
  namespace Core
  {
    class GameState;
    class InputManager;
  }
  namespace Network
  {
    class GlobalURI;
  }
  namespace OgreGui
  {
    class Brush;
    class OgreGuiRenderQueueListener;
  }
}
// End of forward declarations

using namespace std;
using namespace Ogre;

using namespace RainbruRPG::Network;
using namespace RainbruRPG::Network::Ident;

using namespace RainbruRPG::OgreGui;

/** \def GET_SHARE_FILE
  * A wrapper to GlobalURI's getShareFile() function
  *
  * In Win32 platform, we do not use GlobalURI.
  *
  */
#ifdef __linux__
#  define GET_SHARE_FILE(GU,PATH) (GU.getShareFile(PATH))
#elif defined __WIN32__
#  define GET_SHARE_FILE(GU,PATH) (PATH)
#endif

/** \def CLIENT_WIN_CAPTION
  * The client's window title
  * 
  * This is the text used as title in the main Ogre window
  * of the client.
  *
  */
#define CLIENT_WIN_CAPTION "RainbruRPG"

namespace RainbruRPG {
  namespace Core{

    /** A structure that defines the GameEngine's runtime options
      *
      */
    typedef struct {
      /// Should we run ogregui test
      bool ogreGuiTest;
      /// Should we run the game in fullscreen mode
      bool fullscreen;
    }GameEngineOptions;

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
      *
      * \section gameengine_gs_ident Game states identification
      *
      * Each game state added with the \ref registerGameState() function
      * is identified by its name. To switch between states, you would
      * call the \ref changeState() function with the game state name
      * as parameter.
      *
      */
    class GameEngine : public Singleton<GameEngine>, OIS::MouseListener, 
      OIS::KeyListener{

    public:
      /** An empty default constructor */
      GameEngine(){};

      virtual ~GameEngine(){};

      void init(const GameEngineOptions&);
      /// The singleton destructor
      void cleanup();
      void run();
      
      // Set state as actual gameState
      void changeState(const std::string&);
      
      bool running();
      void play();
      void quit();  

      void initOgre();
      void initOIS();

      void showConsole();
      void hideConsole();

      RenderWindow* getRenderWindow();

      void cleanStates();

      bool connectUser(const char* , const char* );
      void setRender(const char*);

      void frameStarted(const FrameEvent&);
      void frameEnded(const FrameEvent&);

      Root *getOgreRoot(void);
      SceneManager* getOgreSceneMgr(void);
      Camera* getCamera(void);
      Viewport* getViewport(void) const;

      virtual bool keyPressed(const OIS::KeyEvent&);
      virtual bool keyReleased(const OIS::KeyEvent&);
      virtual bool mouseMoved(const OIS::MouseEvent&);
      virtual bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
      virtual bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);

      RainbruRPG::Core::InputManager* getInputManager();

      void registerGameState(GameState*);
      size_t getGameStateIndexByName(const std::string&);

      void draw();

      void setGuiTransparency(float);
      float getGuiTransparency(void) const;

    private:
      /** Unimplemented copy constructors 
        *
	* In a singleton the use of this method must be forbidden.
	* 
	* \param obj A GameEngine
	*
	*/
      GameEngine(const GameEngine& obj);

      /** Unimplemented assignment
        *
	* In a singleton the use of this method must be forbidden.
	*
	* \param obj A GameEngine
	*
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
      //      BetaGUI::GUI* mOgreGUI; // Removed to avoid OgreGui deps

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

      /** The Ogre iewport instance */
      Viewport* mViewport;

      /// The options structure instance of this game engine
      GameEngineOptions mOptions;

      /// The primitives drawing object
      Brush* mBrush;

      /// The GUI elements alpha value
      float mGuiTransparency;

      /// The GUI drawing listener
      OgreGuiRenderQueueListener* mRenderQueueListener;

    };
  }
}
#endif // GAME_ENGINE

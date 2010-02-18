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

/** \file gamestate.h
  * Declares a base abstract class of all the GameStates
  *
  * Modifications :
  * - 29 aug 2009 : Made messages transatable with gettext
  * - 18 oct 2008 : Added a state type parameter in constructor
  * - 16 oct 2008 : Added GST_UDEF state type
  * - 15 oct 2008 : Adding name member
  * - 15 aug 2008 : Single file documentation
  * - 22 may 2008 : rootWindowName removed (CEGUI not used anymore)
  * - 25 jul 2007 : rootWindowName added
  *
  */

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <ogreimport.h>

#include <OIS/OISPrereqs.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

#include <logger.h>
#include <rainbrudef.h> // For the GNU gettext stuff

#include <string>

using namespace std;
using namespace Ogre;

namespace RainbruRPG {
  namespace Core {

    /** A GameState type used to change between state
      *
      * When we change the actual state, some states need extra initialization.
      * The GameEngine can test its field to know from which state to which 
      * state we are about to change. 
      *
      */
    typedef enum{
      GST_UDEF, //!< Undefined state type
      GST_MENU, //!< The GameState is a menu
      GST_GAME  //!< The GameState is game (with a map, a moving camera...)
    }tGameStateType;

    /** Base abstract class of all the GameStates
      *
      * A game should provides different states (menus, game, introduction).
      * All the game states \b must inherits this base class. All these
      * game states are managed by the GameEngine class.
      *
      * We must override all this pure virtual functions in each
      * subclass. init() and cleanup() are the constructor and
      * destructor of a game state. the pause() and resume() provides
      * the temporally paused implementation of the state. The frameStarted()
      * and frameEnded() function are used by The GuiFrameListener
      *
      * \sa GameEngine
      *
      */
    class GameState {
    public:
      virtual ~GameState();

      const tGameStateType& getStateType()const;

      /** The constructor of GameState 
        * 
	* To be able to test the isInit boolean, an override of init()
	* must set isInit to true.
        */
      virtual void init() = 0;
      /** The destructor of GameState */
      virtual void cleanup() = 0;
      
      /** Temporally stop the state */
      virtual void pause() = 0;
      /** Rerun after a pause() call or a state change
        *
	* It is used to reload a removed layout when recovering a
	* previous changed state and re-register the events.
	*
        */
      virtual void resume() = 0;

      /** Draw one frame */     
      virtual void run() = 0;
      
      /** Called for each start of frame */
      virtual void frameStarted(const FrameEvent&) = 0;

      /** Called for each end of frame */
      virtual void frameEnded(const FrameEvent&) = 0;

      /** The OIS key pressed implementation */
      virtual bool keyPressed(const OIS::KeyEvent&) = 0;
      /** The OIS key released implementation */
      virtual bool keyReleased(const OIS::KeyEvent&) = 0;
      /** The OIS mouse moved implementation */
      virtual bool mouseMoved(const OIS::MouseEvent&) = 0;
      /** The OIS mouse pressed implementation */
      virtual bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID)=0;
      /** The OIS mouse released implementation */
      virtual bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID)=0;

      bool wasInit();

      void setName(const string&);
      const string& getName(void)const;

    protected:
      GameState(const string&, const tGameStateType& vState = GST_UDEF);

      /** Tells if the gamestate was initialized */
      bool isInit;

      

      /** The name of the state
        *
	* It is used when changing game state in \ref GameEngine.
	*
	*/
      string name;

      /** The common input wrapper */
      tGameStateType stateType;
   };
  }
}

#endif// GAME_STATE_H
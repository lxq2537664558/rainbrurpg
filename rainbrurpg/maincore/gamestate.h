/*
 *  Copyright 2006 Jerome PASQUIER
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

#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <OGRE/OgreFrameListener.h>
#include <logger.h>

#include <OIS/OISPrereqs.h>
#include <OIS/OISKeyboard.h>
#include <OIS/OISMouse.h>

using namespace Ogre;

namespace RainbruRPG {
  namespace Core {

    /** A GameState type used to change between state
      *
      * When we change the actual state, some states need extra initialization.
      * The GameEngine can test its field to know from which state to which 
      * state we change. 
      *
      */
    typedef enum tGameStateType{
      GST_MENU, //!< The GameState is a menu
      GST_GAME  //!< The GameState is game (with a map...)
    };

    /** Base abstract class of all the GameStates
      *
      * We must override all this pure virtual functions in each
      * subclass. init() and cleanup() are the constructor and
      * destructor of a game state. the pause() and resume() provides
      * the temporally paused implementation of the state. The frameStarted()
      * and frameEnded() function are used by The GuiFrameListener
      */
    class GameState {
    public:
      /**A default destructor */
      virtual ~GameState();

      tGameStateType getStateType();

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
      /** Rerun after a pause() call */
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
      virtual bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID) = 0;
      /** The OIS mouse released implementation */
      virtual bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID) = 0;


      bool wasInit();
    protected:
      /**A forbiden constructor */
      GameState();

      /** Tells if the gamestate was initialized */
      bool isInit;

      /** The common input wrapper */
      tGameStateType stateType;
    };
  }
}

#endif// GAME_STATE_H

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
 *  along with Foobar; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA
 *  02110-1301  USA
 *
 */

#ifndef GAME_STATE
#define GAME_STATE

#include <logger.h>

namespace RainbruRPG {
  namespace Core {

    /** Base abstract class of all the GameStates
      *
      * We must override all this pure virtual functions in each
      * subclass. init() and cleanup() are the constructor and
      * destructor of a game state. the pause() and resume() provides
      * the temporally paused implementation of the state and the
      * run() method must call the Irrlichtr driver draw method in a
      * scene. 
      */
    class GameState {
    public:
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
      
      bool wasInit();
    protected:
      /**A forbiden constructor */
      GameState();
      /** Tells if the gamestate was initialized */
      bool isInit;
    };
  }
}

#endif// GAME_STATE

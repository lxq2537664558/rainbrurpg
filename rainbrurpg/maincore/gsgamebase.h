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

/** \file gsgamebase.h
  * Declares a base class for all state supplying game capabilities
  *
  * Modifications :
  * - 29 aug 2009 : Made messages transatable with gettext
  * - 15 oct 2008 : Constructor handles GameState's name
  * - 16 aug 2008 : Single file documentation
  *
  */

#ifndef GS_GAME_BASE_H
#define GS_GAME_BASE_H

#include <ogreimport.h>
#include <string>
#include <rainbrudef.h> // For the GNU gettext stuff

#include "gamestate.h"
#include "inputwrapper.h"

using namespace Ogre;

namespace RainbruRPG {
  namespace Core{

    /** A super-class for game gamestate shareable capabilities
      *
      * A game gamestate is based on a map.
      *
      */
    class gsGameBase : public GameState{
    public:
      /** An empty default destructor needed to avoid compilation warnings */
      virtual ~gsGameBase(){};

      virtual void init();
      virtual void cleanup();
      virtual void pause();
      virtual void resume();
      virtual void run();

      virtual void frameStarted(const FrameEvent&);
      virtual void frameEnded(const FrameEvent&);

      const char* getMapName();

      virtual bool keyPressed(const OIS::KeyEvent&);
      virtual bool keyReleased(const OIS::KeyEvent&);
      virtual bool mouseMoved(const OIS::MouseEvent&);
      virtual bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
      virtual bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);
 

    protected:
      gsGameBase(const std::string&);

      void moveCamera();

      /** A shortcut to the Ogre::Root object */
      Root *mRoot;
       /** A shortcut to the Ogre::SceneManager object */
      SceneManager* mSceneMgr;

      /** The name of the config map to load
        *
	* This value is used with the Ogre setWorldGeometry function.
	*
	*/
      const char* mapName;

      /** The X rotation value */
      Radian mRotX;
      /** The Y rotation value */
      Radian mRotY;
      /** The translation vector */
      Vector3 mTranslateVector;

      /** The input wrapper */
      InputWrapper* inputWrapper;

      /** The moving scale of the camera */
      float mMoveScale;

    };
  }
}

#endif // GS_GAME_BASE_H


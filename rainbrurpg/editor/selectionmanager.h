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

#ifndef SELECTION_MANAGER_H
#define SELECTION_MANAGER_H

#include <singleton.h>
#include <ogreimport.h>

using namespace RainbruRPG::Core;

namespace RainbruRPG {
  namespace Editor{

    /** The class responsible of the entity selection and handles
      *
      * As there is several ways of selection, I gathered the selection
      * functions in this singleton. It must have a pointer to the OgreView's
      * SceneManager, to be able to work with the selectable Ogre entities.
      *
      * To allow multiple selection, there is two methods : 
      * - selectNewObject(Ogre::String) will avoid any selection to select a
      * single object;
      * - selectAddObject(Ohgre::String) to add a new object to the current
      * selection. If the object name is already part of the current selection
      * it is removed.
      *
      * The name of the object to select is generally given by a SelectionCycle
      * instance.
      *
      * This class also creates the move and rotation handles. It needs the
      * Camera position passed as parameter in the init function.
      *
      * \sa SelectionCycle
      *
      */
    class SelectionManager: 
      public RainbruRPG::Core::Singleton<SelectionManager>{

    public:
      SelectionManager();
      ~SelectionManager();

      void init(Ogre::SceneManager*, Ogre::Camera*);
      void selectNewObject(Ogre::String);
      void selectAddObject(Ogre::String);

    private:
      bool checkSceneManager();
      void highlightObject(Ogre::String);

      void createMoveHandle();

      /** Unimplemented forbidden copy constructor
        *
	* \param obj a SelectionManager
	*/
      SelectionManager(const SelectionManager& obj);

      /** Unimplemented forbidden assignment constructor
        *
	* \param obj a SelectionManager
	*/
      SelectionManager& operator=(const SelectionManager& obj);

      /** The scenemanager receiving the selection */
      Ogre::SceneManager* sceneManager;
      /** The scenemanager used to compute handle position */
      Ogre::Camera* camera;
      /** A Ogre scene node used for selection highlighting */
      Ogre::SceneNode* highLightNode;
      /** A Ogre entity used for selection highlighting */
      Ogre::Entity* highLightEntity;
      /** Is there a Highlighted node
        * 
	* The startup value is \c false. When an object is highlighted, it
	* is set to \c true and we know we must deleted the last
	* node used for selection highlighting.
	*
	* \sa highLightNode
	*
	*/
      bool isNodeHighLighted;

      /** The camera to Handles distance */
      Ogre::Real cameraToHandle;

      /** A Ogre scene node used for selection highlighting */
      Ogre::SceneNode* handleNode;
      /** A Ogre entity used for selection highlighting */
      Ogre::Entity* handleEntity;

    };
  }
}

#endif // SELECTION_MANAGER_H

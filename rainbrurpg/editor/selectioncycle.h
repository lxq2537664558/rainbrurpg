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

#ifndef SELECTION_CYCLE_H
#define SELECTION_CYCLE_H

#include <OGRE/OgreSceneQuery.h>
#include <OGRE/OgreMovableObject.h>


namespace RainbruRPG{
  namespace Editor{

    /** A class used to selection an item even if it is hidden
      *
      * In an editor, you can have an object hidden by another one. This class
      * provide a way to navigate through the list of selectable object.
      *
      * From a mouse click to another, this class is called. Between two calls,
      * it keeps the list and the currently selected item \c index. If the next
      * call, the list is the same, we select the \c index++ item.
      *
      * The use is simple, simple create and keep an instance of this class,
      * call getNextEntity() with your RaySceneQueryResult as parameter each
      * time you need it. If the RaySceneQueryResult is the same, it will
      * manage the selection cycle.
      */
    class SelectionCycle{
    public:
      SelectionCycle();
      ~SelectionCycle();

      const Ogre::String& getNextEntity(Ogre::RaySceneQueryResult&);

    private:
      bool compare(Ogre::RaySceneQueryResult*, Ogre::RaySceneQueryResult*);
      const Ogre::String& getFirstEntityName(Ogre::RaySceneQueryResult*);

      /** The last scene query
        *
	* This pointer is used to test if the query changed.
	*
	* The RaySceneQueryResult pointed will not be destroyed by 
	* SelectionCycle. You must destriy it yourself.
	*
	*/
      Ogre::RaySceneQueryResult* lastQuery;
      /** To know which entity was selected in the last call
        *
	* We will start the search of the next entity from this name if
	* the given RaySceneQueryResult is declared unchanged as parameter in 
	* getNextEntity().
	*
	*/
      Ogre::String lastEntityName;
    };
  }
}

#endif // SELECTION_CYCLE_H

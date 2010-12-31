/*
 *  Copyright 2006-2011 Jerome PASQUIER
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

/** \file highlightlistener.h
  * Declares a class used to highlight an entity in the editor 
  *
  * Modifications :
  * - 22 sep 2009 : Made messages transatable with gettext
  * - 18 aug 2008 : Single file documentation
  *
  */

#ifndef HIGHLIGHT_QUEUE_LISTENER_H
#define HIGHLIGHT_QUEUE_LISTENER_H

#include <ogreimport.h>

#include <rainbrudef.h> // For the GNU gettext stuff

namespace RainbruRPG{
  namespace Core{

    /** Used to highlight an entity in the editor 
      *
      * This class is used by the Editor to highlight an object. To use it,
      * you must first register this listener :
      * <pre>
      * // mSceneMgr if a Ogre::SceneManager instance
      * mSceneMgr->addRenderQueueListener(new HighlightQueueListener());
      * </pre>
      *
      * Then you can setup an entity to be highlighted ( A material called
      * \c Outline must exist):
      * <pre>
      * entity->setRenderQueueGroup(90);
      * Ogre::Entity* clone = entity->clone(entity->getName() + "Outline");
      * clone->setRenderQueueGroup(91);
      * clone->setMaterialName("Outline");
      *
      * Ogre::SceneNode* high = entity->getParentSceneNode()
      *   ->createChildSceneNode(parent->getName() + "Outline");
      * high->setScale(Ogre::Vector3(1.1,1.1,1.1));
      * high->attachObject(clone);
      * </pre>
      *
      * This code was found in the Ogre forum : 
      * http://www.ogre3d.org/phpBB2/viewtopic.php?t=25321
      *
      */
    class HighlightQueueListener : public Ogre::RenderQueueListener{
    public:
      virtual void renderQueueStarted(Ogre::uint8, const Ogre::String&, bool&);
      virtual void renderQueueEnded(Ogre::uint8, const Ogre::String&, bool&);
    }; 
  }
}
#endif // HIGHLIGHT_QUEUE_LISTENER_H

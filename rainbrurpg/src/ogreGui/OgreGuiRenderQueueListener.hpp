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

/** \file OgreGuiRenderQueueListener.hpp
  *
  * Declares a Ogre RenderQueue listener that draws the GUI.
  *
  * Modifications :
  * - 16 oct 2010 : Starting implementation.
  *
  */

#ifndef _OGRE_GUI_RENDER_QUEUE_LISTENER_HPP__
#define _OGRE_GUI_RENDER_QUEUE_LISTENER_HPP__

#include <ogreimport.h>

using namespace Ogre;

namespace RainbruRPG{
  namespace OgreGui{

    /** A Ogre RenderQueue listener that draws the GUI
      *
      * To be able to use OgreGui, you must register this by calling
      * Ogre::SceneManager::addRenderQueueListener().
      *
      */
    class OgreGuiRenderQueueListener: public RenderQueueListener{
    public:
      OgreGuiRenderQueueListener(uint8 vQueueID = RENDER_QUEUE_OVERLAY);
      ~OgreGuiRenderQueueListener();
      void renderQueueStarted (uint8, const String&, bool&);
      void renderQueueEnded (uint8, const String&, bool&);
      
    private:
      /** The queue when we draw the gui */
      uint8 mQueue;
    };
  }
}    

#endif // _OGRE_GUI_RENDER_QUEUE_LISTENER_HPP__

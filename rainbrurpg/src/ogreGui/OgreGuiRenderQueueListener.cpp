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

/** \file OgreGuiRenderQueueListener.cpp
  *
  * Implements a Ogre RenderQueue listener that draws the GUI.
  *
  */

#include "OgreGuiRenderQueueListener.hpp"

#include <logger.h>
#include <gameengine.h>

/** Constructor
  *
  * \param vQueueID The QueueGroupId when we draw the GUI
  *
  */
RainbruRPG::OgreGui::OgreGuiRenderQueueListener::
OgreGuiRenderQueueListener(uint8 vQueueID):
  mQueue(vQueueID)
{

}

/** Destructor 
  *
  */
RainbruRPG::OgreGui::OgreGuiRenderQueueListener::
~OgreGuiRenderQueueListener(){

}

/** The QueueStarted listener 
  *
  * \param vQueueGroupId      The render queue group currently drawn
  * \param vInvocation        The name of the invocation which is causing this 
  *                           to be called
  * \param skipThisInvocation A boolean passed by reference which is by 
  *                           default set to false. If the event sets this 
  *                           to true, the queue will be skipped and not 
  *                           rendered. Note that in this case the 
  *                           renderQueueEnded event will not be raised 
  *                           for this queue group. 
  *
  */
void RainbruRPG::OgreGui::OgreGuiRenderQueueListener::
renderQueueStarted (uint8 vQueueGroupId, const String& vInvocation, 
		    bool& skipThisInvocation){

  /*
  if ( vQueueGroupId == mQueue ){
    gm->drawBeforeOverlay();
  }
  */  
}

/** The QueueEnded listener
  *
  * Call draw() function  of gm.
  *
  * \param vQueueGroupId       The render queue group currently drawn
  * \param vInvocation         The name of the invocation which is causing 
  *                            this to be called
  * \param repeatThisInvocation A boolean passed by reference which is by 
  *                             default set to false. If the event sets this 
  *                             to true, this queue will be repeated and the
  *                             RenderQueueStarted and RenderQueueEnded
  *                             events will be fired again.
  *
  */
void RainbruRPG::OgreGui::OgreGuiRenderQueueListener::
renderQueueEnded( uint8 vQueueGroupId, const String& vInvocation, 
		  bool& repeatThisInvocation){

  if ( vQueueGroupId == mQueue ){
    GameEngine::getSingleton().draw();
    //    gm->drawMouseCursor();
  }
}

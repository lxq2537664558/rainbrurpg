/*
 *  Copyright 2006-2009 Jerome PASQUIER
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

/** \file renderqueuelistener.cpp
  * Implements a Ogre RenderQueue listener that draws the GUI
  *
  */

#include "renderqueuelistener.h"

#include <logger.h>

/** Constructor
  *
  * \param g The GuiManager
  * \param vQueueID The QueueGroupId when we draw the GUI
  *
  */
RainbruRPG::OgreGui::OgreGuiRenderQueueListener::
OgreGuiRenderQueueListener(GUI* g, uint8 vQueueID):
  gm(g),
  mQueue(vQueueID)
{

}

/** Destructor 
  *
  */
RainbruRPG::OgreGui::OgreGuiRenderQueueListener::
~OgreGuiRenderQueueListener(){
  gm=NULL;
}

/** The QueueStarted listener 
  *
  * \param vQueueGroupId The render queue group currently drawn
  * \param vInvocation, vRepeatThisInvocation not used parameters
  *
  */
void RainbruRPG::OgreGui::OgreGuiRenderQueueListener::
renderQueueStarted (uint8 vQueueGroupId, const String& vInvocation, 
		    bool& vRepeatThisInvocation){

  if ( vQueueGroupId == mQueue ){
    gm->drawBeforeOverlay();
  }
}

/** The QueueEnded listener
  *
  * Call draw() function  of gm.
  *
  * \param vQueueGroupId The render queue group currently drawn
  * \param vInvocation, vRepeatThisInvocation not used parameters
  *
  */
void RainbruRPG::OgreGui::OgreGuiRenderQueueListener::
renderQueueEnded( uint8 vQueueGroupId, const String& vInvocation, 
		  bool& vRepeatThisInvocation){


  if ( vQueueGroupId == mQueue ){
    gm->draw();
    gm->drawMouseCursor();
  }
}

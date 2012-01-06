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

/** \file highlightlistener.cpp
  * Implements a class used to highlight an entity in the editor 
  *
  */

#include "highlightlistener.h"

/** The Ogre renderQueueStarted implementation
  *
  * The more used parameter is the queueGroupId. 90 is for the 
  * object to be highlighted, 91 is its outline.
  *
  * \param queueGroupId The queue group identifier (90 and 91 are treated)
  * \param invocation Unused Ogre provided parameter
  * \param skipThisInvocation Unused Ogre provided parameter
  *
  */
void RainbruRPG::Core::HighlightQueueListener::
renderQueueStarted(Ogre::uint8 queueGroupId, const Ogre::String& invocation, 
		   bool& skipThisInvocation)

{
  //RenderQueue containing the object to be highlighted
  if (queueGroupId == 90){
    Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton()
      .getRenderSystem();
		
    rendersys->clearFrameBuffer(Ogre::FBT_STENCIL);
    rendersys->setStencilCheckEnabled(true);
    rendersys->setStencilBufferParams(Ogre::CMPF_ALWAYS_PASS,1,0xFFFFFFFF,
				      Ogre::SOP_KEEP,Ogre::SOP_KEEP,
				      Ogre::SOP_REPLACE,false);      
  }
  
  //RenderQueue containing the outline
  if (queueGroupId == 91){
    Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton()
      .getRenderSystem();
    
    rendersys->setStencilCheckEnabled(true);
    rendersys->setStencilBufferParams(Ogre::CMPF_NOT_EQUAL,1,0xFFFFFFFF,
				      Ogre::SOP_KEEP,Ogre::SOP_KEEP,
				      Ogre::SOP_KEEP,false);      
    }
}


/** The Ogre renderQueueStarted implementation
  *
  * The more used parameter is the queueGroupId. 90 is for the 
  * object to be highlighted, 91 is its outline.
  *
  * \param queueGroupId The queue group identifier (90 and 91 are treated)
  * \param invocation Unused Ogre provided parameter
  * \param repeatThisInvocation Unused Ogre provided parameter
  *
  */
void RainbruRPG::Core::HighlightQueueListener::
renderQueueEnded(Ogre::uint8 queueGroupId, const Ogre::String& invocation, 
		 bool& repeatThisInvocation)
{
  if (( queueGroupId == 90 ) || ( queueGroupId == 91 )){
    Ogre::RenderSystem * rendersys = Ogre::Root::getSingleton()
      .getRenderSystem();

    rendersys->setStencilCheckEnabled(false);
    rendersys->setStencilBufferParams();
  }
}

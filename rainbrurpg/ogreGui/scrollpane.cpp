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

#include "scrollpane.h"

#include "bgwindow.h"
#include "quadrenderer.h"

#include <OgreOverlayManager.h>
#include <OgreException.h>

/** The constructor
  *
  * \param dim    The dimensions of the scrollpane
  * \param parent The parent
  * \param sid    The skin identifier
  *
  */
RainbruRPG::OgreGui::ScrollPane::
ScrollPane(Vector4 dim, Window* parent,OgreGuiSkinID sid):  
  Widget(dim, parent, sid)
{

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::ScrollPane::~ScrollPane(){

}

/** Change the transparency of this scrollpane
  *
  * \param f The new transparency
  *
  */
void RainbruRPG::OgreGui::ScrollPane::setTransparency(float f){

}

/** Sraws the Scrollpane content
  *
  * The Scrollpane ability to draw only visible widgets is done using
  * the scissor rectangle. Please see \ref 
  * RainbruRPG::OgreGui::QuadRenderer::useParentScissor "useParentScissor"
  * for more informations.
  *
  */
void RainbruRPG::OgreGui::ScrollPane::draw(QuadRenderer* qr){

  qr->setScissorRectangle(corners);
  qr->setUseParentScissor(true);

  for (unsigned int i=0;i<widgetList.size();i++){
    widgetList[i]->draw(qr);
  }

  qr->setUseParentScissor(false);
}

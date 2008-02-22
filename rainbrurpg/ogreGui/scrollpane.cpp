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
#include "widget.h"
#include "hscrollbar.h"
#include "vscrollbar.h"

#include <OgreOverlayManager.h>
#include <OgreException.h>
#include <logger.h>

#include <algorithm>

/** The constructor
  *
  * Both horizontal and vertical scrollbar are drawn only if needed by default.
  *
  * \param dim    The dimensions of the scrollpane
  * \param parent The parent
  * \param sid    The skin identifier
  *
  */
RainbruRPG::OgreGui::ScrollPane::
ScrollPane(Vector4 dim, Window* parent,OgreGuiSkinID sid):  
  Container(dim, parent, sid),
  mVScrollBarPolicy(SBP_IF_NEEDED),
  mHScrollBarPolicy(SBP_IF_NEEDED)
{

  Vector4 sbDim(dim.z-16,30,14,dim.w-60);
  mVScrollBar=new VScrollBar(sbDim, parent);//, OSI_BETAGUI);
  this->addWidget(mVScrollBar);

  Vector4 sbDim2(2 ,dim.w-16,dim.z-16,14);
  mHScrollBar=new HScrollBar(sbDim2, parent);
  this->addWidget(mHScrollBar);

}

/** The destructor
  *
  */
RainbruRPG::OgreGui::ScrollPane::~ScrollPane(){
  delete mVScrollBar;
  mVScrollBar=NULL;

  delete mHScrollBar;
  mHScrollBar=NULL;

}

/** Draws the Scrollpane content
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
  Container::draw(qr);
  qr->setUseParentScissor(false);
}

/** Changes the horizontal Scrollbar policy
  *
  * \param p The new policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::getHorizontalScrollbarPolicy()
  *     "getHorizontalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
void RainbruRPG::OgreGui::ScrollPane::
setHorizontalScrollbarPolicy(tScrollBarPolicy p){
  mHScrollBarPolicy=p;
}

/** Changes the vertical Scrollbar policy
  *
  * \param p The new policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::getVerticalScrollbarPolicy()
  *     "getVerticalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
void RainbruRPG::OgreGui::ScrollPane::
setVerticalScrollbarPolicy(tScrollBarPolicy p){
  mVScrollBarPolicy=p;
}

/** Get the horizontal Scrollbar policy
  *
  * \return The current policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::setHorizontalScrollbarPolicy()
  *     "setHorizontalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
tScrollBarPolicy RainbruRPG::OgreGui::ScrollPane::
getHorizontalScrollbarPolicy(void){
  return mHScrollBarPolicy;
}

/** Get the vertical Scrollbar policy
  *
  * \return The current policy
  *
  * \sa \ref RainbruRPG::OgreGui::ScrollPane::setVerticalScrollbarPolicy()
  *     "setVerticalScrollbarPolicy()", 
  *     \ref RainbruRPG::OgreGui::tScrollBarPolicy 
  *     "tScrollBarPolicy"
  *
  */
tScrollBarPolicy RainbruRPG::OgreGui::ScrollPane::
getVerticalScrollbarPolicy(void){
  return mVScrollBarPolicy;
}

/** Get the max right position of childs widget
  *
  * \return The max right position
  *
  */
int RainbruRPG::OgreGui::ScrollPane::getMaxChildRight(void){
  int maxRight=0;
  unsigned int i;

  for ( i=0; i<widgetList.size(); i++){
    maxRight=max( maxRight, widgetList[i]->getRight() );
  }

  for ( i=0; i<textInputList.size(); i++){
    maxRight=max( maxRight, textInputList[i]->getRight() );
  }

  for ( i=0; i<buttonList.size(); i++){
    maxRight=max( maxRight, buttonList[i]->getRight() );
  }

  return maxRight;
}

/** Get the max bottom position of childs widget
  *
  * \return The max bottom position
  *
  */
int RainbruRPG::OgreGui::ScrollPane::getMaxChildBottom(void){
  int maxBottom=0;
  unsigned int i;

  for ( i=0; i<widgetList.size(); i++){
    maxBottom = max( maxBottom, widgetList[i]->getBottom() );
  }

  for ( i=0; i<textInputList.size(); i++){
    maxBottom = max( maxBottom, textInputList[i]->getBottom() );
  }

  for ( i=0; i<buttonList.size(); i++){
    maxBottom = max( maxBottom, buttonList[i]->getBottom() );
  }

  return maxBottom;
}

bool RainbruRPG::OgreGui::ScrollPane::isHorizontalScrollbarNeeded(void){
  switch (mHScrollBarPolicy){
  case SBP_NEVER:
    return false;
    break;

  case SBP_ALWAYS:
    return false;
    break;

  case SBP_IF_NEEDED:
    return (getMaxChildRight()>corners.right);
    break;
  }
}

bool RainbruRPG::OgreGui::ScrollPane::isVerticalScrollbarNeeded(void){
  switch (mVScrollBarPolicy){
  case SBP_NEVER:
    return false;
    break;

  case SBP_ALWAYS:
    return false;
    break;

  case SBP_IF_NEEDED:
    return (getMaxChildBottom()>corners.bottom);
    break;
  }
}

void RainbruRPG::OgreGui::ScrollPane::setScrollBarsVisbleStatus(){
  if (isHorizontalScrollbarNeeded()){
    mHScrollBar->setVisible(true);
  }
  else{
    mHScrollBar->setVisible(false);
  }

  if (isVerticalScrollbarNeeded()){
    mVScrollBar->setVisible(true);
  }
  else{
    mVScrollBar->setVisible(false);
  }
}
